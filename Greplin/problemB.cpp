#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <sstream>
using namespace std;

/*
Problem Statement
-----------------
write code to find the first prime fibonacci number larger than a given minimum.

For example, the first prime fibonacci number larger than 10 is 13.

When you are ready, go here or call this automated number (415) 799-9454. You will receive additional instructions at that time.
For the second portion of this task, note that for the number 12 we consider the sum of the prime divisors to be 2 + 3 = 5.  We do not include 2 twice even though it divides 12 twice.

Output
------
352
*/

#define MAX 1000000
bool P[MAX + 1];
bool F[MAX + 1];
vector< int > prime;

void Fibonacci() {
	memset(F, false, sizeof F);
	int A = 0, B = 1;
	F[A] = F[B] = true;
	while (true) {
		int T = B;
		B = A + B;
		A = T;
		if ( B > MAX) break;
		F[B] = true;
		cout << B << endl;
	}
}

void Sieve() {
	memset(P, true, sizeof P);
	P[0] = P[1] = false;
	for (int i = 2; i <= MAX; i++) {
		if (P[i]) {
			prime.push_back(i);
			for (int j = 2 * i; j <= MAX; j += i)
				P[j] = false;
		}
	}
}

int main() {
	//freopen("testI.txt", "r", stdin);
	//freopen("testO.txt", "w", stdout);
	
	Sieve();
	Fibonacci();
	
	int N = 514230;

	int X = 227000;
	for (int i = X + 1; i <= MAX; i++) {
		if (P[i] && F[i]) {
			cout << endl << i << endl;
			break;
		}
	}
	
	int T = 0;
	for (int i = 0; i < prime.size(); i++) {
		if (N % prime[i] == 0) {
			T += prime[i];
			while (N % prime[i] == 0)
				N /= prime[i];
		}
	}
	cout << T << endl;
	return 0;
}
