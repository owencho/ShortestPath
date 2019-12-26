#include "unity.h"
#include "Node.h"
#include "IntNode.h"
#include "AvlAdd.h"
#include "AvlDelete.h"
#include "ShortestPath.h"

Node* root;
NetworkNode nodeA ,nodeB ,nodeC,nodeD,nodeE;
ListItem itemA,itemB,itemC,itemD,itemE;
List listDataA,listDataC,listDataD,listDataE,listDataB;
void setUp(void){
}
void tearDown(void){}


/**
*               3          4
*         (A)--------(B)--------(E)
*        1 \     7 /   \ 5     /
*           \    /      \    / 7
*            (C)---------(D)
*                   2
**/
void test_ShortestPath(void){


    root=shortestPath(&nodeC,(compare)graphCompare);
    TEST_ASSERT_EQUAL_PTR(root,&node);
    TEST_ASSERT_EQUAL_GRAPH_NODE((GraphNode*)root,&node);
}

/**
*               3          4
*         (A)--------(B)--------(E)
*        1 \     7 /   \ 5     /
*           \    /      \    / 7
*            (C)---------(D)
*                   2
**/
void test_ShortestPath(void){


    root=findNearestNode(&nodeC,(compare)graphCompare,);
    TEST_ASSERT_EQUAL_PTR(root,&node);
    TEST_ASSERT_EQUAL_GRAPH_NODE((GraphNode*)root,&node);
}
