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
#include "ShortestPathNode.h"
#include "GraphPath.h"
#include "GraphCompare.h"
#include "CustomAssert.h"
NetworkNode nodeA,nodeB,nodeC,nodeD;
ListItem itemA;
List linkListA;
Link  listItemDataA;
Link *outLink;
ShortestPathNode sPathA,sPathB,sPathC,sPath0,sPathD,sPathE,sPathF,sPathG,sPath;
ShortestPathNode *ShortestPathNode;
CEXCEPTION_T ex;
void setUp(void){}
void tearDown(void){}

void initNetworkNode(NetworkNode * node, char*name,List * links,int marked){
    node->name = name;
    node-> links = links;
    node->marked = marked;
}
void initGraphPath(GraphPath*graphPath,GraphPath*left,GraphPath*right,int bFactor, ShortestPathNode * sPath){
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
void initShortestPathNode(ShortestPathNode *sPath,NetworkNode * dst ,NetworkNode * src ,double pathCost ,List * pathLinks){
    sPath->dst = dst;
    sPath->src = src;
    sPath->pathCost = pathCost;
    sPath->pathLinks = pathLinks;
}

void test_createGraphPath(void){
    GraphPath * graphPathNode;
    initLink(&listItemDataA,0,&nodeA ,&nodeA);
    initList(&linkListA, &itemA ,NULL,1 ,&itemA);
    initShortestPathNode(&sPath,&nodeA ,&nodeA,0,&linkListA);
    graphPathNode = createGraphPath(&sPath);
    TEST_ASSERT_NULL(graphPathNode->left);
    TEST_ASSERT_NULL(graphPathNode->right);
    TEST_ASSERT_EQUAL(0,graphPathNode->bFactor);
    TEST_ASSERT_EQUAL_PTR(&sPath,graphPathNode->sPath);
}

void test_createLinkFromShortestPath(void){
    initLink(&listItemDataA,0,&nodeA ,&nodeA);
    initList(&linkListA, &itemA ,&itemA,1 ,&itemA);
    initShortestPathNode(&sPath,&nodeA ,&nodeB,0,&linkListA);
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
    initShortestPathNode(&sPathC,&nodeB ,&nodeC,3,NULL);
    initShortestPathNode(&sPathA,&nodeA ,&nodeC,2,NULL);
    initShortestPathNode(&sPathB,&nodeB,&nodeA,1,NULL);
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
*                                   nodeA          rotated   nodeB
*    empty ---> (2)NodeA  ---->       \            --->     /   \
*                                     nodeB              nodeA   nodeC
*
**/
void test_addGraphPathIntoPathNameAVL(void){
    GraphPath * graphPathNode;
    initNetworkNode(&nodeA ,"nodeA",NULL,0);
    initNetworkNode(&nodeB ,"nodeB",NULL,0);
    initNetworkNode(&nodeC ,"nodeC",NULL,0);
    initShortestPathNode(&sPathD,&nodeA ,&nodeC,2,&linkListA);
    initShortestPathNode(&sPathE,&nodeB,&nodeC,1,NULL);
    initShortestPathNode(&sPathF,&nodeC,&nodeC,0,NULL);
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
*         (2)a
*         /  \
*      (1)B  (3)C
*
**/
void test_getGraphPathFromPathCost(void){
    GraphPath * graphPathNode;
    initShortestPathNode(&sPathC,&nodeB ,&nodeC,3,NULL);
    initShortestPathNode(&sPathA,&nodeA ,&nodeC,2,NULL);
    initShortestPathNode(&sPathB,&nodeB,&nodeA,1,NULL);

    graphPathNode=getGraphPathFromPathCost(2);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeA,&nodeC,2,NULL);
}
/**
*
*         (2)a
*         /  \
*      (1)B  (3)C
*
**/
void test_getGraphPathFromPathCost_find_B(void){
    GraphPath * graphPathNode;
    initShortestPathNode(&sPathC,&nodeB ,&nodeC,3,NULL);
    initShortestPathNode(&sPathA,&nodeA ,&nodeC,2,NULL);
    initShortestPathNode(&sPathB,&nodeB,&nodeA,1,NULL);

    graphPathNode=getGraphPathFromPathCost(1);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeB,&nodeA,1,NULL);
}

/**
*
*         (2)a
*         /  \
*      (1)B  (3)C
*      /
*    (0)path0
**/
void test_getGraphPathFromPathCost_find_0(void){
    GraphPath * graphPathNode;
    initShortestPathNode(&sPathC,&nodeB ,&nodeC,3,NULL);
    initShortestPathNode(&sPathA,&nodeA ,&nodeC,2,NULL);
    initShortestPathNode(&sPathB,&nodeB,&nodeA,1,NULL);
    initShortestPathNode(&sPath0,&nodeC,&nodeC,0,NULL);
    graphPathNode=(GraphPath*)addGraphPathIntoPathCostAVL(&sPath0);
    graphPathNode=getGraphPathFromPathCost(0);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeC,&nodeC,0,NULL);
}
/**
*
*
*         nodeB
*         /   \
*       nodeA   nodeC
*
**/
void test_getGraphPathFromNodeName(void){
    GraphPath * graphPathNode;
    initNetworkNode(&nodeA ,"nodeA",NULL,0);
    initNetworkNode(&nodeB ,"nodeB",NULL,0);
    initNetworkNode(&nodeC ,"nodeC",NULL,0);
    initShortestPathNode(&sPathD,&nodeA ,&nodeC,2,&linkListA);
    initShortestPathNode(&sPathE,&nodeB,&nodeC,1,NULL);
    initShortestPathNode(&sPathF,&nodeC,&nodeC,0,NULL);
    graphPathNode=getGraphPathFromNodeName("nodeA");
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeA,&nodeC,2,&linkListA);
}

/**
*
*
*         nodeB
*         /   \
*       nodeA   nodeC
*
**/
void test_getGraphPathFromNodeName_findC(void){
    GraphPath * graphPathNode;
    initNetworkNode(&nodeA ,"nodeA",NULL,0);
    initNetworkNode(&nodeB ,"nodeB",NULL,0);
    initNetworkNode(&nodeC ,"nodeC",NULL,0);
    initShortestPathNode(&sPathD,&nodeA ,&nodeC,2,&linkListA);
    initShortestPathNode(&sPathE,&nodeB,&nodeC,1,NULL);
    initShortestPathNode(&sPathF,&nodeC,&nodeC,0,NULL);
    graphPathNode=getGraphPathFromNodeName("nodeC");
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeC,&nodeC,0,NULL);
}
/**
*
*
*         nodeB
*         /   \
*       nodeA   nodeC
*
**/
void test_getGraphPathFromNodeName_findD(void){
    GraphPath * graphPathNode;
    initNetworkNode(&nodeA ,"nodeA",NULL,0);
    initNetworkNode(&nodeB ,"nodeB",NULL,0);
    initNetworkNode(&nodeC ,"nodeC",NULL,0);
    initShortestPathNode(&sPathD,&nodeA ,&nodeC,2,&linkListA);
    initShortestPathNode(&sPathE,&nodeB,&nodeC,1,NULL);
    initShortestPathNode(&sPathF,&nodeC,&nodeC,0,NULL);
    graphPathNode=getGraphPathFromNodeName("nodeD");
    TEST_ASSERT_NULL(graphPathNode);
}


/**
*
*
*         nodeB
*         /   \
*       nodeA   nodeC
*
**/
void test_getGraphPathFromNodeName_findB(void){
    GraphPath * graphPathNode;
    initNetworkNode(&nodeA ,"nodeA",NULL,0);
    initNetworkNode(&nodeB ,"nodeB",NULL,0);
    initNetworkNode(&nodeD ,"nodeD",NULL,0);
    initNetworkNode(&nodeC ,"nodeC",NULL,0);
    initShortestPathNode(&sPathD,&nodeA ,&nodeC,2,&linkListA);
    initShortestPathNode(&sPathE,&nodeB,&nodeC,1,NULL);
    initShortestPathNode(&sPathF,&nodeC,&nodeC,0,NULL);
    initShortestPathNode(&sPathG,&nodeD,&nodeC,3,NULL);
    graphPathNode=getGraphPathFromNodeName("nodeB");
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeB,&nodeC,1,NULL);
}

/**
*
*                          (3)c                (2)a              (2)a
*                (3)C<----  /     <-------      /  \  <-----     /  \
*                        (1)B               (1)B  (3)C       (1)B  (3)C
*                                                            /
*                                                         (0)
**/
void test_deleteGraphPathFromPathCostAVL(void){
    GraphPath * graphPathNode;
    initShortestPathNode(&sPathC,&nodeB ,&nodeC,3,NULL);
    initShortestPathNode(&sPathA,&nodeA ,&nodeC,2,NULL);
    initShortestPathNode(&sPathB,&nodeB,&nodeA,1,NULL);
    initShortestPathNode(&sPath0,&nodeC,&nodeC,0,NULL);
    Try{
        graphPathNode=(GraphPath*)deleteGraphPathFromPathCostAVL(0);
        TEST_ASSERT_EQUAL(0,graphPathNode->bFactor);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeA,&nodeC,2,NULL);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->left->sPath,&nodeB,&nodeA,1,NULL);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->right->sPath,&nodeB,&nodeC,3,NULL);
        graphPathNode=(GraphPath*)deleteGraphPathFromPathCostAVL(2);
        TEST_ASSERT_EQUAL(-1,graphPathNode->bFactor);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeB,&nodeC,3,NULL);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->left->sPath,&nodeB,&nodeA,1,NULL);
        TEST_ASSERT_NULL(graphPathNode->right);
        graphPathNode=(GraphPath*)deleteGraphPathFromPathCostAVL(1);
        TEST_ASSERT_EQUAL(0,graphPathNode->bFactor);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeB,&nodeC,3,NULL);
        TEST_ASSERT_NULL(graphPathNode->right);
        TEST_ASSERT_NULL(graphPathNode->left);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

/**
*
*
*                (3)C
*
*
*
**/
void test_deleteGraphPathFromPathCostAVL_but_not_inside_the_tree(void){
    GraphPath * graphPathNode;
    initShortestPathNode(&sPathC,&nodeB ,&nodeC,3,NULL);
    initShortestPathNode(&sPathA,&nodeA ,&nodeC,2,NULL);
    initShortestPathNode(&sPathB,&nodeB,&nodeA,1,NULL);
    initShortestPathNode(&sPath0,&nodeC,&nodeC,0,NULL);
    Try{
        graphPathNode=(GraphPath*)deleteGraphPathFromPathCostAVL(0);
    }Catch(ex) {
        dumpException(ex);
        TEST_ASSERT_EQUAL(ERR_NODE_NOT_FOUND, ex->errorCode);
    }
}

/**
*
*
*                          nodeB                   nodeB
*     (2)NodeA  <----       /            <---     /   \
*                        nodeA              nodeA   nodeC
*
**/
void test_deleteIntoPathNameAVL(void){
    GraphPath * graphPathNode;
    initNetworkNode(&nodeA ,"nodeA",NULL,0);
    initNetworkNode(&nodeB ,"nodeB",NULL,0);
    initNetworkNode(&nodeC ,"nodeC",NULL,0);
    initShortestPathNode(&sPathA,&nodeA ,&nodeC,2,&linkListA);
    initShortestPathNode(&sPathB,&nodeB,&nodeC,1,NULL);
    initShortestPathNode(&sPathC,&nodeC,&nodeC,0,NULL);
    Try{
        graphPathNode=(GraphPath*)deleteGraphPathFromPathNameAVL("nodeC");
        TEST_ASSERT_EQUAL(-1,graphPathNode->bFactor);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeB,&nodeC,1,NULL);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->left->sPath,&nodeA,&nodeC,2,&linkListA);
        TEST_ASSERT_NULL(graphPathNode->right);
        graphPathNode=(GraphPath*)deleteGraphPathFromPathNameAVL("nodeA");
        TEST_ASSERT_EQUAL(0,graphPathNode->bFactor);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeB,&nodeC,1,NULL);
        TEST_ASSERT_NULL(graphPathNode->left);
        TEST_ASSERT_NULL(graphPathNode->right);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

/**
*
*
*
*     (2)NodeA
*
*
**/
void test_deleteIntoPathNameAVL_could_not_found_the_node(void){
    GraphPath * graphPathNode;
    initNetworkNode(&nodeA ,"nodeA",NULL,0);
    initNetworkNode(&nodeB ,"nodeB",NULL,0);
    initNetworkNode(&nodeC ,"nodeC",NULL,0);
    initShortestPathNode(&sPathA,&nodeA ,&nodeC,2,&linkListA);
    initShortestPathNode(&sPathB,&nodeB,&nodeC,1,NULL);
    initShortestPathNode(&sPathC,&nodeC,&nodeC,0,NULL);
    Try{
        graphPathNode=(GraphPath*)deleteGraphPathFromPathNameAVL("nodeC");
    }Catch(ex) {
        dumpException(ex);
        TEST_ASSERT_EQUAL(ERR_NODE_NOT_FOUND, ex->errorCode);
    }
}

/**
*
*
*                 reset
*     (2)NodeA    --->   NULL
*
*
**/
void test_resetNodeNameAVL(void){
    GraphPath * graphPathNode;
    initNetworkNode(&nodeA ,"nodeA",NULL,0);
    initNetworkNode(&nodeB ,"nodeB",NULL,0);
    initNetworkNode(&nodeC ,"nodeC",NULL,0);
    initShortestPathNode(&sPathA,&nodeA ,&nodeC,2,&linkListA);
    initShortestPathNode(&sPathB,&nodeB,&nodeC,1,NULL);
    initShortestPathNode(&sPathC,&nodeC,&nodeC,0,NULL);
    graphPathNode=(GraphPath*)resetNodeNameAVL();
    TEST_ASSERT_NULL(graphPathNode);
}

/**
*
*                        reset
*                (3)C    --->  NULL
*
*
*
**/
void test_resetPathCostAVL(void){
    GraphPath * graphPathNode;
    initShortestPathNode(&sPathC,&nodeB ,&nodeC,3,NULL);
    initShortestPathNode(&sPathA,&nodeA ,&nodeC,2,NULL);
    initShortestPathNode(&sPathB,&nodeB,&nodeA,1,NULL);
    initShortestPathNode(&sPath0,&nodeC,&nodeC,0,NULL);
    graphPathNode=(GraphPath*)resetPathCostAVL();
    TEST_ASSERT_NULL(graphPathNode);
}
