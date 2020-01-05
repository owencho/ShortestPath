#include "FindShortestPath.h"
#include "ShortestPathNode.h"
#include <stdlib.h>
#include <stdio.h>
#include "AvlAdd.h"
#include "AvlDelete.h"
#include "Compare.h"
#include "NetworkNode.h"
#include "List.h"
#include "ListItem.h"

List * findShortestPath(NetworkNode * nNode){
    GraphPath * gPathNode;
    List * linklist;
    resetWorkingAVL();
    addGraphPathIntoWorkingAVL(initFirstShortestPath(nNode));
    gPathNode = findSmallestPathCostFromAVL();
    while(gPathNode != NULL){
        deleteGraphPathFromWorkingAVL(gPathNode->sPath);
        findAndAddNearestNode(gPathNode);
        linklist = addMarkedNodeIntoLinkList(sPath);
        gPathNode = findSmallestPathCostFromAVL();
    }
    return linklist;
}

void * findAndAddNearestNode(GraphPath* graphPath){
    List * nearestNodelinkList;
    ListItem * listItem;
    Link * linkItemData;
    ShortestPathNode * sPathToAdd;
    nearestNodelinkList= getIteratorOfLinks(graphPath->id);   //retreive the link list
    resetCurrentListItem(nearestNodelinkList);      // reset the linkList

    while(nearestNodelinkList->current !=NULL) {
        listItem = getNextListItem(nearestNodelinkList);
        linkItemData = (Link*)listItem->data;    //retreive the data with cost, head , tail
        sPathToAdd= createShortestPathFromLinkItemData(graphPath->parent,linkItemData);
        compareAndAddShortestPath(sPathToAdd);
    }
    return sPathToAdd;
}

// we know that the source is always at C , so we just need to find its destination
// iterate through to find on the rootTree if not marked
// return the GraphPath of destinated
void* compareAndAddShortestPath(ShortestPathNode * sPathToAdd){
    GraphPath * gPath;
    if(sPathToAdd->id->marked ==0 ){
        gPath = getGraphPathFromNodeName(sPathToAdd->id->name);
        if(gPath->sPath->pathCost > sPathToAdd->pathCost){
            deleteGraphPathFromWorkingAVL(gPath->sPath);
        }
        addGraphPathIntoWorkingAVL(sPathToAdd);
    }
    return gPath;
}

GraphPath* initFirstShortestPath(NetworkNode * firstNode){
    GraphPath * rootTree=(GraphPath *)malloc(sizeof(GraphPath));
    List * firstGraphNodeList;
    sPath->id = firstNode;
    sPath->parent = NULL;
    sPath->pathCost = 0;
    sPath->pathLinks = 0;
    return sPath;
}
