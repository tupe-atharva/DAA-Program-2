#include<iostream>
#include<vector>
#include<math.h>
#include<climits>
using namespace std;

// Helper Function 1 : addMAtrix
vector<vector<long long>> addMatrix(
    const vector<vector<long long>>& A,
    const vector<vector<long long>>& B) 
    {
        int n = A.size();
        vector<vector<long long>> C(n, vector<long long>(n));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                C[i][j] = A[i][j] + B[i][j];
        return C;
    }

// Helper function 2 : subMatrix
vector<vector<long long>> subMatrix(
    const vector<vector<long long>>& A,
    const vector<vector<long long>>& B) 
    {
        int n = A.size();
        vector<vector<long long>> C(n, vector<long long>(n));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                C[i][j] = A[i][j] - B[i][j];
        return C;
    }

// Helper function 3 : splitMatrix
void splitMatrix(const vector<vector<long long>>& A,
    vector<vector<long long>>& A11,
    vector<vector<long long>>& A12,
    vector<vector<long long>>& A21,
    vector<vector<long long>>& A22) 
    {
        int n = A.size() / 2;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + n];
                A21[i][j] = A[i + n][j];
                A22[i][j] = A[i + n][j + n];
            }
        }
    }


// Helper function 4 : combineMatrix
vector<vector<long long>> combineMatrix(
    const vector<vector<long long>>& C11,
    const vector<vector<long long>>& C12,
    const vector<vector<long long>>& C21,
    const vector<vector<long long>>& C22) 
    {
        int n = C11.size();
        vector<vector<long long>> C(2 * n, vector<long long>(2 * n));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                C[i][j] = C11[i][j];
                C[i][j + n] = C12[i][j];
                C[i + n][j] = C21[i][j];
                C[i + n][j + n] = C22[i][j];
            }
        }
        return C;
    }



int main(int argc, char*argv[]){ 
    
    if(argc != 2){
        // ie. if the user does not input exactly 2 arguments in the command line then we will return the program here with a meaningful meassage stating the problem;
        cout << "The program expects exactly 2 command line arguments, please bind to this conditon for the program to run ";
    }

    int n = stoi(argv[1]); // Talking the command line argument and storing the first value to n after converting it from a string to an integer (since the command line values are treated as string values).
    // Stoi function  : string to integer : converts a string to a integer.
    
    // Check for integer overflow within the matrix
    int max_val = INT_MAX / n;

    // Generate Random matrivces A and B :
    srand(time(0)); // seed random numbers
    vector<vector<int>> A(n, vector<int>(n));
    vector<vector<int>> B(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = rand() % max_val; // Take modulus to get the remainder
            B[i][j] = rand() % max_val; // Take modulus to get the remainder
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
    // This is a O(N^3) solution since we are using 3 nested for loops.

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
    // We are gonna create helper functions to evaluate the strassen's intermediate matrices like addMatrix, subMatrix,splitMatrices and combineSubMatrices

    

    


 
    return 0;
}