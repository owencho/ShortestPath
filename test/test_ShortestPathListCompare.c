#include "unity.h"
#include "ShortestPathListCompare.h"
#include "unity.h"
#include "GraphCompare.h"
#include "GraphPath.h"
#include "Node.h"
#include "NetworkNode.h"
#include "List.h"
#include "LinkedListCompare.h"
ShortestPathNode sPathRoot,sPathNode;
NetworkNode nodeA,nodeB,nodeC,nodeD;
ListItem listItem;
void setUp(void){}
void tearDown(void){}

void initNetworkNode(NetworkNode * node, char*name,List * links,int marked){
    node->name = name;
    node-> links = links;
    node->marked = marked;
}
void initShortestPathNode(ShortestPathNode *sPath,NetworkNode * id ,ShortestPathNode * parent ,int pathCost ,int linkCost){
    sPath->id = id;
    sPath->parent = parent;
    sPath->pathCost = pathCost;
    sPath->linkCost = linkCost;
}
void test_ShortestPathListCompare_input_same_name(void){
    LinkedListCompare compare = (LinkedListCompare)shortestPathListCompare;
    initNetworkNode(&nodeA ,"nodeA",NULL,0);
    initShortestPathNode(&sPathRoot,&nodeA ,NULL,1,1);
    listItem.data = (void*)&sPathRoot;
    TEST_ASSERT_EQUAL(1,(compare(&listItem,"nodeA")));
}

void test_ShortestPathListCompare_input_different_name(void){
    LinkedListCompare compare = (LinkedListCompare)shortestPathListCompare;
    initNetworkNode(&nodeA ,"nodeA",NULL,0);
    initNetworkNode(&nodeB ,"nodeB",NULL,0);
    initShortestPathNode(&sPathRoot,&nodeB ,NULL,1,1);
    listItem.data = (void*)&sPathRoot;
    TEST_ASSERT_EQUAL(0,(compare(&listItem,"nodeA")));
}
