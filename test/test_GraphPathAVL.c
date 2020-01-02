#include "unity.h"
#include "GraphPathAVL.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CException.h"
#include "AvlAdd.h"
#include "AvlDelete.h"
#include "Node.h"
#include "IntNode.h"
#include "IntCompare.h"
#include "Compare.h"
#include "Balance.h"
#include "Rotate.h"
#include "Exception.h"
#include "Error.h"
#include "NetworkNode.h"
#include "List.h"
#include "ListItem.h"
#include "ShortestPath.h"
#include "GraphPath.h"
#include "GraphCompare.h"
#include "CustomAssert.h"
NetworkNode nodeA,nodeB,nodeC;
ListItem itemA;
List linkListA;
Link  listItemDataA;
Link *outLink;
ShortestPath sPathA,sPathB,sPathC,sPathD,sPathE,sPathF,sPath;
ShortestPath *shortestPath;
void setUp(void){}
void tearDown(void){}

void initNetworkNode(NetworkNode * node, char*name,List * links,int marked){
    node->name = name;
    node-> links = links;
    node->marked = marked;
}
void initGraphPath(GraphPath*graphPath,GraphPath*left,GraphPath*right,int bFactor, ShortestPath * sPath){
    graphPath->left = left;
    graphPath->right = right;
    graphPath->bFactor = bFactor;
    graphPath->sPath = sPath;
}
void initList(List * link, ListItem * head ,ListItem * tail ,int count ,ListItem * current){
    link->head = head;
    link->tail = tail;
    link->count = count;
    link->current = current;
}
void initLink(Link * linkItemData,int cost,NetworkNode * head ,NetworkNode * tail){
    linkItemData->cost = cost;
    linkItemData->head = head;
    linkItemData->tail = tail;
}
void initShortestPath(ShortestPath *sPath,NetworkNode * dst ,NetworkNode * src ,double pathCost ,List * pathLinks){
    sPath->dst = dst;
    sPath->src = src;
    sPath->pathCost = pathCost;
    sPath->pathLinks = pathLinks;
}

void test_createGraphPath(void){
    GraphPath * graphPathNode;
    initLink(&listItemDataA,0,&nodeA ,&nodeA);
    initList(&linkListA, &itemA ,NULL,1 ,&itemA);
    initShortestPath(&sPath,&nodeA ,&nodeA,0,&linkListA);
    graphPathNode = createGraphPath(&sPath);
    TEST_ASSERT_NULL(graphPathNode->left);
    TEST_ASSERT_NULL(graphPathNode->right);
    TEST_ASSERT_EQUAL(0,graphPathNode->bFactor);
    TEST_ASSERT_EQUAL_PTR(&sPath,graphPathNode->sPath);
}

void test_createLinkFromShortestPath(void){
    initLink(&listItemDataA,0,&nodeA ,&nodeA);
    initList(&linkListA, &itemA ,&itemA,1 ,&itemA);
    initShortestPath(&sPath,&nodeA ,&nodeB,0,&linkListA);
    outLink = createLinkFromShortestPath(&sPath);
    TEST_ASSERT_EQUAL_PTR(&nodeA,outLink->head);
    TEST_ASSERT_EQUAL_PTR(&nodeB,outLink->tail);
    TEST_ASSERT_EQUAL(0,outLink->cost);
}

/**
*
*                                 (2)a          (2)a
*    empty ---> (2)a  ---->       /     --->    /  \
*                               (1)B          (1)B  (3)C
*
**/
void test_addGraphPathIntoPathCostAVL(void){
    GraphPath * graphPathNode;
    initShortestPath(&sPathC,&nodeB ,&nodeC,3,NULL);
    initShortestPath(&sPathA,&nodeA ,&nodeC,2,NULL);
    initShortestPath(&sPathB,&nodeB,&nodeA,1,NULL);
    graphPathNode=(GraphPath*)addGraphPathIntoPathCostAVL(&sPathA);
    TEST_ASSERT_EQUAL_GRAPH_PATH(graphPathNode,NULL,NULL,0,&sPathA);
    graphPathNode=(GraphPath*)addGraphPathIntoPathCostAVL(&sPathB);
    TEST_ASSERT_EQUAL_GRAPH_PATH(graphPathNode->left,NULL,NULL,0,&sPathB);
    TEST_ASSERT_NULL(graphPathNode->right);
    graphPathNode=(GraphPath*)addGraphPathIntoPathCostAVL(&sPathC);
    TEST_ASSERT_EQUAL_GRAPH_PATH(graphPathNode->left,NULL,NULL,0,&sPathB);
    TEST_ASSERT_EQUAL_GRAPH_PATH(graphPathNode->right,NULL,NULL,0,&sPathC);
}

/**
*
*
*                                   nodeA                   nodeB
*    empty ---> (2)NodeA  ---->       \            --->     /   \
*                                     nodeB              nodeA   nodeC
*
**/
void test_addGraphPathIntoPathNameAVL(void){
    GraphPath * graphPathNode;
    initNetworkNode(&nodeA ,"nodeA",NULL,0);
    initNetworkNode(&nodeB ,"nodeB",NULL,0);
    initNetworkNode(&nodeC ,"nodeC",NULL,0);
    initShortestPath(&sPathD,&nodeA ,&nodeC,2,&linkListA);
    initShortestPath(&sPathE,&nodeB,&nodeC,1,NULL);
    initShortestPath(&sPathF,&nodeC,&nodeC,0,NULL);
    graphPathNode=(GraphPath*)addGraphPathIntoPathNameAVL(&sPathD);
    TEST_ASSERT_EQUAL_GRAPH_PATH(graphPathNode,NULL,NULL,0,&sPathD);
    graphPathNode=(GraphPath*)addGraphPathIntoPathNameAVL(&sPathE);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->right->sPath,&nodeB,&nodeC,1,NULL);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeA,&nodeC,2,&linkListA);
    TEST_ASSERT_NULL(graphPathNode->left);
    graphPathNode=(GraphPath*)addGraphPathIntoPathNameAVL(&sPathF);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeB,&nodeC,1,NULL);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->right->sPath,&nodeC,&nodeC,0,NULL);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->left->sPath,&nodeA,&nodeC,2,&linkListA);
}

/**
*
*                                 (3)C             (2)a
*    empty <--- (3)C <-------      /    <-----     /  \
*                               (1)B            (1)B  (3)C
*
**/
void test_deleteGraphPathFromPathCostAVL(void){
    GraphPath * graphPathNode;
    initShortestPath(&sPathC,&nodeB ,&nodeC,3,NULL);
    initShortestPath(&sPathA,&nodeA ,&nodeC,2,NULL);
    initShortestPath(&sPathB,&nodeB,&nodeA,1,NULL);

    addGraphPathIntoPathCostAVL(&sPathA);
    addGraphPathIntoPathCostAVL(&sPathB);
    addGraphPathIntoPathCostAVL(&sPathC);

    graphPathNode=(GraphPath*)deleteGraphPathFromPathCostAVL(&sPathA);
    TEST_ASSERT_EQUAL(-1,graphPathNode->bFactor);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeB,&nodeC,3,NULL);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->left->sPath,&nodeB,&nodeA,1,NULL);
    TEST_ASSERT_NULL(graphPathNode->right);
    graphPathNode=(GraphPath*)deleteGraphPathFromPathCostAVL(&sPathB);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeB,&nodeC,3,NULL);
    TEST_ASSERT_EQUAL(0,graphPathNode->bFactor);
    TEST_ASSERT_NULL(graphPathNode->left);
    TEST_ASSERT_NULL(graphPathNode->right);
    graphPathNode=(GraphPath*)deleteGraphPathFromPathCostAVL(&sPathA);
    TEST_ASSERT_NULL(graphPathNode);
}

/**
*
*
*                                   nodeA                   nodeB
*    empty ---> (2)NodeA  ---->       \            --->     /   \
*                                     nodeB              nodeA   nodeC
*
**/
void xtest_addGraphPathIntoPathNameAVL(void){
    GraphPath * graphPathNode;
    initNetworkNode(&nodeA ,"nodeA",NULL,0);
    initNetworkNode(&nodeB ,"nodeB",NULL,0);
    initNetworkNode(&nodeC ,"nodeC",NULL,0);
    initShortestPath(&sPathA,&nodeA ,&nodeC,2,&linkListA);
    initShortestPath(&sPathB,&nodeB,&nodeC,1,NULL);
    initShortestPath(&sPathC,&nodeC,&nodeC,0,NULL);
    graphPathNode=(GraphPath*)addGraphPathIntoPathNameAVL(&sPathA);
    TEST_ASSERT_EQUAL_GRAPH_PATH(graphPathNode,NULL,NULL,0,&sPathA);
    graphPathNode=(GraphPath*)addGraphPathIntoPathNameAVL(&sPathB);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->right->sPath,&nodeB,&nodeC,1,NULL);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeA,&nodeC,2,&linkListA);
    TEST_ASSERT_NULL(graphPathNode->left);
    graphPathNode=(GraphPath*)addGraphPathIntoPathNameAVL(&sPathC);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeB,&nodeC,1,NULL);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->right->sPath,&nodeC,&nodeC,0,NULL);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->left->sPath,&nodeA,&nodeC,2,&linkListA);
}
