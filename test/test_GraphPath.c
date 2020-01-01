#include "unity.h"
#include "GraphPath.h"
void setUp(void){}
void tearDown(void){}

void initGraphPath(GraphPath*graphPath,GraphPath*left,GraphPath*right,int bFactor, ShortestPath * value){
    graphPath->left = left;
    graphPath->right = right;
    graphPath->bFactor = bFactor;
    graphPath->value = value;
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

void test_createShortestPath(void){
    NetworkNode nodeA;
    ListItem itemA;
    List linkListPathA;
    Link  listItemDataA;
    ShortestPath sPath;
    initLink(&listItemDataA,0,&nodeA ,&nodeA);
    initList(&linkListA, &itemA ,NULL,1 ,&itemA);
    initShortestPath(&sPath,&nodeA ,&nodeA,0,&linkListPathA);
    graphPathNode = createGraphPath(&sPath);
    TEST_ASSERT_NULL(graphPathNode->left);
    TEST_ASSERT_NULL(graphPathNode->right);
}
/*
void test_createGraphPath(void){
    GraphPath graphPathNode;
    NetworkNode nodeA ,nodeC;
    graphPathNode = createGraphPath(ShortestPath * value );
}
*/
