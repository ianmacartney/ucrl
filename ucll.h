#ifndef SOMETHING
#define SOMETHING
//INCLUDE

void ll_init(struct ll **tail);//init list
void ll_init_node(struct ll *n);
struct ll *ll_head(struct ll **list);
void ll_push(struct ll **list, struct ll *n); //push onto top of stack
void ll_append(struct ll **list, struct ll *n); //add to end of list
struct ll *ll_pop(struct ll **list); //remove and return top of stack
struct ll *ll_pop_append(struct ll **list); //returns pop() and re-appends it
struct ll *ll_next(struct ll **list, struct ll *n); //returns next or NULL if at end

#endif

