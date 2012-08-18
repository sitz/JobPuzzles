// Fourth Floor
 
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

#define N 3
#define MAXX 1000

int coin[N  + 1] = {1, 4, 5, 9};
int dp[MAXX + 1];

int greedyCoinCount(int M) {
	int count = 0;
	for (int c = N; c >= 0; c--) {
		int cnt = M / coin[c];
		count += cnt;
		M -= cnt * coin[c];
	}
	return count;
}

void dpCoinCount() {
	memset(dp, 0, sizeof dp);
	
	for (int i = 1; i <= MAXX; i++) {
		dp[i] = MAXX;
		
		for (int c = N; c >= 0; c--) {
			if (coin[c] <= i) {
				int temp = dp[i - coin[c]] + 1;
				dp[i] = min(dp[i], temp);
			}
		}
	}
}

int main() {
	dpCoinCount();
	
	int wrongCount = 0;
	
	for (int i = 1; i <= MAXX; i++) {
		//cout << i << " " << dp[i] << " " << greedyCoinCount(i) << endl;
		wrongCount += (dp[i] - greedyCoinCount(i)) < 0;
	}
	cout << wrongCount << endl;
	
	return 0;
}
