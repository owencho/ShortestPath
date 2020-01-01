#ifndef _CUSTOMASSERT_H
#define _CUSTOMASSERT_H
#include "unity.h"
#include "NetworkNode.h"
#include "List.h"
#include "GraphPath.h"

void assertEqualShortestPath(const ShortestPath * actualShortestPath,
                          const NetworkNode * dst,
                          const NetworkNode * src,
                          const double pathCost,
                          const List * pathLinks,
                          const UNITY_LINE_TYPE lineNumber);

void assertEqualLink(const Link * actualLinkItemData,
                     const NetworkNode * head,
                     const NetworkNode * tail,
                     const int cost,
                     const UNITY_LINE_TYPE lineNumber);

void assertEqualGraphPath(const GraphPath * actualGraphPath,
                         const GraphPath * left,
                         const GraphPath * right,
                         const int bFactor,
                         const ShortestPath * sPath,
                         const UNITY_LINE_TYPE lineNumber);

void testReportFailure (const UNITY_LINE_TYPE lineNumber,char* message ,...);

#define TEST_ASSERT_EQUAL_LINK_LIST_ITEM(actualLinkItemData,head,tail,cost)        \
                      assertEqualLink(actualLinkItemData,head,tail,cost,__LINE__)

#define TEST_ASSERT_EQUAL_SHORTEST_PATH(actualGraphPath,dst,src,pathCost,pathLinks)        \
                      assertEqualShortestPath(actualGraphPath,dst,src,pathCost,pathLinks,__LINE__)

#define TEST_ASSERT_EQUAL_GRAPH_PATH(actualGraphPath,left,right,bFactor,sPath)        \
                      assertEqualGraphPath(actualGraphPath,left,right,bFactor,sPath,__LINE__)
#endif // _CUSTOMASSERT_H
