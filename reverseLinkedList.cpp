#include<iostream>
using namespace std;

struct node {
	int num;
	node* next;
};

node* createList(int);
void reverse(node*);
void printList(node*);

int main() {
	cout << "input the length of the list" << endl;
	int size;
	cin >> size;
	
	node* head = createList(size);
	reverse(head);
	return 0;
}

node* createList(int N) {//默认N＞0
	node* head = new node;
	head->num = N;//头结点存放链表的长度
	head->next = NULL;
	
	node* p = head;
	for (int i = 0; i < N; i++) {
		node* q = new node;
		q->num = i + 1;

		p->next = q;
		if (i < N - 1) {
			p = q;
		} else {
			q->next = NULL;
		}
	}
	printList(head);
	return head;
}

void reverse(node* head) {
	node* p = NULL;
	node* q = head->next;
	while (q) {
		node* temp = q->next;
		q->next = p;
		p = q;
		q = temp;
	}
	head->next = p;
	printList(head);
}

void printList(node* head) {
	node* p = head;
	while (p->next) {
		cout << p->next->num << " ";
		p = p->next;
	}
	cout << endl;
}
