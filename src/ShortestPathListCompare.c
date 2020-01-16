#include "ShortestPathListCompare.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int shortestPathListCompare (ListItem * listItem, char * name){
    ShortestPathNode * sPathNode;
    if(listItem == NULL)
        return 0;
    sPathNode = listItem->data;
    if(strcmp(sPathNode->id->name ,name)==0)
        return 1;
    return 0;
}
