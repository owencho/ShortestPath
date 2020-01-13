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
#include "AvlError.h"
#include "NetworkNode.h"
#include "List.h"
#include "ListItem.h"
#include "ShortestPathNode.h"
#include "GraphPath.h"
#include "GraphCompare.h"
#include "CustomAssert.h"
#include "ShortestPathError.h"
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

// struct initialize for testing
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

// initialize TREE for testing
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

//////////////createGraphPath/////////////////////////////////////////////////////
//createGraphPath is a function to create GraphPath when adding a ShortestPathNode
//into AVLTREE for pathCost and pathName root Tree
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
    freeGraphPath(graphPathNode);
}

void test_createGraphPath_sPath_NULL(void){
    List linkedListA;
    GraphPath * graphPathNode;
    ListItem itemA;
    Link  listItemDataA;
    initLink(&listItemDataA,0,&nodeA ,&nodeA);
    initList(&linkedListA, &itemA ,NULL,1 ,&itemA);
    initShortestPathNode(&sPath,&nodeA ,NULL,1,1);
    graphPathNode = createGraphPath(NULL);
    TEST_ASSERT_NULL(graphPathNode->left);
    TEST_ASSERT_NULL(graphPathNode->right);
    TEST_ASSERT_EQUAL(0,graphPathNode->bFactor);
    TEST_ASSERT_NULL(graphPathNode->sPath);
    freeGraphPath(graphPathNode);
}
///Main function
//////////////addGraphPathIntoWorkingAVL/////////////////////////////////////////////////////
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
//addGraphPathIntoWorkingAVL is a function to add GraphPath
//into both path cost and path Name working TREE
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
        resetWorkingAVL();
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }

}

void test_addGraphPathIntoWorkingAVL_inputNULL(void){
    initShortestPathNodeABC();
    Try{
        addGraphPathIntoWorkingAVL(NULL);
        TEST_ASSERT_NULL(rootTreePathCost);
        TEST_ASSERT_NULL(rootTreeNodeName);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}
void test_resetWorkingAVL_reset_all_Tree(void){
    initShortestPathNodeDEF();
    resetAndAddNodeNameDEF();
    Try{
        resetWorkingAVL();
        TEST_ASSERT_NULL(rootTreePathCost);
        TEST_ASSERT_NULL(rootTreeNodeName);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}
//////////////deleteGraphPathFromWorkingAVL/////////////////////////////////////////////////////
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
//deleteGraphPathFromWorkingAVL is a function to delete selected GraphPath
//from both path cost and path Name working TREE
void test_deleteGraphPathFromWorkingAVL(void){
    initShortestPathNodeABC();
    addGraphPathIntoWorkingAVL(&sPathB);
    addGraphPathIntoWorkingAVL(&sPathA);
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

/**
*
*       (1)B
*         \
*        (2)A
*
*
*        nodeB
*        /
*      nodeA
*
*(Both remains same as input is NULL)
**/
void test_deleteGraphPathFromWorkingAVL_inputNULL(void){
    initShortestPathNodeABC();
    resetWorkingAVL();
    addGraphPathIntoWorkingAVL(&sPathB);
    addGraphPathIntoWorkingAVL(&sPathA);
    Try{
        deleteGraphPathFromWorkingAVL(NULL);
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
///////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////Function for PathCost////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

//////////////addGraphPathIntoPathCostAVL/////////////////////////////////////////////////////
//addGraphPathIntoPathCostAVL is a function to add GraphPath
//into path costworking TREE

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
    resetPathCostAVL();

    Try{
        addGraphPathIntoPathCostAVL(NULL);
        TEST_ASSERT_NULL(rootTreePathCost);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

//////////////getGraphPathFromPathCost/////////////////////////////////////////////////////
//getGraphPathFromPathCost is a function to find path cost GraphPath
//in the path cost working TREE by inputing the value

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
//////////////findSmallestPathCostFromAVL/////////////////////////////////////////////////////
//findSmallestPathCostFromAVL is a function to find smallest path cost GraphPath
//in the path cost working TREE

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
*         (2)a
*          |
*         (2)C
*          |
*        (2)B
**/
void test_findSmallestPathCostFromAVL_tree_NULL(void){
    resetPathCostAVL();
    graphPathNode=findSmallestPathCostFromAVL();
    TEST_ASSERT_NULL(graphPathNode);
    resetPathCostAVL();
}

//////////////deleteGraphPathFromPathCostAVL/////////////////////////////////////////////////////
//deleteGraphPathFromPathCostAVL is a function to delete selected path cost GraphPath
//in the path cost working TREE
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
void test_deleteGraphPathFromPathCostAVL_with_same_cost(void){
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
*                                          (2)a
*                                           |
*                                         (2)C
*                                          |
*                                         (2)B
**/
// tree remain same as input name is NULL couldnt locate
void test_deleteGraphPathFromPathCostAVL_NULL_name(void){
    initShortestPathNodeABC();
    initShortestPathNode(&sPathC,&nodeC ,NULL,2,2);
    initShortestPathNode(&sPathA,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathB,&nodeB ,NULL,2,2);
    resetAndAddNodeCostABC();

    Try{
        //delete B
        deleteGraphPathFromPathCostAVL(2,NULL);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->sPath,&nodeA,NULL,2,2);
        TEST_ASSERT_NULL(rootTreePathCost->left);
        TEST_ASSERT_NULL(rootTreePathCost->right);
        outListItem= getCurrentListItem(rootTreePathCost->listWithSameCost);
        listGraphPath = outListItem->data;
        TEST_ASSERT_EQUAL_SHORTEST_PATH(listGraphPath->sPath,&nodeC,NULL,2,2);
        outListItem= getNextListItem(rootTreePathCost->listWithSameCost);
        listGraphPath = outListItem->data;
        TEST_ASSERT_EQUAL_SHORTEST_PATH(listGraphPath->sPath,&nodeB,NULL,2,2);
        outListItem= getNextListItem(rootTreePathCost->listWithSameCost);
        TEST_ASSERT_NULL(outListItem);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}
//////////////deleteAndOverrideGraphPathWithSameCost/////////////////////////////////////////////////////
//deleteAndOverrideGraphPathWithSameCost is a function to delete selected path cost GraphPath
//in the path cost working TREE
// this function is able to delete the main node that contain the same cost and replace one of the node inside list
// and add back into the tree if the mother node with all same cost graphPath is deleted
// this function are able to find is any listItem with same cost store inside this node
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
    Try{
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
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

/**
*
*                                 (3)c          (2)a
*                                  /     <---    /  \
*                               (1)B          (1)B  (3)C
*
**/
void test_deleteAndOverrideGraphPathWithSameCost_without_sameCost(void){
    initShortestPathNodeABC();
    resetAndAddNodeCostABC();
    Try{
        gPath = getGraphPathFromPathCost(2);
        //this only override when the delete function match the deleted the name with the main gPath node with all sub same module
        deleteAndOverrideGraphPathWithSameCost(gPath,2);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->sPath,&nodeC,NULL,3,3);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->left->sPath,&nodeB,NULL,1,1);
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
*                                          (2)a
*                     no change   <---      |
*                                          (2)C
*                                          |
*                                         (2)B
**/
void test_deleteAndOverrideGraphPathWithSameCost_with_NULL_gPath(void){
    initShortestPathNodeABC();
    initShortestPathNode(&sPathC,&nodeC ,NULL,2,2);
    initShortestPathNode(&sPathA,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathB,&nodeB ,NULL,2,2);
    resetAndAddNodeCostABC();
    Try{
        //delete B
        gPath = getGraphPathFromPathCost(2);
        //this only override when the delete function match the deleted the name with the main gPath node with all sub same module
        deleteAndOverrideGraphPathWithSameCost(NULL,2);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->sPath,&nodeA,NULL,2,2);
        TEST_ASSERT_NULL(rootTreePathCost->left);
        TEST_ASSERT_NULL(rootTreePathCost->right);
        outListItem= getCurrentListItem(rootTreePathCost->listWithSameCost);
        listGraphPath = outListItem->data;
        TEST_ASSERT_EQUAL_SHORTEST_PATH(listGraphPath->sPath,&nodeC,NULL,2,2);
        outListItem= getNextListItem(rootTreePathCost->listWithSameCost);
        listGraphPath = outListItem->data;
        TEST_ASSERT_EQUAL_SHORTEST_PATH(listGraphPath->sPath,&nodeB,NULL,2,2);
        outListItem= getNextListItem(rootTreePathCost->listWithSameCost);
        TEST_ASSERT_NULL(outListItem);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

//////////////deleteSameCostGraphPathListItem/////////////////////////////////////////////////////
//deleteAndOverrideGraphPathWithSameCost is a function to delete selected path cost GraphPath
//in the path cost working TREE
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
    Try{
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
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
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
    Try{
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
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
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

void test_deleteSameCostGraphPathListItem_with_input_NULL(void){
    resetWorkingAVL();
    Try{
        graphPathNode= (GraphPath*)deleteSameCostGraphPathListItem(NULL,"nodeB");
        TEST_ASSERT_NULL(graphPathNode);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

void test_deleteSameCostGraphPathListItem_with_name_NULL(void){
    resetWorkingAVL();
    Try{
        graphPathNode= (GraphPath*)deleteSameCostGraphPathListItem(gPath,NULL);
        TEST_ASSERT_EQUAL_PTR(gPath,graphPathNode);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}
//////////////resetPathCostAVL/////////////////////////////////////////////////////
//resetPathCostAVL is a function to reset path cost working TREE
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
//////////////addGraphPathIntoPathNameAVL/////////////////////////////////////////////////////
//addGraphPathIntoPathNameAVL is a function to add selected path name GraphPath
//in the path name working TREE
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
*    empty
*
**/
void test_addGraphPathIntoPathNameAVL_input_NULL(void){
    initShortestPathNodeDEF();
    resetNodeNameAVL();

    Try{
        addGraphPathIntoPathNameAVL(NULL);
        TEST_ASSERT_NULL(rootTreeNodeName);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

//////////////getGraphPathFromNodeName/////////////////////////////////////////////////////
//getGraphPathFromNodeName is a function to retrieve selected path name GraphPath
//in the path name working TREE by inputing name
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
*         nodeB
*         /   \
*       nodeA   nodeC
*
**/
void test_getGraphPathFromNodeName_NULL_input(void){
    initShortestPathNodeDEF();
    resetAndAddNodeNameDEF();
    graphPathNode=getGraphPathFromNodeName(NULL);
    TEST_ASSERT_NULL(graphPathNode);
}
//////////////deleteGraphPathFromPathNameAVL/////////////////////////////////////////////////////
//deleteGraphPathFromPathNameAVL is a function to delete selected path name GraphPath
//in the path name working TREE
/**
*
*
*                          nodeB                   nodeB
*        NodeB  <----       /            <---     /   \
*                        nodeA              nodeA   nodeC
*
**/
void test_deleteGraphPathFromPathNameAVL(void){
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
void test_deleteGraphPathFromPathNameAVL_could_not_found_the_node(void){
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
*                   nodeB
*                   /   \
*                nodeA   nodeC
*
**/
void test_deleteGraphPathFromPathNameAVL_in_name_NULL(void){
    initShortestPathNodeDEF();
    resetAndAddNodeNameDEF();
    Try{
        deleteGraphPathFromPathNameAVL(NULL);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreeNodeName->sPath,&nodeB,NULL,1,1);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreeNodeName->left->sPath,&nodeA,NULL,2,2);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreeNodeName->right->sPath,&nodeC,NULL,0,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}
//////////////resetNodeNameAVL/////////////////////////////////////////////////////
//resetNodeNameAVL is a function to reset path name working TREE
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
