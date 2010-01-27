#ifndef KERNEL_UT_FRAMEWORK_UNIT_TESTING_H_INCLUDED
#define KERNEL_UT_FRAMEWORK_UNIT_TESTING_H_INCLUDED

/**
 * XXX Rewrite the whole unit testing framework when kernel heap is ready
 * XXX The framework is ugly, classes are coupled, redesign it.
 * XXX Make this framework thread-safe ???
 */

/**
 * Simple helper file.
 *
 * This file used to simplify the use of the unit testing framework, only
 * need to include this file, can a client get the full functionality
 * of the testing framework
 */
#include "UnitTestingAssert.h"
#include "TestCase.h"
#include "TestResult.h"
#include "TestSuite.h"
#include "TestRunner.h"

#endif /* KERNEL_UT_FRAMEWORK_UNIT_TESTING_H_INCLUDED */
