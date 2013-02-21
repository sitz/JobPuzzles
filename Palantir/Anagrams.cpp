#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

int main() {
    string strA, strB;
    
    getline(cin, strA); sort(strA.begin(), strA.end());
    getline(cin, strB); sort(strB.begin(), strB.end());
    
    cout << strA == strB ? "Anagrams!" : "Not anagrams!" << endl;
    return 0;
}
