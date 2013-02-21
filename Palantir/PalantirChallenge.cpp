#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <cctype>
using namespace std;

typedef long long int64;

int64 stringToInt64(string str) {
	stringstream ss;
	int64 val;
	ss << str;
	ss >> val;
	return val;
}

int64 charToInt64(char ch) {
	if (isdigit(ch)) {
		return ch - '0';
	}
	return ch - 'A' + 10;
}

int64 convertToDecimal(string str) {
	int delimiterIndex = str.find("_");
	string number = str.substr(0, delimiterIndex);
	int64 base = stringToInt64(str.substr(delimiterIndex + 1));
	int64 value = 0;

	for (int64 index = number.length() - 1, multiplier = 1; index >= 0; index--, multiplier *= base) {
		value += multiplier * charToInt64(number[index]);
	}
	return value;
}

int main() {
	vector<int64> expression;
	string currentString;
	int64 currentValue = 1;

	while (cin >> currentString) {
		if (currentString == "+") {
			expression.push_back(currentValue);
			currentValue = 1;
		} else if (currentString == "-") {
			expression.push_back(currentValue);
			currentValue = -1;
		} else if (currentString == "*") {
		} else {
			currentValue *= convertToDecimal(currentString);
		}
	}
	expression.push_back(currentValue);

	int64 expressionValue = 0;
	for (int i = 0; i < expression.size(); i++) {
		expressionValue += expression[i];
	}
	cout << expressionValue << endl;

	return 0;
}
