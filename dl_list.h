#ifndef _DL_LIST_H_
#define _DL_LIST_H_

#include <stdlib.h>
#include <string.h>
#include <stdint.h>


#define MALLOC(size) malloc(size)
// TODO(RT): reimplement allocator or provide many backends

typedef enum
{
  OUT_OF_LIST,
  IN_LIST
} NodeStatus;


struct Node
{
  char* data;
  NodeStatus type;
  struct Node *next;
  struct Node *prev;
};
typedef struct Node Node;

struct dl_List
{
  Node *begin;
  Node *end;
};
typedef struct dl_List dl_List;

void dl_init(dl_List *List);
void dl_clear(dl_List *List);
Node* createNode(const char* data);
void addNode(dl_List *List, Node *prevNode, Node *new_node);
void deleteNode(Node *del_node);
void traversing_forward(dl_List List);
void traversing_backward(dl_List List);


#ifdef DL_LIST_IMPLEMENTATION

void dl_init(dl_List* List)
{
  List->begin = (Node*)MALLOC(sizeof(Node));
  List->end = (Node*)MALLOC(sizeof(Node));
  List->begin->data = NULL;
  List->end->data   = NULL;

  List->begin->type = IN_LIST;
  List->end->type   = IN_LIST;

  List->begin->prev = NULL;
  List->begin->next = List->end;
  List->end->prev = List->begin;
  List->end->next = NULL;
}

Node* createNode(const char* data)
{
  Node* new_node;
  new_node = (Node*)MALLOC(sizeof(Node));
  const size_t n = strlen(data);
  new_node->data = (char*)MALLOC(n);
  new_node->type = OUT_OF_LIST;
  memcpy(new_node->data, data, n);
  return new_node;
}

void addNode(dl_List *List, Node *prevNode, Node *new_node)
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

void deleteNode(Node *del_node)
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
