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

ShortestPath sPath ,sPathD, sPathB;
GraphPath* root;
GraphPath inNode;
NetworkNode nodeA ,nodeB,nodeC,nodeD;
Link linkItemDataA,linkItemDataD,linkItemDataB;
ListItem itemA,itemB ,itemD;
List linkList,pathDC, pathAC ,pathBC;



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
void initlinkItemData(Link * linkItemData,NetworkNode * head ,NetworkNode * tail,int cost){
    linkItemData->head = head;
    linkItemData->tail = tail;
    linkItemData->cost = cost;
}
void initShortestPath(ShortestPath *sPath,NetworkNode * dst ,NetworkNode * src ,double pathCost ,List * pathLinks){
    sPath->dst = dst;
    sPath->src = src;
    sPath->pathCost = pathCost;
    sPath->pathLinks = pathLinks;
}
void initGraphPath(GraphPath*graphPath,GraphPath*left,GraphPath*right,int bFactor, ShortestPath * value){
    graphPath->left = left;
    graphPath->right = right;
    graphPath->bFactor = bFactor;
    graphPath->value = value;
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

    sPath.pathCost = 0; //fake inNode as nodeC
    inNode.value = &sPath;
    root=findNearestNode(&inNode,&nodeC);  //function
    root=(GraphPath*)avlRemoveSmallest((Node*)root,(Compare)graphCompare);
    TEST_ASSERT_EQUAL(1,root->value->pathCost);
    TEST_ASSERT_EQUAL_PTR(&nodeA,root->value->dst);
    TEST_ASSERT_EQUAL_PTR(&nodeC,root->value->src);
    TEST_ASSERT_EQUAL_PTR(&pathAC,root->value->pathLinks);

    root=(GraphPath*)avlRemoveSmallest((Node*)root,(Compare)graphCompare);
    TEST_ASSERT_EQUAL(2,root->value->pathCost);
    TEST_ASSERT_EQUAL_PTR(&nodeD,root->value->dst);
    TEST_ASSERT_EQUAL_PTR(&nodeC,root->value->src);
    TEST_ASSERT_EQUAL_PTR(&pathDC,root->value->pathLinks);

    root=(GraphPath*)avlRemoveSmallest((Node*)root,(Compare)graphCompare);
    TEST_ASSERT_EQUAL(7,root->value->pathCost);
    TEST_ASSERT_EQUAL_PTR(&nodeB,root->value->dst);
    TEST_ASSERT_EQUAL_PTR(&nodeC,root->value->src);
    TEST_ASSERT_EQUAL_PTR(&pathBC,root->value->pathLinks);

    TEST_ASSERT_NULL(root);
}

/**
*
*         (A)      (B)                         (2)d
*        1 \     7 /                          /
*           \    /            ------>      (1)a
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

    sPath.pathCost = 0; //fake inNode as nodeC
    inNode.value = &sPath;
    root=findNearestNode(&inNode,&nodeC);  //function
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

/**
*              3
*         (A)------(B)                         (2)d           (2)d
*        1 \     7 /                              \    ---->   \
*           \    /                                (7)B         (4)b
*            (C)------(D)
*                   2
**/
//C is flagged
/*
void test_compareShortestPath(void){
NetworkNode nodeA ,nodeB,nodeC,nodeD;
ShortestPath sPath ,sPathD, sPathB;
GraphPath gPathB,gPathD;
List  pathLinkCD,pathLinkCB,pathLinkCAB;
ListItem listItemCA,listItemCB,listItemCD,listItemAB;
Link linkCA,linkCB,linkCD,linkAB;
GraphPath* root;
    //create GraphPath
    initShortestPath(&sPathD,&nodeD,&nodeC,2,&pathLinkCD);
    initGraphPath(&gPathD,NULL,&gPathB,1,&sPathD);
    initShortestPath(&sPathB,&nodeB,&nodeC,7,&pathLinkCB);
    initGraphPath(&gPathB,NULL,NULL,0,&sPathB);
    //init listItem
    initListItem(&listItemCA, &listItemAB,(void*)&linkCA);
    initListItem(&listItemCB, NULL,(void*)&linkCB);
    initListItem(&listItemCD, NULL,(void*)&linkCD);
    initListItem(&listItemAB, NULL,(void*)&linkAB);
    // init List
    initList(&pathLinkCB,&listItemCB ,&listItemCB ,1 ,&listItemCB);
    initList(&pathLinkCD,&listItemCD ,&listItemCD ,1 ,&listItemCD);
    initList(&pathLinkCAB,&listItemCA ,&listItemAB ,2 ,&listItemCA);  //expected output
    // init link item
    initlinkItemData(&linkAB,&nodeB,&nodeA,3);
    initlinkItemData(&linkCA,&nodeA,&nodeC,1);
    initlinkItemData(&linkCB,&nodeB,&nodeC,7);
    initlinkItemData(&linkCD,&nodeD,&nodeC,2);
    //expected path


    root=compareShortestPath(&gPathD,&nodeA);
    root=(GraphPath*)avlRemoveSmallest((Node*)root,(Compare)graphCompare);
    TEST_ASSERT_EQUAL(2,root->value->pathCost);
    TEST_ASSERT_EQUAL_PTR(&nodeD,root->value->dst);
    TEST_ASSERT_EQUAL_PTR(&nodeC,root->value->src);
    TEST_ASSERT_EQUAL_PTR(&pathLinkCD,root->value->pathLinks);

    root=(GraphPath*)avlRemoveSmallest((Node*)root,(Compare)graphCompare);
    TEST_ASSERT_EQUAL(4,root->value->pathCost);
    TEST_ASSERT_EQUAL_PTR(&nodeB,root->value->dst);
    TEST_ASSERT_EQUAL_PTR(&nodeC,root->value->src);
    TEST_ASSERT_EQUAL_PTR(&pathLinkCAB,root->value->pathLinks);

    TEST_ASSERT_NULL(root);
}
*/
/**
*              3
*         (A)------(B)                         (2)d           (2)d
*        1 \     7 /                              \    ---->   \
*           \    /                                (7)B         (4)b
*            (C)------(D)
*                   2
**/
//C is flagged

void test_findGraphPath(void){
NetworkNode nodeA ,nodeB,nodeC,nodeD;
ShortestPath sPath ,sPathD, sPathB;
GraphPath gPathB,gPathD;
GraphPath* root;
    //create GraphPath
    initShortestPath(&sPathD,&nodeD,&nodeC,2,NULL);
    initGraphPath(&gPathD,NULL,&gPathB,1,&sPathD);
    initShortestPath(&sPathB,&nodeB,&nodeC,7,NULL);
    initGraphPath(&gPathB,NULL,NULL,0,&sPathB);

    root=findGraphPath(&gPathD,&nodeB);
    TEST_ASSERT_EQUAL_PTR(&gPathB,root);
}
