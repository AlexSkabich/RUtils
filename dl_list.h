#ifndef _DL_LIST_H_
#define _DL_LIST_H_

#define DLLIST_API_ _DL_LIST_H_


#include <stdlib.h>
#include <string.h>
#include "misc.h"
#include <stdint.h>


typedef enum
{
  OUT_OF_LIST,
  IN_LIST
} NodeStatus;


struct dlNode
{
  char* data;
  NodeStatus type;
  struct dlNode *next;
  struct dlNode *prev;
};
typedef struct dlNode dlNode;

struct dl_List
{
  dlNode *begin;
  dlNode *end;
};
typedef struct dl_List dl_List;

DLLIST_API_ internal void dl_init(dl_List *List);
DLLIST_API_ void dl_clear(dl_List *List);
DLLIST_API_ dlNode* createNode(const char* data);
DLLIST_API_ void addNode(dl_List *List, dlNode *prevNode, dlNode *new_node);
DLLIST_API_ void deleteNode(dlNode *del_node);
DLLIST_API_ void traversing_forward(dl_List List);
DLLIST_API_ void traversing_backward(dl_List List);


#ifdef DL_LIST_IMPLEMENTATION

internal void dl_init(dl_List* List)
{
  List->begin = (dlNode*)malloc(sizeof(dlNode));
  List->end = (dlNode*)malloc(sizeof(dlNode));
  List->begin->data = NULL;
  List->end->data   = NULL;

  List->begin->type = IN_LIST;
  List->end->type   = IN_LIST;

  List->begin->prev = NULL;
  List->begin->next = List->end;
  List->end->prev = List->begin;
  List->end->next = NULL;
}

dlNode* createNode(const char* data)
{
  dlNode* new_node;
  new_node = (dlNode*)malloc(sizeof(dlNode));
  const size_t n = strlen(data);
  new_node->data = (char*)malloc(n);
  new_node->type = OUT_OF_LIST;
  memcpy(new_node->data, data, n);
  return new_node;
}

void addNode(dl_List *List, dlNode *prevNode, dlNode *new_node)
{
  if(prevNode->type != IN_LIST || new_node->type != OUT_OF_LIST)
    {
      printf("prevNode should be in list and new_node out of list\n");
      return;
    }
  new_node->prev = prevNode;
  new_node->type = IN_LIST;
  prevNode->next = new_node;
  new_node->next = List->end;
  List->end->prev = new_node;
}

void deleteNode(dlNode *del_node)
{
  // prevNode -=- del_node -=- nextNode
  del_node->prev->next = del_node->next;
  del_node->next->prev = del_node->prev;
  free(del_node);
}

void dl_clear(dl_List *List)
{
  while(List->begin->next != NULL && List->begin->next->data != NULL)
    {
      free(List->begin->next);
      List->begin->next = List->begin->next->next;
    }
}

void traversing_forward(dl_List List)
{
  while(List.begin->next != NULL && List.begin->next->data != NULL)
    {
      printf("Node info: addr is %p, data is %s\n", List.begin->next, List.begin->next->data);
      List.begin->next = List.begin->next->next;
    }
}

void traversing_backward(dl_List List)
{
  while(List.end->prev != NULL && List.end->prev->data != NULL)
    {
      printf("Node info: addr is %p, data is %s\n", List.end->prev, List.end->prev->data);
      List.end->prev = List.end->prev->prev;
    }
}

void searchNode(dl_List List, const char* data)
{
  while(List.begin->next != NULL && List.begin->next->data != NULL)
    {
      if(strcmp(List.begin->next->data, data) == 0)
     	{
	  printf("Node info: addr is %p, data is %s\n", List.begin->next, List.begin->next->data);
	}
      List.begin->next = List.begin->next->next;
    }
  return;
}


#endif
#endif
