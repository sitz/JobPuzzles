#include <algorithm>
#include <iostream>
#include <utility>
#include <string>
using namespace std;

typedef long long int64;

struct Song {
	string name;
	int index;
	int64 quality;
};

bool comp(Song A, Song B) {
	if (A.quality != B.quality) {
		return A.quality >= B.quality;
	}
	return A.index < B.index;
}

int main() {
	int N, M;
	cin >> N >> M;
	Song songs[N];
	for (int i = 0; i < N; i++) {
		cin >> songs[i].quality >> songs[i].name;
		songs[i].index = (i + 1);
		songs[i].quality *= (i + 1);
	}
	sort(songs, songs + N, comp);
	for (int i = 0; i < min(M, N); i++) {
		cout << songs[i].name << endl;
	}
	return 0;
}
