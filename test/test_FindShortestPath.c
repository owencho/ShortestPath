#include "FindShortestPath.h"
#include "unity.h"
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
#include "GraphPathAVL.h"
#include "GraphCompare.h"
#include "CustomAssert.h"
#include "ShortestPathListCompare.h"
#include "ShortestPathError.h"
#include "Processor.h"
ShortestPathNode sPathA ,sPathB,sPathC,sPathD,sPathE,sPathF;
Link linkItemDataCA,linkItemDataCB,linkItemDataCD,linkItemDataCE;
Link linkItemDataAC,linkItemDataAB,linkItemDataAD;
Link linkItemDataBC,linkItemDataBA,linkItemDataBD,linkItemDataBE;
Link linkItemDataDC,linkItemDataDB,linkItemDataDE,linkItemDataDA,linkItemDataDF;
Link linkItemDataED,linkItemDataEB,linkItemDataEC,linkItemDataEF;
Link linkItemDataFD ,linkItemDataFE;

ListItem listItemAC,listItemAB,listItemAD;
ListItem listItemBC,listItemBA,listItemBD,listItemBE;
ListItem listItemCA,listItemCB,listItemCD,listItemCE;
ListItem listItemDA,listItemDB,listItemDC,listItemDE,listItemDF;
ListItem listItemEB,listItemED,listItemEC,listItemEF;
ListItem listItemFD , listItemFE;
NetworkNode nodeA ,nodeB,nodeC,nodeD,nodeE,nodeF;
ShortestPathNode * outSPathNode;
List networkListC,networkListA,networkListB,networkListD,networkListE,networkListF;
List shortestPathList;
List * outLinkedList;
ListItem * outListItem;
GraphPath * listGraphPath;
GraphPath * graphPathNode;
GraphPath gPath,gPathA;

extern GraphPath * rootTreePathCost;
CEXCEPTION_T ex;
void setUp(void){}
void tearDown(void){}

void initNetworkNode(NetworkNode * node, char*name,List * links,int marked){
    node->name = name;
    node-> links = links;
    node->marked = marked;
}
void initGraphPath(GraphPath*graphPath,GraphPath*left,GraphPath*right,int bFactor,ShortestPathNode * sPath){
    graphPath->left = left;
    graphPath->right = right;
    graphPath->bFactor = bFactor;
    graphPath->listWithSameCost =NULL;
    graphPath->sPath = sPath;
}
void initList(List * link, ListItem * head ,ListItem * tail ,int count ,ListItem * current){
    link->head = head;
    link->tail = tail;
    link->count = count;
    link->current = current;
    link->previous = NULL;
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
void initListItem(ListItem * listItem ,ListItem * next,void * data){
    listItem->next = next;
    listItem->data = data;
}

/**
*              (3)
*         (A)----- (B)
*        1 \     7 /
*           \    /
*            (C)------(D)
*                   2
**/
void initPartialNetworkMap(void){
    initLink(&linkItemDataCA,1,&nodeA ,&nodeC);
    initLink(&linkItemDataCB,7,&nodeB ,&nodeC);
    initLink(&linkItemDataCD,2,&nodeD,&nodeC);
    initListItem(&listItemCA ,&listItemCD,(void*) &linkItemDataCA);
    initListItem(&listItemCB ,NULL,(void*) &linkItemDataCB);
    initListItem(&listItemCD ,&listItemCB,(void*)&linkItemDataCD);
    initList(&networkListC, &listItemCA ,&listItemCB ,3 ,&listItemCA);

    initLink(&linkItemDataAC,1,&nodeC ,&nodeA);
    initLink(&linkItemDataAB,3,&nodeB ,&nodeA);
    initListItem(&listItemAC ,&listItemAB,(void*) &linkItemDataAC);
    initListItem(&listItemAB ,NULL,(void*) &linkItemDataAB);
    initList(&networkListA, &listItemAC ,&listItemAB ,2 ,&listItemAC);

    initLink(&linkItemDataBC,7,&nodeC ,&nodeB);
    initLink(&linkItemDataBA,3,&nodeA,&nodeB);
    initListItem(&listItemBC ,&listItemBA,(void*) &linkItemDataBC);
    initListItem(&listItemBA ,NULL,(void*) &linkItemDataBA);
    initList(&networkListB, &listItemBA ,&listItemBC ,2 ,&listItemBA);

    initLink(&linkItemDataDC,2,&nodeC ,&nodeD);
    initListItem(&listItemDC ,NULL,(void*) &linkItemDataDC);
    initList(&networkListD, &listItemDC ,&listItemDC ,1 ,&listItemDC);

    initNetworkNode(&nodeA ,"nodeA",&networkListA,0);
    initNetworkNode(&nodeB ,"nodeB",&networkListB,0);
    initNetworkNode(&nodeC ,"nodeC",&networkListC,0);
    initNetworkNode(&nodeD ,"nodeD",&networkListD,0);
}

/**
*              (3)       (1)
*         (A)----- (B) ----- (E)
*        1 \     7 / \ 5    /
*           \    /    \   /  (7)
*            (C)------(D)
*                   2
**/
void initFullNetworkMap(void){
    initLink(&linkItemDataCA,1,&nodeA ,&nodeC);
    initLink(&linkItemDataCB,7,&nodeB ,&nodeC);
    initLink(&linkItemDataCD,2,&nodeD,&nodeC);
    initListItem(&listItemCA ,&listItemCD,(void*) &linkItemDataCA);
    initListItem(&listItemCB ,NULL,(void*) &linkItemDataCB);
    initListItem(&listItemCD ,&listItemCB,(void*)&linkItemDataCD);
    initList(&networkListC, &listItemCA ,&listItemCB ,3 ,&listItemCA);

    initLink(&linkItemDataAC,1,&nodeC ,&nodeA);
    initLink(&linkItemDataAB,3,&nodeB ,&nodeA);
    initListItem(&listItemAC ,&listItemAB,(void*) &linkItemDataAC);
    initListItem(&listItemAB ,NULL,(void*) &linkItemDataAB);
    initList(&networkListA, &listItemAC ,&listItemAB ,2 ,&listItemAC);

    initLink(&linkItemDataBC,7,&nodeC ,&nodeB);
    initLink(&linkItemDataBA,3,&nodeA,&nodeB);
    initLink(&linkItemDataBD,5,&nodeD,&nodeB);
    initLink(&linkItemDataBE,1,&nodeE,&nodeB);
    initListItem(&listItemBC ,&listItemBD,(void*) &linkItemDataBC);
    initListItem(&listItemBA ,&listItemBC,(void*) &linkItemDataBA);
    initListItem(&listItemBD ,&listItemBE,(void*) &linkItemDataBD);
    initListItem(&listItemBE ,NULL,(void*) &linkItemDataBE);
    initList(&networkListB, &listItemBA ,&listItemBE ,4 ,&listItemBA);

    initLink(&linkItemDataDC,2,&nodeC ,&nodeD);
    initLink(&linkItemDataDE,7,&nodeE ,&nodeD);
    initLink(&linkItemDataDB,5,&nodeB ,&nodeD);
    initListItem(&listItemDC ,&listItemDB,(void*) &linkItemDataDC);
    initListItem(&listItemDE ,NULL,(void*) &linkItemDataDE);
    initListItem(&listItemDB ,&listItemDE,(void*) &linkItemDataDB);
    initList(&networkListD, &listItemDC ,&listItemDE ,3 ,&listItemDC);

    initLink(&linkItemDataEB,1,&nodeB ,&nodeE);
    initLink(&linkItemDataED,7,&nodeD ,&nodeE);
    initListItem(&listItemEB ,&listItemED,(void*) &linkItemDataEB);
    initListItem(&listItemED ,NULL,(void*) &linkItemDataED);
    initList(&networkListE, &listItemEB ,&listItemED ,2 ,&listItemEB);

    initNetworkNode(&nodeA ,"nodeA",&networkListA,0);
    initNetworkNode(&nodeB ,"nodeB",&networkListB,0);
    initNetworkNode(&nodeC ,"nodeC",&networkListC,0);
    initNetworkNode(&nodeD ,"nodeD",&networkListD,0);
    initNetworkNode(&nodeE ,"nodeE",&networkListE,0);
}

/**
*                  ( F )
*              6 /     \ 8
*            ( D )      ( E )
*             | 2 \   4 /  |
*         10  |   ( C )    | 1
*            | 2 /   5 \  |
*           (A) ------- (B)
*                 1
**/
void initComplexNetworkMap(void){

    initLink(&linkItemDataAC,2,&nodeC ,&nodeA);
    initLink(&linkItemDataAD,10,&nodeD ,&nodeA);
    initLink(&linkItemDataAB,1,&nodeB ,&nodeA);
    initListItem(&listItemAC ,&listItemAD,(void*) &linkItemDataAC);
    initListItem(&listItemAD ,&listItemAB,(void*) &linkItemDataAD);
    initListItem(&listItemAB ,NULL,(void*) &linkItemDataAB);
    initList(&networkListA, &listItemAC ,&listItemAB ,3 ,&listItemAC);

    initLink(&linkItemDataBC,5,&nodeC ,&nodeB);
    initLink(&linkItemDataBA,1,&nodeA,&nodeB);
    initLink(&linkItemDataBE,1,&nodeE,&nodeB);
    initListItem(&listItemBC ,&listItemBE,(void*) &linkItemDataBC);
    initListItem(&listItemBA ,&listItemBC,(void*) &linkItemDataBA);
    initListItem(&listItemBE ,NULL,(void*) &linkItemDataBE);
    initList(&networkListB, &listItemBA ,&listItemBE ,3 ,&listItemBA);

    initLink(&linkItemDataCA,2,&nodeA ,&nodeC);
    initLink(&linkItemDataCB,5,&nodeB ,&nodeC);
    initLink(&linkItemDataCD,2,&nodeD,&nodeC);
    initLink(&linkItemDataCE,4,&nodeE,&nodeC);
    initListItem(&listItemCA ,&listItemCD,(void*) &linkItemDataCA);
    initListItem(&listItemCB ,NULL,(void*) &linkItemDataCB);
    initListItem(&listItemCE ,&listItemCB,(void*)&linkItemDataCE);
    initListItem(&listItemCD ,&listItemCE,(void*)&linkItemDataCD);
    initList(&networkListC, &listItemCA ,&listItemCB ,4 ,&listItemCA);

    initLink(&linkItemDataDC,2,&nodeC ,&nodeD);
    initLink(&linkItemDataDA,10,&nodeA ,&nodeD);
    initLink(&linkItemDataDF,6,&nodeF ,&nodeD);
    initListItem(&listItemDC ,&listItemDA,(void*) &linkItemDataDC);
    initListItem(&listItemDF ,NULL,(void*) &linkItemDataDF);
    initListItem(&listItemDA ,&listItemDF,(void*) &linkItemDataDA);
    initList(&networkListD, &listItemDC ,&listItemDF ,3 ,&listItemDC);

    initLink(&linkItemDataEB,1,&nodeB ,&nodeE);
    initLink(&linkItemDataEC,4,&nodeC ,&nodeE);
    initLink(&linkItemDataEF,8,&nodeF ,&nodeE);
    initListItem(&listItemEB ,&listItemEF,(void*) &linkItemDataEB);
    initListItem(&listItemEF ,&listItemEC,(void*) &linkItemDataEF);
    initListItem(&listItemEC ,NULL,(void*) &linkItemDataEC);
    initList(&networkListE, &listItemEB ,&listItemEC ,3 ,&listItemEB);

    initLink(&linkItemDataFD,6,&nodeD ,&nodeF);
    initLink(&linkItemDataFE,8,&nodeE ,&nodeF);
    initListItem(&listItemFD ,&listItemFE,(void*) &linkItemDataFD);
    initListItem(&listItemFE ,NULL,(void*) &linkItemDataED);
    initList(&networkListF, &listItemFD ,&listItemFE ,2 ,&listItemFD);

    initNetworkNode(&nodeA ,"nodeA",&networkListA,0);
    initNetworkNode(&nodeB ,"nodeB",&networkListB,0);
    initNetworkNode(&nodeC ,"nodeC",&networkListC,0);
    initNetworkNode(&nodeD ,"nodeD",&networkListD,0);
    initNetworkNode(&nodeE ,"nodeE",&networkListE,0);
    initNetworkNode(&nodeF ,"nodeF",&networkListF,0);
}
//////////////compareAndAddShortestPathIntoWorkingAVL/////////////////////////////////////////////////////
//compareAndAddShortestPathIntoWorkingAVL is function to compare new path cost and old path cost
// and determine the node should be override or not
/**
*                                    compares with sPathD
*                            (A)2     with nodeC id        (A)2
*                           /   \   ---------------->     /  |
*                         (B)1  (C)3                   (B)1 |
*                                                         (C)2
*
**/
void test_compareAndAddShortestPathIntoWorkingAVL_smaller_path(void){
    initNetworkNode(&nodeA ,"nodeA",NULL,0);
    initNetworkNode(&nodeB ,"nodeB",NULL,0);
    initNetworkNode(&nodeC ,"nodeC",NULL,0);
    initShortestPathNode(&sPathD,&nodeC ,&sPathB,2,2);
    initShortestPathNode(&sPathC,&nodeC ,&sPathA,3,3);
    initShortestPathNode(&sPathA,&nodeA ,NULL,2,1);
    initShortestPathNode(&sPathB,&nodeB ,NULL,1,1);

    Try{
        resetWorkingAVL();
        addGraphPathIntoWorkingAVL(&sPathC);
        addGraphPathIntoWorkingAVL(&sPathA);
        addGraphPathIntoWorkingAVL(&sPathB);
        compareAndAddShortestPathIntoWorkingAVL(&sPathD);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->sPath,&nodeA,NULL,2,1);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->left->sPath,&nodeB,NULL,1,1);
        TEST_ASSERT_NULL(rootTreePathCost->right);

        outListItem= getCurrentListItem(rootTreePathCost->listWithSameCost);
        listGraphPath = outListItem->data;
        TEST_ASSERT_EQUAL_SHORTEST_PATH(listGraphPath->sPath,&nodeC,&sPathB,2,2);
        outListItem= getNextListItem(rootTreePathCost->listWithSameCost);
        TEST_ASSERT_NULL(outListItem);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

/**
*           compares with sPathD
*    (A)2     with nodeC id        (A)2
*   /   \   ---------------->     /   \
* (B)1  (C)3                   (B)1  (C)3
*
**/
void test_compareAndAddShortestPathIntoWorkingAVL_larger_path(void){
    initNetworkNode(&nodeA ,"nodeA",NULL,0);
    initNetworkNode(&nodeB ,"nodeB",NULL,0);
    initNetworkNode(&nodeC ,"nodeC",NULL,0);
    initShortestPathNode(&sPathD,&nodeC ,NULL,4,4);
    initShortestPathNode(&sPathC,&nodeC ,NULL,3,3);
    initShortestPathNode(&sPathA,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathB,&nodeB ,NULL,1,1);

    Try{
        resetWorkingAVL();
        addGraphPathIntoWorkingAVL(&sPathC);
        addGraphPathIntoWorkingAVL(&sPathA);
        addGraphPathIntoWorkingAVL(&sPathB);
        compareAndAddShortestPathIntoWorkingAVL(&sPathD);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->sPath,&nodeA,NULL,2,2);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->left->sPath,&nodeB,NULL,1,1);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->right->sPath,&nodeC,NULL,3,3);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}
//remain same as input is NULL couldnt compare anything
void test_compareAndAddShortestPathIntoWorkingAVL_input_NULL(void){
    initNetworkNode(&nodeA ,"nodeA",NULL,0);
    initNetworkNode(&nodeB ,"nodeB",NULL,0);
    initNetworkNode(&nodeC ,"nodeC",NULL,0);
    initShortestPathNode(&sPathD,&nodeC ,NULL,4,4);
    initShortestPathNode(&sPathC,&nodeC ,NULL,3,3);
    initShortestPathNode(&sPathA,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathB,&nodeB ,NULL,1,1);

    Try{
        resetWorkingAVL();
        addGraphPathIntoWorkingAVL(&sPathC);
        addGraphPathIntoWorkingAVL(&sPathA);
        addGraphPathIntoWorkingAVL(&sPathB);
        compareAndAddShortestPathIntoWorkingAVL(NULL);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->sPath,&nodeA,NULL,2,2);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->left->sPath,&nodeB,NULL,1,1);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->right->sPath,&nodeC,NULL,3,3);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}
/**                                              (nodeB) is marked
*              (3)
*         (A)----- (B)                   (A)2     add nodeB            (A)2
*        1 \     7 /                        \   ---------------->        \
*           \    /                          (C)3                        (C)3
*            (C)------(D)
*                   2
**/
void test_compareAndAddShortestPathIntoWorkingAVL_with_marked_node(void){
    initNetworkNode(&nodeA ,"nodeA",NULL,0);
    initNetworkNode(&nodeB ,"nodeB",NULL,1);
    initNetworkNode(&nodeC ,"nodeC",NULL,0);
    initShortestPathNode(&sPathC,&nodeC ,NULL,3,3);
    initShortestPathNode(&sPathA,&nodeA ,NULL,2,2);
    initShortestPathNode(&sPathB,&nodeB ,NULL,1,1);

    Try{
        resetWorkingAVL();
        addGraphPathIntoWorkingAVL(&sPathA);
        addGraphPathIntoWorkingAVL(&sPathC);
        compareAndAddShortestPathIntoWorkingAVL(&sPathB);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->sPath,&nodeA,NULL,2,2);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->right->sPath,&nodeC,NULL,3,3);
        TEST_ASSERT_NULL(rootTreePathCost->left);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}
//////////////addNeighbouringNode/////////////////////////////////////////////////////
//addNeighbouringNode is function to add nearest node into working AVL TREE
/**
*              (3)
*         (A)----- (B)                         (D)2         (D)2
*        1 \     7 /        -------->         /   \    -->     \
*           \    /                          (A)1  (B)7         (B)7
*            (C)------(D)
*                   2
**/
void test_addNeighbouringNode(void){
    initPartialNetworkMap();
    initShortestPathNode(&sPathC,&nodeC ,NULL,0,0);
    initShortestPathNode(&sPathA,&nodeA ,&sPathC,1,1);
    initGraphPath(&gPath,NULL,NULL,0,&sPathC);
    initGraphPath(&gPathA,NULL,NULL,0,&sPathA);
    Try{
        resetWorkingAVL();
        addNeighbouringNode(&gPath); //nearestNode from source C
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->sPath,&nodeD,&sPathC,2,2);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->right->sPath,&nodeB,&sPathC,7,7);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->left->sPath,&nodeA,&sPathC,1,1);
        //mark C
        gPath.sPath->id->marked = 1;
        deleteGraphPathFromWorkingAVL(&sPathA);
        addNeighbouringNode(&gPathA); //nearestNode from source A
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->sPath,&nodeD,&sPathC,2,2);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->right->sPath,&nodeB,&sPathA,4,3);
        TEST_ASSERT_NULL(rootTreePathCost->left);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

/**
*              (3)
*         (A)----- (B)                          (D)2
*        1 \     7 /        -------->              \
*           \    /                                (B)7
*            (C)------(D)
*                   2
**/
// A is marked
void test_addNeighbouringNode_one_of_the_path_is_marked(void){
    initPartialNetworkMap();
    initNetworkNode(&nodeA ,"nodeA",&networkListA,1); //nodeA is marked
    initShortestPathNode(&sPathC,&nodeC ,NULL,0,0);
    initGraphPath(&gPath,NULL,NULL,0,&sPathC);
    Try{
        resetWorkingAVL();
        addNeighbouringNode(&gPath);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->sPath,&nodeD,&sPathC,2,2);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(rootTreePathCost->right->sPath,&nodeB,&sPathC,7,7);
        TEST_ASSERT_NULL(rootTreePathCost->left);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

void test_addNeighbouringNode_NULL_input(void){
    initPartialNetworkMap();
    initNetworkNode(&nodeA ,"nodeA",&networkListA,1); //nodeA is marked
    initShortestPathNode(&sPathC,&nodeC ,NULL,0,0);
    initGraphPath(&gPath,NULL,NULL,0,&sPathC);
    Try{
        resetWorkingAVL();
        addNeighbouringNode(NULL);
        TEST_ASSERT_NULL(rootTreePathCost);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}
//////////////generateShortestPath/////////////////////////////////////////////////////
//generateShortestPath is function to generate shortestPath list with all details from source
// to all node
//
/**
*              (3)
*         (A)----- (B)
*        1 \     7 /
*           \    /
*            (C)------(D)
*                   2
**/
// A is marked
void test_generateShortestPath_expected_LinkedList_with_shortestPath(void){
    initPartialNetworkMap();
    //init expected ShortestPathNode
    initShortestPathNode(&sPathD,&nodeC ,&sPathC,2,2);
    initShortestPathNode(&sPathC,&nodeC ,NULL,0,0);
    initShortestPathNode(&sPathA,&nodeA ,&sPathC,1,1);
    initShortestPathNode(&sPathB,&nodeB ,&sPathA,3,4);
    Try{
        resetWorkingAVL();
        outLinkedList = generateShortestPath(&nodeC);
        outListItem= getCurrentListItem(outLinkedList);
        outSPathNode = outListItem->data;
        TEST_ASSERT_EQUAL_SHORTEST_PATH(outSPathNode,&nodeB,&sPathA,4,3);
        outListItem= getNextListItem(outLinkedList);
        outSPathNode = outListItem->data;
        TEST_ASSERT_EQUAL_SHORTEST_PATH(outSPathNode,&nodeD,&sPathC,2,2);
        outListItem= getNextListItem(outLinkedList);
        outSPathNode = outListItem->data;
        TEST_ASSERT_EQUAL_SHORTEST_PATH(outSPathNode,&nodeA,&sPathC,1,1);
        outListItem= getNextListItem(outLinkedList);
        outSPathNode = outListItem->data;
        TEST_ASSERT_EQUAL_SHORTEST_PATH(outSPathNode,&nodeC,NULL,0,0);
        outListItem= getNextListItem(outLinkedList);
        TEST_ASSERT_NULL(outListItem);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

/**
*              (3)       (1)
*         (A)----- (B) ----- (E)
*        1 \     7 / \ 5    /
*           \    /    \   /  (7)
*            (C)------(D)
*                   2
**/
void test_generateShortestPath_full_networkMap(void){
    initFullNetworkMap();
    //init expected ShortestPathNode
    initShortestPathNode(&sPathD,&nodeC ,&sPathC,2,2);
    initShortestPathNode(&sPathC,&nodeC ,NULL,0,0);
    initShortestPathNode(&sPathA,&nodeA ,&sPathC,1,1);
    initShortestPathNode(&sPathE,&nodeE ,&sPathB,5,1);
    initShortestPathNode(&sPathB,&nodeB ,&sPathA,4,3);
    Try{
        outLinkedList = generateShortestPath(&nodeC);
        outListItem= getCurrentListItem(outLinkedList);
        outSPathNode = outListItem->data;
        TEST_ASSERT_EQUAL_SHORTEST_PATH(outSPathNode,&nodeE,&sPathB,5,1);
        outListItem= getNextListItem(outLinkedList);
        outSPathNode = outListItem->data;
        TEST_ASSERT_EQUAL_SHORTEST_PATH(outSPathNode,&nodeB,&sPathA,4,3);
        outListItem= getNextListItem(outLinkedList);
        outSPathNode = outListItem->data;
        TEST_ASSERT_EQUAL_SHORTEST_PATH(outSPathNode,&nodeD,&sPathC,2,2);
        outListItem= getNextListItem(outLinkedList);
        outSPathNode = outListItem->data;
        TEST_ASSERT_EQUAL_SHORTEST_PATH(outSPathNode,&nodeA,&sPathC,1,1);
        outListItem= getNextListItem(outLinkedList);
        outSPathNode = outListItem->data;
        TEST_ASSERT_EQUAL_SHORTEST_PATH(outSPathNode,&nodeC,NULL,0,0);
        outListItem= getNextListItem(outLinkedList);
        TEST_ASSERT_NULL(outListItem);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}
void test_generateShortestPath_network_node_NULL(void){
    initFullNetworkMap();
    Try{
        outLinkedList = generateShortestPath(NULL);
        TEST_FAIL_MESSAGE("expecting exception to be thrown");
    }Catch(ex) {
        dumpException(ex);
        TEST_ASSERT_EQUAL(ERR_NETWORK_NODE_NULL,ex->errorCode);
    }
}
//////////////printShortestPathDetails/////////////////////////////////////////////////////
//printShortestPathDetails is function to print shortestPath details to users
/**
*              (3)       (1)
*         (A)----- (B) ----- (E)
*        1 \     7 / \ 5    /
*           \    /    \   /  (7)
*            (C)------(D)
*                   2
**/
void test_printShortestPathDetails(void){
    //init expected ShortestPathNode
    initShortestPathNode(&sPathD,&nodeC ,&sPathC,2,2);
    initShortestPathNode(&sPathC,&nodeC ,NULL,0,0);
    initShortestPathNode(&sPathA,&nodeA ,&sPathC,1,1);
    initShortestPathNode(&sPathE,&nodeE ,&sPathB,5,1);
    initShortestPathNode(&sPathB,&nodeB ,&sPathA,4,3);
    Try{
        printShortestPathDetails(&nodeC,&sPathE);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

void test_printShortestPathDetails_networkNode_NULL(void){
    //init expected ShortestPathNode
    initShortestPathNode(&sPathD,&nodeC ,&sPathC,2,2);
    initShortestPathNode(&sPathC,&nodeC ,NULL,0,0);
    initShortestPathNode(&sPathA,&nodeA ,&sPathC,1,1);
    initShortestPathNode(&sPathE,&nodeE ,&sPathB,5,1);
    initShortestPathNode(&sPathB,&nodeB ,&sPathA,4,3);
    Try{
        printShortestPathDetails(NULL,&sPathE);
        TEST_FAIL_MESSAGE("expecting exception to be thrown");
    }Catch(ex) {
        dumpException(ex);
        TEST_ASSERT_EQUAL(ERR_NETWORK_NODE_NULL,ex->errorCode);
    }
}

void test_printShortestPathDetails_Spath_NULL(void){
    //init expected ShortestPathNode
    initShortestPathNode(&sPathD,&nodeC ,&sPathC,2,2);
    initShortestPathNode(&sPathC,&nodeC ,NULL,0,0);
    initShortestPathNode(&sPathA,&nodeA ,&sPathC,1,1);
    initShortestPathNode(&sPathE,&nodeE ,&sPathB,5,1);
    initShortestPathNode(&sPathB,&nodeB ,&sPathA,4,3);
    Try{
        printShortestPathDetails(&nodeC,NULL);
        TEST_FAIL_MESSAGE("expecting exception to be thrown");
    }Catch(ex) {
        dumpException(ex);
        TEST_ASSERT_EQUAL(ERR_SPATH_NULL,ex->errorCode);
    }
}

//////////////findShortestPath/////////////////////////////////////////////////////
//findShortestPath is main function to find shortestPath from the source to destination node
/**
*              (3)       (1)
*         (A)----- (B) ----- (E)
*        1 \     7 / \ 5    /
*           \    /    \   /  (7)
*            (C)------(D)
*                   2
**/
//From source C to nodeB
void test_findShortestPath(void){
    initFullNetworkMap();
    Try{
        findShortestPath(&nodeC,"nodeB");
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }

}
/**
*              (3)       (1)
*         (A)----- (B) ----- (E)
*        1 \     7 / \ 5    /
*           \    /    \   /  (7)
*            (C)------(D)
*                   2
**/
void test_findShortestPath_differentSource(void){
    initFullNetworkMap();
    Try{
        findShortestPath(&nodeE,"nodeC");
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}
/**
*                  ( F )
*              6 /     \ 8
*            ( D )      ( E )
*             | 2 \   4 /  |
*         10  |   ( C )    | 1
*            | 2 /   5 \  |
*           (A) ------- (B)
*                 1
**/
  void test_findShortestPath_complex_map(void){
      initComplexNetworkMap();
      Try{
          findShortestPath(&nodeA,"nodeF");
      }Catch(ex) {
          dumpException(ex);
          TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
      }
  }

void test_findShortestPath_network_node_NULL(void){
    initFullNetworkMap();
    Try{
        findShortestPath(NULL,"nodeC");
        TEST_FAIL_MESSAGE("expecting exception to be thrown");
    }Catch(ex) {
        dumpException(ex);
        TEST_ASSERT_EQUAL(ERR_NETWORK_NODE_NULL,ex->errorCode);
    }
}

void test_findShortestPath_dst_name_NULL(void){
    initFullNetworkMap();
    Try{
        findShortestPath(&nodeE,NULL);
        TEST_FAIL_MESSAGE("expecting exception to be thrown");
    }Catch(ex) {
        dumpException(ex);
        TEST_ASSERT_EQUAL(ERR_DST_NAME_NULL,ex->errorCode);
    }
}
//////////////printPathCostFromShortestPath/////////////////////////////////////////////////////
//printPathCostFromShortestPath is function to print shortestPath path Cost

void test_printPathCostFromShortestPath(void){
    initFullNetworkMap();
    initShortestPathNode(&sPathA,&nodeA ,NULL,2,1);
    ListItem * item;
    item->data = (void*)&sPathA;
    Try{
        printPathCostFromShortestPath(item);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

void test_printPathCostFromShortestPath_listItem_name_NULL(void){
    Try{
        printPathCostFromShortestPath(NULL);
        TEST_FAIL_MESSAGE("expecting exception to be thrown");
    }Catch(ex) {
        dumpException(ex);
        TEST_ASSERT_EQUAL(ERR_SPATH_LIST_ITEM_NULL,ex->errorCode);
    }
}
//////////////findAllShortestPathCost/////////////////////////////////////////////////////
//findAllShortestPathCost is function to find all shortestPath path Cost and print

void test_findAllShortestPathCost(void){
    initFullNetworkMap();
    Try{
        findAllShortestPathCost(&nodeC);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }

}
/**
*                  ( F )
*              6 /     \ 8
*            ( D )      ( E )
*             | 2 \   4 /  |
*         10  |   ( C )    | 1
*            | 2 /   5 \  |
*           (A) ------- (B)
*                 1
**/
void test_findAllShortestPathCost_complex_map(void){
    initComplexNetworkMap();
    Try{
        findAllShortestPathCost(&nodeA);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }

}
