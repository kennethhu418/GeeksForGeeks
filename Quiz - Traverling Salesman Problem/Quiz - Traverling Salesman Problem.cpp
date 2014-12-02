//  Travelling Salesman Problem(TSP) : Given a set of cities and distance between every pair of cities, 
//  the problem is to find the shortest possible route that visits every city exactly once and returns 
//  to the starting point.
//  
//  Note the difference between Hamiltonian Cycle and TSP.The Hamiltoninan cycle problem is to find 
//  if there exist a tour that visits every city exactly once.Here we know that Hamiltonian Tour 
//  exists(because the graph is complete) and in fact many such tours exist, the problem is to find 
//  a minimum weight Hamiltonian Cycle.

#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

#define MAX_CITIES 31

class Solution
{
public:
    vector<int> travelingSalesMan(const unsigned int ** distMatrix, int n) {
        assert(n <= MAX_CITIES);
        vector<int> result;
        if (n == 1) {
            result.push_back(0);
            return result;
        }

        if (n == 2) {
            result.push_back(0);
            result.push_back(1);
            return result;
        }
        
        Initialize(n);

        unsigned int mask = (((1 << n) - 1) & (~1));
        int minDist = solveTraveling(distMatrix, 0, mask);
        unsigned int target = 0, curCity = 0;
        for (unsigned int i = 0; i < n; ++i) {
            result.push_back(curCity);
            target = mMinDistTo[curCity][mask];
            mask &= ~(1 << target);
            curCity = target;
        }
        
        Free();
        return result;    
    }

private:
    int **mMinDist;
    unsigned int **mMinDistTo;
    int mStartingCity;
    int mCityCount;

    // We want to go from curCity to mStartingCity, and we can only go through the cities
    // indicated by the cityMask bitmask.
    unsigned int solveTraveling(const unsigned int ** distMatrix, unsigned int curCity, unsigned int cityMask) {
        if (mMinDist[curCity][cityMask] >= 0)
            return mMinDist[curCity][cityMask];
        if (cityMask == 0) {
            mMinDist[curCity][cityMask] = distMatrix[curCity][mStartingCity];
            return mMinDist[curCity][cityMask];
        }

        int dist = 0;
        for (int i = 0; i < mCityCount; ++i) {
            if (((1 << i) & cityMask) == 0)
                continue;

            dist = distMatrix[curCity][i] + solveTraveling(distMatrix, i, cityMask & ~(1 << i));
            if (mMinDist[curCity][cityMask] < 0 || dist < mMinDist[curCity][cityMask]) {
                mMinDist[curCity][cityMask] = dist;
                mMinDistTo[curCity][cityMask] = i;
            }       
        }

        return mMinDist[curCity][cityMask];
    }

    void Initialize(int n) {
        mStartingCity = 0;
        mCityCount = n;
        unsigned int maskCount = (1 << n);
        mMinDist = new int*[n];
        mMinDistTo = new unsigned int*[n];
        for (int i = 0; i < n; ++i) {
            mMinDist[i] = new int[maskCount];
            mMinDistTo[i] = new unsigned int[maskCount];
            memset(mMinDist[i], 0xFF, maskCount * sizeof(unsigned int));
            memset(mMinDistTo[i], 0xFF, maskCount * sizeof(unsigned int));
        }    
    }

    void Free() {
        for (int i = 0; i < mCityCount; ++i) {
            delete[] mMinDist[i];
            delete[] mMinDistTo[i];
        }
        delete[] mMinDistTo;
        delete[] mMinDist;
    }
};

int main()
{
    const unsigned int CITY_COUNT = 4;
    unsigned int distArr0[CITY_COUNT] = { 0, 10, 15, 20 };
    unsigned int distArr1[CITY_COUNT] = { 10, 0, 35, 25 };
    unsigned int distArr2[CITY_COUNT] = { 15, 35, 0, 30 };
    unsigned int distArr3[CITY_COUNT] = { 20, 25, 30, 0 };
    const unsigned int *distArr[CITY_COUNT] = { distArr0, distArr1, distArr2, distArr3 };
    Solution so;

    vector<int> result = so.travelingSalesMan(distArr, CITY_COUNT);
    int totalDist = 0;
    cout << "Salesman traveling path is:" << endl;
    for (int i = 0; i < result.size(); ++i) {
        cout << result[i] << " ";
        totalDist += distArr[result[i]][result[(i + 1) % result.size()]];
    }

    cout << endl << "Distance is " << totalDist << endl;
    return 0;
}