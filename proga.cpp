#include <stdio.h>
#include <iostream>
#include <cstdlib>

using namespace std;

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
		if (q.is_empty()) {
			cout << "NULL";
			return o;
		}
		Node* node = q.head;
		while (node->next) {
			cout << node->data << " ";
			node = node->next;
		}
		cout << node->data;
		return o;
	}
};

Queue sort(Queue * original) {
	static Queue helpful;
	// cout << *original;
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
	original->clear();
	node = helpful.head;
	// cout << helpful << endl;
	int k = 0; // счётчик;
	while (node->next) {
		if (node->data==0) {
			k+=1;
			node = node->next;
			continue;
		}
		for (int i=1; i<=node->data; i+=1) {
			original->push(k);
		}
		k+=1;
		node = node->next;
	}
	if (node->data!=0) {
		for (int i=1; i<=node->data; i+=1) {
			original->push(k);
		}
	}
	return *original;
}

int main(){
	srand (time(NULL));
	Queue queue;
	for (int i = 0; i < 5; ++i) {
		queue.push( rand()%10 );
	}
	cout << "Original stack is: " << queue << endl;
	queue = sort(&queue);
	cout << "Sorted stack is: " << queue << endl;
	return 0;
};