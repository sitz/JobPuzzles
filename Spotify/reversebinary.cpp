#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;

int main() {
	int64 N, lastOne = 1;
	cin >> N;
	vector<int64> binary;
	while (N) {
		binary.push_back(N % 2);
		if (N % 2) {
			lastOne = binary.size();
		}
		N /= 2;
	}
	int64 reversedBinaryInDecimal = 0;
	for (int64 index = lastOne - 1, multiplier = 1; index >= 0; index--, multiplier *= 2) {
		reversedBinaryInDecimal += multiplier * binary[index];
	}
	cout << reversedBinaryInDecimal << endl;
	return 0;
}
