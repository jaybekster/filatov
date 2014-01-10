#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <assert.h>

using namespace std;

class Node {
	int data;
	Node *next;
public:
	Node() {}
	Node(int arg1) {
		data = arg1;
	}
	int getData() {
		return data;
	}
	void setNext(Node* node) {
		next = node;
		return;
	}
	void setData(int new_data) {
		data = new_data;
		return;
	}
	Node* getNext() {
		return next;
	}
	~Node() {}
};

class Queque {
	Node* head; // голова односвязного списка
	Node* tail; // хвост односвязного списка
public: 
	Queque() {
		head = tail = NULL;
	};
	bool is_empty() const {
		return head == NULL;
	}; 
	Queque& push(const int data) { // добавить элемент в конец очереди
		Node* node = new Node(data);
		if (!head) {
			head = tail = node;
		} else {
			tail->setNext(node);
			tail = node;
		}
		return *this;
	};
	Queque& pop(const int data) { // добавить элемент в неачало очереди
		Node* node = new Node(data);
		if (!head) {
			head = tail = node;
		} else {
			node->setNext(head);
			head = node;
		}
		return *this;
	};
	Node* getFirst() {
		return head;
	}
	Node* getLast() {
		return tail;
	}
	int getFirstData() {
		return head->getData();
	}
	int getLastData() {
		return tail->getData();
	}
	Queque& setFirstData(const int data) {
		head->setData(data);
		return *this;
	}
	Queque& setLastData(const int data) {
		tail->setData(data);
		return *this;
	}
	Node* getn(int ind) {
		Node* node = head;
		int i = 0;
		if (ind==0) return head;
		while (node->getNext()) {
			node = node->getNext();
			i+=1;
			if (i==ind) return node;
		}
		return NULL;
	}
	Queque& clear() {
		// while(!is_empty()) del();
		head = tail = NULL;
		return *this;
	};
	Queque& del() { // удалить элемент из начала очереди
		assert( !is_empty() );
		Node* tmp = head->getNext(); // запоминаем указатель на следующий элемент очереди
		delete head; // удаляем элемент... и переводим указатель на следующий элемент
		if(!tmp) {
			head = tail = NULL;
		} else {
			head = tmp;
		}
		return *this;
	};
	friend ostream& operator<< ( ostream& o, Queque& q) {
		if (q.is_empty()) {
			o << "NULL";
			return o;
		}
		Node* node = q.head;
		while (node->getNext()) {
			o << node->getData() << " ";
			node = node->getNext();
		}
		o << node->getData();
		return o;
	}
};

Queque sort(Queque* original) {
	Queque helpful;
	assert( !original->is_empty() );
	Node *node = original->getFirst();
	int max = node->getData();
	while ( node->getNext() ) {
		if (node->getData()>max) max = node->getData();
		node = node->getNext();
	}
	if (node->getData()>max) max = node->getData();
	for (int i=0; i<=max; i+=1) {
		node = original->getFirst();
		helpful.push(0);
		while (node->getNext()) {
			if (node->getData()==i) {
				helpful.setLastData( helpful.getLastData()+1 );
			}
			node = node->getNext();
		}
		if (node->getData()==i) {
			helpful.setLastData( helpful.getLastData()+1 );
		}
	}
	original->clear();
	node = helpful.getFirst();
	int k = -1; // счётчик;
	while (node->getNext()) {
		k+=1;
		if (node->getData()==0) {
			node = node->getNext();
			continue;
		}
		for (int i=1; i<=node->getData(); i+=1) {
			original->push(k);
		}
		node = node->getNext();
	}
	k+=1;
	for (int i=1; i<=node->getData(); i+=1) {
		original->push(k);
	}
	return *original;
}

int main() {
	srand (time(NULL));
	Queque queque;
	for (int i = 0; i < 10; ++i) {
		queque.push( rand()%10 );
	}
	cout << "Original stack is: " << queque << endl;
	queque = sort(&queque);
	cout << "Sorted stack is: " << queque << endl;
	return 0;
}