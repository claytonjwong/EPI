/*
 
 CH5: Arrays
 
 */

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

template <class T>
class Solution{
public:
    
    void QuickSort(vector<T>& A){
        int size=(int)A.size();
        if (size < 2) { return; }
        QuickSort(A, 0, size-1);
    }
    
    void QuickSort(vector<T>& A, int lo, int hi){
        if (lo >= hi) { return; }
        int p = Partition(A, lo, hi);
        QuickSort(A, lo, p);
        QuickSort(A, p+1, hi);
    }
    
    int Partition(vector<T>& A, int lo, int hi){
        int pivot=A[lo], i=lo-1, j=hi+1;
        while (true){
            do { i++; } while (A[i] < pivot);
            do { j--; } while (A[j] > pivot);
            if (i >= j) { return j; }
            swap(A[i],A[j]);
        }
    }
    
    void BubbleSort(vector<T>& A){
        int size=(int)A.size();
        if (size < 2) { return; }
        for (int i=0; i < size-1; i++){
            for (int j=i+1; j < size; j++){
                if (A[i] > A[j]){ swap(A[i],A[j]); }
            }
        }
    }
    
    /*----------------------------------------------------------------------
     5.2 Increment an arbitrary length integer by one
     ----------------------------------------------------------------------*/
    void PlusOne(vector<int>& A){
        if (A.empty()) { return; }
        A.back()++;
        for (int i=(int)A.size()-1; i > 0 && A[i]==10; i--){
            A[i]=0;
            A[i-1]++;
        }
        if (A[0]==10){
            A[0]=1; A.push_back(0);
        }
    }
    
    /*----------------------------------------------------------------------
     5.4 Advancing through an array
     ----------------------------------------------------------------------*/
    bool CanWin(const vector<int>& A){
        if (A.empty()) { return false; }
        int reach=A[0], target=(int)A.size()-1;
        for (int i=1; i < A.size() && reach < target; i++){
            reach=max(reach,i+A[i]);
        }
        return reach >= target;
    }
    
    /*----------------------------------------------------------------------
     5.5 Delete duplicates from a sorted array
     ----------------------------------------------------------------------*/
    int DeleteDuplicates(vector<T>& A){
        int size=(int)A.size();
        if (size < 2) { return size; }
        if (!is_sorted(A.begin(), A.end())){
            sort(A.begin(), A.end());
        }
        int write_index=1;
        for (int i=1; i < size; i++){
            if (A[write_index-1] != A[i]){
                A[write_index++] = A[i];
            }
        }
        A.resize(write_index);
        return write_index;
    }
    
    /*----------------------------------------------------------------------
     5.6 Buy and sell stock once
     ----------------------------------------------------------------------*/
    T MaxProfit1(const vector<T>& prices){
        T res=0, profit=0;
        for (int i=1; i<prices.size(); i++){
            if (prices[i-1] <= prices[i]){
                profit += prices[i] - prices[i-1];
            } else {
                profit = 0;
            }
            res = max(res, profit);
        }
        return res;
    }
    
    /*----------------------------------------------------------------------
     5.7 Buy and sell stock twice
     ----------------------------------------------------------------------*/
    T MaxProfit2(const vector<T>& prices){
        T res=0, profit=0;
        stack<T> max{};
        for (int i=1; i<prices.size(); i++){
            if (prices[i-1] <= prices[i]){
                profit += prices[i] - prices[i-1];
            } else {
                if (max.empty() || (!max.empty() && profit > max.top())){
                    max.push(profit);
                }
                profit=0;
            }
        }
        res += max.top(); max.pop();
        res += max.top();
        return res;
    }
    
    /*----------------------------------------------------------------------
     5.8 Computing an alternation
     A[0]<=A[1]>=A[2]<=A[3];
     ----------------------------------------------------------------------*/
    void Rearrange(vector<int>& A){
        for (int i=1; i < A.size(); i++){
            if ((!(i%2) && A[i-1] < A[i]) || ((i%2) && A[i-1] > A[i])){
                swap(A[i-1], A[i]);
            }
        }
    }
};


int main(int argc, const char * argv[]) {
    
    // A[0] <= A[1] >= A[2] <= A[3]
    
    vector<int> nums1{0,5,9,4,3,1,8,2,7};

    
    Solution<int> solution;
    solution.QuickSort(nums1);

    
    solution.Rearrange(nums1);
    
    return 0;
}






