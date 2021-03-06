#ifndef _CUSTOMASSERT_H
#define _CUSTOMASSERT_H
#include "unity.h"
#include "NetworkNode.h"
#include "ShortestPathNode.h"
#include "List.h"
#include "GraphPath.h"

void assertEqualShortestPath(const ShortestPathNode * actualShortestPath,
                             const NetworkNode * id,
                             const ShortestPathNode * parent,
                             const int pathCost,
                             const double linkCost,
                             const UNITY_LINE_TYPE lineNumber);

void testReportFailure (const UNITY_LINE_TYPE lineNumber,char* message ,...);

#define TEST_ASSERT_EQUAL_SHORTEST_PATH(actualGraphPath,id,parent,pathCost,linkCost)        \
                      assertEqualShortestPath(actualGraphPath,id,parent,pathCost,linkCost,__LINE__)

#endif // _CUSTOMASSERT_H
