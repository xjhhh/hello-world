#include < stdio.h >
#include < stdlib.h >
#include < time.h >
#include < math.h >

int clear_input(void){
	int ret = 1;
	char ch;
	while ((ch = getchar()) != '\n' && ch != EOF) ret = 0;
	clearerr(stdin);
	return ret;
}

int check_input(int arr[], int size){
	int ret = 1;
	int i = 0;
	while (1) {
		ret *= scanf_s("%d", &arr[i++]);
		if (ret == 0) {
			clear_input();
			break;
		}
		else if (i == size) {
			break;
		}
	}
	if (ret) ret *= clear_input();
	return ret;
}

int get_rand(int num) {
	srand(unsigned int(time(NULL)));
	return rand() % num + 1;
}
