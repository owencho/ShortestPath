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
#include "ShortestPath.h"
#include "GraphPath.h"
#include "GraphCompare.h"
Node* root;
GraphPath*smallestNode;
NetworkNode nodeA ,nodeB,nodeC,nodeD;
Link linkItemDataA,linkItemDataD,linkItemDataB;
ListItem itemA,itemB ,itemD;
List linkList;
void setUp(void){}
void tearDown(void){}

void initNetworkNode(NetworkNode * node, char*name,List * links,int marked){
    node->name = name;
    node-> links = links;
    node->marked = marked;
}
void initList(List * link, ListItem * head ,ListItem * tail ,int count ,ListItem * current){
    link->head = head;
    link->tail = tail;
    link->count = count;
    link->current = current;
}
void initListItem(ListItem * listItem, ListItem * next ,void* data){
    listItem->next = next;
    listItem->data = data;
}
void initlinkItemData(Link * linkItemData,NetworkNode * head ,NetworkNode * tail,int cost  ){
    linkItemData->head = head;
    linkItemData->tail = tail;
    linkItemData->cost = cost;
}

/**
*
*         (A)      (B)                         (2)d
*        1 \     7 /                          /   \
*           \    /            ------>      (1)a   (7)B
*            (C)------(D)
*                   2
**/
//all node without flag
void test_getNearestNode(void){
    List  pathDC, pathAC ,pathBC;
    //create NetworkNode
    initNetworkNode(&nodeC,"nodeC",&linkList,0);
    initNetworkNode(&nodeA,"nodeA",&linkList,0);
    initNetworkNode(&nodeB,"nodeB",&linkList,0);
    initNetworkNode(&nodeD,"nodeD",&linkList,0);
    //init ShortestPath
    initlinkItemData(&linkItemDataA,&nodeA ,&nodeC,1 );
    initlinkItemData(&linkItemDataD,&nodeD ,&nodeC,2 );
    initlinkItemData(&linkItemDataB,&nodeB ,&nodeC,7 );
    //create List Item
    initListItem(&itemA, &itemB ,(void*)&linkItemDataA);
    initListItem(&itemB, &itemD ,(void*)&linkItemDataD);
    initListItem(&itemD, NULL ,(void*)&linkItemDataB);
    //init the Link List
    initList(&linkList, &itemA,&itemD ,0,&itemA);


    root=findNearestNode(&nodeC);  //function
    smallestNode=(GraphPath*)avlRemoveSmallest(root,(Compare)graphCompare);
    TEST_ASSERT_EQUAL(1,smallestNode->value->pathCost);
    TEST_ASSERT_EQUAL_PTR(&nodeA,smallestNode->value->dst);
    TEST_ASSERT_EQUAL_PTR(&nodeC,smallestNode->value->src);
    TEST_ASSERT_EQUAL_PTR(&pathAC,smallestNode->value->pathLinks);

    smallestNode=(GraphPath*)avlRemoveSmallest(root,(Compare)graphCompare);
    TEST_ASSERT_EQUAL(2,smallestNode->value->pathCost);
    TEST_ASSERT_EQUAL_PTR(&nodeD,smallestNode->value->dst);
    TEST_ASSERT_EQUAL_PTR(&nodeC,smallestNode->value->src);
    TEST_ASSERT_EQUAL_PTR(&pathDC,smallestNode->value->pathLinks);

    smallestNode=(GraphPath*)avlRemoveSmallest(root,(Compare)graphCompare);
    TEST_ASSERT_EQUAL(7,smallestNode->value->pathCost);
    TEST_ASSERT_EQUAL_PTR(&nodeB,smallestNode->value->dst);
    TEST_ASSERT_EQUAL_PTR(&nodeC,smallestNode->value->src);
    TEST_ASSERT_EQUAL_PTR(&pathBC,smallestNode->value->pathLinks);

    TEST_ASSERT_NULL(root);
}

/**
*
*         (A)      (B)                         (2)d
*        1 \     7 /                          /   \
*           \    /            ------>      (1)a   (7)B
*            (C)------(D)
*                   2
**/
//B with the flag
/*
void test_getNearestNode_withB_Flag(void){
    List  pathDC, pathAC ,pathBC;
    //create NetworkNode
    initNetworkNode(&nodeC,"nodeC",&linkList,0);
    initNetworkNode(&nodeA,"nodeA",&linkList,0);
    initNetworkNode(&nodeB,"nodeB",&linkList,1);
    initNetworkNode(&nodeD,"nodeD",&linkList,0);
    //init ShortestPath
    initShortestPath(&sPathA,&nodeA ,&nodeC,1 ,&pathAC);
    initShortestPath(&sPathD,&nodeD ,&nodeC,2 ,&pathDC);
    initShortestPath(&sPathB,&nodeB ,&nodeC,7 ,&pathBC);
    //create List Item
    initListItem(&itemA, &itemB ,(void*)&sPathA);
    initListItem(&itemB, &itemD ,(void*)&sPathB);
    initListItem(&itemD, NULL ,(void*)&sPathD);
    //init the Link List
    initList(&linkList, &itemA,&itemD ,0,&itemA);


    root=shortestPath(&nodeC);  //function
    outNode=avlRemoveSmallest(root,(Compare)graphCompare);
    TEST_ASSERT_EQUAL(1,smallestNode->value->pathCost);
    TEST_ASSERT_EQUAL_PTR(&nodeA,smallestNode->value->dst);
    TEST_ASSERT_EQUAL_PTR(&nodeC,smallestNode->value->src);
    TEST_ASSERT_EQUAL_PTR(&pathAC,smallestNode->value->pathLinks);

    smallestNode=avlRemoveSmallest(root,(Compare)graphCompare);
    TEST_ASSERT_EQUAL(2,smallestNode->value->pathCost);
    TEST_ASSERT_EQUAL_PTR(&nodeD,smallestNode->value->dst);
    TEST_ASSERT_EQUAL_PTR(&nodeC,smallestNode->value->src);
    TEST_ASSERT_EQUAL_PTR(&pathDC,smallestNode->value->pathLinks);

    TEST_ASSERT_NULL(root);
}
*/
