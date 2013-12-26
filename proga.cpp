#include <stdio.h>
#include <iostream>
#include <cstdlib>

using namespace std;

void print__(int a, int *arr) {
	for (int i = 0; i < a; ++i)
	{
		cout << *(arr+i) << " ";
	};
}
struct Node
{
	int data;
	Node* next;
};
struct Queue {
	int size;
	Node* head; // голова односвязного списка
	Node* tail; // хвост односвязного списка
public: 
	int cnt; // длина очереди (кол-во элементов в ней)
	Queue() {
		cnt = 0;
		cout << "initialized" << endl;
		head = tail = NULL;
	};
	bool is_empty() {
		return head == NULL;
	}; 
	Queue& del() { // удалить элемент из начала очереди
		if ( is_empty() ) {
			cout << "Stack is empty";
		};
		Node* tmp = head->next; // запоминаем указатель на следующий элемент очереди
		delete head; // удаляем элемент... и переводим указатель на следующий элемент
		if(!tmp) {
			head = tail = NULL;
		} else {
			head = tmp;
		}
		cnt--;
		return *this;
	};
	Queue& clear() {
		while(!is_empty()) del();
		return *this;
	};
	Queue& push(const int& data) { // добавить элемент в конец очереди
		Node* node = new Node();
		node->data = data;
		node->next = NULL;
		if (!head) {
			head = tail = node;
		} else {
			tail->next = node;
			tail = node;
		}
		cnt+=1;
	};
	int pop() { // извлечь элемент из начала очереди
		if ( !is_empty() ) {
			int data = head->data;
			del();
			return data;
		} else {
			cout << "Стек пустой" << endl;
			exit;
		}
	};
	int& get() { //получить элемент из начала очереди
		if ( is_empty() ) {
			cout << "Стек пустой" << endl;
			exit;	
		} else {
			return head->data;
		}
	}
	int& getLast() { //получить элемент из конца очереди
		if ( is_empty() ) {
			cout << "Стек пустой" << endl;
			exit;	
		} else {
			return tail->data;
		}	
	}
	Queue& set(int& data) {
		if ( is_empty() ) {
			cout << "Стек пустой" << endl;
			exit;	
		} else {
			head->data = data;
			return *this;
		}
	};
	Node& getn(int ind) {
		Node *node = head;
		int i = 0;
		if (ind==0) return *head;
		while (node->next) {
			node = node->next;
			i+=1;
			if (i==ind) return *node;
		}
	}
	friend ostream& operator<< ( ostream& o, Queue& q) {
		Node* node = q.head;
		while (node->next) {
			cout << node->data << " ";
			node = node->next;
		}
		cout << node->data << endl;
		return o;
	}
};

Queue sort(Queue *original) {
	static Queue helpful;
	cout << *original;
	if (original->is_empty()) {
		cout << "The stack is empty\n";
		exit(0);
	}
	Node *node = original->head;
	int max = node->data;
	while (node->next) {
		if (node->data>max) max = node->data;
		node = node->next;
	}
	for (int i=0; i<=max; i+=1) {
		node = original->head;
		helpful.push(0);
		while (node->next) {
			if (node->data==i) {
				helpful.getLast()+=1;
			}
			node = node->next;
		}
		if (node->data==i) {
			helpful.getLast()+=1;
		}
	}
	cout << helpful << endl;
	return helpful;
}

int main(){
	int i,n=200;
	Queue queue;
	Queue queue2;
	for (int i = 0; i < 10; ++i) {
		queue.push( rand()%10 );
	}
	queue.getn(2).data;
	queue2 = sort(&queue);
	return 0;
};