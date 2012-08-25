// Circular Buffer

#include <iostream>
#include <deque>
#include <string>
using namespace std;

int main() {
	int N;
	cin >> N;
	deque<string> cque;
	
	int M;
	string str;
	string choice;
	while (true) {
		cin >> choice;
		if (choice == "A") {
			cin >> M;
			while (M--) {
				cin >> str;
				if (cque.size() >= N) {
					cque.pop_front();
				}
				cque.push_back(str);
			}
		}
		else if (choice == "R") {
			cin >> M;
			while (M--) {
				cque.pop_front();
			}
		}
		else if (choice == "L") {
			for (int i = 0; i < cque.size(); i++) {
				cout << cque[i] << endl;
			}
		}		  
		else if (choice == "Q") {
			break;
		}
	}
	return 0;
}
