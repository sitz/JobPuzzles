// MultiplyExceptSelf

#include <iostream>
using namespace std;

typedef long long int64;
#define MAXX 1000
int64 data[MAXX + 5];
int64 prodL[MAXX + 5];
int64 prodR[MAXX + 5];

int main() {
	int N;
	cin >> N;
	
	prodL[0] = prodL[N + 1] = 1;
	prodR[0] = prodR[N + 1] = 1;
	
	for (int i = 1; i <= N; i++) {
		cin >> data[i];
	}
	for (int i = 1; i <= N; i++) {
		prodL[i] = prodL[i - 1] * data[i];
	}
	for (int i = N; i >= 1; i--) {
		prodR[i] = prodR[i + 1] * data[i];
	}
	
	for (int i = 1; i <= N; i++) {
		cout << prodL[i - 1] * prodR[i + 1] << endl;
	}
	
	return 0;
}

