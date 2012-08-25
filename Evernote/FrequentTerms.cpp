// Frequent Terms

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;

map<string, int> ctr;

bool comp(string A, string B) {
	if (ctr[A] != ctr[B])
		return ctr[A] > ctr[B];
	return A < B;
}

int main() {
	int N, K;
	set<string> terms;
	string term;
	
	cin >> N;
	while (N--) {
		cin >> term;
		terms.insert(term);
		++ctr[term];
	}
	cin >> K;
	vector<string> order(terms.begin(), terms.end());
	sort(order.begin(), order.end(), comp);
	
	for (int i = 0; i < K; i++) {
		cout << order[i] << endl;
	}
	return 0;
}
