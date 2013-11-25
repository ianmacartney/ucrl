#include <stddef.h>
#include <assert.h>
#include "ucdq_ll.h"

void DQ_init_list(struct DQ **tailp) {
    *tailp = NULL;
}

void DQ_init_node(struct DQ *n) {
    n->next = n;
}

#define LL_ASSERT_VALID(n) assert({ assert(n); struct DQ *cur = n->next; \
        while (cur != n) { assert(cur); cur = cur->next; } 1; })

struct DQ *DQ_head(struct DQ **tail) {
    assert(tail);
    return *tail? (*tail)->next: NULL;
}

void DQ_push(struct DQ **tail, struct DQ *n) {
    assert(tail);
    LL_ASSERT_VALID(n);
    if (*tail) {
        struct DQ *head = (*tail)->next;
        (*tail)->next = n->next? n->next: n;
        n->next = head;
    } else {
        n->next = n;
        *tail = n;
    }
}

void DQ_append(struct DQ **tail, struct DQ *n) {
    DQ_push(tail, n);
    *tail = n;
}

struct DQ *DQ_pop(struct DQ **tail) {
    assert(tail);
    struct DQ *head = (*tail)->next;
    if (head == *tail) {
        *tail = NULL;
    } else {
        (*tail)->next = head->next;
    }
    head->next = head;
    return head;
}

struct DQ *DQ_pop_append(struct DQ **tail) {
    assert(tail);
    if (*tail) {
        *tail = (*tail)->next;
    }
    return *tail;
}

struct DQ *DQ_next(struct DQ **tail, struct DQ *n) {
    assert(tail);
    return n == *tail? NULL: n->next;
}

#ifdef UCDQ_TEST
#include <stdio.h>
#define TEST_SIZE 15
int main(int argc, void **argv) {
    static struct DQ na[TEST_SIZE];
    static struct DQ *list;
    int i;

    DQ_init_list(&list);
    for (i = 0; i < TEST_SIZE; i++) {
        DQ_init_node(&na[i]);
        DQ_push(&list, &na[i]);
    }
    assert(DQ_head(&list));
    assert(i == TEST_SIZE);
    struct DQ *n;
    for (n = DQ_head(&list); n; n = DQ_next(&list, n)) {
        i--;
        assert(n == &na[i]);
    }
    printf("Countdown from %i to 0!\r\n", TEST_SIZE - 1);
    while(DQ_head(&list) && (n = DQ_pop(&list))) {
        printf("%5li!\r\n", n - na);
    }
    assert(DQ_head(&list) == NULL);
    assert(i == 0);
    for (; i < TEST_SIZE; i++) {
        DQ_append(&list, &na[i]);
    }
    printf("Count 0 up to %i!\r\n", TEST_SIZE - 1);
    struct DQ *head = DQ_head(&list);
    for (i = 0; i < TEST_SIZE; i++) {
        n = DQ_pop_append(&list);
        printf("%5li!\r\n", n - na);
        assert(n == &na[i]);
    }
    assert(head == DQ_head(&list));
    static struct DQ extra1, extra2;
    static struct DQ *extralist;
    DQ_init_list(&extralist);
    DQ_init_node(&extra1);
    DQ_push(&extralist, &extra1);
    DQ_init_node(&extra2);
    DQ_append(&extralist, &extra2);
    DQ_append(&extralist, list);//that's right! It works for lists too!
    assert(DQ_pop(&extralist) == &extra1);
    assert(DQ_pop(&extralist) == &extra2);
    assert(DQ_pop(&extralist) == &na[0]);
}
#endif
