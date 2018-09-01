#include<iostream>
#include<string>
#include<vector>
using namespace std;

int main() {
	long num;
	while (cin >> num, num) {
		bool isNegtive = false;
		if (num < 0) {
			num = -num;
			isNegtive = true;
		}
		vector<char> ns;
		int num_len = 0;
		while (num > 0) {
			short n = num % 10;
			ns.push_back(n + '0');
			num_len++;
			num /= 10;
		}

		cout << num_len << endl;//位数

		vector<char>::iterator iter;//间隔输出
		if (isNegtive) {
			cout << '-';
		}
		for (iter = ns.end(); iter > ns.begin(); iter--) {
			if (iter - 1 == ns.begin()) {
				cout << *(iter - 1);
			}
			else {
				cout << *(iter - 1) << '_';
			}
		}
		cout << endl;

		if (isNegtive) {//逆向输出
			cout << '-';
		}
		for (iter = ns.begin(); iter < ns.end(); iter++) {
			cout << *iter;
		}
		cout << endl;
	}
	return 0;
}
