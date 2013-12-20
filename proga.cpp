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

void sort(Queue *stock, int len) {
	Queue q;

}

int main(){
	int i,n=200;
	Queue queue;
	for (int i = 0; i < 10; ++i)
	{
		queue.push( rand()%10 );
	}
	cout << queue;
	cout << queue.getn(0).data;
	cout << queue.getn(1).data;
	cout << queue.getn(2).data;
	cout << queue.getn(3).data;
	cout << queue.getn(4).data;
	// cout << queue.getn(5).data;
	// sort(&queue, queue.cnt);
	// print__( 10, &queue.data[0] );
	return 0;
};