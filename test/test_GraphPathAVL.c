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
void initShortestPathNode(ShortestPathNode *sPath,NetworkNode * id ,ShortestPathNode * parent ,int pathCost ,int linkCost){
    sPath->id = id;
    sPath->parent = parent;
    sPath->pathCost = pathCost;
    sPath->linkCost = linkCost;
}

void test_createGraphPath(void){
    GraphPath * graphPathNode;
    initLink(&listItemDataA,0,&nodeA ,&nodeA);
    initList(&linkListA, &itemA ,NULL,1 ,&itemA);
    initShortestPathNode(&sPath,&nodeA ,NULL,1,1);
    graphPathNode = createGraphPath(&sPath);
    TEST_ASSERT_NULL(graphPathNode->left);
    TEST_ASSERT_NULL(graphPathNode->right);
    TEST_ASSERT_EQUAL(0,graphPathNode->bFactor);
    TEST_ASSERT_EQUAL_PTR(&sPath,graphPathNode->sPath);
}
///Main function
/**
*
*                                (1)B
*    empty ---> (2)a  ---->       \
*                                 (2)A
*
*
*                                 nodeB
*    empty ---> nodeB  ---->         /
*                                 nodeA
**/
void test_addGraphPathIntoWorkingAVL(void){
    GraphPath * graphPathCost;
    GraphPath * graphPathName;
    ListItem * outListItem;
    initNetworkNode(&nodeA ,"nodeA",NULL,0);
    initNetworkNode(&nodeB ,"nodeB",NULL,0);
    initNetworkNode(&nodeC ,"nodeC",NULL,0);
    initShortestPathNode(&sPathC,&nodeC ,NULL,3,3);
    initShortestPathNode(&sPathA,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathB,&nodeB ,NULL,1,1);

    Try{
        addGraphPathIntoWorkingAVL(&sPathB);
        graphPathCost = getGraphPathFromPathCost(sPathB.pathCost);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathCost->sPath,&nodeB,NULL,1,1);
        TEST_ASSERT_EQUAL(0,graphPathCost->bFactor);
        TEST_ASSERT_NULL(graphPathCost->right);
        TEST_ASSERT_NULL(graphPathCost->left);

        graphPathName = getGraphPathFromNodeName(sPathB.id->name);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathName->sPath,&nodeB,NULL,1,1);
        TEST_ASSERT_EQUAL(0,graphPathName->bFactor);
        TEST_ASSERT_NULL(graphPathName->right);
        TEST_ASSERT_NULL(graphPathName->left);

        addGraphPathIntoWorkingAVL(&sPathA);
        graphPathCost = getGraphPathFromPathCost(sPathB.pathCost);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathCost->sPath,&nodeB,NULL,1,1);
        TEST_ASSERT_EQUAL(1,graphPathCost->bFactor);
        TEST_ASSERT_NULL(graphPathCost->left);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathCost->right->sPath,&nodeA,NULL,2,2);
        TEST_ASSERT_EQUAL(0,graphPathCost->right->bFactor);

        graphPathName = getGraphPathFromNodeName(sPathB.id->name);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathName->sPath,&nodeB,NULL,1,1);
        TEST_ASSERT_EQUAL(-1,graphPathName->bFactor);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathName->left->sPath,&nodeA,NULL,2,2);
        TEST_ASSERT_EQUAL(0,graphPathName->left->bFactor);
        TEST_ASSERT_NULL(graphPathName->right);
      }Catch(ex) {
          dumpException(ex);
          TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
      }

}

/**
*
*                                (1)B
*    empty <--- (2)a  <----       \
*                                 (2)A
*
*
*                                 nodeB
*    empty <--- nodeB  <----         /
*                                 nodeA
**/
void test_deleteGraphPathFromWorkingAVL(void){
    GraphPath * graphPathCost;
    GraphPath * graphPathName;
    ListItem * outListItem;
    initNetworkNode(&nodeA ,"nodeA",NULL,0);
    initNetworkNode(&nodeB ,"nodeB",NULL,0);
    initNetworkNode(&nodeC ,"nodeC",NULL,0);
    initShortestPathNode(&sPathC,&nodeC ,NULL,3,3);
    initShortestPathNode(&sPathA,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathB,&nodeB ,NULL,1,1);

    Try{
        deleteGraphPathFromWorkingAVL(&sPathA);
        graphPathCost = getGraphPathFromPathCost(sPathB.pathCost);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathCost->sPath,&nodeB,NULL,1,1);
        TEST_ASSERT_EQUAL(0,graphPathCost->bFactor);
        TEST_ASSERT_NULL(graphPathCost->right);
        TEST_ASSERT_NULL(graphPathCost->left);

        graphPathName = getGraphPathFromNodeName(sPathB.id->name);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathName->sPath,&nodeB,NULL,1,1);
        TEST_ASSERT_EQUAL(0,graphPathName->bFactor);
        TEST_ASSERT_NULL(graphPathName->right);
        TEST_ASSERT_NULL(graphPathName->left);

        deleteGraphPathFromWorkingAVL(&sPathB);
        graphPathCost = getGraphPathFromPathCost(sPathB.pathCost);
        TEST_ASSERT_NULL(graphPathCost);
        graphPathName = getGraphPathFromNodeName(sPathB.id->name);
        TEST_ASSERT_NULL(graphPathName);
      }Catch(ex) {
          dumpException(ex);
          TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
      }

}
////PathCost/////////////////////////////////////////////////////
/**
*
*                            (2)a          (2)a
*    empty ---> (2)a  ---->   |   --->       |
*                            (2)c          (2)C
*                                          |
*                                         (2)B
**/
void test_addGraphPathIntoPathCostAVL_with_same_cost(void){
    GraphPath * graphPathNode;
    GraphPath * listGraphPath;
    ListItem * outListItem;
    initNetworkNode(&nodeA ,"nodeA",NULL,0);
    initNetworkNode(&nodeB ,"nodeB",NULL,0);
    initNetworkNode(&nodeC ,"nodeC",NULL,0);
    initShortestPathNode(&sPathC,&nodeC ,NULL,2,2);
    initShortestPathNode(&sPathA,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathB,&nodeB ,NULL,2,2);
    resetPathCostAVL();
    graphPathNode=(GraphPath*)addGraphPathIntoPathCostAVL(&sPathA);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeA,NULL,2,2);
    TEST_ASSERT_NULL(graphPathNode->right);
    TEST_ASSERT_NULL(graphPathNode->left);
    // add B
    graphPathNode=(GraphPath*)addGraphPathIntoPathCostAVL(&sPathB);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeA,NULL,2,2);
    TEST_ASSERT_NULL(graphPathNode->left);
    TEST_ASSERT_NULL(graphPathNode->right);
    outListItem= getCurrentListItem(graphPathNode->listWithSameCost);
    listGraphPath = outListItem->data;
    TEST_ASSERT_EQUAL_SHORTEST_PATH(listGraphPath->sPath,&nodeB,NULL,2,2);
    outListItem= getNextListItem(graphPathNode->listWithSameCost);
    TEST_ASSERT_NULL(outListItem);
    //add C
    graphPathNode=(GraphPath*)addGraphPathIntoPathCostAVL(&sPathC);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeA,NULL,2,2);
    TEST_ASSERT_NULL(graphPathNode->left);
    TEST_ASSERT_NULL(graphPathNode->right);
    outListItem= getCurrentListItem(graphPathNode->listWithSameCost);
    listGraphPath = outListItem->data;
    TEST_ASSERT_EQUAL_SHORTEST_PATH(listGraphPath->sPath,&nodeC,NULL,2,2);
    outListItem= getNextListItem(graphPathNode->listWithSameCost);
    listGraphPath = outListItem->data;
    TEST_ASSERT_EQUAL_SHORTEST_PATH(listGraphPath->sPath,&nodeB,NULL,2,2);
    outListItem= getNextListItem(graphPathNode->listWithSameCost);
    TEST_ASSERT_NULL(outListItem);
}

/**
*
*                            (2)a          (2)a
*    empty ---> (2)a  ---->   |   --->       |
*                            (2)c          (2)C
*                                          |
*                                         (2)B
**/
void test_findSmallestPathCostFromAVL_with_same_cost(void){
    GraphPath * graphPathNode;
    GraphPath * listGraphPath;
    ListItem * outListItem;
    initNetworkNode(&nodeA ,"nodeA",NULL,0);
    initNetworkNode(&nodeB ,"nodeB",NULL,0);
    initNetworkNode(&nodeC ,"nodeC",NULL,0);
    initShortestPathNode(&sPathC,&nodeC ,NULL,2,2);
    initShortestPathNode(&sPathA,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathB,&nodeB ,NULL,2,2);
    graphPathNode=findSmallestPathCostFromAVL();
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeC,NULL,2,2);
    resetPathCostAVL();
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
    initNetworkNode(&nodeA ,"nodeA",NULL,0);
    initNetworkNode(&nodeB ,"nodeB",NULL,0);
    initNetworkNode(&nodeC ,"nodeC",NULL,0);
    initShortestPathNode(&sPathC,&nodeC ,NULL,3,3);
    initShortestPathNode(&sPathA,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathB,&nodeB ,NULL,1,1);
    graphPathNode=(GraphPath*)addGraphPathIntoPathCostAVL(&sPathA);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeA,NULL,2,2);
    TEST_ASSERT_NULL(graphPathNode->right);
    TEST_ASSERT_NULL(graphPathNode->left);
    graphPathNode=(GraphPath*)addGraphPathIntoPathCostAVL(&sPathB);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeA,NULL,2,2);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->left->sPath,&nodeB,NULL,1,1);
    TEST_ASSERT_NULL(graphPathNode->right);
    graphPathNode=(GraphPath*)addGraphPathIntoPathCostAVL(&sPathC);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeA,NULL,2,2);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->left->sPath,&nodeB,NULL,1,1);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->right->sPath,&nodeC,NULL,3,3);
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
    initShortestPathNode(&sPathC,&nodeC ,NULL,3,3);
    initShortestPathNode(&sPathA,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathB,&nodeB ,NULL,1,1);


    graphPathNode=getGraphPathFromPathCost(2);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeA,NULL,2,2);
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
    initShortestPathNode(&sPathC,&nodeC ,NULL,3,3);
    initShortestPathNode(&sPathA,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathB,&nodeB ,NULL,1,1);

    graphPathNode=getGraphPathFromPathCost(1);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeB,NULL,1,1);
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
    initShortestPathNode(&sPathC,&nodeC ,NULL,3,3);
    initShortestPathNode(&sPathA,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathB,&nodeB ,NULL,1,1);
    initShortestPathNode(&sPath0,&nodeD,NULL,0,0);
    initNetworkNode(&nodeD ,"nodeD",NULL,0);
    graphPathNode=(GraphPath*)addGraphPathIntoPathCostAVL(&sPath0);
    graphPathNode=getGraphPathFromPathCost(0);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeD,NULL,0,0);
}

/**
*
*         (2)a
*         /  \
*      (1)B  (3)C
*      /
*    (0)path0
**/
void test_findSmallestPathCostFromAVL(void){
    GraphPath * graphPathNode;
    initShortestPathNode(&sPathC,&nodeC ,NULL,3,3);
    initShortestPathNode(&sPathA,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathB,&nodeB ,NULL,1,1);
    initShortestPathNode(&sPath0,&nodeD,NULL,0,0);
    initNetworkNode(&nodeD ,"nodeD",NULL,0);
    graphPathNode=findSmallestPathCostFromAVL();
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeD,NULL,0,0);
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
    initShortestPathNode(&sPathC,&nodeC ,NULL,3,3);
    initShortestPathNode(&sPathA,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathB,&nodeB ,NULL,1,1);
    initShortestPathNode(&sPath0,&nodeD,NULL,0,0);
    Try{
        graphPathNode=(GraphPath*)deleteGraphPathFromPathCostAVL(0,"nodeD");
        TEST_ASSERT_EQUAL(0,graphPathNode->bFactor);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeA,NULL,2,2);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->left->sPath,&nodeB,NULL,1,1);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->right->sPath,&nodeC,NULL,3,3);
        graphPathNode=(GraphPath*)deleteGraphPathFromPathCostAVL(2,"nodeA");
        TEST_ASSERT_EQUAL(-1,graphPathNode->bFactor);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeC,NULL,3,3);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->left->sPath,&nodeB,NULL,1,1);
        TEST_ASSERT_NULL(graphPathNode->right);
        graphPathNode=(GraphPath*)deleteGraphPathFromPathCostAVL(1,"nodeB");
        TEST_ASSERT_EQUAL(0,graphPathNode->bFactor);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeC,NULL,3,3);
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
    initShortestPathNode(&sPathC,&nodeC ,NULL,3,3);
    initShortestPathNode(&sPathA,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathB,&nodeB ,NULL,1,1);
    initShortestPathNode(&sPath0,&nodeD,NULL,0,0);
    Try{
        graphPathNode=(GraphPath*)deleteGraphPathFromPathCostAVL(0,"nodeD");
    }Catch(ex) {
        dumpException(ex);
        TEST_ASSERT_EQUAL(ERR_NODE_NOT_FOUND, ex->errorCode);
    }
}
/**
*
*                            (2)a          (2)a
*               (2)C  <----   |   <---      |
*                            (2)c          (2)C
*                                          |
*                                         (2)B
**/
void test_deleteGraphPathIntoPathCostAVL_with_same_cost(void){
    GraphPath * graphPathNode;
    GraphPath * listGraphPath;
    ListItem * outListItem;
    initNetworkNode(&nodeA ,"nodeA",NULL,0);
    initNetworkNode(&nodeB ,"nodeB",NULL,0);
    initNetworkNode(&nodeC ,"nodeC",NULL,0);
    initShortestPathNode(&sPathC,&nodeC ,NULL,2,2);
    initShortestPathNode(&sPathA,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathB,&nodeB ,NULL,2,2);
    resetPathCostAVL();
    graphPathNode=(GraphPath*)addGraphPathIntoPathCostAVL(&sPathA);
    graphPathNode=(GraphPath*)addGraphPathIntoPathCostAVL(&sPathB);
    graphPathNode=(GraphPath*)addGraphPathIntoPathCostAVL(&sPathC);
    //delete B
    graphPathNode=deleteGraphPathFromPathCostAVL(2,"nodeB");
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeA,NULL,2,2);
    TEST_ASSERT_NULL(graphPathNode->left);
    TEST_ASSERT_NULL(graphPathNode->right);
    outListItem= getCurrentListItem(graphPathNode->listWithSameCost);
    listGraphPath = outListItem->data;
    TEST_ASSERT_EQUAL_SHORTEST_PATH(listGraphPath->sPath,&nodeC,NULL,2,2);
    outListItem= getNextListItem(graphPathNode->listWithSameCost);
    TEST_ASSERT_NULL(outListItem);
    //delete A
    graphPathNode=deleteGraphPathFromPathCostAVL(2,"nodeA");
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeC,NULL,2,2);
    TEST_ASSERT_NULL(graphPathNode->left);
    TEST_ASSERT_NULL(graphPathNode->right);
    outListItem= getCurrentListItem(graphPathNode->listWithSameCost);
    TEST_ASSERT_NULL(outListItem);
    resetPathCostAVL();
}

/**
*
*                            (2)C          (2)a
*                              |   <---      |
*                            (2)B          (2)C
*                                          |
*                                         (2)B
**/
void test_deleteAndOverrideGraphPathWithSameCost_with_same_cost(void){
    GraphPath * graphPathNode;
    GraphPath * listGraphPath;
    GraphPath * gPath;
    ListItem * outListItem;
    initNetworkNode(&nodeA ,"nodeA",NULL,0);
    initNetworkNode(&nodeB ,"nodeB",NULL,0);
    initNetworkNode(&nodeC ,"nodeC",NULL,0);
    initShortestPathNode(&sPathC,&nodeC ,NULL,2,2);
    initShortestPathNode(&sPathA,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathB,&nodeB ,NULL,2,2);
    resetPathCostAVL();
    graphPathNode=(GraphPath*)addGraphPathIntoPathCostAVL(&sPathA);
    graphPathNode=(GraphPath*)addGraphPathIntoPathCostAVL(&sPathB);
    graphPathNode=(GraphPath*)addGraphPathIntoPathCostAVL(&sPathC);
    //delete B
    gPath = getGraphPathFromPathCost(2);
    //this only override when the delete function match the deleted the name with the main gPath node with all sub same module
    graphPathNode= (GraphPath*) deleteAndOverrideGraphPathWithSameCost(gPath,2);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeC,NULL,2,2);
    TEST_ASSERT_NULL(graphPathNode->left);
    TEST_ASSERT_NULL(graphPathNode->right);
    outListItem= getCurrentListItem(graphPathNode->listWithSameCost);
    listGraphPath = outListItem->data;
    TEST_ASSERT_EQUAL_SHORTEST_PATH(listGraphPath->sPath,&nodeB,NULL,2,2);
    outListItem= getNextListItem(graphPathNode->listWithSameCost);
    TEST_ASSERT_NULL(outListItem);
}

/**
*
*                                 (3)c          (2)a
  *                               /     <---    /  \
*                               (1)B          (1)B  (3)C
*
**/
void test_deleteAndOverrideGraphPathWithSameCost_without_sameCost(void){
    GraphPath * graphPathNode;
    GraphPath * listGraphPath;
    GraphPath * gPath;
    ListItem * outListItem;
    initNetworkNode(&nodeA ,"nodeA",NULL,0);
    initNetworkNode(&nodeB ,"nodeB",NULL,0);
    initNetworkNode(&nodeC ,"nodeC",NULL,0);
    initShortestPathNode(&sPathC,&nodeC ,NULL,3,3);
    initShortestPathNode(&sPathA,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathB,&nodeB ,NULL,1,1);
    resetPathCostAVL();
    graphPathNode=(GraphPath*)addGraphPathIntoPathCostAVL(&sPathA);
    graphPathNode=(GraphPath*)addGraphPathIntoPathCostAVL(&sPathB);
    graphPathNode=(GraphPath*)addGraphPathIntoPathCostAVL(&sPathC);
    gPath = getGraphPathFromPathCost(2);
    //this only override when the delete function match the deleted the name with the main gPath node with all sub same module
    graphPathNode= (GraphPath*) deleteAndOverrideGraphPathWithSameCost(gPath,2);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeC,NULL,3,3);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->left->sPath,&nodeB,NULL,1,1);
    TEST_ASSERT_NULL(graphPathNode->right);
    outListItem= getCurrentListItem(graphPathNode->listWithSameCost);
    TEST_ASSERT_NULL(outListItem);
}

/**
*
*                            (2)a          (2)a
*                              |   <---      |
*                            (2)C          (2)C
*                                          |
*                                         (2)B
**/
void test_deleteSameCostGraphPathListItem_with_same_cost(void){
    GraphPath * graphPathNode;
    GraphPath * listGraphPath;
    GraphPath * gPath;
    ListItem * outListItem;
    initNetworkNode(&nodeA ,"nodeA",NULL,0);
    initNetworkNode(&nodeB ,"nodeB",NULL,0);
    initNetworkNode(&nodeC ,"nodeC",NULL,0);
    initShortestPathNode(&sPathC,&nodeC ,NULL,2,2);
    initShortestPathNode(&sPathA,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathB,&nodeB ,NULL,2,2);
    resetPathCostAVL();
    graphPathNode=(GraphPath*)addGraphPathIntoPathCostAVL(&sPathA);
    graphPathNode=(GraphPath*)addGraphPathIntoPathCostAVL(&sPathB);
    graphPathNode=(GraphPath*)addGraphPathIntoPathCostAVL(&sPathC);
    //delete B
    gPath = getGraphPathFromPathCost(2);
    //this function is used to delete linkListItem on sameCostItem
    // it will return graphPath node of main sameCost graphPath
    graphPathNode= (GraphPath*)deleteSameCostGraphPathListItem(gPath,"nodeB");
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeA,NULL,2,2);
    TEST_ASSERT_NULL(graphPathNode->left);
    TEST_ASSERT_NULL(graphPathNode->right);
    outListItem= getCurrentListItem(graphPathNode->listWithSameCost);
    listGraphPath = outListItem->data;
    TEST_ASSERT_EQUAL_SHORTEST_PATH(listGraphPath->sPath,&nodeC,NULL,2,2);
    outListItem= getNextListItem(graphPathNode->listWithSameCost);
    TEST_ASSERT_NULL(outListItem);
}

/**
*
*                            (2)a          (2)a
*                              |   <---      |
*                            (2)B          (2)C
*                                          |
*                                         (2)B
**/
void test_deleteSameCostGraphPathListItem_with_same_cost_delete_C(void){
    GraphPath * graphPathNode;
    GraphPath * listGraphPath;
    GraphPath * gPath;
    ListItem * outListItem;
    initNetworkNode(&nodeA ,"nodeA",NULL,0);
    initNetworkNode(&nodeB ,"nodeB",NULL,0);
    initNetworkNode(&nodeC ,"nodeC",NULL,0);
    initShortestPathNode(&sPathC,&nodeC ,NULL,2,2);
    initShortestPathNode(&sPathA,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathB,&nodeB ,NULL,2,2);
    resetPathCostAVL();
    graphPathNode=(GraphPath*)addGraphPathIntoPathCostAVL(&sPathA);
    graphPathNode=(GraphPath*)addGraphPathIntoPathCostAVL(&sPathB);
    graphPathNode=(GraphPath*)addGraphPathIntoPathCostAVL(&sPathC);
    //delete B
    gPath = getGraphPathFromPathCost(2);
    //this function is used to delete linkListItem on sameCostItem
    // it will return graphPath node of main sameCost graphPath
    graphPathNode= (GraphPath*)deleteSameCostGraphPathListItem(gPath,"nodeC");
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeA,NULL,2,2);
    TEST_ASSERT_NULL(graphPathNode->left);
    TEST_ASSERT_NULL(graphPathNode->right);
    outListItem= getCurrentListItem(graphPathNode->listWithSameCost);
    listGraphPath = outListItem->data;
    TEST_ASSERT_EQUAL_SHORTEST_PATH(listGraphPath->sPath,&nodeB,NULL,2,2);
    outListItem= getNextListItem(graphPathNode->listWithSameCost);
    TEST_ASSERT_NULL(outListItem);
}

/**
*
*                            (2)a
*                                 --> error
*
*
**/
void test_deleteSameCostGraphPathListItem_with_same_cost_delete_C_but_nothing_inside_sameCostPathLink(void){
    GraphPath * graphPathNode;
    GraphPath * listGraphPath;
    GraphPath * gPath;
    ListItem * outListItem;
    initNetworkNode(&nodeA ,"nodeA",NULL,0);
    initNetworkNode(&nodeB ,"nodeB",NULL,0);
    initNetworkNode(&nodeC ,"nodeC",NULL,0);
    initShortestPathNode(&sPathC,&nodeC ,NULL,2,2);
    initShortestPathNode(&sPathA,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathB,&nodeB ,NULL,2,2);

    resetPathCostAVL();
    Try{
        graphPathNode=(GraphPath*)addGraphPathIntoPathCostAVL(&sPathA);
        gPath = getGraphPathFromPathCost(2);
        graphPathNode= (GraphPath*)deleteSameCostGraphPathListItem(gPath,"nodeC");
    }Catch(ex) {
      dumpException(ex);
      TEST_ASSERT_EQUAL(ERR_NODE_NOT_FOUND, ex->errorCode);
  }

}

/**
*
*                        reset
*                Tree   --->  NULL
*
*
*
**/
void test_resetPathCostAVL(void){
    GraphPath * graphPathNode;
    initShortestPathNode(&sPathC,&nodeC ,NULL,3,3);
    initShortestPathNode(&sPathA,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathB,&nodeB ,NULL,1,1);
    initShortestPathNode(&sPath0,&nodeD,NULL,0,0);
    graphPathNode=(GraphPath*)resetPathCostAVL();
    TEST_ASSERT_NULL(graphPathNode);
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
    initNetworkNode(&nodeD ,"nodeD",NULL,0);
    initShortestPathNode(&sPathD,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathE,&nodeB ,NULL,1,1);
    initShortestPathNode(&sPathF,&nodeC ,NULL,0,0);
    resetNodeNameAVL();
    graphPathNode=(GraphPath*)addGraphPathIntoPathNameAVL(&sPathD);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeA,NULL,2,2);
    graphPathNode=(GraphPath*)addGraphPathIntoPathNameAVL(&sPathE);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeA,NULL,2,2);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->right->sPath,&nodeB,NULL,1,1);
    TEST_ASSERT_NULL(graphPathNode->left);
    graphPathNode=(GraphPath*)addGraphPathIntoPathNameAVL(&sPathF);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->left->sPath,&nodeA,NULL,2,2);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeB,NULL,1,1);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->right->sPath,&nodeC,NULL,0,0);
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
    initShortestPathNode(&sPathD,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathE,&nodeB ,NULL,1,1);
    initShortestPathNode(&sPathF,&nodeC ,NULL,0,0);
    graphPathNode=getGraphPathFromNodeName("nodeA");
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeA,NULL,2,2);
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
    initShortestPathNode(&sPathD,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathE,&nodeB ,NULL,1,1);
    initShortestPathNode(&sPathF,&nodeC ,NULL,0,0);
    graphPathNode=getGraphPathFromNodeName("nodeC");
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeC,NULL,0,0);
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
    initShortestPathNode(&sPathD,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathE,&nodeB ,NULL,1,1);
    initShortestPathNode(&sPathF,&nodeC ,NULL,0,0);
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
    initShortestPathNode(&sPathD,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathE,&nodeB ,NULL,1,1);
    initShortestPathNode(&sPathF,&nodeC ,NULL,0,0);
    initShortestPathNode(&sPathG,&nodeD,NULL,3,3);
    graphPathNode=getGraphPathFromNodeName("nodeB");
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeB,NULL,1,1);
}
/**
*
*
*                          nodeB                   nodeB
*        NodeB  <----       /            <---     /   \
*                        nodeA              nodeA   nodeC
*
**/
void test_deleteIntoPathNameAVL(void){
    GraphPath * graphPathNode;
    initNetworkNode(&nodeA ,"nodeA",NULL,0);
    initNetworkNode(&nodeB ,"nodeB",NULL,0);
    initNetworkNode(&nodeC ,"nodeC",NULL,0);
    initShortestPathNode(&sPathD,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathE,&nodeB ,NULL,1,1);
    initShortestPathNode(&sPathF,&nodeC ,NULL,0,0);
    Try{
        graphPathNode=(GraphPath*)deleteGraphPathFromPathNameAVL("nodeC");
        TEST_ASSERT_EQUAL(-1,graphPathNode->bFactor);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeB,NULL,1,1);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->left->sPath,&nodeA,NULL,2,2);
        TEST_ASSERT_NULL(graphPathNode->right);
        graphPathNode=(GraphPath*)deleteGraphPathFromPathNameAVL("nodeA");
        TEST_ASSERT_EQUAL(0,graphPathNode->bFactor);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeB,NULL,1,1);
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
    initShortestPathNode(&sPathD,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathE,&nodeB ,NULL,1,1);
    initShortestPathNode(&sPathF,&nodeC ,NULL,0,0);
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
    initShortestPathNode(&sPathD,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathE,&nodeB ,NULL,1,1);
    initShortestPathNode(&sPathF,&nodeC ,NULL,0,0);
    graphPathNode=(GraphPath*)resetNodeNameAVL();
    TEST_ASSERT_NULL(graphPathNode);
}
