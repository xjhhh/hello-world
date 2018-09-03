#include<iostream>
#include<string>
#include<ctype.h>
#include<vector>
using namespace std;

vector<int> str2vector(string str);
int str2int(string str);
bool pk2num(int, int);
void myInsert(vector<int>&, int);
void print_ret(vector<int>, int);
int main() {
	string input;
	int idx;
	getline(cin, input);
	cin >> idx;

	vector<int> ret = str2vector(input);
	print_ret(ret, idx);
	return 0;
}

vector<int> str2vector(string str) {
	vector<int> ret;
	while (str.length()) {
		int end = str.find(' ');
		if (end == -1) {
			end = (int)str.length();
		}
		int c_num = str2int(str.substr(0, end));
		if (c_num) {
			myInsert(ret, c_num);
			str.erase(0, end + 1);
		}
		else {
			ret.clear();
			return ret;
		}
	}
	return ret;
}

int str2int(string str) {
	int num = 0;
	int str_len = str.length();
	for (int i = 0; i < str_len; i++) {
		if (isdigit(str[i])) {
			num += (str[i] - '0') * pow(10, str_len - i - 1);
		}
		else {//有非法字符
			return 0;
		}
	}
	return num;
}

bool pk2num(int a, int b) {//a比b大返回false，否则返回true
	int a1 = a % 1000;
	int b1 = b % 1000;
	return a1 <= b1;
}

void myInsert(vector<int> &vect, int n) {
	vector<int>::iterator iter;
	for (iter = vect.begin(); iter < vect.end(); iter++) {
		if (!pk2num(*iter, n)) {//n小，需要调换顺序
			break;
		}
	}
	vect.insert(iter, n);
}

void print_ret(vector<int> vect, int i) {
	if (vect.size()) {
		vector<int>::iterator iter = vect.begin() + i - 1;
		cout << *iter << endl;
	}
	else {
		cout << "Invalide input!" << endl;
	}
}
