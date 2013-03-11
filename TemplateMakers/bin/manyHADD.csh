
set thisYear = "2012_53x"
set thisLabel = limits_v1

./haddAll.py --moveFiles --sumData --year=${thisYear} ${thisLabel}
./haddAll.py --moveFiles --sumData --year=${thisYear} ${thisLabel}_JESUp
./haddAll.py --moveFiles --sumData --year=${thisYear} ${thisLabel}_JESDown
./haddAll.py --moveFiles --sumData --year=${thisYear} ${thisLabel}_btagHFUp
./haddAll.py --moveFiles --sumData --year=${thisYear} ${thisLabel}_btagHFDown
./haddAll.py --moveFiles --sumData --year=${thisYear} ${thisLabel}_btagLFUp
./haddAll.py --moveFiles --sumData --year=${thisYear} ${thisLabel}_btagLFDown

