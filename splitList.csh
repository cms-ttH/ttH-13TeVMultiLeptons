#!/bin/tcsh -f 



if ($#argv < 1) then

echo "Not enough args"
exit 2

endif 

set myList = $1

set listSize = `wc -l $myList | awk '{ print $1 }'`

foreach time (`seq 1 $listSize`)

echo $time
head -n $time $myList | tail -n 1 >&! ${myList:r}_part${time}.list

end
