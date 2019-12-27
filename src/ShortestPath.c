#include "ShortestPath.h"
#include "ShortestPath.h"
#include <stdlib.h>
#include <stdio.h>
#include "../AvlTree/src/AvlAdd.h"
#include "../AvlTree/src/Compare.h"
#include "../LinkList/src/NetworkNode.h"
#include "../LinkList/src/List.h"
#include "../LinkList/src/ListItem.h"
/*
Node * shortestPath(NetworkNode * nNode){
    List * linkList;
    Node*root,smallestNode;
    //first time
    linkList=getIteratorOfLinks(&nNode);
    root = findNearestNode(&nNode,linkList); //generate AvlTree with cost (not shortest path yet)
    //second time
    for(root != NULL){
        nextNode= avlRemoveSmallest(root,(compare)graphCompare);
        //function to detect the shortestPath
    }
    return root;
*/


Node * findNearestNode(NetworkNode * node){
    Node* root;
    ShortestPath sPath;
    List * linkList;
    ListItem * listItem;
    Link * linkItemData;
    GraphPath  gNode;
    linkList= getIteratorOfLinks(node);   //retreive the link list
    resetCurrentListItem(linkList);      // reset the linkList
    while(linkList->current !=NULL) {
        listItem = getNextListItem(linkList);
        linkItemData = (Link*)listItem->data;    //retreive the data with cost, head , tail
        if(linkItemData->head->marked ==0 ){
            createShortestPath(&sPath,linkItemData);
            createGraphPath(&gNode,&sPath);
            root = avlAdd(root,(Node*)&gNode,(Compare)graphCompare);
        }
    }
    return root;
}
