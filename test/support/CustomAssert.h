#ifndef _CUSTOMASSERT_H
#define _CUSTOMASSERT_H
#include "unity.h"
#include "NetworkNode.h"
#include "List.h"
#include "GraphPath.h"

void assertEqualGraphPath(const GraphPath * actualGraphPath,
                          const NetworkNode * dst,
                          const NetworkNode * src,
                          const double pathCost,
                          const List * pathLinks,
                          const UNITY_LINE_TYPE lineNumber);

void testReportFailure (const UNITY_LINE_TYPE lineNumber,char* message ,...);


#define TEST_ASSERT_EQUAL_GRAPH_PATH(actualGraphPath,dst,src,pathCost,pathLinks)        \
                      assertEqualGraphPath(actualGraphPath,dst,src,pathCost,pathLinks,__LINE__)
#endif // _CUSTOMASSERT_H
