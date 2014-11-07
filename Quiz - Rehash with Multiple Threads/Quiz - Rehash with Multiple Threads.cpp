// 1. How to implement hash data structure with nearly O(1) time complexity of insert/ search / erase. 
// 2. At some time point, we want to change the hash function. Can you do the rehash in-place?
// 3. How would you do 2 in multiple threads environment.That is, when you do the rehash, you should not block users' operation.

//Here is the answer and design by Kenneth Hu
//Q1:
//Yes, we can.Instead of using balanced binary search tree, we can use array of linked list for the implementation of hash.The linked list is for confict elements.
//
//Q2 & Q3 :
//Our goal is when doing rehashing, we should not block users' operation such as search/insert/remove.
//
//In this senario, there are following threads :
//(1) A background thread, which is used to do the rehashing.
//(2) Users' threads, which calls our search/insert/remove API.
//
//Here is my design :
//Globally, there are
//(1) hash_old : the old hash function.When is_in_rehashing is false, this is NULL
//(2) hash_cur : the new / current hash function.No matter whether is_in_rehashing is true or false, this function must exist.
//(3) mRehashCheckpoint : the checkpoint indicating the next bucket that needs to be rehashed.If this checkpoint is INVALID, then it means no rehashing is ongoing.
//(4) spinlock mGlobalLock
//
//For each hash bucket, there are two lists :
//(1) list_cur : current list to hold the collsion items.When a new item is added, it goes into this list.
//(2) list_old : during rehashing, this list holds all items which are in this bucket by old hash function.
//(3) boolean entered_new_items : whether there are new items put into this bucket before the bucket is processed by the background rehash thread.
//(4) spinlock mBucketLock
//
//So let us see how the above data structures work in a rehashing case:
//
//    A rehash request comes :
//    (1) mGlobalLock is acquired
//        (2) hash_cur is assigned to hash_old, and hash_cur is assigned by the new function
//        (3) mRehashCheckpoint = 0
//        (4) Wake up the background rehash thread
//        (5) Release mGlobalLock
//
//        During the rehashing, if another rehash request comes, the request sees mRehashCheckpoint != INVALID, so the request is refused  or queued in the waiting_queue because at any time we could only allow one rehash onging.
//
//        What the background rehash thread does ?
//        It processes one bucket by one bucket.After processing all buckets, it
//        (1) mGlobalLock is acquired
//        (2) hash_old is invalidated
//        (3) mRehashCheckpoint = INVALID
//        (4) Rehash thread goes into sleep or continue next rehash request from the waiting_queue
//        (5) Release mGlobalLock
//
//        When processing one bucket(incicated by mRehashCheckpoint), e.g., we are going to process bucket 12:
//    (1) Acquire bucket 12's mBucketLock
//
//        (2) If entered_new_items is false, it means nobody has modified the current bucket after the rehash begins at the very beginning.So we assert(list_old == NULL) and swap list_old and list_cur.
//        If entered_new_items is true, it means someone(either this background rehash thread or a user thread) has modified the current bucket(already swapped the list_old and list_cur), so we do nothing except reset entered_new_items = false
//
//        (3) Taken out the item from the list_old one by one.For one item, we recalculate its bucket number(let's say it is ITEM_CC) by the new hash function. For example, by the new function this item ITEM_CC should be put into bucket 88. So we acquire the mBucketLock of bucket 88, and check
//        - If bucket 88's entered_new_items is true, it means a user thread has modified that bucket (switched the list_old and list_cur). So do nothing (DO NOT reset entered_new_items = false)
//        - If bucket 88's entered_new_items is false, it means nobody has modified the bucket after the rehash begins at the very beginning. So set entered_new_items = true and swap list_old and list_cur because we will insert a rehashed item into it.
//
//        After the above check to bucket 88, insert the item ITEM_CC into its list_cur.
//
//        (4) After processing all items in list_old, we acquire mGlobalLock and ++mRehashCheckpoint and release mGlobalLock and then release this bucket's mBucketLock
//
//        During the rehashing by the background rehash thread, one user may insert / search / remove one item, we call this "on-demand partial rehashing" cases.
//
//        >> Insert
//        It uses the new hash function to calculate the target bucket, i.e., whick bucket this new item should be put into.
//        If target bucket < mRehashCheckpoint, then it is just put into the target bucket(acquire the lock first of course).
//        If target bucket >= mRehashCheckpoint, it means the background hash thread has not taken care of the bucket yet.So it checkes
//        (1) If entered_new_items is false, it means nobody has modified the bucket after the rehash begins at the very beginning.So set entered_new_items = true and swap list_old and list_cur because we will insert a rehashed item into it.
//        (2) If entered_new_items is true, it means previously it has been modified(switched the list_old and list_cur).So do nothing.
//        After the above check, we insert the new item into this target bucket's list_cur.
//
//        >> Search
//        First use the new hash function to get the target bucket.Check the target bucket's both list_cur and list_old.
//        If not found, then use the old hash function to get the target bucket.Check the target bucket's both list_cur and list_old.
//
//        >> Remove
//        Same with search

int main()
{
	return 0;
}

