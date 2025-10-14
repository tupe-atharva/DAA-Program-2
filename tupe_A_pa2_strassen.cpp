#include<iostream>
#include<vector>
#include<math.h>
#include<climits>
using namespace std;
 
int main(int argc, char*argv[]){ 
    
    if(argc != 2){
        // ie. if the user does not input exactly 2 arguments in the command line then we will return the program here with a meaningful meassage stating the problem;
        cout << "The program expects exactly 2 command line arguments, please bind to this conditon for the program to run ";
    }

    int n = stoi(argv[1]); // Talking the command line argument and storing the first value to n after converting it from a string to an integer (since the command line values are treated as string values).
    
    // Check for integer overflow within the matrix
    int max_val = INT_MAX / n;

    // Generate Random matrivces A and B :
    srand(time(0)); // seed random numbers
    vector<vector<int>> A(n, vector<int>(n));
    vector<vector<int>> B(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = rand() % max_val;
            B[i][j] = rand() % max_val;
        }
    }

    // Printing to check the generated matrices :
    // cout << "Matrix A : " << endl;
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cout << A[i][j] << " ";   
    //     }cout << endl;
    // }

    // cout << "Matrix B : " << endl;
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cout << B[i][j] << " ";   
    //     }cout << endl;
    // }


    // Initialize the result matrix C :
    vector<vector<long long>> C(n, vector<long long>(n, 0)); // We used long type to make sure integer overflow does not happen and we can hold a big integer value.


    // Compute A*B using the standard matrix multiplication
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += (long long)A[i][k] * B[k][j]; // Type casting to long long to ensure large elements fit in.
            }
        }
    }

    // Printing the resulting C matrix :
    cout << "Matrix C : " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << C[i][j] << " ";   
        }cout << endl;
    }

    // Compute A*B using the Strassen's matrix multiplication
    
    // Base Case : n = 1 ==> Simply return 
    // A[0][0] * B[0][0]

    vector<vector<long long>> strassenMultiply(const vector<vector<long long>>& A,const vector<vector<long long>>& B);

    


 
    return 0;
}