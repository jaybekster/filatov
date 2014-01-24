#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <assert.h>
#include <ctime>
#include <sys/time.h>

using namespace std;

class Node {
	int data;
	Node *next;
	public:
	Node() {}
	Node(int arg1) { //+1
		data = arg1; //+1
	}
	int getData() { //0
		return data;
	}
	void setNext(Node* node) {
		next = node; //+1
		return;
	}
	void setData(int new_data) { //+1
		data = new_data; //+1;
		return;
	}
	Node* getNext() { //+1
		return next; //+1;
	}
	~Node() {}
};

class Queque {
	Node* head; // голова односвязного списка
	Node* tail; // хвост односвязного списка
	public: 
	Queque() {
		head = tail = NULL; //+2
	};
	bool is_empty() const {
		return head == NULL; //+1
	}; 
	Queque& push(const int data) { // добавить элемент в конец очереди //+6
		Node* node = new Node(data); //+2
		if (!head) { +1;
			head = tail = node;
		} else {
			tail->setNext(node); //+2;
			tail = node; //+1;
		}
		return *this; //+1
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
	Node* getFirst() { //+1
		return head; //+1;
	}
	Node* getLast() {
		return tail;
	}
	int getFirstData() {
		return head->getData();
	}
	int getLastData() { //+2
		return tail->getData(); //+2
	}
	Queque& setFirstData(const int data) {
		head->setData(data);
		return *this;
	}
	Queque& setLastData(const int data) { //+3
		tail->setData(data); //+2
		return *this; //+1
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
	Queque& clear() { //+3
		head = tail = NULL; //+2;
		return *this; //+1;
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
	assert( !original->is_empty() ); //+2
	Node *node = original->getFirst();  //+3
	int max = node->getData(); //+3
	while ( node->getNext() ) { //sum(i=0; n-1) +2
		if (node->getData()>max) max = node->getData(); //+6
		node = node->getNext(); //+3
	}
	if (node->getData()>max) max = node->getData(); //+6
	for (int i=0; i<=max; i+=1) { //+1 //sum(i=1,  max+1) +3
		node = original->getFirst(); //+3
		helpful.push(0); //+7
		while (node->getNext() ) { //sum(0, n-1) +2
			if (node->getData()==i) { //+3
				helpful.setLastData( helpful.getLastData()+1 ); //+4 +4 = +8
			}
			node = node->getNext(); //+3
		}
		if (node->getData()==i) { //+3
			helpful.setLastData( helpful.getLastData()+1 ); //+2 +2 = +8
		}
	}
	original->clear(); //+4
	node = helpful.getFirst(); //+3
	int k = -1; // счётчик //+1;
	while (node->getNext()) { //sum(0, max-1) +2
		k+=1; //+2
		if (node->getData()==0) { //+3
			node = node->getNext(); //+3
			continue;
		}
		for (int i=1; i<=node->getData(); i+=1) { //+1 //sum(i=1, i=n) +4
			original->push(k); //+6
		}
		node = node->getNext(); //+3
	}
	k+=1; //+1
	for (int i=1; i<=node->getData(); i+=1) { //+1 //sum(i=1, i=n) +4
		original->push(k); //+6;
	}
	return *original; //+1
}

int main() {
	srand (time(NULL));
	Queque queque;
	for (int i = 0; i < 200; ++i) {
		queque.push( rand()%200 );
	}
	// cout << "Original stack is: " << queque << endl;
	
	int nop = 0;

	struct timeval start, end;
    long mtime, seconds, useconds;    
    gettimeofday(&start, NULL);
	
	// queque = sort(&queque);

    sort(&queque);

    gettimeofday(&end, NULL);
    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;
    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
    printf("Elapsed time: %ld milliseconds\n", mtime);
    // cout << queque << endl;
	return 0;
}	