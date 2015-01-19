set tagFile = ${CMSSW_BASE}/src/ttH-13TeVMultiLeptons/TemplateMakers/bean.tags 

ctags -e -R -f $tagFile ${CMSSW_BASE}/src/ttH-13TeVMultiLeptons/
ctags -e -R -a -f $tagFile  ${CMSSW_BASE}/src/BEAN

echo "Done updating $tagFile"
