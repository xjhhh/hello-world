#include < stdio.h >
#include < stdlib.h >

#include "Tools.h"

int play(int x, int y);
void print_board(void);
void AI(void);
void AI0(int part, int & ret, int & index);
void cal_score(int arr[], int part);
int check_line(int, int, int, int);
int check_end(void);

int ai_lv;//电脑难度，1，2，3。从低到高
int odd;//先后手，0：先手，1：后手
int turn = 1;//回合数
int ** board;//棋盘
int size;//棋盘大小
int main(){
	printf("这是一个井字棋游戏。\n");
	// while(1){
	// 	printf("请输入棋盘的边长（输入0结束游戏）：\n");
	// 	int a[1];
	// 	if(!check_input(a,1)){
	// 		printf("非法输入！\n");
	// 	} else {
	// 		int size = a[0];
	size = 3;
	// 		if(size==0){
	// 			printf("游戏结束！\n");
	// 			break;
	// 		}else if(size<3){
	// 			printf("棋盘边长至少是3！\n");
	// 		}else{
	board = (int **)malloc(sizeof(int *)* size);//使用malloc申请二维数组
	for (int i = 0; i < size; i++) {
		board[i] = (int *)malloc(sizeof(int)* size);
	}
	while (1) {
		//确定电脑难度
		int a[1];
		while (1) {
			printf("请选择电脑难度\n1：低，2：中，3：高（输入0退出游戏）\n");
			if (!check_input(a, 1)) {
				printf("非法输入！\n");
			}
			else {
				ai_lv = a[0];
				if (ai_lv >= 0 && ai_lv <= 3) {
					break;
				}
				else {
					printf("您只能输入0、1、2、3中的一个！\n");
				}
			}
		}
		if (!ai_lv) break;
		//确定先后手
		while (1) {
			printf("请选择先后手\n0：先手，1：后手\n");
			if (!check_input(a, 1)) {
				printf("非法输入！\n");
			}
			else {
				odd = a[0];
				if (odd == 0 || odd == 1) {
					break;
				}
				else {
					printf("您只能输入0或1！\n");
				}
			}
		}

		printf("游戏开始！\n");
		play(0, 0);
		printf("\n");
		while (1) {
			bool one_step = false;
			if (turn % 2 ^ odd) {
				printf("请输入落子的行和列（输入0 0退出本局游戏）：\n");
				int xy[2];
				if (check_input(xy, 2) == 0) {
					printf("非法输入！\n");
				}
				else {
					int x = xy[0];
					int y = xy[1];
					if (!x && !y) {
						printf("退出本局游戏！\n");
						break;
					}
					else {
						if (play(x, y)) {
							one_step = true;
							printf("--------\n");
						}
					}
				}
			}
			else {
				AI();
				one_step = true;
			}
			if (one_step) {
				int end = check_end();
				if (end) {
					if (end == 1) {
						if (turn % 2 ^ odd) {
							printf("玩家胜利！\n");
						}
						else {
							printf("电脑胜利！\n");
						}
					}
					else if (end == -1) {
						printf("平局\n");
					}
					turn = 1;
					break;
				}
				turn++;
			}
		}
	}
	free(board);
	// 		}
	// 	}
	// }
	return 0;
}

int play(int x, int y){
	if (!x && !y) {
		int i = 0, j = 0;
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
				board[i][j] = 0;
			}
		}
		printf("生成棋局...\n");
		print_board();
	}
	else if (x < 1 || x > size || y < 1 || y > size) {
		printf("落子失败，行（列）超出范围\n");
	}
	else {
		int cur = board[x - 1][y - 1];
		if (cur == 0) {
			board[x - 1][y - 1] = 2 * (turn % 2) - 1;
			if (turn % 2 ^ odd) {//玩家回合
				printf("落子成功\n");
			}
			print_board();
			return 1;
		}
		else {
			printf("落子失败，目标位置已有棋子\n");
		}
	}
	return 0;
}

void print_board(){
	int i = 0, j = 0;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			int chess = board[i][j];
			switch (chess) {
			case 0:
				printf("%c ", 'o');
				break;
			default:
				if (chess == 1 && odd == 0 || chess == -1 && odd == 1) {
					printf("%c ", 1);
				}
				else {
					printf("%c ", 'x');
				}
				break;
			}
		}
		printf("\n");
	}
}

void AI0(int part, int & max, int & index){
	int i, j, num = 0, random;
	int * score_tab = (int *)malloc(sizeof(int)* size * size);
	int * opp_tab = (int *)malloc(sizeof(int)* size * size);
	cal_score(score_tab, part);//自己的分数图
	cal_score(opp_tab, -part);//对方的分数图

	max = -1;
	for (i = 0; i < size * size; i++) {//确定最高分，以及最高分的个数
		int my_score = score_tab[i];
		if (my_score == 5) {//游戏结束
			max = 5;
			index = i;
			return;
		}
		int cur_max = MAX(my_score, opp_tab[i]);
		if (cur_max > max) {
			max = cur_max;
			j = i;
			num = 1;
		}
		else if (cur_max == max) {
			num++;
		}
	}
	random = get_rand(num);
	for (i = 0; i < size * size; i++) {//随机一个最大值的位置，落子
		int cur_max = MAX(score_tab[i], opp_tab[i]);
		if (cur_max == max) {
			if (random == 1) {
				index = i;
				return;
			}
			else {
				random--;
			}
		}
	}
}

void AI(void){
	int i, j;
	int max = -1, num = 0, random;//最高分，最高分的个数，随机取的那个序数
	int part = 2 * (turn % 2) - 1;//我是哪一方（1：先手方，-1：后手方）
	switch (ai_lv) {
	case 1:
		num = size * size - turn + 1;
		random = get_rand(num);
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
				if (board[i][j] == 0) {
					if (random == 1) {
						play(i + 1, j + 1);
						return;
					}
					else {
						random--;
					}
				}
			}
		}
		break;
	case 2:
		AI0(part, max, i);
		play(i / size + 1, i % size + 1);
		break;
	case 3:
		int * score_tab = (int *)malloc(sizeof(int)* size * size);
		cal_score(score_tab, part);//自己的分数图
		int * cur_opp = (int *)malloc(sizeof(int)* size * size);
		cal_score(cur_opp, -part);//对手的分数图

		int * tab = (int *)malloc(sizeof(int)* size * size);//综合分数图
		for (i = 0; i < size * size; i++) {
			if (board[i / 3][i % 3]) {
				tab[i] = -1;
			}
			else {
				tab[i] = 0;
			}
		}

		for (i = 0; i < size * size; i++) {
			int my_score = score_tab[i];//这一步我的分数
			if (my_score == 5) {//游戏结束
				play(i / size + 1, i % size + 1);
				return;
			}
			else if (my_score == -1) {
				continue;
			}
			my_score = MAX(score_tab[i], cur_opp[i]);

			int temp = board[i / size][i % size];
			board[i / size][i % size] = part;

			int opp_score = -1;//下一步对手的最高分
			AI0(-part, opp_score, j);

			tab[i] = my_score - opp_score;
			if (tab[i] > max) {
				max = tab[i];
				num = 1;
			}
			else if (tab[i] == max) {
				num++;
			}

			board[i / size][i % size] = temp;
		}

		random = get_rand(num);
		for (i = 0; i < size * size; i++) {
			if (tab[i] == max) {
				if (random == 1) {
					play(i / size + 1, i % size + 1);
					return;
				}
				else {
					random--;
				}
			}
		}
		break;
	}
}

void cal_score(int arr[], int part){//-1：已有落子；0-4：空的位置
	int i, j, bonus;
	for (i = 0; i < size * size; i++) {
		if (board[i / 3][i % 3]) {
			arr[i] = -1;
		}
		else {
			arr[i] = 0;
		}
	}
	for (i = 0; i < size; i++) {
		bonus = check_line(board[i][0], board[i][1], board[i][2], part);
		if (bonus >= 0) {//横向
			for (j = 0; j < size; j++) {
				if (!board[i][j]) {
					arr[i * size + j] += bonus + (bonus == 2 ? 3 : 1);
				}
			}
		}
		bonus = check_line(board[0][i], board[1][i], board[2][i], part);
		if (bonus >= 0) {//纵向
			for (j = 0; j < size; j++) {
				if (!board[j][i]) {
					arr[j * size + i] += bonus + (bonus == 2 ? 3 : 1);
				}
			}
		}
	}
	bonus = check_line(board[0][2], board[1][1], board[2][0], part);
	if (bonus >= 0) {//正对角线
		if (!board[0][2]) arr[2] += bonus + (bonus == 2 ? 3 : 1);
		if (!board[1][1]) arr[4] += bonus + (bonus == 2 ? 3 : 1);
		if (!board[2][0]) arr[6] += bonus + (bonus == 2 ? 3 : 1);
	}
	bonus = check_line(board[0][0], board[1][1], board[2][2], part);
	if (bonus >= 0) {//斜对角线
		if (!board[0][0]) arr[0] += bonus + (bonus == 2 ? 3 : 1);
		if (!board[1][1]) arr[4] += bonus + (bonus == 2 ? 3 : 1);
		if (!board[2][2]) arr[8] += bonus + (bonus == 2 ? 3 : 1);
	}
}

int check_line(int one, int two, int three, int part){
	int bonus = 0;
	bool line = true;
	if (one) {
		if (one != part) {
			line = false;
		}
		else {
			bonus++;
		}
	}
	if (two) {
		if (two != part) {
			line = false;
		}
		else {
			bonus++;
		}
	}
	if (three) {
		if (three != part) {
			line = false;
		}
		else {
			bonus++;
		}
	}
	if (line) {
		return bonus;
	}
	else {
		return -1;
	}
}

int check_end(void){
	int i, j;
	for (i = 0; i < size; i++) {
		if (board[i][0] && board[i][0] == board[i][1] && board[i][0] == board[i][2]) {//横向
			return 1;
		}
		if (board[0][i] && board[0][i] == board[1][i] && board[0][i] == board[2][i]) {//纵向
			return 1;
		}
	}
	if (board[0][2] && board[0][2] == board[1][1] && board[0][2] == board[2][0]) {//正对角线
		return 1;
	}
	if (board[0][0] && board[0][0] == board[1][1] && board[0][0] == board[2][2]) {//斜对角线
		return 1;
	}
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (board[i][j] == 0) {
				return 0;
			}
		}
	}
	return -1;//平局
}
