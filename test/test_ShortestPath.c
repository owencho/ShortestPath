#include "unity.h"
#include "Node.h"
#include "IntNode.h"
#include "AvlAdd.h"
#include "AvlDelete.h"
#include "ShortestPath.h"

Node* root;
IntNode nodeA ,nodeB ,nodeC,nodeD,nodeE;
void setUp(void){}
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

    root=ShortestPath((Node*)nodeC,(compare)intCompare);
    TEST_ASSERT_EQUAL_INT_NODE()
}
