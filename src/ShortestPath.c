#include "ShortestPath.h"
#include "NetworkNode.h"
#include "AvlAdd.h"
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


Node * findNearestNode(NetworkNode * node, List * linkList){
    Node * root;
    ListItem * listItem;
    Link linkData;
    GraphPath * gNode;
    ShortestPath sPath;
    resetCurrentListItem(linkList);
    while(listItem !=NULL) {
        listItem = getNextListItem(linkList);
        &linkData = listItem->data;
        createShortestPath(&sPath, &linkData);
        createGraphPath(gNode,&sPath);
        root = avlAdd(root,gNode,(compare)graphCompare);
    }
    return root;
}
