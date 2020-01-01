#include "ShortestPath.h"
#include "ShortestPath.h"
#include <stdlib.h>
#include <stdio.h>
#include "AvlAdd.h"
#include "AvlDelete.h"
#include "Compare.h"
#include "NetworkNode.h"
#include "List.h"
#include "ListItem.h"
/*
Node * shortestPath(NetworkNode * nNode){
    List * linkList;
    Node*root,smallestNode;
    //first time
    linkList=getIteratorOfLinks(&nNode);
    smallestNode=(GraphPath*)avlRemoveSmallest((Node*)root,(Compare)graphCompare);
    root = findNearestNode(Working AVLTree,root); //generate AvlTree with cost (not shortest path yet)
    //second time
    return root;

*/
/*
GraphPath* findNearestNode(GraphPath* graphRoot,NetworkNode * node){
    Node * root;
    List * nearestNodelinkList;
    List * pathLinkList;
    ListItem * listItem;
    Link * linkItemData;
    Node * inputNode;
    GraphPath * gNode =(GraphPath *)malloc(sizeof(GraphPath)+sizeof(ShortestPath));
    root = (Node *)graphRoot;
    nearestNodelinkList= getIteratorOfLinks(node);   //retreive the link list
    resetCurrentListItem(nearestNodelinkList);      // reset the linkList

    while(nearestNodelinkList->current !=NULL) {
        listItem = getNextListItem(nearestNodelinkList);
        linkItemData = (Link*)listItem->data;    //retreive the data with cost, head , tail
      //  linkItemData -> cost = linkItemData -> cost + currentPointingNode->value->pathCost;
        if(linkItemData->head->marked ==0 ){
            //pathLinkList = compareShortestPath(GraphPath * currentPointingNode,GraphPath * rootTree,Link * linkItemData)
            //compare inside the working AVL tree see there is any shorter path (then if yes overwrite linkItemData and input PathLink)
            //compareShortestPath(GraphPath * root,Link * linkItemData)
            // pathLink(Link * linkItemData)
            //graphNode value points to shortestPath struct
            gNode =createGraphPath(createShortestPath(linkItemData,pathLinkList));
            root = avlAdd(root,(Node*)gNode,(Compare)graphCompare);
            return NULL; // remember to remove
        }
    }
    return (GraphPath*)root;
}

*/

/*
List * compareShortestPath(GraphPath * currentPointingNode,GraphPath * rootTree,Link * linkItemData){
    ListItem * listItem;
    Link * newItemData;
    List * nearestNodelinkList;
    GraphPath *nodeOut;
    nearestNodelinkList= getIteratorOfLinks(currentPointingNode->dst); //this might fail
    listItem= getNextListItem(nearestNodelinkList);
    while(listItem != NULL){
        newItemData = (Link*)listItem->data;
        if(newItemData->head->marked != 1){
            nodeOut = findGraphPath(rootTree, newItemData->head);
            if(nodeOut != NULL){
                nodeOut=modifyGraphNodeWithShorterPath(GraphPath * rootTree,GraphPath * nodeOut,GraphPath * currentPointingNode);
            }
            // we know that the source is always at C , so we just need to find its destination
            // iterate through to find on the rootTree if not marked
            // return the GraphPath of destinated
            // nodeOut =
        }
    }
}
// check is new route cost is smaller than pathCost
// if yes then override the old pathCost
// avlDelete it and add it back
*/

GraphPath* modifyGraphNodeWithShorterPath(Link*ListItemData,GraphPath * rootTree,GraphPath * nodeOut,GraphPath * currentPointingNode){
    double newPathCost;
    ListItem * newListItem;
    Link * newListItemData;
    Node*root;

    newPathCost = ListItemData->cost + currentPointingNode->sPath->pathCost;
    if(nodeOut->sPath->pathCost > newPathCost){
        root = avlDelete((Node*)rootTree,(void*)nodeOut->sPath,(Compare)graphCompareForAvlDelete); //remove the old node that contain old data
        nodeOut->sPath->pathCost = newPathCost;
        newListItemData = createLinkFromShortestPath(currentPointingNode->sPath);
        newListItem -> data = (void*)newListItemData; // put Link
        nodeOut->sPath->pathLinks = listAddItemToTail(nodeOut->sPath->pathLinks, newListItem);
        root = avlAdd(root,(Node*)nodeOut,(Compare)graphCompareForAvlAdd);
    }
    return (GraphPath*)root;
}


GraphPath* findGraphPath(GraphPath * root,NetworkNode * dstNode){
    GraphPath * graphNode = NULL;
    if(root->sPath->dst == dstNode){
      return root;
    }
    if(root->left != NULL){
        graphNode = findGraphPath(root->left,dstNode);
        if(graphNode !=NULL)
            return graphNode;
    }
    if (root->right != NULL){
        graphNode = findGraphPath(root->right,dstNode);
        if(graphNode !=NULL)
            return graphNode;
    }
    return root;
}

GraphPath * avlRemoveSmallestGraphPath(GraphPath*root){
    GraphPath * smallestNode = NULL;
    GraphPath * outNode = NULL;
    smallestNode = (GraphPath*)findSmallestNode((Node*)root);
    outNode = (GraphPath*)avlDelete((Node*)root,smallestNode->sPath,(Compare)graphCompareForAvlDelete);
    root = outNode;
    return smallestNode;
}
