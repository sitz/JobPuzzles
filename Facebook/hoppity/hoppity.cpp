#include <fstream>  
#include <iostream>  
using namespace std;

int main(int argc, char *argv[]) {  
        ifstream input(argv[1]);  
        int n;  
        input >> n;  
        for(int i = 1; i <= n; ++i) {  
                if(i % 3 == 0 && i % 5 == 0)
                     cout << "Hop\n";  
                else if(i % 3 == 0)
                     cout << "Hoppity\n";  
                else if(i % 5 == 0)
                     cout << "Hophop\n";  
        }  
        return 0;  
}
