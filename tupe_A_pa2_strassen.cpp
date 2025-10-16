#include<iostream>
#include<vector>
#include<math.h>
#include<climits>
using namespace std;

// Helper Function 1 : addMAtrix
// Takes 2 matrices A and B as input and adds their elements
vector<vector<long long>> addMatrix(
    const vector<vector<long long>>& A,
    const vector<vector<long long>>& B) 
{
    int n = A.size();
    vector<vector<long long>> C(n, vector<long long>(n));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

// Helper function 2 : subMatrix
// Takes 2 matrices A and B as input and subtracts their elements
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
// Takes 2 matrices A and B as input and splits them into A11, A12, A21, A22 and each of them have size n/2;
void splitMatrix(const vector<vector<long long>>& A,
    vector<vector<long long>>& A11,
    vector<vector<long long>>& A12,
    vector<vector<long long>>& A21,
    vector<vector<long long>>& A22) 
{
    int n = A.size() / 2;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A11[i][j] = A[i][j]; // Left top corner
            A12[i][j] = A[i][j + n]; // Right top corner
            A21[i][j] = A[i + n][j]; // Bottom left corner
            A22[i][j] = A[i + n][j + n]; // Bottom right corner
        }
    }
}

// Helper function 4 : combineMatrix
// This helper function takes 4 submatrices ie. C11, C12, C21, C22 as input and combines them 
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

vector<vector<long long>> strassenMultiply(const vector<vector<long long>>& A,const vector<vector<long long>>& B){
// We have created helper functions to evaluate the strassen's intermediate matrices like addMatrix, subMatrix,splitMatrices and combineSubMatrices
// Compute A*B using the Strassen's matrix multiplication
    
    // Base Case : n = 1 ==> Simply return 
    // A[0][0] * B[0][0]

    if(A.size() == 1)
    {
        return{{A[0][0] * B[0][0]}};
    }
    // Else split the matrix into 4 parts of n/2 size and use the strassen's equations to solve the mstrix multiplication
    int n = A.size();
    int k = n / 2;

    vector<vector<long long>> 
        // Decalring intermediate matrices A11, A21, B11, B21
        A11(k, vector<long long>(k)), A12(k, vector<long long>(k)),
        A21(k, vector<long long>(k)), A22(k, vector<long long>(k)),
        B11(k, vector<long long>(k)), B12(k, vector<long long>(k)),
        B21(k, vector<long long>(k)), B22(k, vector<long long>(k));

    splitMatrix(A, A11, A12, A21, A22);
    splitMatrix(B, B11, B12, B21, B22);

    // Evaluate M1 - M7 as per strassen's given equations.
    // Note : auto is a keyword that automatically takes the type of the variable from the RHS.
    auto M1 = strassenMultiply(addMatrix(A11, A22), addMatrix(B11, B22));
    auto M2 = strassenMultiply(addMatrix(A21, A22), B11);
    auto M3 = strassenMultiply(A11, subMatrix(B12, B22));
    auto M4 = strassenMultiply(A22, subMatrix(B21, B11));
    auto M5 = strassenMultiply(addMatrix(A11, A12), B22);
    auto M6 = strassenMultiply(subMatrix(A21, A11), addMatrix(B11, B12));
    auto M7 = strassenMultiply(subMatrix(A12, A22), addMatrix(B21, B22));

    auto C11 = addMatrix(subMatrix(addMatrix(M1, M4), M5), M7);
    auto C12 = addMatrix(M3, M5);
    auto C21 = addMatrix(M2, M4);
    auto C22 = addMatrix(subMatrix(addMatrix(M1, M3), M2), M6);

    return combineMatrix(C11, C12, C21, C22);

}

vector<vector<long long>> stdMatrixMul(int n, const vector<vector<long long>>& A,const vector<vector<long long>>& B){
    // Initialize the result matrix C :
    vector<vector<long long>> C(n, vector<long long>(n, 0)); // We used long type to make sure integer overflow does not happen and we can hold a big integer value.
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += (long long)A[i][k] * B[k][j]; // Type casting to long long to ensure large elements fit in.
            }
        }
    }
    // This is a O(N^3) solution since we are using 3 nested for loops.

    // Printing the resulting C matrix :
    // cout << "Matrix C : " << endl;
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cout << C[i][j] << " ";   
    //     }cout << endl;
    // }

    return C;

}

void printMatrix(vector<vector<long long>> A, int n){
    for(int i = 0; i<n; i++){
        for (int j = 0; j < n; j++)
        {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
}

int main(int argc, char*argv[]){ 
    
    if(argc != 2){
        // ie. if the user does not input exactly 2 arguments in the command line then we will return the program here with a meaningful meassage stating the problem;
        cout << "The program expects exactly 2 command line arguments, please bind to this conditon for the program to run ";

        return 0;
    }

    int n = stoi(argv[1]); // Talking the command line argument and storing the first value to n after converting it from a string to an integer (since the command line values are treated as string values).
    // Stoi function  : string to integer : converts a string to a integer.
    
    // Check for integer overflow within the matrix
    int max_val = INT_MAX / n;

    // Generate Random matrices A and B :
    srand(time(0)); // seed random numbers
    vector<vector<long long>> A(n, vector<long long>(n));
    vector<vector<long long>> B(n, vector<long long>(n));

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
    cout << "A = " << endl ;
    printMatrix(A, n);
    cout << endl;
    cout << "B = " << endl ;
    printMatrix(B, n);
    cout << endl;

    // Compute A*B using the standard and strassen's matrix multiplication
    auto C_std = stdMatrixMul(n, A, B);
    

    // Padding the input matrices if their size is not a factor of 2^k since strassen's algorithm works recursively dividing the size from n to n/2.
    int m = 1;
    while (m < n) m *= 2;

    // pad if needed
    vector<vector<long long>> A_pad(m, vector<long long>(m, 0));
    vector<vector<long long>> B_pad(m, vector<long long>(m, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            A_pad[i][j] = A[i][j];
            B_pad[i][j] = B[i][j];
        }

    // multiply
    auto C_pad = strassenMultiply(A_pad, B_pad);

    // trim to n×n
    vector<vector<long long>> C_strassen(n, vector<long long>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C_strassen[i][j] = C_pad[i][j];


    // Printing the resulting matrices
    cout << "The Standard Matrix multiplication A*B = " << endl;
    printMatrix(C_std, n);
    cout << endl;

    cout << "The Strassen's Matrix multiplication A*B = : " << endl;
    printMatrix(C_strassen, n);
    cout << endl;

    return 0;
}