#include "unity.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CException.h"
#include "ShortestPathNode.h"
#include "NetworkNode.h"
#include "List.h"
#include "ListItem.h"
#include "GraphPath.h"
#include "CustomAssert.h"

void setUp(void){}
void tearDown(void){}

Link  linkItData;
NetworkNode nodeA ,nodeB,nodeC,nodeD;
ShortestPathNode sPath;
ShortestPathNode * outSPathNode;
void initNetworkNode(NetworkNode * node, char*name,List * links,int marked){
    node->name = name;
    node-> links = links;
    node->marked = marked;
}
void initGraphPath(GraphPath*graphPath,GraphPath*left,GraphPath*right,int bFactor, ShortestPathNode * sPath){
    graphPath->left = left;
    graphPath->right = right;
    graphPath->bFactor = bFactor;
    graphPath->sPath = sPath;
}
void initList(List * link, ListItem * head ,ListItem * tail ,int count ,ListItem * current){
    link->head = head;
    link->tail = tail;
    link->count = count;
    link->current = current;
}
void initLink(Link * linkItemData,int cost,NetworkNode * head ,NetworkNode * tail){
    linkItemData->cost = cost;
    linkItemData->head = head;
    linkItemData->tail = tail;
}
void initShortestPathNode(ShortestPathNode *sPath,NetworkNode * id ,ShortestPathNode * parent ,int pathCost ,int linkCost){
    sPath->id = id;
    sPath->parent = parent;
    sPath->pathCost = pathCost;
    sPath->linkCost = linkCost;
}
/**
*
*         (A)      (B)
*        1 \     7 /
*           \    /            ------>     (0)C
*            (C)------(D)
*                   2
**/
//This function is used to convert the first networkNode into ShortestPathNode
void test_createFirstShortestPath(void){
      initNetworkNode(&nodeC,"nodeC",NULL,0);
      outSPathNode = createFirstShortestPath(&nodeC);
      TEST_ASSERT_EQUAL_SHORTEST_PATH(outSPathNode,&nodeC,NULL,0,0);
}

//This function is used to convert the first networkNode into ShortestPathNode
void test_createShortestPathFromLinkItemData(void){
      initLink(&linkItData,1,&nodeA,&nodeC);
      initNetworkNode(&nodeA,"nodeA",NULL,0);
      initNetworkNode(&nodeC,"nodeC",NULL,0);
      initShortestPathNode(&sPath,&nodeC,NULL,0,0);
      outSPathNode = createShortestPathFromLinkItemData(&sPath, &linkItData);
      TEST_ASSERT_EQUAL_SHORTEST_PATH(outSPathNode,&nodeA,&sPath,1,1);
}

void test_createShortestPathFromLinkItemData_parent_with_pathCost(void){
      initLink(&linkItData,1,&nodeA,&nodeC);
      initNetworkNode(&nodeA,"nodeA",NULL,0);
      initNetworkNode(&nodeC,"nodeC",NULL,0);
      initShortestPathNode(&sPath,&nodeC,NULL,3,1);
      outSPathNode = createShortestPathFromLinkItemData(&sPath, &linkItData);
      TEST_ASSERT_EQUAL_SHORTEST_PATH(outSPathNode,&nodeA,&sPath,4,1);
}

void test_createShortestPathFromLinkItemData_parentNULL_with_pathCost(void){
      initLink(&linkItData,1,&nodeA,&nodeC);
      initNetworkNode(&nodeA,"nodeA",NULL,0);
      initNetworkNode(&nodeC,"nodeC",NULL,0);
      initShortestPathNode(&sPath,&nodeC,NULL,3,1);
      outSPathNode = createShortestPathFromLinkItemData(NULL, &linkItData);
      TEST_ASSERT_EQUAL_SHORTEST_PATH(outSPathNode,&nodeA,NULL,1,1);
}
