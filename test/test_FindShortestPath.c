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
#include "Error.h"
#include "NetworkNode.h"
#include "List.h"
#include "ListItem.h"
#include "ShortestPathNode.h"
#include "GraphPath.h"
#include "GraphPathAVL.h"
#include "GraphCompare.h"
#include "CustomAssert.h"

ShortestPathNode sPathA ,sPathB,sPathC,sPathD;
Link linkItemDataCD,linkItemDataCA,linkItemDataCB;
Link linkItemDataAC,linkItemDataAB;
Link linkItemDataBC,linkItemDataBA;
Link linkItemDataDC;
ListItem listItemCD,listItemCA,listItemCB;
ListItem listItemAC,listItemAB;
ListItem listItemBC,listItemBA;
ListItem listItemDC;
NetworkNode nodeA ,nodeB,nodeC,nodeD;
ShortestPathNode * outSPathNode;
List networkListC,networkListA,networkListB,networkListD;
List shortestPathList;
List * outLinkList;
ListItem * outListItem;
GraphPath * listGraphPath;
GraphPath * graphPathNode;
GraphPath gPath;
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
    initLink(&linkItemDataCB,2,&nodeB ,&nodeC);
    initLink(&linkItemDataCD,7,&nodeD,&nodeC);
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
*              (3)                               compares with sPathD
*         (A)----- (B)                   (A)2     with nodeC id        (A)2
*        1 \     7 /                    /   \   ---------------->     /  |
*           \    /                    (B)1  (C)3                   (B)1 |
*            (C)------(D)                                              (C)2
*                   2
**/
void test_compareAndAddShortestPathIntoWorkingAVL_smaller_path(void){
    initNetworkNode(&nodeA ,"nodeA",NULL,0);
    initNetworkNode(&nodeB ,"nodeB",NULL,0);
    initNetworkNode(&nodeC ,"nodeC",NULL,0);
    initShortestPathNode(&sPathD,&nodeC ,&sPathB,2,2);
    initShortestPathNode(&sPathC,&nodeC ,&sPathA,3,3);
    initShortestPathNode(&sPathA,&nodeA ,NULL,1,2);
    initShortestPathNode(&sPathB,&nodeB ,NULL,1,1);

    Try{
        resetWorkingAVL();
        addGraphPathIntoWorkingAVL(&sPathC);
        addGraphPathIntoWorkingAVL(&sPathA);
        addGraphPathIntoWorkingAVL(&sPathB);
        graphPathNode=(GraphPath*)compareAndAddShortestPathIntoWorkingAVL(&sPathD);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeA,NULL,2,2);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->left->sPath,&nodeB,NULL,1,1);
        TEST_ASSERT_NULL(graphPathNode->right);

        outListItem= getCurrentListItem(graphPathNode->listWithSameCost);
        listGraphPath = outListItem->data;
        TEST_ASSERT_EQUAL_SHORTEST_PATH(listGraphPath->sPath,&nodeC,&sPathB,2,2);
        outListItem= getNextListItem(graphPathNode->listWithSameCost);
        TEST_ASSERT_NULL(outListItem);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}
/**
*              (3)                               compares with sPathD
*         (A)----- (B)                   (A)2     with nodeC id        (A)2
*        1 \     7 /                    /   \   ---------------->     /   \
*           \    /                    (B)1  (C)3                   (B)1  (C)3
*            (C)------(D)
*                   2
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
        graphPathNode=(GraphPath*)compareAndAddShortestPathIntoWorkingAVL(&sPathD);
        TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeC,NULL,3,3);
        TEST_ASSERT_NULL(graphPathNode->left);
        TEST_ASSERT_NULL(graphPathNode->right);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}
/**                                              (nodeB) is marked
*              (3)                               compares with sPathB
*         (A)----- (B)                   (A)2     with nodeB id        (A)2
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
        graphPathNode=(GraphPath*)compareAndAddShortestPathIntoWorkingAVL(&sPathB);
        TEST_ASSERT_NULL(graphPathNode);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

/**
*              (3)
*         (A)----- (B)                         (D)2
*        1 \     7 /        -------->         /   \
*           \    /                          (A)1  (B)7
*            (C)------(D)
*                   2
**/
void test_findAndAddNearestNode_initial(void){
    initPartialNetworkMap();
    initShortestPathNode(&sPathC,&nodeC ,NULL,0,0);
    initGraphPath(&gPath,NULL,NULL,0,&sPathC);
    Try{
        resetWorkingAVL();
        findAndAddNearestNode(&gPath);
      //  TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeB,NULL,1,1);
        //TEST_ASSERT_NULL(graphPathNode->left);
      //  TEST_ASSERT_NULL(graphPathNode->right);
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
void test_findAndAddNearestNode_one_of_the_path_is_marked(void){
    initPartialNetworkMap();
    initNetworkNode(&nodeA ,"nodeA",&networkListA,1); //nodeA is marked
    initShortestPathNode(&sPathC,&nodeC ,NULL,0,0);
    initGraphPath(&gPath,NULL,NULL,0,&sPathC);
    Try{
        resetWorkingAVL();
        findAndAddNearestNode(&gPath);
      //  TEST_ASSERT_EQUAL_SHORTEST_PATH(graphPathNode->sPath,&nodeB,NULL,1,1);
        //TEST_ASSERT_NULL(graphPathNode->left);
      //  TEST_ASSERT_NULL(graphPathNode->right);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

/**
*              (3)
*         (A)----- (B)
*        1 \     7 /
*           \    /
*            (C)------(D)
*                   2
**/
// A is marked
void test_generateShortestPath_expected_linkList_with_graphPath(void){
    initPartialNetworkMap();
    Try{
        resetWorkingAVL();
        outLinkList = generateShortestPath(&nodeC);
        resetWorkingAVL();

        outListItem= getCurrentListItem(outLinkList);
        outSPathNode = outListItem->data;
        TEST_ASSERT_EQUAL_SHORTEST_PATH(outSPathNode,&nodeB,&sPathA,4,3);
        outListItem= getNextListItem(outLinkList);
        outSPathNode = outListItem->data;
        TEST_ASSERT_EQUAL_SHORTEST_PATH(outSPathNode,&nodeD,&sPathC,2,2);
        outListItem= getNextListItem(outLinkList);
        outSPathNode = outListItem->data;
        TEST_ASSERT_EQUAL_SHORTEST_PATH(outSPathNode,&nodeA,&sPathC,1,1);
        outListItem= getNextListItem(outLinkList);
        outSPathNode = outListItem->data;
        TEST_ASSERT_EQUAL_SHORTEST_PATH(outSPathNode,&nodeC,NULL,0,0);
        outListItem= getNextListItem(outLinkList);
        outSPathNode = outListItem->data;
        TEST_ASSERT_NULL(outListItem);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

/**
*              (3)
*         (A)----- (B)
*        1 \     7 /
*           \    /
*            (C)------(D)
*                   2
**/
// A is marked
void test_generateShortestPath_full_networkMap(void){
    initPartialNetworkMap();
    Try{
        resetWorkingAVL();
        outLinkList = generateShortestPath(&nodeC);
        resetWorkingAVL();

        outListItem= getCurrentListItem(outLinkList);
        outSPathNode = outListItem->data;
        TEST_ASSERT_EQUAL_SHORTEST_PATH(outSPathNode,&nodeB,&sPathA,4,3);
        outListItem= getNextListItem(outLinkList);
        outSPathNode = outListItem->data;
        TEST_ASSERT_EQUAL_SHORTEST_PATH(outSPathNode,&nodeD,&sPathC,2,2);
        outListItem= getNextListItem(outLinkList);
        outSPathNode = outListItem->data;
        TEST_ASSERT_EQUAL_SHORTEST_PATH(outSPathNode,&nodeA,&sPathC,1,1);
        outListItem= getNextListItem(outLinkList);
        outSPathNode = outListItem->data;
        TEST_ASSERT_EQUAL_SHORTEST_PATH(outSPathNode,&nodeC,NULL,0,0);
        outListItem= getNextListItem(outLinkList);
        outSPathNode = outListItem->data;
        TEST_ASSERT_NULL(outListItem);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}
