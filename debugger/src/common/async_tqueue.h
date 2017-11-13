/**
 * @file
 * @copyright  Copyright 2016 GNSS Sensor Ltd. All right reserved.
 * @author     Sergey Khabarov - sergeykhbr@gmail.com
 * @brief      Asynchronous queue with time markers.
 */

#ifndef __DEBUGGER_ASYNC_TQUEUE_H__
#define __DEBUGGER_ASYNC_TQUEUE_H__

#include "api_types.h"
#include "iface.h"
#include "attribute.h"

namespace debugger {

class AsyncTQueueType {
public:
    AsyncTQueueType();
    ~AsyncTQueueType();

    /** Thread safe method of the callbacks registration */
    void put(AttributeType *item);

    /** push registered to the main queue */
    void pushPreQueued();

    /** Reset proccessed counter at the begining of each iteration */
    void initProc();

protected:
    AttributeType item_;
    AttributeType stepQueue_;
    AttributeType stepPreQueued_;
    unsigned curIdx_;
    unsigned preLen_;
    unsigned curLen_;    // to avoid reallocation
    mutex_def mutex_;
};


class ClockAsyncTQueueType : public AsyncTQueueType {
public:
    ClockAsyncTQueueType();

    /** Thread safe method of the callbacks registration */
    void put(uint64_t time, IFace *cb);

    /**
     * Get next registered interface with counter less or equal to 'step_cnt'
     */
    IFace *getNext(uint64_t step_cnt);

private:
    enum QueueItemNames {
        Queue_Time, 
        Queue_IFace, 
        Queue_Total
    };
};


class GuiAsyncTQueueType : public AsyncTQueueType {
public:
    GuiAsyncTQueueType();

    /** Thread safe method of the callbacks registration */
    void put(IFace *src, AttributeType *cmd, bool silent);
    bool getNext(IFace **src, AttributeType &cmd, bool &silent);
    void remove(IFace *src);

private:
    enum QueueItemNames {
        Queue_Source, 
        Queue_Command, 
        Queue_Silent,
        Queue_Total
    };
    int dbg_cnt_;
};

}  // namespace debugger

#endif  // __DEBUGGER_ASYNC_TQUEUE_H__
