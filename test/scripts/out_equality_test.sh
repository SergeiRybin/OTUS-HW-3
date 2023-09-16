#!/bin/bash

TEMP_FOLDER=test-tmp

# get out of build dir
echo $CMAKE_BUILD_TYPE > $TEMP_FOLDER/log.txt
[ -d $TEMP_FOLDER ] || mkdir $TEMP_FOLDER
cat $CMAKE_CURRENT_SOURCE_DIR/test/data/ip_filter.tsv | $CMAKE_CURRENT_BINARY_DIR/ipfilter > ./$TEMP_FOLDER/out.txt
diff $CMAKE_CURRENT_SOURCE_DIR/test/data/ip_filter.tst ./$TEMP_FOLDER/out.txt > ./$TEMP_FOLDER/diff.txt
STATUS_CODE=$?

if [[ $STATUS_CODE -eq 0 ]]
then
    rm -rf $TEMP_FOLDER
fi

exit $STATUS_CODE