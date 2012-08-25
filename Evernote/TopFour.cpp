// Top Four

#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long int64;

int main() {
	int64 data[4], dat, N;
	
	scanf("%lld", &N);
	for (int i = 0; i < 4; i++) {
		scanf("%lld", &data[i]);
	}
	sort(data, data + 4);
	for (int i = 4; i < N; i++) {
		scanf("%lld", &dat);
		if (dat > data[0]) {
			swap(dat, data[0]);
			sort(data, data + 4);
		}
	}
	for (int i = 3; i >= 0; i--) {
		printf("%lld\n", data[i]);
	}
	
	return 0;
}
