// Triangle

#include <iostream>
using namespace std;

typedef long long int64;

#define MAXX 100
int64 triangle[MAXX][MAXX];

int main() {
	for (int i = 0; i < MAXX; i++)
		for (int j = 0; j <= i; j++)
			cin >> triangle[i][j];
			
	for (int i = MAXX - 2; i >= 0; i--)
		for (int j = 0; j <= i; j++) {
			int k = triangle[i + 1][j] < triangle[i + 1][j + 1];
			
			triangle[i][j] += triangle[i + 1][j + k];
		}
	cout << triangle[0][0] << endl;
	
	return 0;
}
