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
#include "ShortestPathListCompare.h"
#include "LinkedListCompare.h"
#include "Exception.h"
#include "AvlError.h"
#include "Processor.h"
#include "ShortestPathError.h"

void findShortestPath(NetworkNode * nNode , char * name){
    List * shortestPathList ;
    ListItem * listItem;
    ShortestPathNode * sPath;
    if(name == NULL){
        throwException(ERR_DST_NAME_NULL,"Invalid input destination ode name");
    }
    shortestPathList = generateShortestPath(nNode);
    listItem =findListItem(shortestPathList,name,(LinkedListCompare)shortestPathListCompare);
    if(listItem == NULL){
        throwException(ERR_SPATH_NODE_NOT_FOUND,"Couldn't find and locate %s in ShortestPath",name);
    }
    printShortestPathDetails(nNode,listItem->data);
}

void printShortestPathDetails(NetworkNode * nNode,ShortestPathNode * sPath){
    ShortestPathNode * currentPath = sPath;
    if(nNode == NULL){
        throwException(ERR_NETWORK_NODE_NULL,"Couldn't print as input networkNode is NULL");
    }
    else if (sPath == NULL){
        throwException(ERR_SPATH_NULL,"Couldn't print as input shortestPath is NULL");
    }
    printf("\n================================= \n");
    printf("ShortestPath from source %s to %s \n" ,nNode->name,sPath->id->name);
    printf("Total Path cost is %d \n",sPath->pathCost);
    printf("%s ",currentPath->id->name);
    currentPath = currentPath->parent;
    while(currentPath != NULL){
        printf("< ");
        printf("%s ",currentPath->id->name);
        currentPath = currentPath->parent;
    }
    printf(" \n================================= \n");
}

void findAllShortestPathCost(NetworkNode * nNode){
    List * shortestPathList ;
    if(nNode == NULL)
        throwException(ERR_NETWORK_NODE_NULL,"Couldn't print all path cost as input networkNode is NULL");
    shortestPathList = generateShortestPath(nNode);
    printf("\nAll Shortest path cost from %s \n",nNode->name);
    printf("------------------------ \n");
    listForEach(shortestPathList,(Processor)printPathCostFromShortestPath);
    printf("------------------------ \n");
}

void findAllShortestPath(NetworkNode * nNode){
    List * shortestPathList ;
    if(nNode == NULL)
        throwException(ERR_NETWORK_NODE_NULL,"Couldn't print all path cost as input networkNode is NULL");
    shortestPathList = generateShortestPath(nNode);
    printf("\nAll Shortest path from %s \n",nNode->name);
    printf("------------------------ \n");
    listForEach(shortestPathList,(Processor)printPathCostFromShortestPath);
    printf("------------------------ \n");
}

void printPathCostFromShortestPath(ListItem * item){
    ShortestPathNode * sPath;
    if (item == NULL)
        throwException(ERR_SPATH_LIST_ITEM_NULL,"couldn't print as input shortestPath is NULL");
    sPath = item ->data;
    printf("| %s's Path cost : %d |\n",sPath->id->name,sPath->pathCost);
}

List * generateShortestPath(NetworkNode * nNode){
    GraphPath * gPathNode;
    List * linkedList;
    if(nNode == NULL){
        throwException(ERR_NETWORK_NODE_NULL," source node is NULL and couldn't generate ShortestPath ");
    }
    resetWorkingAVL();
    linkedList = createList(); //initialize the list for shortestPath
    addGraphPathIntoWorkingAVL(createFirstShortestPath(nNode)); //add source node into working Tree
    gPathNode = findSmallestPathCostFromAVL();   //find the smallestNode (source Node)
    while(gPathNode != NULL){ //find the smallest gPathNode until the root tree is NULL
      addNeighbouringNode(gPathNode); //find the NearestNode and Add into working Tree
      gPathNode->sPath->id->marked = 1;  //mark the current pointed networkNode as checked
      linkedList = listAddItemToHead(linkedList,(void*)gPathNode->sPath); //after marked then add shortestPath into Spath LinkedList
      deleteGraphPathFromWorkingAVL(gPathNode->sPath); //delete the gPath from both tree
      gPathNode = findSmallestPathCostFromAVL(); //find the smallestNode
    }
    return linkedList;
}

void addNeighbouringNode(GraphPath* graphPath){
    List * nearestNodeLinkedList;
    ListItem * listItem;
    Link * linkItemData;
    ShortestPathNode * sPathToAdd;
    if(graphPath == NULL)
        return ;
    nearestNodeLinkedList= getIteratorOfLinks(graphPath->sPath->id);   //retreive the link list
    resetCurrentListItem(nearestNodeLinkedList);      // reset the linkedList
    listItem = getCurrentListItem(nearestNodeLinkedList);
    while(listItem !=NULL) { //add all listItem until the current points to NULL
        linkItemData = (Link*)listItem->data;    //retreive the data with cost, head , tail
        sPathToAdd= createShortestPathFromLinkItemData(graphPath->sPath,linkItemData); //create the shortestPath from LinkedListItemData
        compareAndAddShortestPathIntoWorkingAVL(sPathToAdd); //compare the previous and new pathCost and add into the working Tree
        listItem = getNextListItem(nearestNodeLinkedList);   // get next List Item
    }
}

void compareAndAddShortestPathIntoWorkingAVL(ShortestPathNode * sPathToAdd){
    GraphPath * gPath;
    GraphPath * rootTree;
    int pathCostCompare;
    if(sPathToAdd == NULL)
        return;
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
