#include <bits/stdc++.h>
using namespace std;

int main() {
    // 1001100的所有子集
    
    // 1000000
    // 0001000
    // 0000100

    // 1001000
    // 1000100
    // 0001100

    // 1001100
    
    int cnt = 0b1001100;
    for (int j = cnt; j > 0; j = (j - 1) & cnt) {
        cout << bitset<7>(j) << endl;
    }
}