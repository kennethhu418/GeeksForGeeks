//A triangulation of a convex polygon is formed by drawing diagonals between non - adjacent 
//vertices(corners) such that the diagonals never intersect.The problem is to find the cost 
//of triangulation with the minimum cost.The cost of a triangulation is sum of the weights of 
//its component triangles.Weight of each triangle is its perimeter(sum of lengths of all sides)
//Please see the figure attached in this project for vivid explanation of the problem


//This problem has recursive substructure.The idea is to divide the polygon into three parts :
//a single triangle, the sub - polygon to the left, and the sub - polygon to the right.We try 
//all possible divisions like this and find the one that minimizes the cost of the triangle 
//plus the cost of the triangulation of the two sub - polygons.
//We use DP to solve this problem
#include <iostream>
#include <cmath>
#include <cstring>
#define MAX_COST 10000000000
using namespace std;

typedef struct __Point
{
    int x;
    int y;

    __Point(int x, int y) : x(x), y(y) {}

    double calculateDist(const __Point &another) const
    {
        return sqrt((x - another.x)*(x - another.x) +
            (y - another.y)*(y - another.y));
    }
}Point;

double getPerimeter(const Point &p1, const Point &p2, const Point &p3)
{
    return p1.calculateDist(p2) + p2.calculateDist(p3) + p1.calculateDist(p3);
}

double getMinimumCut(const Point *pointArr, int n)
{
    if (n < 3) return 0;
    if (n == 3) return getPerimeter(pointArr[0], pointArr[1], pointArr[2]);

    char *buffer = new char[sizeof(double)*n*n + sizeof(double*)*n];
    memset(buffer, 0, sizeof(double)*n*n + sizeof(double*)*n);
    double** resultArr = (double**)(buffer + sizeof(double)*n*n);
    for (int i = 0; i < n; ++i)
        resultArr[i] = (double*)(buffer + i*sizeof(double)*n);

    //Run DP
    int i = 0, j = 0;
    double minCost = MAX_COST, curCost = 0;
    for (int len = 3; len <= n; ++len){
        for (i = 0; i < n; ++i){
            j = (i + len - 1) % n;
            minCost = MAX_COST;
            for (int k = (i + 1) % n; k !=  j; k = (k + 1)%n){
                curCost = getPerimeter(pointArr[i], pointArr[k], pointArr[j]);
                curCost += (resultArr[i][k] + resultArr[k][j]);
                if (curCost < minCost) minCost = curCost;
            }

            resultArr[i][j] = minCost;
        }
    }

    minCost = resultArr[0][n - 1];
    delete[] buffer;
    return minCost;
}

int main() {
    Point points[] = { { 0, 2 }, { 1, 2 }, { 2, 1 }, { 1, 0 }, { 0, 0 } };
    int n = sizeof(points) / sizeof(Point);

    cout << getMinimumCut(points, n) << endl;
    return 0;
}