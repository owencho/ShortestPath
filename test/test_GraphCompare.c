#include "unity.h"
#include "GraphCompare.h"
#include "GraphPath.h"
#include "Node.h"
#include "NetworkNode.h"
#include "List.h"
#include "Compare.h"
#include "LinkListCompare.h"

NetworkNode nodeA , nodeB;
ShortestPathNode sPathRoot ,sPathNode;
GraphPath root,inputNode;
GraphPath * inNode;
List * pathLinks;
ListItem  listItem;
void setUp(void){}

void tearDown(void){}

void initShortestPathNode(ShortestPathNode *sPath,NetworkNode * id ,ShortestPathNode * parent ,int pathCost ,int linkCost){
    sPath->id = id;
    sPath->parent = parent;
    sPath->pathCost = pathCost;
    sPath->linkCost = linkCost;
}
void initNetworkNode(NetworkNode * node, char*name,List * links,int marked){
    node->name = name;
    node->links = links;
    node->marked = marked;
}
void test_graphCompareForPathCostAvlAdd_input_larger_node(void){
    Compare compare = (Compare)graphCompareForPathCostAvlAdd;
    initShortestPathNode(&sPathRoot,NULL ,NULL,1,1);
    initShortestPathNode(&sPathNode,NULL ,NULL,2,2);
    root.sPath = &sPathRoot;
    inputNode.sPath = &sPathNode;
    inNode = &inputNode;
    TEST_ASSERT_EQUAL(-1,(compare((Node*)&root,(void *)inNode)));
}

void test_graphCompareForPathCostAvlAdd_input_smaller_node(void){
    Compare compare = (Compare)graphCompareForPathCostAvlAdd;
    initShortestPathNode(&sPathRoot,NULL ,NULL,2,2);
    initShortestPathNode(&sPathNode,NULL ,NULL,1,1);
    root.sPath = &sPathRoot;
    inputNode.sPath = &sPathNode;
    inNode = &inputNode;
    TEST_ASSERT_EQUAL(1,(compare((Node*)&root,(void *)inNode)));
}

void test_graphCompareForPathCostAvlAdd_input_same_node(void){
    Compare compare = (Compare)graphCompareForPathCostAvlAdd;
    initShortestPathNode(&sPathRoot,NULL ,NULL,1,1);
    initShortestPathNode(&sPathNode,NULL ,NULL,1,1);
    root.sPath = &sPathRoot;
    inputNode.sPath = &sPathNode;
    inNode = &inputNode;
    TEST_ASSERT_EQUAL(0,(compare((Node*)&root,(void *)inNode)));
}

void test_graphCompareForPathCost_input_larger_node(void){
    Compare compare = (Compare)graphCompareForPathCost;
    initShortestPathNode(&sPathRoot,NULL ,NULL,1,1);
    initShortestPathNode(&sPathNode,NULL ,NULL,2,2);
    root.sPath = &sPathRoot;
    inputNode.sPath = &sPathNode;
    inNode = &inputNode;
    TEST_ASSERT_EQUAL(-1,(compare((Node*)&root,(void *)&inNode->sPath->pathCost)));
}

void test_graphCompareForPathCost_input_smaller_node(void){
    Compare compare = (Compare)graphCompareForPathCost;
    initShortestPathNode(&sPathRoot,NULL ,NULL,2,2);
    initShortestPathNode(&sPathNode,NULL ,NULL,1,1);
    root.sPath = &sPathRoot;
    inputNode.sPath = &sPathNode;
    inNode = &inputNode;
    TEST_ASSERT_EQUAL(1,(compare((Node*)&root,(void *)&inNode->sPath->pathCost)));
}

void test_graphCompareForPathCost_input_same_node(void){
    Compare compare = (Compare)graphCompareForPathCost;
    initShortestPathNode(&sPathRoot,NULL ,NULL,1,1);
    initShortestPathNode(&sPathNode,NULL ,NULL,1,1);
    root.sPath = &sPathRoot;
    inputNode.sPath = &sPathNode;
    inNode = &inputNode;
    TEST_ASSERT_EQUAL(0,(compare((Node*)&root,(void *)&inNode->sPath->pathCost)));
}

void test_graphCompareForNameAvlAdd_input_larger_node(void){
    Compare compare = (Compare)graphCompareForNameAvlAdd;
    initNetworkNode(&nodeA,"nodeA",NULL,0);
    initNetworkNode(&nodeB,"nodeB",NULL,0);
    initShortestPathNode(&sPathRoot,&nodeA ,NULL,1,1);
    initShortestPathNode(&sPathNode,&nodeB ,NULL,2,2);
    root.sPath = &sPathRoot;
    inputNode.sPath = &sPathNode;
    inNode = &inputNode;
    TEST_ASSERT_EQUAL(-1,(compare((Node*)&root,(void *)inNode)));
}

void test_graphCompareForNameAvlAdd_input_smaller_node(void){
    Compare compare = (Compare)graphCompareForNameAvlAdd;
    initNetworkNode(&nodeA,"nodeA",NULL,0);
    initNetworkNode(&nodeB,"nodeB",NULL,0);
    initShortestPathNode(&sPathRoot,&nodeB ,NULL,1,1);
    initShortestPathNode(&sPathNode,&nodeA ,NULL,2,2);
    root.sPath = &sPathRoot;
    inputNode.sPath = &sPathNode;
    inNode = &inputNode;
    TEST_ASSERT_EQUAL(1,(compare((Node*)&root,(void *)inNode)));
}

void test_graphCompareForNameAvlAdd_input_same_node(void){
    Compare compare = (Compare)graphCompareForNameAvlAdd;
    initNetworkNode(&nodeA,"nodeA",NULL,0);
    initNetworkNode(&nodeB,"nodeB",NULL,0);
    initShortestPathNode(&sPathRoot,&nodeA ,NULL,1,1);
    initShortestPathNode(&sPathNode,&nodeA ,NULL,2,2);
    root.sPath = &sPathRoot;
    inputNode.sPath = &sPathNode;
    inNode = &inputNode;
    TEST_ASSERT_EQUAL(0,(compare((Node*)&root,(void *)inNode)));
}


void test_graphCompareForName_input_larger_node(void){
    Compare compare = (Compare)graphCompareForName;
    initNetworkNode(&nodeA,"nodeA",NULL,0);
    initNetworkNode(&nodeB,"nodeB",NULL,0);
    initShortestPathNode(&sPathRoot,&nodeA ,NULL,1,1);
    initShortestPathNode(&sPathNode,&nodeB ,NULL,2,2);
    root.sPath = &sPathRoot;
    inputNode.sPath = &sPathNode;
    inNode = &inputNode;
    TEST_ASSERT_EQUAL(-1,(compare((Node*)&root,(void *)inNode->sPath->id->name)));
}

void test_graphCompareForName_input_smaller_node(void){
    Compare compare = (Compare)graphCompareForName;
    initNetworkNode(&nodeA,"nodeA",NULL,0);
    initNetworkNode(&nodeB,"nodeB",NULL,0);
    initShortestPathNode(&sPathRoot,&nodeB ,NULL,1,1);
    initShortestPathNode(&sPathNode,&nodeA ,NULL,2,2);
    root.sPath = &sPathRoot;
    inputNode.sPath = &sPathNode;
    inNode = &inputNode;
    TEST_ASSERT_EQUAL(1,(compare((Node*)&root,(void *)inNode->sPath->id->name)));
}

void test_graphCompareForName_input_same_node(void){
    Compare compare = (Compare)graphCompareForName;
    initNetworkNode(&nodeA,"nodeA",NULL,0);
    initNetworkNode(&nodeB,"nodeB",NULL,0);
    initShortestPathNode(&sPathRoot,&nodeA ,NULL,1,1);
    initShortestPathNode(&sPathNode,&nodeA ,NULL,2,2);
    root.sPath = &sPathRoot;
    inputNode.sPath = &sPathNode;
    inNode = &inputNode;
    TEST_ASSERT_EQUAL(0,(compare((Node*)&root,(void *)inNode->sPath->id->name)));
}

void test_graphCompareForSameCostList_different_name_return_0(void){
    LinkListCompare compare = (LinkListCompare)graphCompareForSameCostList;
    initNetworkNode(&nodeA,"nodeA",NULL,0);
    initNetworkNode(&nodeB,"nodeB",NULL,0);
    initShortestPathNode(&sPathRoot,&nodeA ,NULL,1,1);
    initShortestPathNode(&sPathNode,&nodeB ,NULL,2,2);
    root.sPath = &sPathRoot;
    inputNode.sPath = &sPathNode;
    listItem.data = (void*)&inputNode;
    TEST_ASSERT_EQUAL(0,(compare(&listItem,(void *)&root)));
}

void test_graphCompareForSameCostList_same_name_return_1(void){
    LinkListCompare compare = (LinkListCompare)graphCompareForSameCostList;
    initNetworkNode(&nodeA,"nodeA",NULL,0);
    initNetworkNode(&nodeB,"nodeB",NULL,0);
    initShortestPathNode(&sPathRoot,&nodeA ,NULL,1,1);
    initShortestPathNode(&sPathNode,&nodeA ,NULL,2,2);
    root.sPath = &sPathRoot;
    inputNode.sPath = &sPathNode;
    listItem.data = (void*)&inputNode;
    TEST_ASSERT_EQUAL(1,(compare(&listItem,(void *)&root)));
}
