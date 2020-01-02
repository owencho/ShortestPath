#include "unity.h"
#include "GraphCompare.h"
#include "GraphPath.h"
#include "Node.h"
#include "NetworkNode.h"
#include "List.h"
#include "Compare.h"

NetworkNode nodeA , nodeB;
ShortestPath sPathRoot ,sPathNode;
GraphPath root,inputNode;
GraphPath * inNode;
List * pathLinks;
void setUp(void){}

void tearDown(void){}

void initShortestPath(ShortestPath *sPath,NetworkNode * dst ,NetworkNode * src ,double pathCost ,List * pathLinks){
    sPath->dst = dst;
    sPath->src = src;
    sPath->pathCost = pathCost;
    sPath->pathLinks = pathLinks;
}
void initNetworkNode(NetworkNode * node, char*name,List * links,int marked){
    node->name = name;
    node-> links = links;
    node->marked = marked;
}
void test_graphCompareForPathCostAvlAdd_input_larger_node(void){
    Compare compare = (Compare)graphCompareForPathCostAvlAdd;
    initShortestPath(&sPathRoot,NULL ,NULL,1,pathLinks);
    initShortestPath(&sPathNode,NULL ,NULL,2,pathLinks);
    root.sPath = &sPathRoot;
    inputNode.sPath = &sPathNode;
    inNode = &inputNode;
    TEST_ASSERT_EQUAL(-1,(compare((Node*)&root,(void *)inNode)));
}

void test_graphCompareForPathCostAvlAdd_input_smaller_node(void){
    Compare compare = (Compare)graphCompareForPathCostAvlAdd;
    initShortestPath(&sPathRoot,NULL ,NULL,2,pathLinks);
    initShortestPath(&sPathNode,NULL ,NULL,1,pathLinks);
    root.sPath = &sPathRoot;
    inputNode.sPath = &sPathNode;
    inNode = &inputNode;
    TEST_ASSERT_EQUAL(1,(compare((Node*)&root,(void *)inNode)));
}

void test_graphCompareForPathCostAvlAdd_input_same_node(void){
    Compare compare = (Compare)graphCompareForPathCostAvlAdd;
    initShortestPath(&sPathRoot,NULL ,NULL,1,pathLinks);
    initShortestPath(&sPathNode,NULL ,NULL,1,pathLinks);
    root.sPath = &sPathRoot;
    inputNode.sPath = &sPathNode;
    inNode = &inputNode;
    TEST_ASSERT_EQUAL(0,(compare((Node*)&root,(void *)inNode)));
}

void test_graphCompareForNameAvlAdd_input_larger_node(void){
    Compare compare = (Compare)graphCompareForNameAvlAdd;
    initNetworkNode(&nodeA,"nodeA",NULL,0);
    initNetworkNode(&nodeB,"nodeB",NULL,0);
    initShortestPath(&sPathRoot,&nodeA ,NULL,1,pathLinks);
    initShortestPath(&sPathNode,&nodeB ,NULL,2,pathLinks);
    root.sPath = &sPathRoot;
    inputNode.sPath = &sPathNode;
    inNode = &inputNode;
    TEST_ASSERT_EQUAL(-1,(compare((Node*)&root,(void *)inNode)));
}

void test_graphCompareForNameAvlAdd_input_smaller_node(void){
    Compare compare = (Compare)graphCompareForNameAvlAdd;
    initNetworkNode(&nodeA,"nodeA",NULL,0);
    initNetworkNode(&nodeB,"nodeB",NULL,0);
    initShortestPath(&sPathRoot,&nodeB ,NULL,2,pathLinks);
    initShortestPath(&sPathNode,&nodeA ,NULL,1,pathLinks);
    root.sPath = &sPathRoot;
    inputNode.sPath = &sPathNode;
    inNode = &inputNode;
    TEST_ASSERT_EQUAL(1,(compare((Node*)&root,(void *)inNode)));
}

void test_graphCompareForNameAvlAdd_input_same_node(void){
    Compare compare = (Compare)graphCompareForNameAvlAdd;
    initNetworkNode(&nodeA,"nodeA",NULL,0);
    initNetworkNode(&nodeB,"nodeB",NULL,0);
    initShortestPath(&sPathRoot,&nodeA ,NULL,1,pathLinks);
    initShortestPath(&sPathNode,&nodeA ,NULL,1,pathLinks);
    root.sPath = &sPathRoot;
    inputNode.sPath = &sPathNode;
    inNode = &inputNode;
    TEST_ASSERT_EQUAL(0,(compare((Node*)&root,(void *)inNode)));
}

void test_graphCompareForPathCost_input_larger_node(void){
    Compare compare = (Compare)graphCompareForPathCost;
    initShortestPath(&sPathRoot,NULL ,NULL,1,pathLinks);
    initShortestPath(&sPathNode,NULL ,NULL,2,pathLinks);
    root.sPath = &sPathRoot;
    inputNode.sPath = &sPathNode;
    inNode = &inputNode;
    TEST_ASSERT_EQUAL(-1,(compare((Node*)&root,(void *)&inNode->sPath->pathCost)));
}

void test_graphCompareForPathCost_input_smaller_node(void){
    Compare compare = (Compare)graphCompareForPathCost;
    initShortestPath(&sPathRoot,NULL ,NULL,2,pathLinks);
    initShortestPath(&sPathNode,NULL ,NULL,1,pathLinks);
    root.sPath = &sPathRoot;
    inputNode.sPath = &sPathNode;
    inNode = &inputNode;
    TEST_ASSERT_EQUAL(1,(compare((Node*)&root,(void *)&inNode->sPath->pathCost)));
}

void test_graphCompareForPathCost_input_same_node(void){
    Compare compare = (Compare)graphCompareForPathCost;
    initShortestPath(&sPathRoot,NULL ,NULL,1,pathLinks);
    initShortestPath(&sPathNode,NULL ,NULL,1,pathLinks);
    root.sPath = &sPathRoot;
    inputNode.sPath = &sPathNode;
    inNode = &inputNode;
    TEST_ASSERT_EQUAL(0,(compare((Node*)&root,(void *)&inNode->sPath->pathCost)));
}

void test_graphCompareForName_input_larger_node(void){
    Compare compare = (Compare)graphCompareForName;
    initNetworkNode(&nodeA,"nodeA",NULL,0);
    initNetworkNode(&nodeB,"nodeB",NULL,0);
    initShortestPath(&sPathRoot,&nodeA ,NULL,1,pathLinks);
    initShortestPath(&sPathNode,&nodeB ,NULL,2,pathLinks);
    root.sPath = &sPathRoot;
    inputNode.sPath = &sPathNode;
    inNode = &inputNode;
    TEST_ASSERT_EQUAL(-1,(compare((Node*)&root,(void *)inNode->sPath->dst->name)));
}

void test_graphCompareForName_input_smaller_node(void){
    Compare compare = (Compare)graphCompareForName;
    initNetworkNode(&nodeA,"nodeA",NULL,0);
    initNetworkNode(&nodeB,"nodeB",NULL,0);
    initShortestPath(&sPathRoot,&nodeB ,NULL,2,pathLinks);
    initShortestPath(&sPathNode,&nodeA ,NULL,1,pathLinks);
    root.sPath = &sPathRoot;
    inputNode.sPath = &sPathNode;
    inNode = &inputNode;
    TEST_ASSERT_EQUAL(1,(compare((Node*)&root,(void *)inNode->sPath->dst->name)));
}

void test_graphCompareForName_input_same_node(void){
    Compare compare = (Compare)graphCompareForName;
    initNetworkNode(&nodeA,"nodeA",NULL,0);
    initNetworkNode(&nodeB,"nodeB",NULL,0);
    initShortestPath(&sPathRoot,&nodeA ,NULL,1,pathLinks);
    initShortestPath(&sPathNode,&nodeA ,NULL,1,pathLinks);
    root.sPath = &sPathRoot;
    inputNode.sPath = &sPathNode;
    inNode = &inputNode;
    TEST_ASSERT_EQUAL(0,(compare((Node*)&root,(void *)inNode->sPath->dst->name)));
}
