# ShortestPath

## 1.0 About Shortest Path
This is the Shortest Path project which a algorithm that search and find the shortest path from the source to the destination node
The findShortestPath function will generate a list of shortestPath from the source to all Node and print out the shortestPath with the path cost
from the user input.

This Shortest Path is based on one of the shortest path algorithm which is called Dijkstra algorithm that allows user
to calculate and find the shortest path between one node that the user pick and every other node in the graph. 

# 2.0 Finding the Shortest Path
In this project , submodule of AVL tree and LinkedList <!--add the link there --> is required for this shortest path to works.
Shortest path project requires linkedlist to generate a list of shortest Path and store a list of nearest node in the Network Node.
AVL tree which is a self-balancing binary tree also requires in this project as it able balance the tree and the find 
smallest path in the working tree for finding the next nearest network.

## 2.1 How does this shortest Path works 
1. Initially the first selected (source) Network node will added with GraphPath node(contains shortestPath details) into the tree. 

2. The system will find the node with the smallest path cost from the AVL tree and actually finds and add all the nearest Network Node in GraphPath node 
from the node with smallest path cost.If the system found there's existing node with larger path cost compared to new path cost , system will 
override<!-- put link here--> the old node and replaced it with the new node with smaller path cost and new path.

3. After adding all nearest node from the node with smallest path cost , the network node in the graphPath node with the smallest path cost will be marked as verified shortest path from source.

4. The smallest node that just been marked will be removed from the from the working Tree.

5. Then the system will find a 
# .0 The AVL tree in ShortestPath
This AVL tree will act as a working tree for this project to actually store the node that the system found when searching the nearest node , 
it will only add the network node that has not marked (marked means the nearest node of the network node has been checked and verified with the shortestPath)
