#!/bin/bash

TEMP_FOLDER=test-tmp

# get out of build dir
cd ../..
echo $CMAKE_BUILD_TYPE > $TEMP_FOLDER/log.txt
[ -d $TEMP_FOLDER ] || mkdir $TEMP_FOLDER
cat ./test/data/ip_filter.tsv | ./build/$CMAKE_BUILD_TYPE/ipfilter > ./$TEMP_FOLDER/out.txt
diff ./test/data/ip_filter.tst ./$TEMP_FOLDER/out.txt > ./$TEMP_FOLDER/diff.txt
STATUS_CODE=$?

if [[ $STATUS_CODE -eq 0 ]]
then
    rm -rf $TEMP_FOLDER
fi

exit $STATUS_CODE