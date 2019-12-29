#include "ShortestPath.h"
#include "ShortestPath.h"
#include <stdlib.h>
#include <stdio.h>
#include "AvlAdd.h"
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
GraphPath* findNearestNode(GraphPath* AVLroot,GraphPath * currentPointingNode){
    Node * root;
    List * nearestNodelinkList;
    List * pathLinkList;
    ListItem * listItem;
    Link * linkItemData;
    GraphPath * gNode;
    ShortestPath * sPath;
    root = (Node *)graphRoot;
    nearestNodelinkList= getIteratorOfLinks(node);   //retreive the link list
    resetCurrentListItem(nearestNodelinkList);      // reset the linkList

    while(nearestNodelinkList->current !=NULL) {
        listItem = getNextListItem(nearestNodelinkList);
        linkItemData = (Link*)listItem->data;    //retreive the data with cost, head , tail
        linkItemData -> cost = linkItemData -> cost + currentPointingNode->value->pathCost;
        if(linkItemData->head->marked ==0 ){
            //pathLinkList = compareShortestPath(GraphPath * currentPointingNode,GraphPath * rootTree,Link * linkItemData)
            //compare inside the working AVL tree see there is any shorter path (then if yes overwrite linkItemData and input PathLink)
            //compareShortestPath(GraphPath * root,Link * linkItemData)
            //create pathLinks
          //  pathLink(Link * linkItemData)
            sPath=createShortestPath(linkItemData,pathLinkList);  //graphNode value points to shortestPath struct
            gNode =createGraphPath(sPath);
            root = avlAdd(root,(Node*)gNode,(Compare)graphCompare);
        }
    }
    return (GraphPath*)root;
}

*/
// compare
//compareShortestPath(starting node from beginning,working AVLTree , )

List * compareShortestPath(GraphPath * currentPointingNode,GraphPath * rootTree,Link * linkItemData){
    ListItem * listItem;
    Link * newItemData;
    List * nearestNodelinkList;
    double newPathCost;
    GraphPath *nodeOut;
    nearestNodelinkList= getIteratorOfLinks(currentPointingNode->dst);
    listItem= getNextListItem(nearestNodelinkList);
    while(listItem != NULL){
        newItemData = (Link*)listItem->data;
        if(listItem->head->marked != 1){
            (GraphPath*)nodeOut = findGraphPath(rootTree, listItem->head);
            // we know that the source is always at C , so we just need to find its destination
            // iterate through to find on the rootTree if not marked
            // return the GraphPath of destinated
            newPathCost = listItem->cost + currentPointingNode->value->pathCost;
            if(nodeOut->value->pathCost > newPathCost){
              rootTree = avlDelete(rootTree,(Node*)nodeOut,(Compare)graphCompare);
              nodeOut->value->pathCost = newPathCost;
              //find new pathLink
            }
            // rootTree = avlDelete(rootTree,(Node*)nodeOut,(Compare)graphCompare);
            // nodeOut =
        }
    }

// check is new route cost is smaller than pathCost
// if yes then override the old pathCost
// avlDelete it and add it back


}

/*
List * pathLink(Link * linkItemData){
    List pathLinkList;
    pathLinkList=listAddItemToHead(&pathLinkList, ListItem * item );
}
*/

GraphPath* findGraphPath(GraphPath * root,NetworkNode * dstNode){
    if(root->value->dst == dstNode){
      return root;
    }
    if(root->left != NULL){
        root = findGraphPath(root->left,dstNode);
    }
    if (root->right != NULL){
        root = findGraphPath(root->right,dstNode);
    }
    return root;
}
