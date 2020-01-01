#include "GraphPath.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

GraphPath *createGraphPath(ShortestPath * sPath){
    GraphPath*graphPath= (GraphPath *)malloc(sizeof(GraphPath));
    graphPath->left = NULL;
    graphPath->right = NULL;
    graphPath->bFactor = 0;
    graphPath->sPath = sPath; // can change to shortestPath
    return graphPath;
}

ShortestPath* createShortestPath(Link * linkItemData, List * pathLinks){
    ShortestPath* sPath = (ShortestPath *)malloc(sizeof(ShortestPath));
    sPath->dst = linkItemData->head;
    sPath->src = linkItemData->tail;
    sPath->pathCost = linkItemData->cost;
    sPath->pathLinks = pathLinks;
    return sPath;
}

Link* createLinkFromShortestPath(ShortestPath * sPath){
    Link* linkItemData = (Link *)malloc(sizeof(Link));
    linkItemData->head= sPath->dst ;
    linkItemData->tail= sPath->src ;
    linkItemData->cost= sPath->pathCost ;
    return linkItemData;
}

List* createLinkListForShortestPath(NetworkNode * head,NetworkNode * tail,int cost){
    List * linkList = (List *)malloc(sizeof(List));
    Link *listItemData= (Link *)malloc(sizeof(Link));
    ListItem newListItem;
    listItemData->head =head;
    listItemData->tail =tail;
    listItemData->cost =cost;
    newListItem.data = (void*)listItemData;
    linkList->head =NULL;
    linkList->tail =NULL;
    linkList->count =0;
    linkList->current =NULL;
    linkList=listAddItemToHead(linkList,&newListItem);
    return linkList;
}
