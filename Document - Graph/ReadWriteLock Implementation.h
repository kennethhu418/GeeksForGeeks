#include <queue>
using namespace std;

class ThreadObject;
class spinlock_t;
extern ThreadObject* getCurrentThreadObject();
extern void sleep(unsigned int);

typedef enum __RWLockStatus
{
    LOCKSTATUS_FREE = 0,
    LOCKSTATUS_READING = 1,
    LOCKSTATUS_WRITING = 2
}RWLockStatus;

typedef enum __RWLockType
{
    RWLOCK_INVALID = 0,
    RWLOCK_READ = 1,
    RWLOCK_WRITE = 2
}RWLockType;

typedef struct __RWLockWaiter
{
    RWLockType       request; //request what kind of lock
    ThreadObject*   thread;  //the thread for this waiter
    bool    *granted; //whether the lock has been granted
}RWLockWaiter;

class RWLock
{
private:
    spinlock_t              mLock;
    RWLockStatus      mStatus; // is the lock busy, and busy for read or write?
    unsigned int          mUserCount; // how many threads are granted with the RW lock now. If mStatus == LOCKSTATUS_WRITING, this count is always 1
    queue<RWLockWaiter> mWaiterQ; // all threads that are waiting for lock granted

public:
    RWLock() {
        mLock.Initialize();
        mStatus = RWLockStatus::LOCKSTATUS_FREE;
        mUserCount = 0;
    }

    void acquireLock(RWLockType accType) {
        mLock.lock();
        if (mStatus == RWLockStatus::LOCKSTATUS_FREE) {
            mStatus = accType == RWLockType::RWLOCK_READ ? RWLockStatus::LOCKSTATUS_READING : RWLockStatus::LOCKSTATUS_WRITING;
            ++mUserCount;
            mLock.unlock();
            return;
        }

        volatile bool granted = false;
        RWLockWaiter waiter = { accType, getCurrentThreadObject(), &granted};
        if (!mWaiterQ.empty())
            mWaiterQ.push(waiter);
        else {
            if (mStatus == RWLockStatus::LOCKSTATUS_WRITING)
                mWaiterQ.push(waiter);
            else {
                if (accType == RWLockType::RWLOCK_READ) {
                    ++mUserCount;
                    mLock.unlock();
                    return;
                }
                else
                    mWaiterQ.push(waiter);
            }
        }

        /***********************  PAY ATTENTION FOR FOLLOWING CODE PIECE  *******************************
         * We must accessing granted with acquiring the mLock. If not, that is, we write it like this:
         *        while (!granted) {
         *            sleep(1);
         *        }
         * Then we have the risk in following case.
         * Assume the unlock logic first set granted = true and then wake up the thread. Assume before the wake up thread
         * operation, the thread wakes up because the 1 millisecond passed. Then it checks that granted = true, so it exits the
         * acquireLock function. And after some processing, the thread waits on some other resource or sleeps for some
         * well-predefined time. Now the wake up thread operation in the unlock logic performs, we can see the thread would
         * be unexpectly waken up though its waiting resource may not be ready.
         * Assume the unlock logic first wakes up the thread and then set granted = true, though there is no problem and risk 
         * under this case, this behavior is not appropriate from performance aspective. Because the purpose of waking up the
         * thread is to expect it to immediately run after its lock is ready so that it can do its work as quickly as possible and minimize
         * other waiter's time. However, if we wakes up the thread first, the thread may check the granted is still false, and it sleeps
         * again for another 1 millisecond.
         **********************************************************************************************/
        while (!granted) {
            mLock.unlock();
            sleep(1); //sleep for 1 millisecond
            mLock.lock(); 
        }
        mLock.unlock();
    }

    void releaseLock() {
        mLock.lock();
        --mUserCount;
        if (mUserCount > 0) {
            mLock.unlock();
            return;
        }

        if (!mWaiterQ.empty()) {
            mStatus = RWLockStatus::LOCKSTATUS_FREE;
            mLock.unlock();
            return;
        }

        RWLockWaiter waiter = mWaiterQ.front();
        if (waiter.request == RWLockType::RWLOCK_WRITE) {
            mWaiterQ.pop();
            ++mUserCount;
            mStatus = RWLockStatus::LOCKSTATUS_WRITING;
            *(waiter.granted) = true;
            waiter.thread->wakeup(); 
            // We must first wakeup the thread and then unlock the mLock. Otherwise, the problem
            // described in the long comments in function acquireLock() would occur
            mLock.unlock(); 
            return;
        }

        mStatus = RWLockStatus::LOCKSTATUS_READING;
        while (waiter.request == RWLockType::RWLOCK_READ) {
            mWaiterQ.pop();
            ++mUserCount;
            *(waiter.granted) = true;
            waiter.thread->wakeup();
            if (mWaiterQ.empty()) break;
            waiter = mWaiterQ.front();
        }
        // We must first wakeup all the threads and then unlock the mLock. Otherwise, the problem
        // described in the long comments in function acquireLock() would occur
        mLock.unlock();    
    }
};