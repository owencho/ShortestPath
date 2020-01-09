#include "unity.h"
#include "CustomAssert.h"
NetworkNode nodeA ,nodeB,nodeC,nodeD;
ShortestPathNode sPathA,sPathD, sPathB;
GraphPath gPathB,gPathA,gPathD;
Link outItem;
List  pathLinkCA,pathLinkCD,pathLinkCB;
void setUp(void){}
void tearDown(void){}

void initNetworkNode(NetworkNode * node, char*name,List * links,int marked){
    node->name = name;
    node-> links = links;
    node->marked = marked;
}
void initList(List * link, ListItem * head ,ListItem * tail ,int count ,ListItem * current){
    link->head = head;
    link->tail = tail;
    link->count = count;
    link->current = current;
}
void initListItem(ListItem * listItem, ListItem * next ,void* data){
    listItem->next = next;
    listItem->data = data;
}
void initlinkItemData(Link * linkItemData,NetworkNode * head ,NetworkNode * tail,int cost){
    linkItemData->head = head;
    linkItemData->tail = tail;
    linkItemData->cost = cost;
}
void initShortestPathNode(ShortestPathNode *sPath,NetworkNode * id ,ShortestPathNode * parent ,int pathCost ,int linkCost){
    sPath->id = id;
    sPath->parent = parent;
    sPath->pathCost = pathCost;
    sPath->linkCost = linkCost;
}

void initGraphPath(GraphPath*graphPath,GraphPath*left,GraphPath*right,int bFactor, ShortestPathNode * sPath){
    graphPath->left = left;
    graphPath->right = right;
    graphPath->bFactor = bFactor;
    graphPath->sPath = sPath;
}

void test_CustomAssert_SHORTEST_PATH_all_pass(void){
    //create GraphPath
    initNetworkNode(&nodeC, "nodeC",NULL,0);
    initNetworkNode(&nodeD, "nodeD",NULL,0);
    initShortestPathNode(&sPathD,&nodeC,NULL,2,2);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(&sPathD,&nodeC,NULL,2,2);
}

void test_CustomAssert_SHORTEST_PATH_fail_actualpath_NULL(void){
    //create GraphPath
    TEST_ASSERT_EQUAL_SHORTEST_PATH(NULL,&nodeC,NULL,2,2);
}

void test_CustomAssert_SHORTEST_PATH_actualParent_not_NULL(void){
    //create GraphPath
    initNetworkNode(&nodeC, "nodeC",NULL,0);
    initNetworkNode(&nodeA, "nodeA",NULL,0);
    initShortestPathNode(&sPathD,&nodeC,&sPathA,2,2);
    initShortestPathNode(&sPathA,&nodeA,NULL,1,1);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(&sPathD,&nodeC,NULL,2,2);
}

void test_CustomAssert_SHORTEST_PATH_actualParent_check_both_parent(void){
    //create GraphPath
    initNetworkNode(&nodeC, "nodeC",NULL,0);
    initNetworkNode(&nodeA, "nodeA",NULL,0);
    initShortestPathNode(&sPathD,&nodeC,&sPathA,2,2);
    initShortestPathNode(&sPathA,&nodeA,NULL,1,1);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(&sPathD,&nodeC,&sPathA,2,2);
}

void test_CustomAssert_SHORTEST_PATH_actualParent_is_NULL(void){
    //create GraphPath
    initNetworkNode(&nodeC, "nodeC",NULL,0);
    initNetworkNode(&nodeA, "nodeA",NULL,0);
    initShortestPathNode(&sPathD,&nodeC,NULL,2,2);
    initShortestPathNode(&sPathA,&nodeA,NULL,1,1);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(&sPathD,&nodeC,&sPathA,2,2);
}

void test_CustomAssert_SHORTEST_PATH_expected_id_NULL(void){
    //create GraphPath
    initNetworkNode(&nodeC, "nodeC",NULL,0);
    initNetworkNode(&nodeD, "nodeD",NULL,0);
    initShortestPathNode(&sPathD,&nodeC,NULL,2,2);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(&sPathD,NULL,NULL,2,2);
}

void test_CustomAssert_SHORTEST_PATH_wrong_id(void){
    //create GraphPath
    initNetworkNode(&nodeC, "nodeC",NULL,0);
    initNetworkNode(&nodeD, "nodeD",NULL,0);
    initShortestPathNode(&sPathD,&nodeC,NULL,2,2);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(&sPathD,&nodeD,NULL,2,2);
}

void test_CustomAssert_SHORTEST_PATH_wrong_pathcost(void){
    //create GraphPath
    initNetworkNode(&nodeC, "nodeC",NULL,0);
    initNetworkNode(&nodeD, "nodeD",NULL,0);
    initShortestPathNode(&sPathD,&nodeC,NULL,2,2);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(&sPathD,&nodeC,NULL,1,2);
}

void test_CustomAssert_SHORTEST_PATH_wrong_linkcost(void){
    //create GraphPath
    initNetworkNode(&nodeC, "nodeC",NULL,0);
    initNetworkNode(&nodeD, "nodeD",NULL,0);
    initShortestPathNode(&sPathD,&nodeC,NULL,2,2);
    TEST_ASSERT_EQUAL_SHORTEST_PATH(&sPathD,&nodeC,NULL,2,1);
}

void test_CustomAssert_LINK_LIST_ITEM_all_pass(void){
    //create GraphPath
    initNetworkNode(&nodeC, "nodeC",NULL,0);
    initNetworkNode(&nodeD, "nodeD",NULL,0);
    initlinkItemData(&outItem,&nodeC ,&nodeD,2);
    TEST_ASSERT_EQUAL_LINK_LIST_ITEM(&outItem,&nodeC,&nodeD,2);
}

void test_CustomAssert_LINK_LIST_ITEM_fail_actualpath_NULL(void){
    //create GraphPath
    TEST_ASSERT_EQUAL_LINK_LIST_ITEM(NULL,&nodeC,&nodeD,2);
}

void test_CustomAssert_LINK_LIST_ITEM_fail_dst_NULL(void){
    //create GraphPath
    initNetworkNode(&nodeC, "nodeC",NULL,0);
    initNetworkNode(&nodeD, "nodeD",NULL,0);
    initlinkItemData(&outItem,&nodeC ,&nodeD,2);
    TEST_ASSERT_EQUAL_LINK_LIST_ITEM(&outItem,NULL,&nodeD,2);
}

void test_CustomAssert_LINK_LIST_ITEM_fail_dst_wrong(void){
    //create GraphPath
    initNetworkNode(&nodeC, "nodeC",NULL,0);
    initNetworkNode(&nodeD, "nodeD",NULL,0);
    initlinkItemData(&outItem,&nodeC ,&nodeD,2);
    TEST_ASSERT_EQUAL_LINK_LIST_ITEM(&outItem,&nodeD,&nodeD,2);
}

void test_CustomAssert_LINK_LIST_ITEM_fail_src_NULL(void){
    //create GraphPath
    initNetworkNode(&nodeC, "nodeC",NULL,0);
    initNetworkNode(&nodeD, "nodeD",NULL,0);
    initlinkItemData(&outItem,&nodeC ,&nodeD,2);
    TEST_ASSERT_EQUAL_LINK_LIST_ITEM(&outItem,&nodeC,NULL,2);
}

void test_CustomAssert_LINK_LIST_ITEM_fail_src_wrong(void){
    //create GraphPath
    initNetworkNode(&nodeC, "nodeC",NULL,0);
    initNetworkNode(&nodeD, "nodeD",NULL,0);
    initlinkItemData(&outItem,&nodeC ,&nodeD,2);
    TEST_ASSERT_EQUAL_LINK_LIST_ITEM(&outItem,&nodeC,&nodeC,2);
}

void test_CustomAssert_LINK_LIST_ITEM_wrong_pathcost(void){
    //create GraphPath
    initNetworkNode(&nodeC, "nodeC",NULL,0);
    initNetworkNode(&nodeD, "nodeD",NULL,0);
    initlinkItemData(&outItem,&nodeC ,&nodeD,2);
    TEST_ASSERT_EQUAL_LINK_LIST_ITEM(&outItem,&nodeC,&nodeD,1);
}
/*
void test_CustomAssert_GRAPH_PATH_all_pass(void){
    //create GraphPath
    initNetworkNode(&nodeA, "nodeA",NULL,0);
    initNetworkNode(&nodeB, "nodeB",NULL,0);
    initNetworkNode(&nodeC, "nodeC",NULL,0);
    initNetworkNode(&nodeD, "nodeD",NULL,0);
    initShortestPathNode(&sPathD,&nodeD,&nodeC,2,&pathLinkCD);
    initShortestPathNode(&sPathB,&nodeB,&nodeC,1,&pathLinkCB);
    initShortestPathNode(&sPathA,&nodeA,&nodeC,2,&pathLinkCA);
    initGraphPath(&gPathA,&gPathB,&gPathD,0, &sPathA);
    initGraphPath(&gPathD,NULL,NULL,0, &sPathD);
    initGraphPath(&gPathB,NULL,NULL,0, &sPathB);
    //TEST
    TEST_ASSERT_EQUAL_GRAPH_PATH(&gPathA,&gPathB,&gPathD,0,&sPathA);
}

void test_CustomAssert_GRAPH_PATH_fail_on_actual_left_is_NULL(void){
    //create GraphPath
    initNetworkNode(&nodeA, "nodeA",NULL,0);
    initNetworkNode(&nodeB, "nodeB",NULL,0);
    initNetworkNode(&nodeC, "nodeC",NULL,0);
    initNetworkNode(&nodeD, "nodeD",NULL,0);
    initShortestPathNode(&sPathD,&nodeD,&nodeC,2,&pathLinkCD);
    initShortestPathNode(&sPathB,&nodeB,&nodeC,1,&pathLinkCB);
    initShortestPathNode(&sPathA,&nodeA,&nodeC,2,&pathLinkCA);
    initGraphPath(&gPathA,NULL,&gPathD,0, &sPathA);
    initGraphPath(&gPathD,NULL,NULL,0, &sPathD);
    initGraphPath(&gPathB,NULL,NULL,0, &sPathB);
    //TEST
    TEST_ASSERT_EQUAL_GRAPH_PATH(&gPathA,&gPathB,&gPathD,0,&sPathA);
}

void test_CustomAssert_GRAPH_PATH_fail_on_expected_left_is_NULL(void){
    //create GraphPath
    initNetworkNode(&nodeA, "nodeA",NULL,0);
    initNetworkNode(&nodeB, "nodeB",NULL,0);
    initNetworkNode(&nodeC, "nodeC",NULL,0);
    initNetworkNode(&nodeD, "nodeD",NULL,0);
    initShortestPathNode(&sPathD,&nodeD,&nodeC,2,&pathLinkCD);
    initShortestPathNode(&sPathB,&nodeB,&nodeC,1,&pathLinkCB);
    initShortestPathNode(&sPathA,&nodeA,&nodeC,2,&pathLinkCA);
    initGraphPath(&gPathA,&gPathB,&gPathD,0, &sPathA);
    initGraphPath(&gPathD,NULL,NULL,0, &sPathD);
    initGraphPath(&gPathB,NULL,NULL,0, &sPathB);
    //TEST
    TEST_ASSERT_EQUAL_GRAPH_PATH(&gPathA,NULL,&gPathD,0,&sPathA);
}

void test_CustomAssert_GRAPH_PATH_fail_on_left_is_different(void){
    //create GraphPath
    initNetworkNode(&nodeA, "nodeA",NULL,0);
    initNetworkNode(&nodeB, "nodeB",NULL,0);
    initNetworkNode(&nodeC, "nodeC",NULL,0);
    initNetworkNode(&nodeD, "nodeD",NULL,0);
    initShortestPathNode(&sPathD,&nodeD,&nodeC,2,&pathLinkCD);
    initShortestPathNode(&sPathB,&nodeB,&nodeC,1,&pathLinkCB);
    initShortestPathNode(&sPathA,&nodeA,&nodeC,2,&pathLinkCA);
    initGraphPath(&gPathA,&gPathB,&gPathD,0, &sPathA);
    initGraphPath(&gPathD,NULL,NULL,0, &sPathD);
    initGraphPath(&gPathB,NULL,NULL,0, &sPathB);
    //TEST
    TEST_ASSERT_EQUAL_GRAPH_PATH(&gPathA,&gPathD,&gPathD,0,&sPathA);
}


void test_CustomAssert_GRAPH_PATH_fail_on_actual_right_is_NULL(void){
    //create GraphPath
    initNetworkNode(&nodeA, "nodeA",NULL,0);
    initNetworkNode(&nodeB, "nodeB",NULL,0);
    initNetworkNode(&nodeC, "nodeC",NULL,0);
    initNetworkNode(&nodeD, "nodeD",NULL,0);
    initShortestPathNode(&sPathD,&nodeD,&nodeC,2,&pathLinkCD);
    initShortestPathNode(&sPathB,&nodeB,&nodeC,1,&pathLinkCB);
    initShortestPathNode(&sPathA,&nodeA,&nodeC,2,&pathLinkCA);
    initGraphPath(&gPathA,&gPathB,NULL,0, &sPathA);
    initGraphPath(&gPathD,NULL,NULL,0, &sPathD);
    initGraphPath(&gPathB,NULL,NULL,0, &sPathB);
    //TEST
    TEST_ASSERT_EQUAL_GRAPH_PATH(&gPathA,&gPathB,&gPathD,0,&sPathA);
}
void test_CustomAssert_GRAPH_PATH_fail_on_expected_right_is_NULL(void){
    //create GraphPath
    initNetworkNode(&nodeA, "nodeA",NULL,0);
    initNetworkNode(&nodeB, "nodeB",NULL,0);
    initNetworkNode(&nodeC, "nodeC",NULL,0);
    initNetworkNode(&nodeD, "nodeD",NULL,0);
    initShortestPathNode(&sPathD,&nodeD,&nodeC,2,&pathLinkCD);
    initShortestPathNode(&sPathB,&nodeB,&nodeC,1,&pathLinkCB);
    initShortestPathNode(&sPathA,&nodeA,&nodeC,2,&pathLinkCA);
    initGraphPath(&gPathA,&gPathB,&gPathD,0, &sPathA);
    initGraphPath(&gPathD,NULL,NULL,0, &sPathD);
    initGraphPath(&gPathB,NULL,NULL,0, &sPathB);
    //TEST
    TEST_ASSERT_EQUAL_GRAPH_PATH(&gPathA,&gPathB,NULL,0,&sPathA);
}

void test_CustomAssert_GRAPH_PATH_fail_on_right_is_different(void){
    //create GraphPath
    initNetworkNode(&nodeA, "nodeA",NULL,0);
    initNetworkNode(&nodeB, "nodeB",NULL,0);
    initNetworkNode(&nodeC, "nodeC",NULL,0);
    initNetworkNode(&nodeD, "nodeD",NULL,0);
    initShortestPathNode(&sPathD,&nodeD,&nodeC,2,&pathLinkCD);
    initShortestPathNode(&sPathB,&nodeB,&nodeC,1,&pathLinkCB);
    initShortestPathNode(&sPathA,&nodeA,&nodeC,2,&pathLinkCA);
    initGraphPath(&gPathA,&gPathB,&gPathD,0, &sPathA);
    initGraphPath(&gPathD,NULL,NULL,0, &sPathD);
    initGraphPath(&gPathB,NULL,NULL,0, &sPathB);
    //TEST
    TEST_ASSERT_EQUAL_GRAPH_PATH(&gPathA,&gPathB,&gPathB,0,&sPathA);
}

void test_CustomAssert_GRAPH_PATH_fail_on_different_shortest_path(void){
    //create GraphPath
    initNetworkNode(&nodeA, "nodeA",NULL,0);
    initNetworkNode(&nodeB, "nodeB",NULL,0);
    initNetworkNode(&nodeC, "nodeC",NULL,0);
    initNetworkNode(&nodeD, "nodeD",NULL,0);
    initShortestPathNode(&sPathD,&nodeD,&nodeC,2,&pathLinkCD);
    initShortestPathNode(&sPathB,&nodeB,&nodeC,1,&pathLinkCB);
    initShortestPathNode(&sPathA,&nodeA,&nodeC,2,&pathLinkCA);
    initGraphPath(&gPathA,&gPathB,&gPathD,0, &sPathA);
    initGraphPath(&gPathD,NULL,NULL,0, &sPathD);
    initGraphPath(&gPathB,NULL,NULL,0, &sPathB);

    TEST_ASSERT_EQUAL_GRAPH_PATH(&gPathA,&gPathB,&gPathD,0,&sPathD);
}

void test_CustomAssert_GRAPH_PATH_fail_on_wrong_balanceFactor(void){
    //create GraphPath
    initNetworkNode(&nodeA, "nodeA",NULL,0);
    initNetworkNode(&nodeB, "nodeB",NULL,0);
    initNetworkNode(&nodeC, "nodeC",NULL,0);
    initNetworkNode(&nodeD, "nodeD",NULL,0);
    initShortestPathNode(&sPathD,&nodeD,&nodeC,2,&pathLinkCD);
    initShortestPathNode(&sPathB,&nodeB,&nodeC,1,&pathLinkCB);
    initShortestPathNode(&sPathA,&nodeA,&nodeC,2,&pathLinkCA);
    initGraphPath(&gPathA,&gPathB,&gPathD,0, &sPathA);
    initGraphPath(&gPathD,NULL,NULL,0, &sPathD);
    initGraphPath(&gPathB,NULL,NULL,0, &sPathB);
    //TEST
    TEST_ASSERT_EQUAL_GRAPH_PATH(&gPathA,&gPathB,&gPathD,1,&sPathA);
}
*/
