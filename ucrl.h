#ifndef RUNLOOP_H
#define RUNLOOP_H
#include "ucdq.h"
#include "uceq.h"

typedef struct RunLoop {
    DQ *idlers;
    DQ *dispatches;
    EQ *events;
} RunLoop;

void RL_Init(RunLoop *rl);
void RL_AddIdler(RunLoop *rl, Dispatch *dispatch);
void RL_QueueDispatch(RunLoop *rl, Dispatch *dispatch);
void RL_PostEvent(RunLoop *rl, Event *event);
void RL_Run(RunLoop *rl);

#endif

