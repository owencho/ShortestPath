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

extern GraphPath * rootTreePathCost;
extern GraphPath * rootTreeNodeName;

NetworkNode nodeA,nodeB,nodeC,nodeD;
ShortestPathNode sPathA,sPathB,sPathC,sPath0,sPathD,sPathE,sPathF,sPathG,sPath;
GraphPath * graphPathCost;
GraphPath * graphPathNode;
GraphPath * graphPathName;
ListItem * outListItem;
GraphPath * listGraphPath;
GraphPath * gPath;
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

void resetAndAddNodeCostABC(void){
    resetPathCostAVL();
    addGraphPathIntoPathCostAVL(&sPathA);
    addGraphPathIntoPathCostAVL(&sPathB);
    addGraphPathIntoPathCostAVL(&sPathC);
}
void initShortestPathNodeABC(void){
    initNetworkNode(&nodeA ,"nodeA",NULL,0);
    initNetworkNode(&nodeB ,"nodeB",NULL,0);
    initNetworkNode(&nodeC ,"nodeC",NULL,0);
    initShortestPathNode(&sPathC,&nodeC ,NULL,3,3);
    initShortestPathNode(&sPathA,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathB,&nodeB ,NULL,1,1);
}
void resetAndAddNodeNameDEF(void){
    resetNodeNameAVL();
    addGraphPathIntoPathNameAVL(&sPathD);
    addGraphPathIntoPathNameAVL(&sPathE);
    addGraphPathIntoPathNameAVL(&sPathF);
}
void initShortestPathNodeDEF(void){
    initNetworkNode(&nodeA ,"nodeA",NULL,0);
    initNetworkNode(&nodeB ,"nodeB",NULL,0);
    initNetworkNode(&nodeC ,"nodeC",NULL,0);
    initShortestPathNode(&sPathD,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathE,&nodeB ,NULL,1,1);
    initShortestPathNode(&sPathF,&nodeC ,NULL,0,0);
}



void test_createGraphPath(void){
    List linkedListA;
    GraphPath * graphPathNode;
    ListItem itemA;
    Link  listItemDataA;
    initLink(&listItemDataA,0,&nodeA ,&nodeA);
    initList(&linkedListA, &itemA ,NULL,1 ,&itemA);
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
    initShortestPathNodeABC();
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
    initShortestPathNodeABC();
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
*                            (2)B          (2)B
*                                          |
*                                         (2)C
**/
void test_addGraphPathIntoPathCostAVL_with_same_cost(void){
    initShortestPathNodeABC();
    initShortestPathNode(&sPathC,&nodeC ,NULL,2,2);
    initShortestPathNode(&sPathA,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathB,&nodeB ,NULL,2,2);
    resetPathCostAVL();
    Try{
        addGraphPathIntoPathCostAVL(&sPathA);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->sPath,&nodeA,NULL,2,2);
        TEST_ASSERT_NULL(rootTreePathCost->right);
        TEST_ASSERT_NULL(rootTreePathCost->left);
        // add B
        addGraphPathIntoPathCostAVL(&sPathB);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->sPath,&nodeA,NULL,2,2);
        TEST_ASSERT_NULL(rootTreePathCost->left);
        TEST_ASSERT_NULL(rootTreePathCost->right);
        outListItem= getCurrentListItem(rootTreePathCost->listWithSameCost);
        listGraphPath = outListItem->data;
        TEST_ASSERT_EQUAL_SHORTEST_PATH(listGraphPath->sPath,&nodeB,NULL,2,2);
        outListItem= getNextListItem(rootTreePathCost->listWithSameCost);
        TEST_ASSERT_NULL(outListItem);
        //add C
        addGraphPathIntoPathCostAVL(&sPathC);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->sPath,&nodeA,NULL,2,2);
        TEST_ASSERT_NULL(rootTreePathCost->left);
        TEST_ASSERT_NULL(rootTreePathCost->right);
        // expect C on the listWithSameCost
        outListItem= getCurrentListItem(rootTreePathCost->listWithSameCost);
        listGraphPath = outListItem->data;
        TEST_ASSERT_EQUAL_SHORTEST_PATH(listGraphPath->sPath,&nodeC,NULL,2,2);
        // expect B on the listWithSameCost
        outListItem= getNextListItem(rootTreePathCost->listWithSameCost);
        listGraphPath = outListItem->data;
        TEST_ASSERT_EQUAL_SHORTEST_PATH(listGraphPath->sPath,&nodeB,NULL,2,2);
        // expect NULL as the list is already ended  on the listWithSameCost
        outListItem= getNextListItem(rootTreePathCost->listWithSameCost);
        TEST_ASSERT_NULL(outListItem);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }

}

void test_addGraphPathIntoPathCostAVL_NULL(void){
    initShortestPathNodeABC();
    initShortestPathNode(&sPathC,&nodeC ,NULL,2,2);
    initShortestPathNode(&sPathA,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathB,&nodeB ,NULL,2,2);
    resetPathCostAVL();

    Try{
        addGraphPathIntoPathCostAVL(NULL);
        TEST_ASSERT_NULL(rootTreePathCost);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

/**
*
*                                 (2)a          (2)a
*    empty ---> (2)a  ---->       /     --->    /  \
*                               (1)B          (1)B  (3)C
*
**/
void test_addGraphPathIntoPathCostAVL(void){
    initShortestPathNodeABC();
    resetPathCostAVL();

    Try{
        addGraphPathIntoPathCostAVL(&sPathA);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->sPath,&nodeA,NULL,2,2);
        TEST_ASSERT_NULL(rootTreePathCost->right);
        TEST_ASSERT_NULL(rootTreePathCost->left);
        addGraphPathIntoPathCostAVL(&sPathB);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->sPath,&nodeA,NULL,2,2);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->left->sPath,&nodeB,NULL,1,1);
        TEST_ASSERT_NULL(rootTreePathCost->right);
        addGraphPathIntoPathCostAVL(&sPathC);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->sPath,&nodeA,NULL,2,2);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->left->sPath,&nodeB,NULL,1,1);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->right->sPath,&nodeC,NULL,3,3);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}
/**
*
*         (2)a
*         /  \
*      (1)B  (3)C
*
**/
void test_getGraphPathFromPathCost(void){
    initShortestPathNodeABC();
    resetAndAddNodeCostABC();

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
    initShortestPathNodeABC();
    resetAndAddNodeCostABC();

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
    initShortestPathNodeABC();
    resetAndAddNodeCostABC();
    initShortestPathNode(&sPath0,&nodeD,NULL,0,0);
    initNetworkNode(&nodeD ,"nodeD",NULL,0);
    addGraphPathIntoPathCostAVL(&sPath0);

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
    initShortestPathNodeABC();
    resetAndAddNodeCostABC();
    initShortestPathNode(&sPath0,&nodeD,NULL,0,0);
    initNetworkNode(&nodeD ,"nodeD",NULL,0);
    addGraphPathIntoPathCostAVL(&sPath0);

    graphPathNode=findSmallestPathCostFromAVL();
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeD,NULL,0,0);
}

//This function will return the head of the listWithSameCost if the graphPath has same pathCost item inside
/**
*
*         (2)a
*          |
*         (2)C
*          |
*        (2)B
**/
void test_findSmallestPathCostFromAVL_with_same_cost(void){
    initShortestPathNodeABC();
    initShortestPathNode(&sPathC,&nodeC ,NULL,2,2);
    initShortestPathNode(&sPathA,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathB,&nodeB ,NULL,2,2);
    resetAndAddNodeCostABC();
    graphPathNode=findSmallestPathCostFromAVL();
    TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeC,NULL,2,2);
    resetPathCostAVL();
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
    initShortestPathNodeABC();
    resetAndAddNodeCostABC();
    initShortestPathNode(&sPath0,&nodeD,NULL,0,0);
    initNetworkNode(&nodeD ,"nodeD",NULL,0);
    addGraphPathIntoPathCostAVL(&sPath0);
    Try{
        deleteGraphPathFromPathCostAVL(0,"nodeD");
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->sPath,&nodeA,NULL,2,2);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->left->sPath,&nodeB,NULL,1,1);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->right->sPath,&nodeC,NULL,3,3);
        deleteGraphPathFromPathCostAVL(2,"nodeA");
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->sPath,&nodeC,NULL,3,3);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->left->sPath,&nodeB,NULL,1,1);
        TEST_ASSERT_NULL(rootTreePathCost->right);
        deleteGraphPathFromPathCostAVL(1,"nodeB");
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->sPath,&nodeC,NULL,3,3);
        TEST_ASSERT_NULL(rootTreePathCost->right);
        TEST_ASSERT_NULL(rootTreePathCost->left);
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
    initShortestPathNodeABC();
    resetAndAddNodeCostABC();
    Try{
        deleteGraphPathFromPathCostAVL(0,"nodeD");
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
    initShortestPathNodeABC();
    initShortestPathNode(&sPathC,&nodeC ,NULL,2,2);
    initShortestPathNode(&sPathA,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathB,&nodeB ,NULL,2,2);
    resetAndAddNodeCostABC();

    Try{
        //delete B
        deleteGraphPathFromPathCostAVL(2,"nodeB");
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->sPath,&nodeA,NULL,2,2);
        TEST_ASSERT_NULL(rootTreePathCost->left);
        TEST_ASSERT_NULL(rootTreePathCost->right);
        outListItem= getCurrentListItem(rootTreePathCost->listWithSameCost);
        listGraphPath = outListItem->data;
        TEST_ASSERT_EQUAL_SHORTEST_PATH(listGraphPath->sPath,&nodeC,NULL,2,2);
        outListItem= getNextListItem(rootTreePathCost->listWithSameCost);
        TEST_ASSERT_NULL(outListItem);
        //delete A
        deleteGraphPathFromPathCostAVL(2,"nodeA");
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->sPath,&nodeC,NULL,2,2);
        TEST_ASSERT_NULL(rootTreePathCost->left);
        TEST_ASSERT_NULL(rootTreePathCost->right);
        outListItem= getCurrentListItem(rootTreePathCost->listWithSameCost);
        TEST_ASSERT_NULL(outListItem);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
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
    initShortestPathNodeABC();
    initShortestPathNode(&sPathC,&nodeC ,NULL,2,2);
    initShortestPathNode(&sPathA,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathB,&nodeB ,NULL,2,2);
    resetAndAddNodeCostABC();
    //delete B
    gPath = getGraphPathFromPathCost(2);
    //this only override when the delete function match the deleted the name with the main gPath node with all sub same module
    deleteAndOverrideGraphPathWithSameCost(gPath,2);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->sPath,&nodeC,NULL,2,2);
    TEST_ASSERT_NULL(rootTreePathCost->left);
    TEST_ASSERT_NULL(rootTreePathCost->right);
    outListItem= getCurrentListItem(rootTreePathCost->listWithSameCost);
    listGraphPath = outListItem->data;
    TEST_ASSERT_EQUAL_SHORTEST_PATH(listGraphPath->sPath,&nodeB,NULL,2,2);
    outListItem= getNextListItem(rootTreePathCost->listWithSameCost);
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
    initShortestPathNodeABC();
    resetAndAddNodeCostABC();

    gPath = getGraphPathFromPathCost(2);
    //this only override when the delete function match the deleted the name with the main gPath node with all sub same module
    deleteAndOverrideGraphPathWithSameCost(gPath,2);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->sPath,&nodeC,NULL,3,3);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->left->sPath,&nodeB,NULL,1,1);
    TEST_ASSERT_NULL(rootTreePathCost->right);
    outListItem= getCurrentListItem(rootTreePathCost->listWithSameCost);
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
    initShortestPathNodeABC();
    initShortestPathNode(&sPathC,&nodeC ,NULL,2,2);
    initShortestPathNode(&sPathA,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathB,&nodeB ,NULL,2,2);
    resetAndAddNodeCostABC();
    //delete B
    gPath = getGraphPathFromPathCost(2);
    //this function is used to delete LinkedListItem on sameCostItem
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
    initShortestPathNodeABC();
    initShortestPathNode(&sPathC,&nodeC ,NULL,2,2);
    initShortestPathNode(&sPathA,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathB,&nodeB ,NULL,2,2);
    resetAndAddNodeCostABC();
    //delete B
    gPath = getGraphPathFromPathCost(2);
    //this function is used to delete linkedListItem on sameCostItem
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
    initShortestPathNodeABC();
    resetPathCostAVL();
    Try{
        addGraphPathIntoPathCostAVL(&sPathA);
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
    initShortestPathNodeABC();
    resetAndAddNodeCostABC();

    resetPathCostAVL();
    TEST_ASSERT_NULL(rootTreePathCost);
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
    initShortestPathNodeDEF();
    resetNodeNameAVL();

    Try{
        addGraphPathIntoPathNameAVL(&sPathD);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreeNodeName->sPath,&nodeA,NULL,2,2);
        addGraphPathIntoPathNameAVL(&sPathE);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreeNodeName->sPath,&nodeA,NULL,2,2);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreeNodeName->right->sPath,&nodeB,NULL,1,1);
        TEST_ASSERT_NULL(rootTreeNodeName->left);
        addGraphPathIntoPathNameAVL(&sPathF);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreeNodeName->left->sPath,&nodeA,NULL,2,2);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreeNodeName->sPath,&nodeB,NULL,1,1);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreeNodeName->right->sPath,&nodeC,NULL,0,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
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
    initShortestPathNodeDEF();
    resetAndAddNodeNameDEF();
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
    initShortestPathNodeDEF();
    resetAndAddNodeNameDEF();
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
    initShortestPathNodeDEF();
    resetAndAddNodeNameDEF();
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
    initShortestPathNodeDEF();
    resetAndAddNodeNameDEF();
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
    initShortestPathNodeDEF();
    resetAndAddNodeNameDEF();
    Try{
        deleteGraphPathFromPathNameAVL("nodeC");
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreeNodeName->sPath,&nodeB,NULL,1,1);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreeNodeName->left->sPath,&nodeA,NULL,2,2);
        TEST_ASSERT_NULL(rootTreeNodeName->right);
        deleteGraphPathFromPathNameAVL("nodeA");
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreeNodeName->sPath,&nodeB,NULL,1,1);
        TEST_ASSERT_NULL(rootTreeNodeName->left);
        TEST_ASSERT_NULL(rootTreeNodeName->right);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

/**
*
*
*             nodeB
*             /   \
*          nodeA   nodeC
*
**/
void test_deleteIntoPathNameAVL_could_not_found_the_node(void){
    initShortestPathNodeDEF();
    resetAndAddNodeNameDEF();
    Try{
        deleteGraphPathFromPathNameAVL("nodeD");
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
    initNetworkNode(&nodeA ,"nodeA",NULL,0);
    initNetworkNode(&nodeB ,"nodeB",NULL,0);
    initNetworkNode(&nodeC ,"nodeC",NULL,0);
    initShortestPathNode(&sPathD,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathE,&nodeB ,NULL,1,1);
    initShortestPathNode(&sPathF,&nodeC ,NULL,0,0);
    resetNodeNameAVL();
    TEST_ASSERT_NULL(rootTreeNodeName);
}
