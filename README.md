# ShortestPath

## 1.0 About Shortest Path
This is the Shortest Path project which a algorithm that search and find the shortest path from the source to the destination node. \
The findShortestPath function will generate a list of shortestPath from the source to all Node and print out the shortestPath with the path cost from the user input.

This Shortest Path is based on one of the shortest path algorithm which is called **Dijkstra algorithm** that allows user to calculate and find the shortest path between one node that the user pick and every other node in the graph. 
![mapdrawio(1)](https://user-images.githubusercontent.com/51066670/72487979-a4b0b180-384a-11ea-9a5e-24155f5794f8.png)
# 2.0 Finding the Shortest Path
In this project , submodule of AVL tree and LinkedList <!--add the link there --> is required for this shortest path to works.
Shortest path project requires linkedlist to generate a list of shortest Path and store a list of nearest node in the Network Node.
AVL tree which is a self-balancing binary tree also requires in this project as it able balance the tree and the find 
smallest path in the working tree for finding the next nearest network.

## 2.1 How does this shortest Path works 
1. Initially the first selected (source) Network node will added with GraphPath node(contains shortestPath details) into the tree. 
![1](https://user-images.githubusercontent.com/51066670/72495870-e188a280-3862-11ea-8f56-4e2c05fbd115.png)
2. The system will find the node with the smallest path cost from the AVL tree and actually finds and add all the nearest Network Node in GraphPath node from the node with smallest path cost.If the system found there's existing node with larger path cost compared to new path cost , system will override the old node and replaced it with the new node with smaller path cost and new path.
![Copy x2 of Untitled Diagram](https://user-images.githubusercontent.com/51066670/72496001-36c4b400-3863-11ea-97da-5add51a905f4.png)
3. After adding all nearest node from the node with smallest path cost , the network node in the graphPath node with the smallest path cost will be marked as verified shortest path from source.
![2](https://user-images.githubusercontent.com/51066670/72495867-e188a280-3862-11ea-9c21-9fd21bc6138d.png)
4. The smallest node with  marked network Node will be removed from the from the working Tree.
![3](https://user-images.githubusercontent.com/51066670/72495869-e188a280-3862-11ea-8fef-4de6c889d7b7.png)
5. The shortest path node that contains marked network node and some cost data will added into the final linkedList that stores all the final shortest path details.

6. The system will continue find the smallest node and repeat the step from 2 to 5 until the working tree is empty (all network node has shortest path calculated and the node is already marked as checked). 

7. Lastly the program will return a linkedList with all ShortestPath data.

# 3.0 Network Node
Network node is a node that consists of the node name , the links that contains all the nearest node and marked flag that indicates is the network Node marked and it has already confirm that the shortest path data in the linkedList are the most shortest path in the network map.

# 4.0 The AVL tree in ShortestPath
This AVL tree will act as a working tree for this project to actually store the node that the system found when searching the nearest node , it will only add the network node that has not marked (marked means the nearest node of the network node has been checked and verified with the shortestPath).The structure of the node in the working AVL will be GraphPath Node.

The AVL tree actually separated into two AVL tree one is sorted with the path Cost and another one is sorted by node Name. Once the shortestPath program add anything into the node, both path cost tree and node Name will add the node into the tree . 
![Copy of Copy of Untitled Diagram](https://user-images.githubusercontent.com/51066670/72492658-f19b8480-3858-11ea-9ceb-c5a8571905b3.png)
The reason why we separates two working AVL tree is because sorting with path Cost is used for removal of smallest node as stated on the steps 2 on 2.1 .

Sorting with node Name is used to locates the node and extract the pathCost out for comparision when the system found out this graphPath node with other shortestPath details to reach the same destination are exist in the tree. The system will extract this node from the pathName for comparision to decide whether should replace the node with the newer path depending on the path Cost. This due to cons of the AVL tree that unable to store the node with same value in a same tree .Thus , an linkedList is exist inside the graphPath Node
to store the node with the same cost.

## 4.3 Adding the node 
Adding graphPath node on the node Name Tree is similar as the normal adding function in AVL Tree . 
But for insertion (adding) of graphPath node on the path cost AVL tree has a bit difference between the normal adding function in AVL Tree.As it is possible to have a **same cost** on different path such as (A) -> (B) has a path cost of 2 and (A) -> (C) also has a path cost of 2. This is cause problem on AVL tree as the submodule AVL tree that this project used **does not support middle node that has a same value as its parent.**
![Copy of Copy of Copy of Untitled Diagram](https://user-images.githubusercontent.com/51066670/72493966-72f51600-385d-11ea-87fd-9a58705d71d8.png)
As this problem exist, this program provide a solution which the function of adding the node on path cost tree will catch exception from the original avlAdd function . As we know that the AvlAdd function will throw exception where if the node with the same path cost has been exist inside . The program will catch the exception and executes another task to actually add the node into the same path cost linkedlist on the graphPath with the same cost.

## 4.4 Removing the node
Removing the graphPath node on the node Name Tree is similar as the normal delete function in AVL Tree.
But for removal (delete) of graphPath node on the path cost AVL tree is different than remvoing the node from node name AVL tree due to the consideration of same cost node on the AVL tree for path cost.
Thus , before removing the specific node ,user are requires to insert both pathCost and name in order to remove a node in pathCost binary tree. the system will try to find the node from the path cost with the user input path cost to delete. 

After the system found the parent node with same path cost , the system will starts to compare the name. 
If the name match with the parent node ,the system will remove the node and check whether is there any (shortest path with same path cost)graphPath node in the same cost list .
If there is graphPath node in the same cost list , the head of the same cost list will be replacing the deleted Parent Node.

If the name does not match with the parent node , and there is (a list of shortest path node with same cost) graphPath node in the same cost list of the parent node.The system will starts to iterate the same cost list and compare the node with the name .After the system found a same name in listItem with the input name , system will runs linkedlist function to actually remove the listItem that carries the graphPath Data. 

![Copy of Copy of Untitled Diagram(3)](https://user-images.githubusercontent.com/51066670/72494011-8f914e00-385d-11ea-96e1-7dc52f3ab4c1.png)

## 4.5 Finding the smallest node
Finding the smallest node is pretty simple , it is just take the most left node (smallest on AVL tree) on the path Cost AVL tree.
if the smallest node has a list of same cost graphPath , it will return the head of the same cost linked list.

# 5.0 Creating ShortestPath node when the node was found at nearest node
When a node was found at the nearest current pointing node , it will automatically generate a shortestPath node from the nearest node that carries all the node information including the network node , parent , path cost (cost from source to destination) and link cost(cost from previous node to destination node) by using this function createShortestPathFromLinkItemData. This node is used to compares the node with same path Name in the AVL tree to compare the path Cost and decides whether to replace the node with newer path cost node.

When a shortestPath node is generated , the parent of the shortestPath node will automatically assigned with the data of shortestPath node in the current pointing node. Its path cost will be  `path cost = parent path cost + current link cost` and its link cost will be the cost value in the LinkItemData that consist of head , tail and the cost.

For example , 
![Copy of Untitled Diagram(3)](https://user-images.githubusercontent.com/51066670/72495606-22cc8280-3862-11ea-931a-5656722b4aad.png)
## 5.1 Adding the node into tree after ShortestPath node was created
After a shortest Path node was created , system will check whether is the id (network node) inside the shortest path marked (confirmed as the shortest path to destination node in the map).The system will only add the graphPath that stores the shortestPath data into both tree when is not marked. this node will also be compared with the node inside the tree to check is there any node has similar destination and with different path Cost to decide whether should the node to be overriden or keep the old node. 

## 5.2 overriding the node with larger old path cost with new node with smaller path cost
overriding the node is pretty simple, after the system found that the new node has a shorter path cost than the existing node in AVLTree 
the system will try to remove the old node with a longer path cost and replace it with the new node with smaller path cost.


# 6.0 Printing out the shortest path details
User are able to find the shortest path details by implementing this three function
```
void findShortestPath(NetworkNode * nNode , char * name);
void findAllShortestPathCost(NetworkNode * nNode);  
void findAllShortestPathLink(NetworkNode * nNode);
```
## 6.1 findShortestPath
`findShortestPath(nodeA , "nodeF");` This line of code is used to find the shortest path from the source network node A to network node F.
![mapdrawio(1)](https://user-images.githubusercontent.com/51066670/72496342-2cef8080-3864-11ea-82de-56a3dc5b111f.png)
## 6.2 findAllShortestPathCost
`findAllShortestPathCost(nodeA);` This line of code is used to find all the path cost of the shortest path from the source A to all network node.
![mapdrawio(2)](https://user-images.githubusercontent.com/51066670/72496343-2d881700-3864-11ea-8069-c074ba8506f0.png)
## 6.3 findAllShortestPathLink
`findAllShortestPathLink(nodeA);` This line of code is used to find all the shortest path from the source network node A to all network node.
![mapdrawio(3)](https://user-images.githubusercontent.com/51066670/72496344-2d881700-3864-11ea-8ff9-856c134ce307.png)

# 7.0 Reference
1. https://www.codingame.com/playgrounds/1608/shortest-paths-with-dijkstras-algorithm/dijkstras-algorithm
2. https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
3. https://github.com/owencho/AVLTree
4. https://github.com/owencho/LinkedList
