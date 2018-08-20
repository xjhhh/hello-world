#include<iostream>
#include<string>
#include<ctype.h>
#include<vector>

using namespace std;

int main(void){
	char str[30];
	cout << "please input a string with length <= 20" << endl;
	cin.get(str, 30);
	if (strlen(str) > 20){
		cout << "ERROR!" << endl;
	}
	vector<char> s;
	for (int i = 0; i < strlen(str); i++){
		if (isalnum(str[i])){
			if (i % 2){
				s.push_back(str[i]);
			}
		} else {
			cout << "ERROE!" << endl;
			break;
		}
		if (i == strlen(str)){
			for (int i = 0; i < s.size(); i++){
				cout << s[i];
			}
			cout << endl;
		}
	}
}
