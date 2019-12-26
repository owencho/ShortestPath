#include "ShortestPath.h"
/*
Node * shortestPath(NetworkNode * nNode,Compare compare){
    List * linkList;
    Node*root,smallestNode;
    //first time
    linkList=getIteratorOfLinks(&nNode);
    root = findNearestNode(nNode,nNode,compare , linkList);
    //second time
    for(root != NULL){
        smallestNode = findSmallestNode(root);
        root=avlDelete(root,smallestNode->value,compare);
        linkList=getIteratorOfLinks(smallestNode->nNode);
        root = findNearestNode(smallestNode->nNode,compare , linkList);
        nextNode= avlRemoveSmallest(root,compare);

    }
    return root;



Node * findNearestNode(NetworkNode * node,NetworkNode * firstNode,Compare compare , List * linkList){
    ListItem * listItem;
    Link*linkData;
    Node * root;
    GraphPath * gNode;
    resetCurrentListItem(linkList);
    while(listItem !=NULL) {
        listItem = getNextListItem(linkList);
        linkData = listItem->data;
        createGraphPath(gNode,linkData->cost,linkData->head);
        root = avlAdd(root,gNode,(compare)graphCompare);
    }
    return root;
}
*/
