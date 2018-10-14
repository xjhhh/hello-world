#include<iostream>
#include<math.h>
using namespace std;

struct node {
	int num;
	node* left;
	node* right;
};

node* createList(int);
void execute(node*, int);

int main() {
	cout << "input M,N" << endl;
	int M, N;
	cin >> M >> N;
	
	node* head = createList(N);
	execute(head, M);
	return 0;
}

node* createList(int N) {//默认N＞0
	node* head = new node;
	head->num = N;//头结点存放链表的长度
	head->left = NULL;
	head->right = NULL;
	
	for (int i = 0; i < N; i++) {
		node* q = new node;
		q->num = i + 1;

		node* h = head->right;
		if (h) {
			q->left = h->left;
			h->left->right = q;

			q->right = h;
			h->left = q;
		} else {
			head->right = q;
			q->left = q;
			q->right = q;
		}
	}
	return head;
}

void execute(node* head, int M) {
	int N = head->num;
	node* p = head->right;

	int m = M;
	m = m%N;
	if (!m) {
		m = N;
	}

	if (m <= ceil((N + 1) / 2.0)) {
		while (m-- > 1) {
			p = p->right;
		}
	} else {
		m = (N + 2) - m;
		while (m-- > 1) {
			p = p->left;
		}
	}
	cout << p->num << endl;
	node* left = p->left;
	node* right = p->right;
	left->right = right;
	right->left = left;
	head->right = right;
	delete p;
	head->num--;
	if (head->num) {
		execute(head, M);
	}
}
