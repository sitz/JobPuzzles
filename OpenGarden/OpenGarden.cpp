#include <iostream>
using namespace std;

/*
Solution
--------
Total = 100000000
Value = {2134411, 2142508, 2226009, 2543482, 2812896, 3095313, 3279833, 4224851, 4296250, 4335391, 4552402, 5268860, 5582170, 5946800, 6371773, 9461105, 12828837, 18897109}
*/
bool subset(int population[], int sum, int N) {
	bool** dp = new bool*[N + 1];
    for (int i = 0; i <= N; i++) {
    	dp[i] = new bool[sum + 1];
        for(int j = 0; j<= sum; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = false;
                dp[i][0] = true;
            }
            else if (j < population[i - 1])
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - population[i - 1]];
        }
    }

    if (dp[N][sum]) {
        int i = N, j = sum;
        while (i >= 0 && j >= 0) {	
            if (j == 0) break;

            if (!dp[i][j] || !dp[i - 1][j]) {
                cout << population[i - 1] << " ";
                j -= population[i - 1];
            }
            --i;
        }
    }

    for (int i = 0; i <= N; i++) delete[] dp[i];
    delete[] dp;

    return dp[N][sum];
}

int main() {
	int census[] = {18897109, 12828837, 9461105, 6371773, 5965343, 5946800, 5582170, 5564635, 5268860, 4552402, 4335391, 4296250, 4224851, 4192887, 3439809, 3279833, 3095313, 2812896, 2783243, 2710489, 2543482, 2356285, 2226009, 2149127, 2142508, 2134411};
	int N = sizeof(census) / sizeof(census[0]);
	int sum = 100000000;

    cout << (subset(census, sum, N) ? "\nYes\n" : "\nNo\n");

    return EXIT_SUCCESS;
}
