#include<iostream>
#include<string>
#include<vector>
#include<math.h>
using namespace std;

int toInt(char c);//将字符值转换成进制值
char toChar(int n);//将进制值转换成字符值
long toTen(string str, int o);//将原进制转换成十进制（long）
void toNew(long num, int n);//将十进制（long）转换成新进制

int main() {
	int o, n;
	string str;
	while (cin >> o >> n >> str, o != 0) {
		if (str[0] == '-') {//负数直接输出"-"，并把"-"去掉
			cout << '-';
			str.erase(str.begin());
		}
		toNew(toTen(str, o), n);
	}
	return 0;
}

int toInt(char c) {
	if (c >= '0' && c <= '9') {
		return c - '0';
	}
	else if (c >= 'a' && c <= 'z') {
		return c - 'a' + 10;
	}
	else if (c >= 'A' && c <= 'Z') {
		return c - 'A' + 36;
	}
}

char toChar(int n) {
	if (n <= 9){
		return n + '0';
	}
	else if (n <= 35){
		return n - 10 + 'a';
	}
	else if (n <= 62) {
		return n - 36 + 'A';
	}
}

long toTen(string str, int o) {
	long ret = 0;
	for (int i = 0; i < str.length(); i++) {
		ret += toInt(str[i]) * pow(o, str.length() - i - 1);
	}
	return ret;
}

void toNew(long num, int n) {
	vector<char> ret;
	while (num > 0) {
		int b = num % n;
		ret.push_back(toChar(b));
		num /= n;
	}
	vector<char>::iterator iter;
	for (iter = ret.end(); iter > ret.begin(); --iter) {//vector从后向前遍历
		cout << *(iter - 1);
	}
	cout << endl;
}
