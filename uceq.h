#ifndef UCEQ_H
#define UCEQ_H
#include "ucdq.h"

typedef struct EQ {
    DQ *listeners;
    struct EQ *next;
} EventQ;
typedef struct EQ Event;

void EQ_InitQueue(EventQ **queue);
void EQ_InitEvent(Event *event);
void EQ_AddListener(Dispatch *listener);

#endif

