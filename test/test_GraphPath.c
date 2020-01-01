#include "unity.h"
#include "GraphPath.h"
#include "List.h"
#include "ListItem.h"
#include "NetworkNode.h"
NetworkNode nodeA,nodeB;
ListItem itemA;
List linkListA;
Link  listItemDataA;
Link *outLink;
ShortestPath sPath;
ShortestPath *shortestPath;
void setUp(void){}
void tearDown(void){}

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
void test_createShortestPath(void){
    initLink(&listItemDataA,0,&nodeA ,&nodeB);
    initList(&linkListA, &itemA ,&itemA,1 ,&itemA);
    shortestPath = createShortestPath(&listItemDataA,&linkListA);
    TEST_ASSERT_EQUAL_PTR(&nodeA,shortestPath->dst);
    TEST_ASSERT_EQUAL_PTR(&nodeB,shortestPath->src);
    TEST_ASSERT_EQUAL(0,shortestPath->pathCost);
    TEST_ASSERT_EQUAL_PTR(&linkListA,shortestPath->pathLinks);
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

void test_createLinkListForShortestPath(void){
    List* outLinkList;
    ListItem* listItem;
    NetworkNode * node1 ;
    NetworkNode * node2;
    outLinkList = createLinkListForShortestPath(node1,node2,1);
    listItem = getNextListItem(outLinkList);
    outLink = (Link*)listItem;
    TEST_ASSERT_EQUAL_PTR(node1,outLink->head);
    TEST_ASSERT_EQUAL_PTR(node2,outLink->tail);
    TEST_ASSERT_EQUAL(1,outLink->cost);
    listItem = getNextListItem(outLinkList);
    TEST_ASSERT_NULL(outLinkList);
}
