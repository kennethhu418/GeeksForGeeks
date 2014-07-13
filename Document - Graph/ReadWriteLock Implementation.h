class ThreadObject;

typedef enum __RWLockStatus
{
    FREE = 0,
    READING = 1,
    WRITING = 2
}RWLockStatus;

typedef struct __RWLockWaiter
{
    __RWLockWaiter  *next;
    RWLockStatus    request; //request what kind of lock
    ThreadObject*   thread;
}RWLockWaiter;

class RWLock
{
public:
    RWLock() :mStatus(FREE), mWaitingWriterCount(0), mOutstandingReaderCount(0)
    {
        mLock.initialize();
        mWaitersTail = NULL;
        mWaiters = NULL;
    }

    void    read_lock()
    {
        mLock.lock();
        //If there is no outstanding write lock request and no waiting write lock request.
        //Go ahead take the lock.
        if (mStatus != RWLockStatus::WRITING && !mWaitingWriterCount)
        {
            mOutstandingReaderCount++;
            mStatus = READING;
            mLock.unlock();
            return;
        }

        //If there is outstanding or waiting write lock request, we should wait in the queue
        //for fairness
        RWLockWaiter waiter;
        waiter.request = RWLockStatus::READING;
        waiter.thread = GetCurrentThreadObject();
        addWaiter(&waiter);

        mLock.unlock();
        waiter.thread.sleep(INFINITE);
    }

    void    read_unlock()
    {
        mLock.lock();
        --mOutstandingReaderCount;
        if (mOutstandingReaderCount)
        {
            mLock.unlock();
            return;
        }

        //When all outstanding read requests complete, take the next waiting
        //thread from the queue and satisefy it.
        mStatus = RWLockStatus::FREE;
        checkOutWaiterAndUnlock();
    }

    void    write_lock()
    {
        mLock.lock();

        //Only when there is no outstanding requests (no matter read or write)
        //can we grant the write lock
        if (mStatus == RWLockStatus::FREE)
        {
            mLock.unlock();
            return;
        }

        RWLockWaiter waiter;
        waiter.request = RWLockStatus::WRITING;
        waiter.thread = GetCurrentThreadObject();
        addWaiter(&waiter);

        mLock.unlock();
        waiter.thread.sleep(INFINITE);
    }

    void    write_unlock()
    {
        mLock.lock();

        //Take the next waiting thread from the queue and satisefy it.
        mStatus = RWLockStatus::FREE;
        checkOutWaiterAndUnlock();
    }

private:
    RWLockStatus            mStatus;
    spin_lock_t             mLock;
    RWLockWaiter    *mWaiters;
    RWLockWaiter    *mWaitersTail;
    unsigned int    mWaitingWriterCount;
    unsigned int    mOutstandingReaderCount;

    void checkOutWaiterAndUnlock()
    {
        if (mWaiters.empty())
        {
            mLock.unlock();
            return;
        }

        queue<RWLockWaiter*>    grantedThreads;
        RWLockWaiter    *newHead = NULL, *newTail = NULL;

        if (mWaiters->request == RWLockStatus::READING)
        {
            while (mWaiters)
            {
                if (mWaiters->request == RWLockStatus::READING)
                {
                    grantedThreads.push(mWaiters);
                    mOutstandingReaderCount++;
                }
                else
                {
                    if (newHead == NULL)    newHead = newTail = mWaiters;
                    else
                    {
                        newTail->next = mWaiters; newTail = mWaiters;
                    }
                }
                mWaiters = mWaiters->next;
            }

            mStatus = RWLockStatus::READING;
        }
        else
        {
            newHead = newTail = mWaiters->next;
            grantedThreads.push(mWaiters);
            mStatus = RWLockStatus::WRITING;
        }

        newTail->next = NULL;
        mWaiters = newHead;
        mLock.unlock();

        ThreadObject* thread;
        while (!grantedThreads.empty())
        {
            thread = grantedThreads.front()->thread;
            grantedThreads.pop();
            thread->wakeup();
        }
    }

    inline void addWaiter(RWLockWaiter *waiter)
    {
        waiter->next = NULL;

        if (mWaiters == NULL)
            mWaiters = mWaitersTail = waiter;
        else
        {
            mWaitersTail->next = waiter;
            mWaitersTail = waiter;
        }
    }

    inline bool noWaiters()
    {
        return mWaiters == NULL;
    }
};