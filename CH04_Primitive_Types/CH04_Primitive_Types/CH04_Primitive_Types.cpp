/*
 
 CH04: Primitive Types
 
 */

#include <iostream>
#include <unordered_map>

using namespace std;

class Solution{
public:
    
    /*----------------------------------------------------------------------
    4.0 Counting Bits
    ---------------------------------------------------------------------*/
    int CountBits1(int n){
        int cnt=0;
        for (int i=0; i < 31; i++){
            if (n & (1<<i)) { cnt++; }
        }
        return cnt;
    }
    
    int CountBits2(int n){
        int cnt=0;
        while (n){
            n&=(n-1); // unset right most bit
            cnt++;
        }
        return cnt;
    }
    
    int CountBits3(int n){
        return __builtin_popcount(n);
    }
    
    /*----------------------------------------------------------------------
     4.1 Parity
     ---------------------------------------------------------------------*/
    int Parity1(int n){
        int res=0;
        for (int i=0; i < 31; i++){
            if (n & (1<<i)) { res^=1; }
        }
        return res;
    }
    
    int Parity2(int n){
        int res=0;
        while(n){
            n&=(n-1); // unset right-most bit set
            res^=1; // res is 0 for even iterations and 1 for odd iterations
        }
        return res;
    }

    int Parity3(int n){
        int res=0;
        int mask = 3; // 11
        unordered_map<int,int> table{ // pre-computed parity lookup
            {0,0}, // 00 ==> 0
            {1,1}, // 01 ==> 1
            {2,1}, // 10 ==> 1
            {3,0}  // 11 ==> 0
        };
        while (n){
            res^=table[n & mask];
            n >>= 2;
        }
        return res;
    }
    
    int Parity4(int n){
        n ^= (n >> 16);
        n ^= (n >> 8);
        n ^= (n >> 4);
        n ^= (n >> 2);
        n ^= (n >> 1);
        return n & 1;
    }
    
    /*----------------------------------------------------------------------
     4.2 Swap Bits
     ---------------------------------------------------------------------*/
    int SwapBits(int n, int i, int j){
        if (i==j || (n&&(1<<i) == n&&(1<<j))){ return n; }
        int mask = (1<<i) | (1<<j);
        return n^mask;
    }
    
    void SwapRightMostNBits(int& x, int& y, int n){
        if (&x==&y){return;}
        if (n>31) {n=31;}
        int mask=(1<<n)-1;
        x^=y&mask;
        y^=x&mask;
        x^=y&mask;
    }
    
    /*----------------------------------------------------------------------
     4.3 Reverse 8-bit Integer by bits
     ---------------------------------------------------------------------*/
    int Reverse8bitInt(int n){
        int mask=3; // 11
        int size=2; // size of each "chunk" in the lookup table
        unordered_map<int,int> table{ // pre-computed reverse table
            {0,0}, // 00 ==> 00
            {1,2}, // 01 ==> 10
            {2,1}, // 10 ==> 01
            {3,3}  // 11 ==> 11
        };
        return
            (table[(n >> 0*size) & mask] << 3*size)
        |   (table[(n >> 1*size) & mask] << 2*size)
        |   (table[(n >> 2*size) & mask] << 1*size)
        |   (table[(n >> 3*size) & mask] << 0*size);
    }
    
    /*----------------------------------------------------------------------
     4.4 Closest Integer with same Weight
     
     (Input cannot be all 0s or all 1s)
    ---------------------------------------------------------------------*/
    int ClosestIntSameWeight(int n){
        if (n==0) { return 0; }
        for (int i=0; i <= 30; i++){
            if (((n>>i) & 1) != ((n>>(i+1)) & 1)){
                return SwapBits(n, i, i+1);
            }
        }
        throw invalid_argument("Invalid input: n is all zeros or all ones");
    }
    
    /*----------------------------------------------------------------------
     4.5 Multiply: Compute x*y without arithmetical operators.  The only operators
     allowed are: assignment, bitwise operators >>, <<, |, &, ~, and ^, and
     equality checks == and boolean combinations thereof.  Loops and functions
     created from scratch are allowed.  These constraints imply, for example,
     that increment or decrement, or test if x<y can NOT be used.
     ---------------------------------------------------------------------*/
    
    /* Shift is a helper method for Multiply */
    unsigned int Shift(unsigned int num, int bitval){
        while (bitval > 1){
            num <<= 1;
            bitval >>= 1;
        }
        return num;
    }
    
    /* Add is a helper method for Multiply */
    unsigned int Add(unsigned int x, unsigned int y){
        unsigned int res=0; int pos=1;
        bool carry=false;
        while (x || y){
            bool curr = (x&1) ^ (y&1);
            if (carry) { curr = !curr; }
            carry = ((x&1 && y&1) || ( (x&1 || y&1) & carry ));
            x >>= 1; y >>= 1;
            if (curr){
                res |= Shift((unsigned int)curr, pos);
            }
            pos <<= 1;
        }
        if (carry) {
            res |= Shift(1U, pos);
        }
        return res;
    }
    
    unsigned int Multiply(unsigned int x, unsigned int y){
        unsigned int res=0;
        while (x){
            if (x&1){ res=Add(res, y); }
            x >>= 1;
            y <<= 1; // y=(2^k)(y) [note: k is implicit here since + and ++ are NOT allowed]
        }
        return res;
    }
    
    /*----------------------------------------------------------------------
     4.6 Divide: Given two positive integers, compute their quotient,
     using only the addition, subtraction, and shifting operators
     ---------------------------------------------------------------------*/
    unsigned int Divide1(unsigned int x, unsigned int y){
        if (y==0) { throw overflow_error("cannot divide by 0"); }
        int res=0;
        while (x >= y){ // find biggest chunk of (2^k)(y) and subtract from x
            int k=1, chunk=y;
            while (x >= (chunk << 1)){
                chunk <<= 1;
                k <<= 1;
            }
            x -= chunk;
            res += k;
        }
        return res;
    }
    
    int Divide2(int dividend, int divisor) {
        long long x=abs((long long)dividend), y=abs((long long)divisor), res=0;
        if (y==0){ return INT_MAX; }
        
        while (x >= y){ // find biggest chunk of (2^k)(y) and subtract from x
            long long k=1, chunk=y;
            while (x >= (chunk << 1)){
                chunk <<= 1;
                k <<= 1;
            }
            x -= chunk;
            res += k;
        }
        
        if ((dividend < 0 && divisor > 0) || (dividend > 0 && divisor < 0)){ res = -res; }
        if (res > INT_MAX){ res = INT_MAX; }
        return (int)res;
    }
    
    /*----------------------------------------------------------------------
     4.7 Power
     ---------------------------------------------------------------------*/
    double Power1(double x, int y){
        if (y==0){ return 1.0; }
        double res=x;
        int exp=abs(y);
        while (exp>1){
            res *= x;
            exp--;
        }
        return res;
    }
    
    double Power2(double x, int exp){
        int res=1.0;
        while(exp){
            if (exp & 1){
                res *= x;
            }
            x *= x; exp >>= 1;
        }
        return res;
    }
    
    /*----------------------------------------------------------------------
     4.8 Reverse Int (decimal)
     ---------------------------------------------------------------------*/
    int ReverseDecimal(int n){
        int res=0;
        bool neg=n<0 ? true : false;
        if (neg) { n *= -1; }
        while (n>0){
            res *= 10;
            res += n%10;
            n/=10;
        }
        if (neg){
            res *= -1;
        }
        return res;
    }
    
    /*----------------------------------------------------------------------
     4.9 Palindrome Number
     ---------------------------------------------------------------------*/
    bool IsPalindrome(int n){
        if (n<0) { return false; } // negatives NOT palindromes due to leading "-"
        int rev=ReverseDecimal(n);
        while (n>0){
            if (n%10 != rev%10){ return false; }
            n/=10;
            rev/=10;
        }
        return true;
    }
};


int main(int argc, const char * argv[]) {

    Solution solution;
    /*
    while (true){
        int n;
        cout << "N: ";
        cin >> n;
        cout << endl;
        cout << "count1: " << solution.CountBits1(n) << endl;
        cout << "count2: " << solution.CountBits2(n) << endl;
        cout << "count3: " << solution.CountBits3(n) << endl;
        cout << "parity1: " << solution.Parity1(n) << endl;
        cout << "parity2: " << solution.Parity2(n) << endl;
        cout << "parity3: " << solution.Parity3(n) << endl;
        cout << "parity4: " << solution.Parity4(n) << endl;
        cout << "closest: " << solution.ClosestIntSameWeight(n) << endl;
        cout << "rev(dec): " << solution.ReverseDecimal(n) << endl;
        cout << "palindrome: " << solution.IsPalindrome(n) << endl;
    }
    */
    
    
    while (true){
        int x,y;
        cout << "x y: ";
        cin >> x >> y;
        cout << x << "+" << y << "=" << solution.Add(x, y) << endl;
        cout << x << "*" << y << "=" << solution.Multiply(x, y) << endl;
        cout << x << "/" << y << "=" << solution.Divide2(x, y) << endl;
        cout << x << "^" << y << "=" << (int)solution.Power1(x, y) << endl;
        cout << x << "^" << y << "=" << (int)solution.Power2(x, y) << endl;
    }
    
    
    return 0;
}




