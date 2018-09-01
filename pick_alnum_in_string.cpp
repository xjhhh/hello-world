#include<iostream>
#include<string>
#include<ctype.h>
#include<vector>

using namespace std;

int main(void){
	int s_len;
	cout << "please input a string with length <= 20" << endl;
	//char str[30];
	//cin.get(str, 30);//cin.getline(str, 30);
	//s_len = strlen(str);
	string str;
	getline(cin, str);
	s_len = str.length();
	if (s_len > 20){
		cout << "ERROR!" << endl;
	}

	vector<char> s;
	for (int i = 0; i < s_len; i++) {
		if (isalnum(str[i])){
			if (i % 2){
				s.push_back(str[i]);
			}
		}
		else {
			cout << "ERROR!" << endl;
			break;
		}
		if (i == s_len - 1){
			for (unsigned int i = 0; i < s.size(); i++){
				cout << s[i];
			}
			cout << endl;
		}
	}
}
