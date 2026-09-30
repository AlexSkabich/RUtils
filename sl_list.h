#ifndef _SINGLE_LINKED_LIST_
#define _SINGLE_LINKED_LIST_
#define SLLIST_API_ _SINGLE_LINKED_LIST_


struct slNode
{
  void *data;
  struct slNode *next;
};
typedef struct slNode slNode;

struct sl_list
{
  slNode Head;
};
typedef struct sl_list sl_list;

SLLIST_API_ internal void sllist_init(slNode Node);
SLLIST_API_ void sllist_addNode(slNode Node);
SLLIST_API_ void sllist_delNode(slNode Node);
SLLIST_API_ void sllist_searchNode(slNode Node);
SLLIST_API_ void sllist_traversary(slNode Node);

#ifdef _SLLIST_IMPLEMENTATION_

// implementations here


#endif
#endif
