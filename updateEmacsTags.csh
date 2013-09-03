set tagFile = ${CMSSW_BASE}/src/ttHMultileptonAnalysis/TemplateMakers/bean.tags 

ctags -e -R -f $tagFile ${CMSSW_BASE}/src/ttHMultileptonAnalysis/
ctags -e -R -a -f $tagFile  ${CMSSW_BASE}/src/BEAN

echo "Done updating $tagFile"
