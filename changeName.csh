

set fileNames = `cat filesToChange.log`

foreach thing ($fileNames)
    echo "considering file $thing"
   sed -i 's|ttH-Multileptons|ttHMultileptonAnalysis|g' $thing
end
