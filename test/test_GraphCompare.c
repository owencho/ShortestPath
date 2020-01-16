#include "unity.h"
#include "GraphCompare.h"
#include "GraphPath.h"
#include "Node.h"
#include "NetworkNode.h"
#include "List.h"
#include "Compare.h"
#include "LinkedListCompare.h"

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

//////////////graphCompareForPathCostAvlAdd/////////////////////////////////////////////////////
//graphCompareForPathCostAvlAdd is function to compare graphPath for pathCost AvlADD
// by comparing two node
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

//////////////graphCompareForPathCost/////////////////////////////////////////////////////
//graphCompareForPathCost is function to compare graphPath for pathCost
// by comparing value in the node and input value
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
//////////////graphCompareForNameAvlAdd/////////////////////////////////////////////////////
//graphCompareForNameAvlAdd is function to compare graphPath for pathName AvlADD
// by comparing two node
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

//////////////graphCompareForName/////////////////////////////////////////////////////
//graphCompareForName is function to compare graphPath for pathName
// by comparing name in the node and input name
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
//////////////listCompareForListWithSameCostGraph/////////////////////////////////////////////////////
//graphCompareForName is function to compare graphPath inside sameCostList
// by comparing listItem and the input Node
void test_listCompareForListWithSameCostGraph_different_name_return_0(void){
    LinkedListCompare compare = (LinkedListCompare)listCompareForListWithSameCostGraph;
    initNetworkNode(&nodeA,"nodeA",NULL,0);
    initNetworkNode(&nodeB,"nodeB",NULL,0);
    initShortestPathNode(&sPathRoot,&nodeA ,NULL,1,1);
    initShortestPathNode(&sPathNode,&nodeB ,NULL,2,2);
    root.sPath = &sPathRoot;
    inputNode.sPath = &sPathNode;
    listItem.data = (void*)&inputNode;
    TEST_ASSERT_EQUAL(0,(compare(&listItem,(void *)&root)));
}

void test_listCompareForListWithSameCostGraph_NULL(void){
    LinkedListCompare compare = (LinkedListCompare)listCompareForListWithSameCostGraph;
    initNetworkNode(&nodeA,"nodeA",NULL,0);
    initNetworkNode(&nodeB,"nodeB",NULL,0);
    initShortestPathNode(&sPathRoot,&nodeA ,NULL,1,1);
    initShortestPathNode(&sPathNode,&nodeB ,NULL,2,2);
    root.sPath = &sPathRoot;
    inputNode.sPath = &sPathNode;
    listItem.data = (void*)&inputNode;
    TEST_ASSERT_EQUAL(0,(compare(NULL,(void *)&root)));
}

void test_listCompareForListWithSameCostGraph_same_name_return_1(void){
    LinkedListCompare compare = (LinkedListCompare)listCompareForListWithSameCostGraph;
    initNetworkNode(&nodeA,"nodeA",NULL,0);
    initNetworkNode(&nodeB,"nodeB",NULL,0);
    initShortestPathNode(&sPathRoot,&nodeA ,NULL,1,1);
    initShortestPathNode(&sPathNode,&nodeA ,NULL,2,2);
    root.sPath = &sPathRoot;
    inputNode.sPath = &sPathNode;
    listItem.data = (void*)&inputNode;
    TEST_ASSERT_EQUAL(1,(compare(&listItem,(void *)&root)));
}
