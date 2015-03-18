#include <cstdlib>
#include <sys/time.h>
#include <string>
#include <algorithm>
#include <functional>
//#include <type_traits>
#include <typeinfo>
using namespace std;

////////////////////////////////////////////////////////////////////////////
///////////////////////////// Some Utilities ///////////////////////////////

double get_wall_time()
{
    struct timeval time;
    if (gettimeofday(&time,NULL))
    {
        //  Handle error
        return 0;
    }
    
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

// maybe not really nec.? (I think fabs is really double by now)
double dabs(double value)
{
    if (value>=0.0) return value;
    else return (-1.0*value);
}

// true if same types, false if not:
//template<typename T, typename U> bool isSame(T type1, U type2) { return false; }
//template<typename T> bool isSame(T type1, T type2) { return true; }
template<typename T, typename U> bool isSame(T type1, U type2)
{
    auto firstType = typeid(type1).name();
    auto secondType = typeid(type2).name();
    if (firstType==secondType) return true;
    return false;
}



/////////////////// examples of what works, what doesn't: ///////////////////

// works without incident:
template <typename doubletype> auto atestfunction (doubletype input) -> decltype( input )
{
    //multiply by 2:
    auto val = 2.5*input;
    
    return val;
}

// // Does NOT work. "val" out of scope:
// template <typename doubletype> auto atestfunction2 (doubletype input) -> decltype( val )
// {
//     //multiply by 2:
//     auto val = 2*input;
//     
//     return val;
// }

// works! but, warning: 'atestfunction3' function uses 'auto' type specifier without trailing return type
template <typename doubletype> auto atestfunction3 (doubletype input)
{
    //multiply by 2:
    auto val = 2*input;
    
    return val;
}


////////////////////////////////////////////////////////////////////////////
/////////////////////// Begin Analysis Variables ///////////////////////////


////////////////////////////////////////////////////////////////////////////
/////////////////////get sum pt of arbitrary collections////////////////////

template <typename coll1type> double getsumpt( coll1type collection1 )
{
    typename coll1type::value_type collection1el;
    double thept = 0.;
    
    for (auto it = collection1.begin(); it != collection1.end(); ++it)
    {
        thept += (*it).obj.Pt();
    }
        
    return thept;
}

template <typename coll1type, typename coll2type> double getsumpt( coll1type collection1, coll2type collection2 )
{
    double sumpt = getsumpt(collection1);
    sumpt += getsumpt(collection2);
    return sumpt;
}

template <typename coll1type, typename coll2type, typename coll3type> double getsumpt( coll1type collection1, coll2type collection2, coll3type collection3 )
{
    double sumpt = getsumpt(collection1);
    sumpt += getsumpt(collection2);
    sumpt += getsumpt(collection3);
    return sumpt;
}

////////////////////////////////////////////////////////////////////////////
//////////////////get sum energy of arbitrary collections///////////////////

template <typename coll1type> double getsumEnergy( coll1type collection1 )
{
    typename coll1type::value_type collection1el;
    double theE = 0.;
    
    for (auto it = collection1.begin(); it != collection1.end(); ++it)
    {
        theE += (*it).obj.E();
    }
        
    return theE;
}

template <typename coll1type, typename coll2type> double getsumEnergy( coll1type collection1, coll2type collection2)
{
    double sumE = getsumEnergy(collection1);
    sumE += getsumEnergy(collection2);
    return sumE;
}
 
template <typename coll1type, typename coll2type, typename coll3type> double getsumEnergy( coll1type collection1, coll2type collection2, coll3type collection3 )
{
    double sumE = getsumEnergy(collection1);
    sumE += getsumEnergy(collection2);
    sumE += getsumEnergy(collection3);
    return sumE;
}

////////////////////////////////////////////////////////////////////////////
/////////////get sum TLorentzVector of arbitrary collections////////////////

template <typename coll1type> auto getsumTLV( coll1type collection1 )
{
    typename coll1type::value_type collection1el;
    decltype(collection1el.obj) newobj;
    
    for (auto it = collection1.begin(); it != collection1.end(); ++it)
    {
        newobj += (*it).obj;
    }
        
    return newobj;
}

template <typename coll1type, typename coll2type> auto getsumTLV( coll1type collection1, coll2type collection2 )
{
    auto newobj = getsumTLV(collection1);
    newobj += getsumTLV(collection2);
    return newobj;
}

template <typename coll1type, typename coll2type, typename coll3type> auto getsumTLV( coll1type collection1, coll2type collection2, coll3type collection3)
{
    auto newobj = getsumTLV(collection1);
    newobj += getsumTLV(collection2);
    newobj += getsumTLV(collection3);
    return newobj;
}


////////////////////////////////////////////////////////////////////////////

double convertWPtoCSVvalue(string tagtype)
{
    double tagcut=0.0;
    if (tagtype=="None") return tagcut;   
    else if (tagtype=="L") tagcut = 0.423; // 10.1716% DUSG mistag efficiency
    else if (tagtype=="M") tagcut = 0.814; // 1.0623% DUSG mistag efficiency
    else if (tagtype=="T") tagcut = 0.941; // 0.1144% DUSG mistag efficiency
    return tagcut;
}
    
////////////////////////////////////////////////////////////////////////////
    
template <typename coll1type> double getAvgCSV(coll1type collection1, string tagtype="None", bool isTag=true ) // has to be jet or lep collection
{
    double tagcut = convertWPtoCSVvalue(tagtype);
    double tagsum = 0.0;
    int count = 0;
    for (auto it = collection1.begin(); it != collection1.end(); ++it)
    {    
        double thecsv = (*it).csv;
        
        if (tagtype!="None")
        {
            if (isTag && (tagcut<thecsv))
            {
                tagsum += thecsv;
                count += 1;
            }
        
            if ((!isTag) && (tagcut>=thecsv))
            {
                tagsum += thecsv;
                count += 1;
            }
        }
        else
        {
            tagsum += thecsv;
            count += 1;
        }
    }   
            
    if (count>0) tagsum = tagsum / count;

    return tagsum;
}
////////////////////////////////////////////////////////////////////////////

template <typename coll1type> auto keepTagged(coll1type collection1, string tagtype="None")
{
    if (tagtype=="None") return collection1;
    double tagcut = convertWPtoCSVvalue(tagtype);
    decltype(collection1) keptobjs;
    for (auto it = collection1.begin(); it != collection1.end(); ++it)
    {
        if (tagcut<(*it).csv) keptobjs.push_back((*it));
    }
    
    return keptobjs;
}
    
////////////////////////////////////////////////////////////////////////////

template <typename coll1type> auto keepUnTagged(coll1type collection1, string tagtype="None")
{
    if (tagtype=="None") return collection1;
    double tagcut = convertWPtoCSVvalue(tagtype);
    decltype(collection1) keptobjs;
    for (auto it = collection1.begin(); it != collection1.end(); ++it)
    {    
        if (tagcut>=(*it).csv) keptobjs.push_back((*it));
    }
  
    return keptobjs;
}            

////////////////////////////////////////////////////////////////////////////

template <typename ob1type, typename ob2type> double getdPhi(ob1type object1, ob2type object2 ) // get dPhi between two objects (i.e. getdPhi(lep,jet), not getdPhi(lep.obj,jet.obj))
{
    double dPhi = object2.obj.Phi() - object1.obj.Phi();
    double pi = 2.0*asin(1.0);
    if (dPhi>=pi) dPhi = dPhi - 2.0*pi;     // from TVector2
    if (dPhi<(-pi)) dPhi = dPhi + 2.0*pi;   // from TVector2
    return dPhi;
}


////////////////////////////////////////////////////////////////////////////

template <typename ob1type, typename ob2type> double getdR(ob1type object1, ob2type object2 ) // get dR between two objects (i.e. getdR(lep,jet), not getdR(lep.obj,jet.obj))
{
    double dR = (object1.obj.Eta() - object2.obj.Eta())*(object1.obj.Eta() - object2.obj.Eta());
    dR += (getdPhi(object1,object2))*(getdPhi(object1,object2));
    dR = sqrt(dR);
    return dR;
}



////////////////////////////////////////////////////////////////////////////

template <typename coll1type, typename coll2type> double getTwoObjKineExtreme( coll1type collection1, coll2type collection2, string extremetype, string quantity )
{
    double minvalue = 999999.;
    double maxvalue = 0.;

    bool sametypes = isSame(collection1,collection2);

    for (auto obj1 = collection1.begin(); obj1 != collection1.end(); ++obj1)
    {
        for (auto obj2 = collection2.begin(); obj2 != collection2.end(); ++obj2)
        {
            bool thesame = false;
            
            if (sametypes) thesame = ((*obj1).obj==(*obj2).obj);
            
            if (!thesame)
            {
                if (extremetype=="min")
                {
                    if (quantity=="dR")
                    {
                        double testvalue = getdR((*obj1),(*obj2));
                        if (testvalue<minvalue) minvalue = testvalue;
                    }
                    else if (quantity=="dEta")
                    {
                        double testvalue = dabs((*obj1).obj.Eta()-(*obj2).obj.Eta());
                        if (testvalue<minvalue) minvalue = testvalue;
                    }
                    else if (quantity=="dPhi")
                    {
                        double testvalue = dabs(getdPhi((*obj1),(*obj2)));
                        if (testvalue<minvalue) minvalue = testvalue;
                    }
                    else if (quantity=="mass")
                    {
                        auto obj12 = (*obj1).obj + (*obj2).obj;
                        double testvalue = obj12.M();
                        if (testvalue<minvalue) minvalue = testvalue;
                    }
                }
                if (extremetype=="max")
                {
                    if (quantity=="dR")
                    {
                        double testvalue = getdR((*obj1),(*obj2));
                        if (testvalue>maxvalue) maxvalue = testvalue;
                    }
                    else if (quantity=="dEta")
                    {
                        double testvalue = dabs((*obj1).obj.Eta()-(*obj2).obj.Eta());
                        if (testvalue>maxvalue) maxvalue = testvalue;
                    }
                    else if (quantity=="dPhi")
                    {
                        double testvalue = dabs(getdPhi((*obj1),(*obj2)));
                        if (testvalue>maxvalue) maxvalue = testvalue;
                    }
                    else if (quantity=="mass")
                    {
                        auto obj12 = (*obj1).obj + (*obj2).obj;
                        double testvalue = obj12.M();
                        if (testvalue>maxvalue) maxvalue = testvalue;
                    }
                }      
            }
        }
    }                
                        
    if (extremetype=="min") return minvalue;
    else if (extremetype=="max") return maxvalue;
    return -9999.;
}
    
template <typename coll1type> double getTwoObjKineExtreme( coll1type collection1, string extremetype, string quantity )
{
    double samecollectionitem = getTwoObjKineExtreme( collection1, collection1, extremetype, quantity );
    return samecollectionitem;
    
}
////////////////////////////////////////////////////////////////////////////


template <typename coll1type, typename coll2type> vector<double> getTwoObjKineRawCollection(coll1type collection1, coll2type collection2, string quantity="dR", bool thesamecols=false )
{
    int size1 = collection1.size();
    //int size2 = collection2.size();

    vector<double> kineRawCollecion;
    
    //bool sametypes = isSame(collection1,collection2);   
    
    //bool thesamecols = false;
    
    //if (sametypes) if (collection1==collection2) thesamecols = true;
    //Above doesn't compile. Line below is sort of a hack for now (should eventually fix this):
    //if (sametypes && size1 && size2) if (collection1[0].obj==collection2[0].obj) thesamecols = true; // <- really only a GUESS that they are same collections
    
    
    if (!thesamecols)
    {
        for (auto obj1 = collection1.begin(); obj1 != collection1.end(); ++obj1)
        {
            for (auto obj2 = collection2.begin(); obj2 != collection2.end(); ++obj2)
            {             
                if (quantity=="dR")
                {
                    double value = getdR((*obj1),(*obj2));
                    kineRawCollecion.push_back(value);
                }
                else if (quantity=="dEta")
                {
                    double value = (*obj1).obj.Eta()-(*obj2).obj.Eta();
                    kineRawCollecion.push_back(value);
                }
                else if (quantity=="dPhi")
                {
                    double value = getdPhi((*obj1),(*obj2));
                    kineRawCollecion.push_back(value);
                }
                else if (quantity=="mass")
                {   
                    auto obj12 = (*obj1).obj + (*obj2).obj;
                    kineRawCollecion.push_back(obj12.M());  
                }    
                else if (quantity=="massSFOS")
                {
                    if ( ((*obj1).pdgID/(*obj2).pdgID) == -1 ) // this doesn't work for ttH::MET (should fix)
                    {
                        auto obj12 = (*obj1).obj + (*obj2).obj;
                        kineRawCollecion.push_back(obj12.M());
                    }
                }
            }
        }
    }
    
    else
    {
        if (size1>1)
        {
            int count1=0;
           
            for (auto obj1 = collection1.begin(); obj1 != collection1.end(); ++obj1)
            {               
                int count2=0;
                
                for (auto obj2 = collection2.begin(); obj2 != collection2.end(); ++obj2)
                {
                    if (count2>count1)
                    {
                        if (quantity=="dR")
                        {
                            double value = getdR((*obj1),(*obj2));
                            kineRawCollecion.push_back(value);
                        }
                        else if (quantity=="dEta")
                        {
                            double value = (*obj1).obj.Eta()-(*obj2).obj.Eta();
                            kineRawCollecion.push_back(value);
                        }
                        else if (quantity=="dPhi")
                        {
                            double value = getdPhi((*obj1),(*obj2));
                            kineRawCollecion.push_back(value);
                        }
                        else if (quantity=="mass")
                        {   
                            auto obj12 = (*obj1).obj + (*obj2).obj;
                            kineRawCollecion.push_back(obj12.M());  
                        }    
                        else if (quantity=="massSFOS" && ((*obj1).pdgID/(*obj2).pdgID == -1))
                        {
                            auto obj12 = (*obj1).obj + (*obj2).obj;
                            kineRawCollecion.push_back(obj12.M());
                        }
                    }
                                        
                    count2++;
                }
                
                count1++;
            }
        }
    }

    return kineRawCollecion;
}
////////////////////////////////////////////////////////////////////////////

// use this overloaded version when comparing objects from different collections:
template <typename coll1type, typename coll2type> double pickFromSortedTwoObjKine( coll1type collection1, coll2type collection2, string quantity, int whichInOrder, double comparisonValue, bool thesamecols=false)
{
    //"if no comparison value, whichInOrder picks the ith quanity from the list (in decending order). If comparison value provided, whichInOrder picks the ith quanity closest to the value."    
    
    vector<double> thelist = getTwoObjKineRawCollection( collection1, collection2, quantity, thesamecols);
    int size = thelist.size();

    if (!size) return -99999.;
    if (size<whichInOrder) whichInOrder = size;

    if (comparisonValue==0.)
    {
        sort(thelist.begin(), thelist.end(), std::greater<double>());
        return thelist[whichInOrder-1];
    }
    
    std::vector<std::pair<double, int> > newlist;
    
    for (int i=0; i<size; i++)
    {
        double newvalue = dabs(thelist[i] - comparisonValue);
        std::pair<double, int> newpair (newvalue, i);
        newlist.push_back(newpair);
        
    }

    sort(newlist.begin(), newlist.end());

    return thelist[newlist[whichInOrder-1].second];
}

// use this overloaded version when comparing objects from the same collection:
template <typename coll1type> double pickFromSortedTwoObjKine( coll1type collection1, string quantity, int whichInOrder, double comparisonValue)
{   
    double samecollectionitem = pickFromSortedTwoObjKine( collection1, collection1, quantity, whichInOrder, comparisonValue, true);
    return samecollectionitem;
}


////////////////////////////////////////////////////////////////////////////

// use this overloaded version when comparing objects from different collections:
template <typename coll1type, typename coll2type> int getNumTwoObjKineInRange( coll1type collection1, coll2type collection2, string quantity, double comparisonValue, double withinrange, bool thesamecols=false)
{
    vector<double> thelist = getTwoObjKineRawCollection( collection1, collection2, quantity, thesamecols);
    int count = 0;
    for (auto elem = thelist.begin(); elem != thelist.end(); ++elem) if (dabs((*elem) - comparisonValue)<withinrange) count += 1;
    return count;
}

// use this overloaded version when comparing objects from the same collection:
template <typename coll1type> int getNumTwoObjKineInRange( coll1type collection1, string quantity, double comparisonValue, double withinrange)
{
    int samecollectionitem = getNumTwoObjKineInRange( collection1, collection1, quantity, comparisonValue, withinrange, true);
    return samecollectionitem;
}



////////////////////////////////////////////////////////////////////////////

double getFinalBDTOSTwoLep()
{
    // still need to do this...
    return 0.;
}



