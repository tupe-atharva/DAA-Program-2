#include<iostream>
#include<vector>
#include<math.h>
using namespace std;

int generateRandomNumbers(int n ){


    return ;
}


void orignalLargeIntMul (int a, int b){

}

void modifiedLargeIntMul(int a, int b){

}



int main(int argc, char*argv[]){ 
    int n = stoi(argv[1]); // string to integer conversion of the command line input

    if (argc != 2){
        cout << "This program expects a single input along with the file name in the command line, please abide to the same to avoid crashes and errors" << endl;
        return 0;
    }

    if(n%2 !=0 || n%3 != 0){
        cout << "Enter the value of n of the order 6k, ie. a number divisble by both 2 and 3" << endl;
        return 0;
    }

    // Call function to generate 2 n digit random numbers
    int a = generateRandomNumbers(n);
    int b = generateRandomNumbers(n);

    // Call function to calculate LIM using orignal algorithm -> n => n/2
    orignalLargeIntMul(a,b);

    // Call function to calculate LIM using modified algorithm -> n => n/3
    modifiedLargeIntMul(a,b);

    return 0;
}