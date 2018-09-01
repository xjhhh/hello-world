#include < stdio.h >
#include < stdlib.h >
#include < time.h >
#include < math.h >

int clear_input(void) {//检查输入缓冲区，如果不为空，返回0。并清空输入缓冲区
	int ret = 1;
	char ch;
	while ((ch = getchar()) != '\n' && ch != EOF) ret = 0;
	clearerr(stdin);
	return ret;
}

int check_input(int arr[], int size){//限定输入为整数，非法输入返回0
	int ret = 1;
	int i = 0;
	while (1) {
		ret *= scanf_s("%d", &arr[i++]);
		if (ret == 0) {//读到一个非整数
			clear_input();//清空输入缓冲区
			break;
		}
		else if (i == size) {//已经读到指定数目的输入
			break;
		}
	}
	if (ret) {//目前没有读到非法输入
		ret *= clear_input();//检测输入缓冲区
	}
	return ret;
}

int get_rand(int num) {//随机一个1-num之间的数
	srand(unsigned int(time(NULL)));
	return rand() % num + 1;
}
