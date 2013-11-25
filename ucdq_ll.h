#ifndef UCDQ_H
#define UCDQ_H
#include "ucdq.h"

void DQ_init_list(struct DQ **tail);
void DQ_init_node(struct DQ *n);
struct DQ *DQ_head(struct DQ **list);
//onto top of stack
void DQ_push(struct DQ **list, struct DQ *n);
//onto end of list
void DQ_append(struct DQ **list, struct DQ *n);
//remove and return top of stack
struct DQ *DQ_pop(struct DQ **list);
//returns pop() result and re-appends it
struct DQ *DQ_pop_append(struct DQ **list);
//returns element after n or NULL if at end
struct DQ *DQ_next(struct DQ **list, struct DQ *n);

#endif

