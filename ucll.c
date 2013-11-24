/**
 * ll: Linked List
 * n: node
 * front/head = top of stack
 * back/end/tail = bottom of stack
 */
struct ll {
    void *data;
    struct ll *next;
};

void ll_init(struct ll **tail);//init list
void ll_init_node(struct ll *n, void *data);
struct ll *ll_head(struct ll **list);
void ll_push(struct ll **list, struct ll *n); //push onto top of stack
void ll_append(struct ll **list, struct ll *n); //add to end of list
struct ll *ll_pop(struct ll **list); //remove and return top of stack
struct ll *ll_pop_append(struct ll **list); //returns pop() and re-appends it
struct ll *ll_next(struct ll **list, struct ll *n); //returns next or NULL if at end
 
//.c
#include <stddef.h>
#include <assert.h>
 
void ll_init(struct ll **tailp) {
    *tailp = NULL;
}

void ll_init_node(struct ll *n, void *data) {
    n->next = n;
    n->data = data;
}

#define LL_ASSERT_VALID(n) assert({ assert(n); struct ll *cur = n->next; while (cur != n) { assert(cur); cur = cur->next; } 1; })
 
struct ll *ll_head(struct ll **tail) {
    assert(tail);
    return *tail? (*tail)->next: NULL;
}
 
void ll_push(struct ll **tail, struct ll *n) {
    assert(tail);
    LL_ASSERT_VALID(n);
    if (*tail) {
        struct ll *head = (*tail)->next;
        (*tail)->next = n->next? n->next: n;
        n->next = head;
    } else {
        n->next = n;
        *tail = n;
    }
}
 
void ll_append(struct ll **tail, struct ll *n) {
    ll_push(tail, n);
    *tail = n;
}
 
struct ll *ll_pop(struct ll **tail) {
    assert(tail);
    struct ll *head = (*tail)->next;
    if (head == *tail) {
        *tail = NULL;
    } else {
        (*tail)->next = head->next;
    }
    head->next = head;
    return head;
}
 
struct ll *ll_pop_append(struct ll **tail) {
    assert(tail);
    if (*tail) {
        *tail = (*tail)->next;
    }
    return *tail;
}
 
struct ll *ll_next(struct ll **tail, struct ll *n) {
    assert(tail);
    return n == *tail? NULL: n->next;
}
 
#define LL_TEST
#ifdef LL_TEST
#include <stdio.h>
 
#define TEST_SIZE 15
int main(int argc, void **argv) {
    static struct ll na[TEST_SIZE];
    static struct ll *list;
    static int ia[TEST_SIZE];
    int i;
 
    ll_init(&list);
    for (i = 0; i < TEST_SIZE; i++) {
        ia[i] = i;
        ll_init_node(&na[i], &ia[i]);
        ll_push(&list, &na[i]);
    }
    assert(ll_head(&list));
    assert(i == TEST_SIZE);
    struct ll *n;
    for (n = ll_head(&list); n; n = ll_next(&list, n)) {
        i--;
        assert(*(int*)n->data == i);
    }
    printf("Countdown from %i to 0!\r\n", TEST_SIZE - 1);
    while(ll_head(&list) && (n = ll_pop(&list))) {
        printf("%5i!\r\n", *(int*)n->data);
    }
    assert(ll_head(&list) == NULL);
    assert(i == 0);
    for (; i < TEST_SIZE; i++) {
        ll_append(&list, &na[i]);
    }
    printf("Count 0 up to %i!\r\n", TEST_SIZE - 1);
    struct ll *head = ll_head(&list);
    for (i = 0; i < TEST_SIZE; i++) {
        n = ll_pop_append(&list);
        printf("%5i!\r\n", *(int*)n->data);
        assert(*(int*)n->data == i);
    }
    assert(head == ll_head(&list));
    static struct ll extra1, extra2;
    static struct ll *extralist;
    ll_init(&extralist);
    ll_init_node(&extra1, (void*)13);
    ll_push(&extralist, &extra1);
    ll_init_node(&extra2, (void*)37);
    ll_append(&extralist, &extra2);
    ll_append(&extralist, list);//that's right! It works for lists too!
    assert(ll_pop(&extralist)->data == (void*)13);
    assert(ll_pop(&extralist)->data == (void*)37);
    assert(*(int*)ll_pop(&extralist)->data == 0);
}
#endif
