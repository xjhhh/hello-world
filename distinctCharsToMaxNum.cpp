#include<iostream>
#include<string>
#include<ctype.h>
#include<vector>
using namespace std;

bool checkIndex(string str, int i);

vector<vector<int> > str_ana(10);//用于解析输入的字符串
int main() {
	string str;
	while (getline(cin, str), str != "0") {
		int s_len = str.length();
		for (int i = 0; i < s_len; i++) {
			if (isdigit(str[i])) {//这是一个数字
				int c_number = str[i] - '0';
				str_ana[c_number].push_back(i);//push这个数字的当前下标
			} else {
				cout << "please input a number!" << endl;
				continue;
			}
			if (i == s_len - 1) {//输入是合法的
				vector<int> ret;
				for (int i = 0; i < s_len; i++) {
					if (checkIndex(str, i)) {//找到真数后，该真数的索引桶只保留当前这个索引
						int c_number = str[i] - '0';
						str_ana[c_number].clear();
						str_ana[c_number].push_back(i);
						ret.push_back(c_number);
					}
				}
				for (unsigned int i = 0; i < ret.size(); i++){
					cout << ret[i];
				}
				cout << endl;
			}
		}
	}
	return 0;
}

bool checkIndex(string str, int i) {
	if (i > (int)(str.length() - 1)) {
		cout << "索引越界" << endl;
	} else {
		int c_number = str[i] - '0';
		vector<int> c_vector = str_ana[c_number];
		vector<int>::iterator itor = c_vector.begin();
		while (*itor != i && itor + 1 != c_vector.end()) {//!!!!!!  itor + 1
			itor++;
		}
		if (itor + 1 == c_vector.end()) {
			return *itor == i;
		} else {
			int j = *(itor + 1);
			for (int k = i + 1; k < j; k++) {
				if (checkIndex(str, k)) {
					return (str[k] - '0') <= c_number;
				}
			}
			return true;
		}
	}
}