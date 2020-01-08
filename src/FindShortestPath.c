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
#include "GraphPathAVL.h"

List * generateShortestPath(NetworkNode * nNode){
    GraphPath * gPathNode;
    List * linkList;
    resetWorkingAVL();
    linkList = createList(); //initialize the list for shortestPath
    addGraphPathIntoWorkingAVL(createFirstShortestPath(nNode)); //add source node into working Tree
    gPathNode = findSmallestPathCostFromAVL();   //find the smallestNode (source Node)
    while(gPathNode != NULL){ //find the smallest gPathNode until the root tree is NULL
        deleteGraphPathFromWorkingAVL(gPathNode->sPath); //found and then delete the gPath from both tree
        findAndAddNearestNode(gPathNode); //find the NearestNode and Add into working Tree
        gPathNode->sPath->id->marked = 1;  //mark the current pointed networkNode as checked
        linkList = listAddItemToHead(linkList, createListItem((void*)gPathNode->sPath)); //after marked then add shortestPath into Spath LinkList
        gPathNode = findSmallestPathCostFromAVL(); //find the smallestNode
    }
    return linkList;
}



void * findAndAddNearestNode(GraphPath* graphPath){
    List * nearestNodelinkList;
    ListItem * listItem;
    Link * linkItemData;
    ShortestPathNode * sPathToAdd;
    nearestNodelinkList= getIteratorOfLinks(graphPath->sPath->id);   //retreive the link list
    resetCurrentListItem(nearestNodelinkList);      // reset the linkList
    listItem = getCurrentListItem(nearestNodelinkList);
    while(listItem !=NULL) { //add all listItem until the link points to NULL
        linkItemData = (Link*)listItem->data;    //retreive the data with cost, head , tail
        sPathToAdd= createShortestPathFromLinkItemData(graphPath->sPath->parent,linkItemData); //create the shortestPath from linkListItemData
        compareAndAddShortestPathIntoWorkingAVL(sPathToAdd); //compare the previous and new pathCost and add into the working Tree
        listItem = getNextListItem(nearestNodelinkList);
    }
    return sPathToAdd;
}

// ask dr Poh about this
void* compareAndAddShortestPathIntoWorkingAVL(ShortestPathNode * sPathToAdd){
    GraphPath * gPath;
    GraphPath * rootTree;
    int pathCostCompare;
    if(sPathToAdd->id->marked ==0 ){
        gPath = getGraphPathFromNodeName(sPathToAdd->id->name);
        if(gPath != NULL){
            if(gPath->sPath->pathCost > sPathToAdd->pathCost)
                deleteGraphPathFromWorkingAVL(gPath->sPath);
            else
                return gPath;
        }
        return addGraphPathIntoWorkingAVL(sPathToAdd);
    }
    return NULL;
}
