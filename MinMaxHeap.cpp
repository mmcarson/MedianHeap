#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <iomanip>

using namespace std;

class Heap{
    public:
    Heap(){
        size = 0;
    }
    void add(int n){
        heap.push_back(n);
        size++;
        reheapUp();
    }
    void deleteTop(){
       // cout << "deleteTop" << endl; // debugging
        size--;
        swap(0,size);
        heap.pop_back();
        reheapDown();
    }
    int getSize(){
        return size;
    }
    int getTop(){
        return heap[0];
    }
    virtual void reheapUp()=0;
    virtual void reheapDown()=0;
    protected:
    int getAt(int i){
        return heap[i];
    }
    int getLeftIndex(int i){
        return i*2+1;
    }
    int getRightIndex(int i){
        return i*2+2;
    }
    int getParentIndex(int i){
        return (i-2)/2;
    }
    int hasParent(int i){
        return i>0;
    }
    int hasLeft(int i){
        return getLeftIndex(i)<size;
    }
    int hasRight(int i){
        return getRightIndex(i)<size;
    }
    int getLeft(int i){
        return heap[getLeftIndex(i)];
    }
    int getRight(int i){
        return heap[getRightIndex(i)];
    }
    int getParent(int i){
        return heap[getParentIndex(i)];
    }
    void swap(int i, int j){ // two indices
        int i_e = heap[i];
        heap[i] = heap[j];
        heap[j] = i_e;
    }
    private:
    vector<int> heap;
    int size;
};

class MinHeap : public Heap{
    public:
    void reheapUp(){
        int i=getSize()-1;
        while(hasParent(i)){
            if (getAt(i)<getParent(i)){
                swap(i, getParentIndex(i));
                i = getParentIndex(i);
            }
            else
                i = 0;
        }
    }
    void reheapDown(){
        int i = 0;
        while (hasLeft(i)){
            int minChildIndex = getLeftIndex(i);
            if (hasRight(i)){
                if (getRight(i)<getLeft(i)){
                    minChildIndex = getRightIndex(i);
                }
            }
            if (getAt(i)>getAt(minChildIndex)){
                swap(i, minChildIndex);
                i = minChildIndex;
            }
            else{
                i = getSize()-1;
            }
        }
    }
};

class MaxHeap : public Heap{
    public:
    void reheapUp(){
        int i=getSize()-1;
        while(hasParent(i)){
            if (getAt(i)>getParent(i)){
                swap(i, getParentIndex(i));
                i = getParentIndex(i);
            }
            else
                i = 0;
        }
    }
    void reheapDown(){
        int i = 0;
        while (hasLeft(i)){
            int maxChildIndex = getLeftIndex(i);
            if (hasRight(i)){
                if (getRight(i)>getLeft(i)){
                    maxChildIndex = getRightIndex(i);
                }
            }
            if (getAt(i)<getAt(maxChildIndex)){
                swap(i, maxChildIndex);
                i = maxChildIndex;
            }
            else{
                i = getSize()-1;
            }
        }
    }
};

class MinMaxHeap {
    public:
    void add(int x){
       // cout << x; // debugging
        if (maxHeap.getSize() == 0) // default: add to maxHeap
            maxHeap.add(x);
        else if (x>getMedian()){
            minHeap.add(x);
        }
        else{
            maxHeap.add(x);
        }
        rebalance();
    }
    double getMedian(){
        if (maxHeap.getSize() == 0){ // both are empty if maxHeap is empty
            return 0;
        }
        if (minHeap.getSize()>maxHeap.getSize()){
            return minHeap.getTop();
        }
        else if (minHeap.getSize()<maxHeap.getSize()){
            return maxHeap.getTop();
        }
        else
            return (double)(minHeap.getTop() + maxHeap.getTop())/2;
    }
    private:
    void rebalance(){
        while (minHeap.getSize()-maxHeap.getSize()>1){
            maxHeap.add(minHeap.getTop());
            minHeap.deleteTop();
        }
        while (maxHeap.getSize()-minHeap.getSize()>1){
            minHeap.add(maxHeap.getTop());
            maxHeap.deleteTop();
        }
    }
    MinHeap minHeap;
    MaxHeap maxHeap;
};

int main(){
    int n, x;
    cin >> n;
    MinMaxHeap a;
    cout.precision(1);
    for(int a_i = 0;a_i < n;a_i++){
        cin >> x;
        a.add(x);
        cout << fixed << a.getMedian() << endl;
    }
    return 0;
}

