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
For the final task, you must find all subsets of an array where the largest number is the sum of the remaining numbers.

For example, for an input of: (1, 2, 3, 4, 6),
the subsets would be
	1 + 2 = 3
	1 + 3 = 4
	2 + 4 = 6
	1 + 2 + 3 = 6
	
Here is the list of numbers you should run your code on. The password is the number of subsets. 
In the above case the answer would be 4.

Input
-----
{3, 4, 9, 14, 15, 19, 28, 37, 47, 50, 54, 56, 59, 61, 70, 73, 78, 81, 92, 95, 97, 99}

Output
------
179
*/

int main() {
	//freopen("testI.txt", "r", stdin);
	//freopen("testO.txt", "w", stdout);
	
	int A[] = {3, 4, 9, 14, 15, 19, 28, 37, 47, 50, 54, 56, 59, 61, 70, 73, 78, 81, 92, 95, 97, 99};
	int M = sizeof(A) / sizeof(int);
	int N = 1<<M;
	int Cnt = 0;
	for (int i = 1; i < N; i++) {
		//printf("%d\n", i);
		int R = i;
		vector< int > V;
		for (int j = 0; j < M; j++) {
			V.push_back((R % 2) * A[j]);
			R /= 2;
		}
		if (V.size() > 1) {
			sort(V.begin(), V.end());
			int T = 0;
			for (int k = 0; k + 1 < V.size(); k++)
				T += V[k];
			if (T == V[V.size() - 1]) ++Cnt;
		}
	}
	cout << endl << Cnt << endl;
	return 0;
}
