#include<iostream>
#include<vector>
#include<math.h>
#include<ctime>
using namespace std;

unsigned long long generateRandomNumbers(int n ){
    // This function can generate a number of maximum 19 digits, after that overflow happens

    long long lower = pow(10, (n-1)); // This will give the lowest n digit number 
    long long upper = pow(10, n) - 1; // This will give the highest n digit number 

    long long a = lower + rand() % (upper - lower + 1);
    // rand() % (upper - lower + 1), generates a random number between 0 and (upper - lower)
    // Adding lower to it shifts the range to [lower, upper].

    return a;
}

long long orignalLargeIntMul (long long a, long long b ,int n ){
    // This is supposed to be a recursive function
    if(a == 0 || b == 0){
        // Checking edge case where if either of the number is 0, then product is 0.
        // (Although the assignment says that the Most Significant Bit cannot be 0, this edge case is included as part of clean coding in order to cover all edge cases !)
        return 0;
    }
    // Base Case : if the max number of digits in either of the number is less than the threshold then multiply the 2 numbers using normal multiplication.
    if(n < 12){ // lets use 12 digits as the threshold
        return (a*b); // Normal multiplication untill 12 digits.
    }
    // Use else instead of else if so that this case is always executed in case the value of n is less than the threshold
    else{
        // Use a divide and conquer approach
        long long x, y, z ,w;
        int halfDigits = floor(n/2);
        x = a / pow(10,halfDigits);
        y = a % int(pow(10,halfDigits));
        z = b / pow(10, halfDigits);
        w = b % int(pow(10, halfDigits)); 
        // the pow function only works on integer types, since halfDigits is of type long long, we have to explicitly typecast it to integer.

        // a = x * 10^halfDigits + y
        // b = z * 10^halfDigits + w
        // in this way we have divided the input a and b into 2 halves and now we will recursively multiply them.

        return orignalLargeIntMul(x,y , n/2) * pow(10, 2*halfDigits) + orignalLargeIntMul(w,y, n/2) * pow(10, 2*halfDigits) + orignalLargeIntMul(y,w, n/2) ; 
        // Recursive call to the same function and reducing size to half in every recursive call.
    }
}

long long modifiedLargeIntMul(long long a, long long b , int n){
    int subPart = floor(n/3); // Taking the floor just to be sure, even though the main function ensures that the input is of the order 6k which is always divisible by 3.

    long long part1;
    long long part2;
    long long part3;
}

int main(int argc, char*argv[]){ 
    // Make sure that checking whether we are getting 2 inputs from the command line is the first thing we do in the main function, else if we end up using the 1st argument and then check for the 2nd one, we will get a warning error.
    if (argc != 2){
        cerr << "This program expects a single input along with the file name in the command line, please abide to the same to avoid crashes and errors" << endl;
        return 1;
    }

    int n = stoi(argv[1]); // string to integer conversion of the command line input

    // Check if the input n is divisble by 3 and 2.
    if(n%2 !=0 || n%3 != 0){
        cout << "Enter the value of n of the order 6k, ie. a number divisble by both 2 and 3" << endl;
        return 0;
    }

    // Call function to generate 2 n-digit random numbers
    srand(time(0)); // seed random number generator using current time
    long long a = generateRandomNumbers(n);
    long long b = generateRandomNumbers(n);

    // Print outputs for orignal algorithm - ie. divding the number into 2 parts in every call untill the base case is hit and then returning multiplication.
    // Print a, b and the resulting multiplication
    cout << "Number 1 : " << a << endl << "Number 2 : " << b << endl << endl;
    cout << "The large integer multiplication from the division of two smaller integers is A*B = " << orignalLargeIntMul(a,b, n) << endl; // Call function to calculate LIM using orignal algorithm -> n => n/2

    // Print outputs for modified algorithm
    // Print a, b and the resulting multiplication
    cout << "Number 1 : " << a <<endl << "Number 2 : " << b <<endl << endl;
    cout << "The large integer multiplication from the division of three smaller integers is A*B = " << modifiedLargeIntMul(a,b, n) << endl; // Call function to calculate LIM using modified algorithm -> n => n/3

    return 0;
}