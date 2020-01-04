#include "FindShortestPath.h"
#include "unity.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CException.h"
#include "AvlAdd.h"
#include "AvlDelete.h"
#include "Node.h"
#include "IntNode.h"
#include "IntCompare.h"
#include "Compare.h"
#include "Balance.h"
#include "Rotate.h"
#include "Exception.h"
#include "Error.h"
#include "NetworkNode.h"
#include "List.h"
#include "ListItem.h"
#include "ShortestPathNode.h"
#include "GraphPath.h"
#include "GraphCompare.h"
#include "CustomAssert.h"

NetworkNode nodeA ,nodeB,nodeC,nodeD;
ShortestPathNode sPath,sPathA ,sPathD, sPathB;
GraphPath gPathB,gPathA,gPathD;
List  pathLinkCA,pathLinkCD,pathLinkCB,pathLinkCAB,linkListA,linkList;
ListItem listItemCA,listItemAC,listItemCB,listItemCD,listItemAB;
ListItem * outListItem;
Link linkCA,linkAC,linkCB,linkCD,linkAB;
Link* linkItemData;
GraphPath* root;
GraphPath* smallestNode;
ListItem*pathLinksItem;


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
/**
*
*         (A)      (B)
*        1 \     7 /
*           \    /            ------>     (0)C
*            (C)------(D)
*                   2
**/
void test_addFirstGraphNodeIntoRootTree(void){
      initNetworkNode(&nodeC,"nodeC",&linkList,0);
}

/**
*
*         (A)      (B)                         (2)d
*        1 \     7 /                          /   \
*           \    /            ------>      (1)a   (7)B
*            (C)------(D)
*                   2
**/
//all node without flag
/*
void test_getNearestNode(void){
    //create NetworkNode
    initNetworkNode(&nodeC,"nodeC",&linkList,0);
    initNetworkNode(&nodeA,"nodeA",&linkList,0);
    initNetworkNode(&nodeB,"nodeB",&linkList,0);
    initNetworkNode(&nodeD,"nodeD",&linkList,0);
    //init ShortestPathNode
    initlinkItemData(&linkItemDataA,&nodeA ,&nodeC,1 );
    initlinkItemData(&linkItemDataD,&nodeD ,&nodeC,2 );
    initlinkItemData(&linkItemDataB,&nodeB ,&nodeC,7 );
    //create List Item
    initListItem(&itemA, &itemB ,(void*)&linkItemDataA);
    initListItem(&itemB, &itemD ,(void*)&linkItemDataD);
    initListItem(&itemD, NULL ,(void*)&linkItemDataB);
    //init the Link List
    initList(&linkList, &itemA,&itemD ,0,&itemA);

    sPath.pathCost = 0; //fake inNode as nodeC
    inNode.value = &sPath;
    root=findNearestNode(&inNode,&nodeC);  //function
    root=(GraphPath*)avlRemoveSmallest((Node*)root,(Compare)graphCompareForAvlDelete);
    TEST_ASSERT_EQUAL(1,root->sPath->pathCost);
    TEST_ASSERT_EQUAL_PTR(&nodeA,root->sPath->dst);
    TEST_ASSERT_EQUAL_PTR(&nodeC,root->sPath->src);
    TEST_ASSERT_EQUAL_PTR(&pathAC,root->sPath->pathLinks);

    root=(GraphPath*)avlRemoveSmallest((Node*)root,(Compare)graphCompareForAvlDelete);
    TEST_ASSERT_EQUAL(2,root->sPath->pathCost);
    TEST_ASSERT_EQUAL_PTR(&nodeD,root->sPath->dst);
    TEST_ASSERT_EQUAL_PTR(&nodeC,root->sPath->src);
    TEST_ASSERT_EQUAL_PTR(&pathDC,root->sPath->pathLinks);

    root=(GraphPath*)avlRemoveSmallest((Node*)root,(Compare)graphCompareForAvlDelete);
    TEST_ASSERT_EQUAL(7,root->sPath->pathCost);
    TEST_ASSERT_EQUAL_PTR(&nodeB,root->sPath->dst);
    TEST_ASSERT_EQUAL_PTR(&nodeC,root->sPath->src);
    TEST_ASSERT_EQUAL_PTR(&pathBC,root->sPath->pathLinks);

    TEST_ASSERT_NULL(root);
}

/**
*
*         (A)      (B)                         (2)d
*        1 \     7 /                          /
*           \    /            ------>      (1)a
*            (C)------(D)
*                   2
**/
//B with the flag
/*
void test_getNearestNode_withB_Flag(void){
    List  pathDC, pathAC ,pathBC;
    //create NetworkNode
    initNetworkNode(&nodeC,"nodeC",&linkList,0);
    initNetworkNode(&nodeA,"nodeA",&linkList,0);
    initNetworkNode(&nodeB,"nodeB",&linkList,1);
    initNetworkNode(&nodeD,"nodeD",&linkList,0);
    //init ShortestPathNode
    initShortestPathNode(&sPathA,&nodeA ,&nodeC,1 ,&pathAC);
    initShortestPathNode(&sPathD,&nodeD ,&nodeC,2 ,&pathDC);
    initShortestPathNode(&sPathB,&nodeB ,&nodeC,7 ,&pathBC);
    //create List Item
    initListItem(&itemA, &itemB ,(void*)&sPathA);
    initListItem(&itemB, &itemD ,(void*)&sPathB);
    initListItem(&itemD, NULL ,(void*)&sPathD);
    //init the Link List
    initList(&linkList, &itemA,&itemD ,0,&itemA);

    sPath.pathCost = 0; //fake inNode as nodeC
    inNode.value = &sPath;
    root=findNearestNode(&inNode,&nodeC);  //function
    outNode=avlRemoveSmallest(root,(Compare)graphCompare);
    TEST_ASSERT_EQUAL(1,smallestNode->value->pathCost);
    TEST_ASSERT_EQUAL_PTR(&nodeA,smallestNode->value->dst);
    TEST_ASSERT_EQUAL_PTR(&nodeC,smallestNode->value->src);
    TEST_ASSERT_EQUAL_PTR(&pathAC,smallestNode->value->pathLinks);

    smallestNode=avlRemoveSmallest(root,(Compare)graphCompare);
    TEST_ASSERT_EQUAL(2,smallestNode->value->pathCost);
    TEST_ASSERT_EQUAL_PTR(&nodeD,smallestNode->value->dst);
    TEST_ASSERT_EQUAL_PTR(&nodeC,smallestNode->value->src);
    TEST_ASSERT_EQUAL_PTR(&pathDC,smallestNode->value->pathLinks);

    TEST_ASSERT_NULL(root);
}
*/

/**
*              3
*         (A)------(B)                         (2)d           (2)d
*        1 \     7 /                              \    ---->   \
*           \    /                                (7)B         (4)b
*            (C)------(D)
*                   2
**/
//C is already checked

void test_compareAndAddShortestPath(void){
    //create GraphPath
    initShortestPathNode(&sPathD,&nodeD,&nodeC,2,&pathLinkCD);
    initGraphPath(&gPathD,NULL,&gPathB,1,&sPathD);
    initShortestPathNode(&sPathB,&nodeB,&nodeC,7,&pathLinkCB);
    initGraphPath(&gPathB,NULL,NULL,0,&sPathB);
    initShortestPathNode(&sPathA,&nodeA,&nodeC,1,&pathLinkCA);
    initGraphPath(&gPathA,NULL,NULL,0,&sPathA);
    //init listItem
    initListItem(&listItemCA, &listItemAB,(void*)&linkCA);
    initListItem(&listItemCB, NULL,(void*)&linkCB);
    initListItem(&listItemCD, NULL,(void*)&linkCD);
    initListItem(&listItemAB, NULL,(void*)&linkAB);
    initListItem(&listItemAC, &listItemAB,(void*)&linkAC);
    // init List
    initList(&pathLinkCA,&listItemCA ,&listItemCA ,1 ,&listItemCA);
    initList(&linkListA,&listItemAC ,&listItemAB ,2 ,&listItemAC);
    initList(&pathLinkCB,&listItemCB ,&listItemCB ,1 ,&listItemCB);
    initList(&pathLinkCD,&listItemCD ,&listItemCD ,1 ,&listItemCD);
    initList(&pathLinkCAB,&listItemCA ,&listItemAB ,2 ,&listItemCA);  //expected output
    // init link item
    initlinkItemData(&linkAB,&nodeB,&nodeA,3);
    initlinkItemData(&linkAC,&nodeC,&nodeA,1);
    initlinkItemData(&linkCA,&nodeA,&nodeC,1);
    initlinkItemData(&linkCB,&nodeB,&nodeC,7);
    initlinkItemData(&linkCD,&nodeD,&nodeC,2);
    //init NetworkNode
    initNetworkNode(&nodeC,"nodeC",&linkList,1);
    initNetworkNode(&nodeA,"nodeA",&linkListA,0);
    initNetworkNode(&nodeB,"nodeB",&linkList,0);
    initNetworkNode(&nodeD,"nodeD",&linkList,0);
    //expected path

    root=compareAndAddShortestPath(&gPathD,&gPathA);
    smallestNode = (GraphPath*)findSmallestNode((Node*)root);
    root = (GraphPath*)avlDelete((Node*)root,smallestNode->sPath,(Compare)graphCompareForAvlDelete);
    TEST_ASSERT_EQUAL(2,smallestNode->sPath->pathCost);
    TEST_ASSERT_EQUAL_PTR(&nodeD,smallestNode->sPath->dst);
    TEST_ASSERT_EQUAL_PTR(&nodeC,smallestNode->sPath->src);

    resetCurrentListItem(smallestNode->sPath->pathLinks);
    pathLinksItem=getNextListItem(smallestNode->sPath->pathLinks);
    TEST_ASSERT_EQUAL_LINK_LIST_ITEM(pathLinksItem->data,&nodeD,&nodeC,2);
    pathLinksItem=getNextListItem(smallestNode->sPath->pathLinks);
    TEST_ASSERT_NULL(pathLinksItem);

    smallestNode = (GraphPath*)findSmallestNode((Node*)root);
    root = (GraphPath*)avlDelete((Node*)root,smallestNode->sPath,(Compare)graphCompareForAvlDelete);
    TEST_ASSERT_EQUAL(4,smallestNode->sPath->pathCost);
    TEST_ASSERT_EQUAL_PTR(&nodeB,smallestNode->sPath->dst);
    TEST_ASSERT_EQUAL_PTR(&nodeC,smallestNode->sPath->src);

    resetCurrentListItem(smallestNode->sPath->pathLinks);
    pathLinksItem=getNextListItem(smallestNode->sPath->pathLinks);
    TEST_ASSERT_EQUAL_LINK_LIST_ITEM((Link*)pathLinksItem->data,&nodeA,&nodeC,1);
    pathLinksItem=getNextListItem(smallestNode->sPath->pathLinks);
    TEST_ASSERT_EQUAL_LINK_LIST_ITEM((Link*)pathLinksItem->data,&nodeB,&nodeA,3);
    pathLinksItem=getNextListItem(smallestNode->sPath->pathLinks);
    TEST_ASSERT_NULL(pathLinksItem);

    TEST_ASSERT_NULL(root);
}

/**
*              3
*         (A)------(B)                         (2)d           (2)d
*        1 \     7 /                                    ---->   \
*           \    /                                              (4)b
*            (C)------(D)
*                   2
**/
//C is already checked
//Assume B is not found in C and it force the node A to find B and add into the tree
/*
void test_compareAndAddShortestPath_to_add_B_into_the_working_tree(void){
    //create GraphPath
    initShortestPathNode(&sPathD,&nodeD,&nodeC,2,&pathLinkCD);
    initGraphPath(&gPathD,NULL,NULL,1,&sPathD);
    initShortestPathNode(&sPathB,&nodeB,&nodeC,7,&pathLinkCB);
    initGraphPath(&gPathB,NULL,NULL,0,&sPathB);
    initShortestPathNode(&sPathA,&nodeA,&nodeC,1,&pathLinkCA);
    initGraphPath(&gPathA,NULL,NULL,0,&sPathA);
    //init listItem
    initListItem(&listItemCA, &listItemAB,(void*)&linkCA);
    initListItem(&listItemCB, NULL,(void*)&linkCB);
    initListItem(&listItemCD, NULL,(void*)&linkCD);
    initListItem(&listItemAB, NULL,(void*)&linkAB);
    initListItem(&listItemAC, &listItemAB,(void*)&linkAC);
    // init List
    initList(&pathLinkCA,&listItemCA ,&listItemCA ,1 ,&listItemCA);
    initList(&linkListA,&listItemAC ,&listItemAB ,2 ,&listItemAC);
    initList(&pathLinkCB,&listItemCB ,&listItemCB ,1 ,&listItemCB);
    initList(&pathLinkCD,&listItemCD ,&listItemCD ,1 ,&listItemCD);
    initList(&pathLinkCAB,&listItemCA ,&listItemAB ,2 ,&listItemCA);  //expected output
    // init link item
    initlinkItemData(&linkAB,&nodeB,&nodeA,3);
    initlinkItemData(&linkAC,&nodeC,&nodeA,1);
    initlinkItemData(&linkCA,&nodeA,&nodeC,1);
    initlinkItemData(&linkCB,&nodeB,&nodeC,7);
    initlinkItemData(&linkCD,&nodeD,&nodeC,2);
    //init NetworkNode
    initNetworkNode(&nodeC,"nodeC",&linkList,1);
    initNetworkNode(&nodeA,"nodeA",&linkListA,0);
    initNetworkNode(&nodeB,"nodeB",&linkList,0);
    initNetworkNode(&nodeD,"nodeD",&linkList,0);
    //expected path

    root=compareAndAddShortestPath(&gPathD,&gPathA);
    smallestNode = (GraphPath*)findSmallestNode((Node*)root);
    root = (GraphPath*)avlDelete((Node*)root,smallestNode->sPath,(Compare)graphCompareForAvlDelete);
    TEST_ASSERT_EQUAL(2,smallestNode->sPath->pathCost);
    TEST_ASSERT_EQUAL_PTR(&nodeD,smallestNode->sPath->dst);
    TEST_ASSERT_EQUAL_PTR(&nodeC,smallestNode->sPath->src);

    resetCurrentListItem(smallestNode->sPath->pathLinks);
    pathLinksItem=getNextListItem(smallestNode->sPath->pathLinks);
    TEST_ASSERT_EQUAL_LINK_LIST_ITEM(pathLinksItem->data,&nodeD,&nodeC,2);
    pathLinksItem=getNextListItem(smallestNode->sPath->pathLinks);
    TEST_ASSERT_NULL(pathLinksItem);

    smallestNode = (GraphPath*)findSmallestNode((Node*)root);
    root = (GraphPath*)avlDelete((Node*)root,smallestNode->sPath,(Compare)graphCompareForAvlDelete);
    TEST_ASSERT_EQUAL(4,smallestNode->sPath->pathCost);
    TEST_ASSERT_EQUAL_PTR(&nodeB,smallestNode->sPath->dst);
    TEST_ASSERT_EQUAL_PTR(&nodeC,smallestNode->sPath->src);

    resetCurrentListItem(smallestNode->sPath->pathLinks);
    pathLinksItem=getNextListItem(smallestNode->sPath->pathLinks);
    TEST_ASSERT_EQUAL_LINK_LIST_ITEM((Link*)pathLinksItem->data,&nodeA,&nodeC,1);
    pathLinksItem=getNextListItem(smallestNode->sPath->pathLinks);
    TEST_ASSERT_EQUAL_LINK_LIST_ITEM((Link*)pathLinksItem->data,&nodeB,&nodeA,3);
    pathLinksItem=getNextListItem(smallestNode->sPath->pathLinks);
    TEST_ASSERT_NULL(pathLinksItem);

    TEST_ASSERT_NULL(root);
}
//modifyGraphNodeWithShorterPath(Link*ListItemData,GraphPath * rootTree,
//GraphPath * nodeOut,GraphPath * currentPointingNode)
//ListItemData is the data that retreived from the linklistItem of nearest node
// rootTree is the working AVLtree that havent been checked for ShortestPathNode
// the nodeOut is the node is going to check is the new path is better than the old path
// the currentPointingNode is used to compare the pathCost and add the pathLink if
// the new path is better than the original one

/**                                                 rootTree
*              3
*         (A)------(B)                         (2)d           (2)d
*        1 \     7 /                              \    ---->   \
*           \    /                                (7)B         (4)b
*            (C)------(D)
*                   2
**/
//C is flagged
//current pointed to nodeA
// C is already checked so didnt added into the rootTree
void test_modifyGraphNodeWithShorterPath(void){
    //create GraphPath
    initShortestPathNode(&sPathD,&nodeD,&nodeC,2,&pathLinkCD);
    initGraphPath(&gPathD,NULL,&gPathB,1,&sPathD);
    initShortestPathNode(&sPathB,&nodeB,&nodeC,7,&pathLinkCB);
    initGraphPath(&gPathB,NULL,NULL,0,&sPathB);
    initShortestPathNode(&sPathA,&nodeA,&nodeC,1,&pathLinkCA);
    initGraphPath(&gPathA,NULL,NULL,0,&sPathA);
    // init link item
    initlinkItemData(&linkAB,&nodeB,&nodeA,3);
    initlinkItemData(&linkCA,&nodeA,&nodeC,1);
    initlinkItemData(&linkCB,&nodeB,&nodeC,7);
    initlinkItemData(&linkCD,&nodeD,&nodeC,2);
    //init listItem
    initListItem(&listItemCA, NULL,(void*)&linkCA);
    initListItem(&listItemCB, NULL,(void*)&linkCB);
    initListItem(&listItemCD, NULL,(void*)&linkCD);
    initListItem(&listItemAB, NULL,(void*)&linkAB);
    // init List
    initList(&pathLinkCB,&listItemCB ,&listItemCB ,1 ,&listItemCB);
    initList(&pathLinkCD,&listItemCD ,&listItemCD ,1 ,&listItemCD);
    initList(&pathLinkCA,&listItemCA ,&listItemCA ,1 ,&listItemCA);
    //expected path

    //modify B from 7 to 4
    root=modifyGraphNodeWithShorterPath(&linkAB,&gPathD,&gPathB,&gPathA);
    smallestNode = (GraphPath*)findSmallestNode((Node*)root);
    root = (GraphPath*)avlDelete((Node*)root,smallestNode->sPath,(Compare)graphCompareForAvlDelete);
    TEST_ASSERT_EQUAL(2,smallestNode->sPath->pathCost);
    TEST_ASSERT_EQUAL_PTR(&nodeD,smallestNode->sPath->dst);
    TEST_ASSERT_EQUAL_PTR(&nodeC,smallestNode->sPath->src);

    resetCurrentListItem(smallestNode->sPath->pathLinks);
    pathLinksItem=getNextListItem(smallestNode->sPath->pathLinks);
    TEST_ASSERT_EQUAL_LINK_LIST_ITEM(pathLinksItem->data,&nodeD,&nodeC,2);
    pathLinksItem=getNextListItem(smallestNode->sPath->pathLinks);
    TEST_ASSERT_NULL(pathLinksItem);

    smallestNode = (GraphPath*)findSmallestNode((Node*)root);
    root = (GraphPath*)avlDelete((Node*)root,smallestNode->sPath,(Compare)graphCompareForAvlDelete);
    TEST_ASSERT_EQUAL(4,smallestNode->sPath->pathCost);
    TEST_ASSERT_EQUAL_PTR(&nodeB,smallestNode->sPath->dst);
    TEST_ASSERT_EQUAL_PTR(&nodeC,smallestNode->sPath->src);

    resetCurrentListItem(smallestNode->sPath->pathLinks);
    pathLinksItem=getNextListItem(smallestNode->sPath->pathLinks);
    TEST_ASSERT_EQUAL_LINK_LIST_ITEM((Link*)pathLinksItem->data,&nodeA,&nodeC,1);
    pathLinksItem=getNextListItem(smallestNode->sPath->pathLinks);
    TEST_ASSERT_EQUAL_LINK_LIST_ITEM((Link*)pathLinksItem->data,&nodeB,&nodeA,3);
    pathLinksItem=getNextListItem(smallestNode->sPath->pathLinks);
    TEST_ASSERT_NULL(pathLinksItem);

}



/**
*              3
*         (A)------(B)                         (2)d
*        1 \     3 /                              \    ----> no change
*           \    /                                (3)B
*            (C)------(D)
*                   2
**/
//C is flagged

void test_modifyGraphNodeWithShorterPath_for_new_pathcost_longer_than_old_pathCost(void){
    //create GraphPath
    initShortestPathNode(&sPathD,&nodeD,&nodeC,2,&pathLinkCD);
    initGraphPath(&gPathD,NULL,&gPathB,1,&sPathD);
    initShortestPathNode(&sPathB,&nodeB,&nodeC,3,&pathLinkCB);
    initGraphPath(&gPathB,NULL,NULL,0,&sPathB);
    initShortestPathNode(&sPathA,&nodeA,&nodeC,1,&pathLinkCA);
    initGraphPath(&gPathA,NULL,NULL,0,&sPathA);
    // init link item
    initlinkItemData(&linkAB,&nodeB,&nodeA,3);
    initlinkItemData(&linkCA,&nodeA,&nodeC,1);
    initlinkItemData(&linkCB,&nodeB,&nodeC,3);
    initlinkItemData(&linkCD,&nodeD,&nodeC,2);
    //init listItem
    initListItem(&listItemCA, NULL,(void*)&linkCA);
    initListItem(&listItemCB, NULL,(void*)&linkCB);
    initListItem(&listItemCD, NULL,(void*)&linkCD);
    initListItem(&listItemAB, NULL,(void*)&linkAB);
    // init List
    initList(&pathLinkCB,&listItemCB ,&listItemCB ,1 ,&listItemCB);
    initList(&pathLinkCD,&listItemCD ,&listItemCD ,1 ,&listItemCD);
    initList(&pathLinkCA,&listItemCA ,&listItemCA ,1 ,&listItemCA);
    //expected path

    //modify B from 7 to 4
    root=modifyGraphNodeWithShorterPath(&linkAB,&gPathD,&gPathB,&gPathA);
    smallestNode = (GraphPath*)findSmallestNode((Node*)root);
    root = (GraphPath*)avlDelete((Node*)root,smallestNode->sPath,(Compare)graphCompareForAvlDelete);
    TEST_ASSERT_EQUAL(2,smallestNode->sPath->pathCost);
    TEST_ASSERT_EQUAL_PTR(&nodeD,smallestNode->sPath->dst);
    TEST_ASSERT_EQUAL_PTR(&nodeC,smallestNode->sPath->src);

    resetCurrentListItem(smallestNode->sPath->pathLinks);
    pathLinksItem=getNextListItem(smallestNode->sPath->pathLinks);
    TEST_ASSERT_EQUAL_LINK_LIST_ITEM(pathLinksItem->data,&nodeD,&nodeC,2);
    pathLinksItem=getNextListItem(smallestNode->sPath->pathLinks);
    TEST_ASSERT_NULL(pathLinksItem);

    smallestNode = (GraphPath*)findSmallestNode((Node*)root);
    root = (GraphPath*)avlDelete((Node*)root,smallestNode->sPath,(Compare)graphCompareForAvlDelete);
    TEST_ASSERT_EQUAL(3,smallestNode->sPath->pathCost);
    TEST_ASSERT_EQUAL_PTR(&nodeB,smallestNode->sPath->dst);
    TEST_ASSERT_EQUAL_PTR(&nodeC,smallestNode->sPath->src);

    resetCurrentListItem(smallestNode->sPath->pathLinks);
    pathLinksItem=getNextListItem(smallestNode->sPath->pathLinks);
    TEST_ASSERT_EQUAL_LINK_LIST_ITEM((Link*)pathLinksItem->data,&nodeB,&nodeC,3);
    pathLinksItem=getNextListItem(smallestNode->sPath->pathLinks);
    TEST_ASSERT_NULL(pathLinksItem);

}

/**
*              3
*         (A)------(B)                         (2)d
*        1 \     7 /                              \
*           \    /                                (7)B
*            (C)------(D)
*                   2
**/
//current node points at A
// nodeC is already marked

void test_findGraphPath_on_right(void){
    //create GraphPath
    initShortestPathNode(&sPathD,&nodeD,&nodeC,2,NULL);
    initGraphPath(&gPathD,NULL,&gPathB,1,&sPathD);
    initShortestPathNode(&sPathB,&nodeB,&nodeC,7,NULL);
    initGraphPath(&gPathB,NULL,NULL,0,&sPathB);

    root=findGraphPath(&gPathD,&nodeB);
    TEST_ASSERT_EQUAL_PTR(&gPathB,root);
}

/**
*              3
*         (A)------(B)          Working AVl        (2)d
*        1 \     7 /           -->               /    \
*           \    /                             (1)a   (7)B
*            (C)------(D)
*                   2
**/
//current node points on C

void test_findGraphPath_on_left(void){
    //create GraphPath
    initShortestPathNode(&sPathD,&nodeD,&nodeC,2,NULL);
    initGraphPath(&gPathD,&gPathA,&gPathB,0,&sPathD);
    initShortestPathNode(&sPathB,&nodeB,&nodeC,7,NULL);
    initGraphPath(&gPathB,NULL,NULL,0,&sPathB);
    initShortestPathNode(&sPathA,&nodeA,&nodeC,7,NULL);
    initGraphPath(&gPathA,NULL,NULL,0,&sPathA);

    root=findGraphPath(&gPathD,&nodeA);
    TEST_ASSERT_EQUAL_PTR(&gPathA,root);
}
