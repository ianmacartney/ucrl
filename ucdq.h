#ifndef UCDQ_H
#define UCDQ_H

typedef struct DQ {
    int (*fn)(void *ctx);
    void *ctx;
    struct DQ *next;
} DispatchQ;
typedef struct DQ Dispatch;

void DQ_InitQueue(DispatchQ **queue);
void DQ_InitDispatch(
        Dispatch *dq,
        int (*callback)(void *context),
        void *context);
void DQ_RegisterDispatch(DispatchQ **queue, Dispatch *dispatch);

#endif
