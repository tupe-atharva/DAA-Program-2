#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

/*
-----------------------------------------
 Helper Function 1 : generateRandomNumberString
 Generates a random n-digit number as a string.
 The first digit is between 1–9 (to avoid leading zeros).
-----------------------------------------
*/
string generateRandomNumberString(int n) {
    string num = "";
    num += '1' + rand() % 9;        // First digit non-zero
    for (int i = 1; i < n; i++)
        num += '0' + rand() % 10;   // Remaining digits can be any digit
    return num;
}

/*
-----------------------------------------
 Helper Function 2 : addStrings
 Performs addition of two large integers represented as strings.
-----------------------------------------
*/
string addStrings(string a, string b) {
    if (a.size() < b.size()) swap(a, b);
    int carry = 0;
    string res = "";
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    for (int i = 0; i < a.size(); i++) {
        int sum = (a[i] - '0') + (i < b.size() ? b[i] - '0' : 0) + carry;
        res += (sum % 10) + '0';
        carry = sum / 10;
    }
    if (carry) res += (carry + '0');
    reverse(res.begin(), res.end());
    return res;
}

/*
-----------------------------------------
 Helper Function 3 : subtractStrings
 Performs subtraction of two large integers represented as strings.
 Assumes a >= b.
-----------------------------------------
*/
string subtractStrings(string a, string b) {
    int borrow = 0;
    string res = "";
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    for (int i = 0; i < a.size(); i++) {
        int diff = (a[i] - '0') - (i < b.size() ? b[i] - '0' : 0) - borrow;
        if (diff < 0) diff += 10, borrow = 1;
        else borrow = 0;
        res += diff + '0';
    }
    while (res.size() > 1 && res.back() == '0') res.pop_back();
    reverse(res.begin(), res.end());
    return res;
}

/*
-----------------------------------------
 Helper Function 4 : shiftLeft
 Appends k zeros to simulate multiplication by 10^k.
-----------------------------------------
*/
string shiftLeft(string a, int k) {
    return a + string(k, '0');
}

/*
-----------------------------------------
 Function 5 : originalLargeIntMul
 Recursive divide-and-conquer (2-part split) multiplication.
 Equivalent to Karatsuba-like approach.
-----------------------------------------
*/
string originalLargeIntMul(string a, string b, int n) {
    if (a == "0" || b == "0") return "0";
    if (n <= 4) return to_string(stoll(a) * stoll(b));

    while (a.size() < n) a = "0" + a;
    while (b.size() < n) b = "0" + b;

    int half = n / 2;
    string x = a.substr(0, n - half), y = a.substr(n - half);
    string z = b.substr(0, n - half), w = b.substr(n - half);

    string p1 = originalLargeIntMul(x, z, n - half);
    string p2 = originalLargeIntMul(y, w, half);
    string p3 = originalLargeIntMul(addStrings(x, y), addStrings(z, w), n - half);

    string part1 = shiftLeft(p1, 2 * half);
    string part2 = shiftLeft(subtractStrings(subtractStrings(p3, p1), p2), half);
    return addStrings(addStrings(part1, part2), p2);
}

/*
-----------------------------------------
 Function 6 : modifiedLargeIntMul
 Modified algorithm dividing input into 3 equal parts.
 Follows slide 28 of Ch5 Divide-and-Conquer notes.
-----------------------------------------
*/
string modifiedLargeIntMul(string a, string b, int n) {
    if (a == "0" || b == "0") return "0";
    if (n <= 4) return to_string(stoll(a) * stoll(b));

    while (a.size() < n) a = "0" + a;
    while (b.size() < n) b = "0" + b;

    int m = n / 3;

    // Divide each number into three parts
    string a1 = a.substr(0, n - 2 * m);
    string a2 = a.substr(n - 2 * m, m);
    string a3 = a.substr(n - m);
    string b1 = b.substr(0, n - 2 * m);
    string b2 = b.substr(n - 2 * m, m);
    string b3 = b.substr(n - m);

    // Compute all 9 necessary partial products
    string p1 = modifiedLargeIntMul(a1, b1, a1.size());       // a1*b1
    string p2 = modifiedLargeIntMul(a2, b2, a2.size());       // a2*b2
    string p3 = modifiedLargeIntMul(a3, b3, a3.size());       // a3*b3
    string p4 = modifiedLargeIntMul(a1, b2, max(a1.size(), b2.size())); // a1*b2
    string p5 = modifiedLargeIntMul(a2, b1, max(a2.size(), b1.size())); // a2*b1
    string p6 = modifiedLargeIntMul(a1, b3, max(a1.size(), b3.size())); // a1*b3
    string p7 = modifiedLargeIntMul(a3, b1, max(a3.size(), b1.size())); // a3*b1
    string p8 = modifiedLargeIntMul(a2, b3, max(a2.size(), b3.size())); // a2*b3
    string p9 = modifiedLargeIntMul(a3, b2, max(a3.size(), b2.size())); // a3*b2

    // Combine results using the correct formula:
    // A*B = a1b1*10^(4m) + (a1b2 + a2b1)*10^(3m) +
    //        (a1b3 + a2b2 + a3b1)*10^(2m) + (a2b3 + a3b2)*10^m + a3b3
    string term1 = shiftLeft(p1, 4 * m);
    string term2 = shiftLeft(addStrings(p4, p5), 3 * m);
    string term3 = shiftLeft(addStrings(addStrings(p6, p2), p7), 2 * m);
    string term4 = shiftLeft(addStrings(p8, p9), m);

    return addStrings(addStrings(addStrings(addStrings(term1, term2), term3), term4), p3);
}

/*
-----------------------------------------
 Main Function
 - Validates input
 - Generates random n-digit numbers
 - Executes both algorithms
 - Compares their outputs
-----------------------------------------
*/
int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./tupe_a_pa2_lim <n>" << endl;
        return 1;
    }

    int n = stoi(argv[1]);
    if (n % 2 != 0 || n % 3 != 0) {
        cout << "Enter n = 6k (divisible by both 2 and 3)" << endl;
        return 0;
    }

    srand(time(0));
    string a = generateRandomNumberString(n);
    string b = generateRandomNumberString(n);

    cout << "A : " << a << endl;
    cout << "B : " << b << endl << endl;

    cout << "The large integer multiplication from the division of two small integers is :" << endl;
    cout << "A*B = " << originalLargeIntMul(a, b, n) << endl << endl;

    cout << "The large integer multiplication from the division of three small integers is :" << endl;
    cout << "A*B = " << modifiedLargeIntMul(a, b, n) << endl;

    return 0;
}
