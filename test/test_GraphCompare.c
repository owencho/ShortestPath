#include "unity.h"
#include "GraphCompare.h"
#include "GraphPath.h"
#include "Node.h"
#include "NetworkNode.h"
#include "List.h"
#include "Compare.h"

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

void test_graphCompare_input_larger_node(void){
    Compare compare = (Compare)graphCompare;
    initShortestPath(&sPathRoot,NULL ,NULL,1,pathLinks);
    initShortestPath(&sPathNode,NULL ,NULL,2,pathLinks);
    root.value = &sPathRoot;
    inputNode.value = &sPathNode;
    inNode = &inputNode;
    TEST_ASSERT_EQUAL(-1,(compare((Node*)&root,(void *)inNode->value)));
}

void test_graphCompare_input_smaller_node(void){
    Compare compare = (Compare)graphCompare;
    initShortestPath(&sPathRoot,NULL ,NULL,2,pathLinks);
    initShortestPath(&sPathNode,NULL ,NULL,1,pathLinks);
    root.value = &sPathRoot;
    inputNode.value = &sPathNode;
    inNode = &inputNode;
    TEST_ASSERT_EQUAL(1,(compare((Node*)&root,(void *)inNode->value)));
}

void test_graphCompare_input_same_node(void){
    Compare compare = (Compare)graphCompare;
    initShortestPath(&sPathRoot,NULL ,NULL,1,pathLinks);
    initShortestPath(&sPathNode,NULL ,NULL,1,pathLinks);
    root.value = &sPathRoot;
    inputNode.value = &sPathNode;
    inNode = &inputNode;
    TEST_ASSERT_EQUAL(0,(compare((Node*)&root,(void *)inNode->value)));
}
