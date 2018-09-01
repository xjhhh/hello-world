#include<iostream>
#include<string>
#include<ctype.h>
#include<math.h>
using namespace std;

int ip2int(string str);
int main() {
	string ip1, ip2, ip3, ip4;
	cin >> ip1 >> ip2 >> ip3 >> ip4;
	int ip1num = ip2int(ip1);
	int ip2num = ip2int(ip2);
	int ip3num = ip2int(ip3);
	int ip4num = ip2int(ip4);
	if (!ip1num || !ip2num || !ip3num || !ip4num) {
		cout << "Invalide input!" << endl;
	}
	else if (ip2num <= ip1num || ip4num <= ip3num) {
		cout << "The end should be bigger than the start!" << endl;
	}
	else {
		if (ip1num < ip3num) {
			if (ip2num < ip3num) {
				cout << "No Overlap IP" << endl;
			}
			else {
				cout << "Overlap IP" << endl;
			}
		}
		else if (ip1num == ip3num) {
			cout << "Overlap IP" << endl;
		}
		else {
			if (ip1num > ip4num) {
				cout << "No Overlap IP" << endl;
			}
			else {
				cout << "Overlap IP" << endl;
			}
		}
	}
	return 0;
}

int ip2int(string str) {
	int ret = 0;
	int w = 1000;
	while (str.length()) {
		if (!w) {//超过4段
			return 0;
		}
		int end = str.find('.');
		if (end == -1) {
			end = (int)str.length();
		}
		int num = 0;
		for (int i = 0; i < end; i++) {
			if (isdigit(str[i])) {
				num += (str[i] - '0') * pow(10, end - i - 1);
			}
			else {//有非法字符
				return 0;
			}
		}
		if (w == 1000) {//第一段不能是0
			if (num == 0) {
				return 0;
			}
		}
		ret += num * w;
		str.erase(0, end + 1);
		w /= 10;
	}
	if (w) {//不足4段
		return 0;
	}
	else {
		return ret;
	}
}
