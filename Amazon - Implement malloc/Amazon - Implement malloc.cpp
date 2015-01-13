/**************************************************
* Further optimization of previous codes with optimizations
* discussed in the interview, including
* (1) Link the free memory blocks
* (2) Merge adjacent memory blocks when freeing memory
* (3) Search best fit memory block when allocating memory
*
* created by Kenneth @ 1/12/2015
**************************************************/

#include <iostream>
#include <cstring>
#include <assert.h>  // included for tests
#include <vector>  // included for tests
#include <algorithm>  //included for tests
using namespace std;

#define MIN_MALLOC_SIZE 20  // at least request this size of memory when calling sbrk

static inline int min(int a, int b) {
    return a < b ? a : b;
}

static inline int max(int a, int b) {
    return a > b ? a : b;
}

static char *sbrk(int size);

typedef struct __MemoryBlk {
    int     size;  // size of this memory block
    __MemoryBlk *next;  // next memory block
}MemoryBlk;

class MemoryAllocator {
private:
    MemoryBlk *mFreeBlocks; // free blocks are sorted by their memory address
    char	*mMemoryStart;
    char    *mMemoryEnd;

public:
    MemoryAllocator() : mFreeBlocks(NULL), mMemoryStart(NULL), mMemoryEnd(NULL) {

    }

    char *malloc(int requestSize) {
        if (requestSize == 0) return NULL;

        int totalSize = sizeof(MemoryBlk)+requestSize;

        // If we have never allocated memory, allocate now
        if (mMemoryStart == NULL) {
            mMemoryStart = sbrk(max(MIN_MALLOC_SIZE, totalSize));
            mMemoryEnd = mMemoryStart + max(MIN_MALLOC_SIZE, totalSize);
            mFreeBlocks = (MemoryBlk*)mMemoryStart;
            mFreeBlocks->size = max(MIN_MALLOC_SIZE, totalSize);
            mFreeBlocks->next = NULL;
        }

        // Search best fit block whose size is the smallest one that fits the request size
        MemoryBlk* bestFitBlk = NULL, *prevBlkBeforeBestFitBlk = NULL;
        MemoryBlk* curBlk = mFreeBlocks, *prevBlk = NULL;
        while (curBlk) {
            if (curBlk->size == totalSize) {
                bestFitBlk = curBlk;
                prevBlkBeforeBestFitBlk = prevBlk;
                break;
            }

            if (curBlk->size > totalSize) {
                if (bestFitBlk == NULL || bestFitBlk->size > curBlk->size) {
                    bestFitBlk = curBlk;
                    prevBlkBeforeBestFitBlk = prevBlk;
                }
            }

            prevBlk = curBlk;
            curBlk = curBlk->next;
        }

        // If there is no free block that can satisefy the request size, allocate more memory from sbrk
        if (bestFitBlk == NULL) {
            sbrk(max(totalSize, MIN_MALLOC_SIZE));
            bestFitBlk = (MemoryBlk*)mMemoryEnd;
            bestFitBlk->size = max(totalSize, MIN_MALLOC_SIZE);
            bestFitBlk->next = NULL;
            prevBlkBeforeBestFitBlk = prevBlk;
            mMemoryEnd = sbrk(0);
        }

        // Split the best fit block into two blocks if the remaining block can hold at least 1 byte
        if (bestFitBlk->size - totalSize > sizeof(MemoryBlk)) {
            MemoryBlk* nextBlk = (MemoryBlk*)((char*)bestFitBlk + totalSize);
            nextBlk->size = bestFitBlk->size - totalSize;
            nextBlk->next = bestFitBlk->next;
            bestFitBlk->size = totalSize;
            if (prevBlkBeforeBestFitBlk == NULL)
                mFreeBlocks = nextBlk;
            else
                prevBlkBeforeBestFitBlk->next = nextBlk;
        }
        else {
            if (prevBlkBeforeBestFitBlk == NULL)
                mFreeBlocks = bestFitBlk->next;
            else
                prevBlkBeforeBestFitBlk->next = bestFitBlk->next;
        }

        bestFitBlk->next = NULL;
        return (char*)bestFitBlk + sizeof(MemoryBlk);
    }

    void free(char *buffer) {
        if (buffer == NULL) return;

        MemoryBlk *returnBlk = (MemoryBlk*)((char*)buffer - sizeof(MemoryBlk));
        MemoryBlk *prevBlk = NULL, *curBlk = mFreeBlocks;
        while (curBlk) {
            if (curBlk > returnBlk) break;
            prevBlk = curBlk;
            curBlk = curBlk->next;
        }

        // prevBlk's memory address is smaller than that of the returned memory block
        // curBlk's memory address is larger than that of the returned memory block

        // merge backwards (i.e., merge with previous block)
        if (prevBlk == NULL)
            mFreeBlocks = returnBlk;
        else if ((char*)prevBlk + prevBlk->size == (char*)returnBlk) {
            prevBlk->size += returnBlk->size;
            returnBlk = prevBlk;
        }
        else
            prevBlk->next = returnBlk;

        // merge forwards (i.e., merge with next block)
        if (curBlk && ((char*)returnBlk + returnBlk->size == (char*)curBlk)) {
            returnBlk->size += curBlk->size;
            returnBlk->next = curBlk->next;
        }
        else
            returnBlk->next = curBlk;
    }

    void printFreeLists() {
        MemoryBlk *curBlk = mFreeBlocks;
        cout << "Start Address\t End Address\t Size" << endl;
        while (curBlk) {
            cout << curBlk << "\t " << (void*)((char*)curBlk + curBlk->size) << "\t " << curBlk->size << endl;
            curBlk = curBlk->next;
        }
        cout << endl;
    }
};


/*****************************************************************
********************** Test Codes Below****************************
****************************************************************/

// Simulate sbrk functions with static memory
static char *sbrk(int size)
{
    static char buffer[12288];
    static char *head = buffer;

    char *orgBreakPoint = head;
    head += size;
    return orgBreakPoint;
}

void printHelp() {
    cout << "h:\t show this help." << endl;
    cout << "a:\t allocate memory. (  requirement of test: <= 100 B  )" << endl;
    cout << "f:\t free an allocated memory." << endl;
    cout << "l:\t list all allocated memory." << endl;
    cout << "k:\t see all free memory blocks in the memory allocator." << endl;
    cout << "q:\t quit test." << endl;
    cout << endl;
}

typedef struct __AllocatedUserMem {
    char        *address;
    int             size;
    __AllocatedUserMem(char *mem, int size = 0) : address(mem), size(size) {}
}AllocatedUserMem;

static bool compareUserMem(const AllocatedUserMem &mem1, const AllocatedUserMem &mem2) {
    return mem1.address < mem2.address;
}

int main() {
    const int MAX_MEM_SIZE = 100;
    MemoryAllocator mgmt;
    vector<AllocatedUserMem>   allocatedMemoryArr;
    char    commandLine[100];
    int         size = 0;

    printHelp();
    while (cin.getline(commandLine, 100)) {
        if (commandLine[0] == 'q')
            break;

        if (commandLine[0] == 'l') {
            cout << "Memories are sorted by address." << endl;
            cout << "Index\t " << "Mem Address\t " << "Mem Size" << endl;
            for (int i = 0; i < allocatedMemoryArr.size(); ++i)
                cout << i << ":\t " << (void*)allocatedMemoryArr[i].address << "\t " << allocatedMemoryArr[i].size << endl;
            cout << endl;
        }
        else if (commandLine[0] == 'k') {
            cout << "Free Memory Blocks in Memory Allocator are sorted by addresses." << endl;
            mgmt.printFreeLists();
        }
        else if (commandLine[0] == 'a') {
            cout << "Input Memory Size (  <= 100 B  ): ";
            cin >> size;
            if (size > 100) {
                cout << "Invalid Input." << endl;
            }
            else {
                allocatedMemoryArr.push_back(AllocatedUserMem(mgmt.malloc(size), size));
                cout << "Memory Allocated at " << (void*)allocatedMemoryArr.back().address << endl;
                sort(allocatedMemoryArr.begin(), allocatedMemoryArr.end(), compareUserMem);
            }
        }
        else if (commandLine[0] == 'f') {
            cout << "Input the index of the freed memory (use 'l' to see the index): ";
            cin >> size;
            if (size < 0 || size >= allocatedMemoryArr.size())
                cout << "Invalid Input." << endl;
            else {
                char *targetMem = allocatedMemoryArr[size].address;
                allocatedMemoryArr.erase(allocatedMemoryArr.begin() + size);
                mgmt.free(targetMem);
                cout << "Successfully Erased Memory at " << (void*)targetMem << endl;
                cout << "ATTENTION: After removing this memory, the indexes of memories would change. Please type 'l' again to see new indexes." << endl;
            }
        }
        else if (commandLine[0] == 'h')
            printHelp();
        cout << endl;
    }

    return 0;
}