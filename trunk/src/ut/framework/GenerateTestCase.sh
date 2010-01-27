#!/usr/bin/env bash

testHeader="$1"
testName=`basename ${testHeader} | sed s/\.h$//g`
sourcePath=`echo ${testHeader} | sed s/\.h$/.cpp/g`

cat > ${sourcePath} << EOF
/******************************************************************
 * DO NOT EDIT                                                    *
 * This file is generated by shell script "GenerateTestCase.sh"   *
 ******************************************************************/

#include "ut/framework/TestCase.h"
#include "${testHeader}"

namespace kernel {

bool ${testName}::getTestPoint(TestPoint& point, const char*& name) {
	static int index = 0;
	switch (index) {
EOF

methodList=`egrep 'void test[a-zA-Z0-9_]+ *\(\)' "$1" | sed 's/void//'| sed 's/[(){}]//g'`

methodIndex=0
for method in ${methodList}; do
	cat >> ${sourcePath} << EOF
	case ${methodIndex}:
		point = (TestPoint)(&${testName}::${method});
		name = "${method}";
		break;
EOF
	methodIndex=`expr ${methodIndex} + 1`
done

cat >> ${sourcePath} << EOF
	default:
		++index;
		return false;
	}
	++index;
	return true;
}

} /* namespace kernel */

EOF
