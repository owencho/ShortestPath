#include "unity.h"
#include "../AvlTree/src/AvlAdd.h"
#include "../AvlTree/src/AvlDelete.h"
#include "../AvlTree/src/Node.h"
#include "../AvlTree/src/IntNode.h"
#include "../AvlTree/src/IntCompare.h"
#include "../AvlTree/src/Balance.h"
#include "../AvlTree/src/Rotate.h"
#include "../AvlTree/src/Exception.h"
#include "../AvlTree/src/Error.h"
#include "../AvlTree/src/CExceptionConfig.h"
#include "../LinkList/src/NetworkNode.h"
#include "../LinkList/src/List.h"
#include "../LinkList/src/ListItem.h"
#include "ShortestPath.h"
#include "GraphPath.h"
#include "GraphCompare.h"
Node* root;
ShortestPath sPath;
NetworkNode nodeA ,nodeB ,nodeC,nodeD,nodeE;
ListItem itemA,itemB,itemC,itemD,itemE;
List linkList;
List * outList;
void setUp(void){
    sPath.cost = 3;
    itemA.data = (void*)sPath;
    sPath.cost = 5;
    itemB.data = (void*)sPath;
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

    root=shortestPath(&nodeC);
    TEST_ASSERT_EQUAL_PTR(root,&node);
    TEST_ASSERT_EQUAL_GRAPH_NODE((GraphNode*)root,&node);
}
