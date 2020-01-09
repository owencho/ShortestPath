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
#include "ListItem.h"
#include "GraphPathAVL.h"
#include "ShortestPathListCompare.h"
void findShortestPath(NetworkNode * nNode , char * name){
    List * shortestPathList ;
    ListItem * listItem;
    ShortestPathNode * sPath;
    shortestPathList = generateShortestPath(nNode);
    listItem =findListItem(shortestPathList,name,(LinkListCompare)shortestPathListCompare);
    printShortestPathDetails(nNode,listItem->data);
}

void printShortestPathDetails(NetworkNode * nNode,ShortestPathNode * sPath){
    ShortestPathNode * currentPath = sPath;
    printf("============================== \n");
    printf("ShortestPath from source %s to %s \n" ,nNode->name,sPath->id->name);
    printf("Total Path cost is %d \n",sPath->pathCost);
    printf("%s ",currentPath->id->name);
    currentPath = currentPath->parent;
    while(currentPath != NULL){
        printf("< ");
        printf("%s ",currentPath->id->name);
        currentPath = currentPath->parent;
    }
    printf(" \n============================== \n");
}

List * generateShortestPath(NetworkNode * nNode){
    GraphPath * gPathNode;
    List * linkList;
    resetWorkingAVL();
    linkList = createList(); //initialize the list for shortestPath
    addGraphPathIntoWorkingAVL(createFirstShortestPath(nNode)); //add source node into working Tree
    gPathNode = findSmallestPathCostFromAVL();   //find the smallestNode (source Node)
    while(gPathNode != NULL){ //find the smallest gPathNode until the root tree is NULL
        deleteGraphPathFromWorkingAVL(gPathNode->sPath); //found and then delete the gPath from both tree
        addNeighbouringNode(gPathNode); //find the NearestNode and Add into working Tree
        gPathNode->sPath->id->marked = 1;  //mark the current pointed networkNode as checked
        linkList = listAddItemToHead(linkList,(void*)gPathNode->sPath); //after marked then add shortestPath into Spath LinkList
        gPathNode = findSmallestPathCostFromAVL(); //find the smallestNode
    }
    return linkList;
}



void addNeighbouringNode(GraphPath* graphPath){
    List * nearestNodelinkList;
    ListItem * listItem;
    Link * linkItemData;
    ShortestPathNode * sPathToAdd;
    nearestNodelinkList= getIteratorOfLinks(graphPath->sPath->id);   //retreive the link list
    resetCurrentListItem(nearestNodelinkList);      // reset the linkList
    listItem = getCurrentListItem(nearestNodelinkList);
    while(listItem !=NULL) { //add all listItem until the current points to NULL
        linkItemData = (Link*)listItem->data;    //retreive the data with cost, head , tail
        sPathToAdd= createShortestPathFromLinkItemData(graphPath->sPath,linkItemData); //create the shortestPath from linkListItemData
        compareAndAddShortestPathIntoWorkingAVL(sPathToAdd); //compare the previous and new pathCost and add into the working Tree
        listItem = getNextListItem(nearestNodelinkList);   // get next List Item
    }
}

void compareAndAddShortestPathIntoWorkingAVL(ShortestPathNode * sPathToAdd){
    GraphPath * gPath;
    GraphPath * rootTree;
    int pathCostCompare;
    if(sPathToAdd->id->marked ==0 ){       //if the networkNode is not marked
        gPath = getGraphPathFromNodeName(sPathToAdd->id->name); //find and check is the node exist inside tree
        if(gPath != NULL){ //if the node exist inside tree
            if(gPath->sPath->pathCost > sPathToAdd->pathCost) //compare new PathCost and old PathCost
                deleteGraphPathFromWorkingAVL(gPath->sPath); // if new pathCost < old pathCost (remove the old node)
            else
                return; //if new pathCost > old pathCost (do nothing)
        }
        addGraphPathIntoWorkingAVL(sPathToAdd);  //add the node into working Tree
    }
}
