#include <iostream>

using namespace std;

class ListNode {
private:
	int value;
	ListNode *prev = NULL;
	ListNode *next = NULL;
public:
	ListNode(int setVal) {
		value = setVal;
	}
	void setPrev(ListNode *toSet) {
		prev = toSet;
	}
	void setNext(ListNode *toSet) {
		next = toSet;
	}
	ListNode* getPrev() {
		return prev;
	}
	ListNode* getNext() {
		return next;
	}
	int getValue() {
		return value;
	}
	void setValue(int setVal) {
		value = setVal;
	}
};

class LinkedList {
private:
	ListNode *head = NULL;
	ListNode *tail = NULL;
	int size;
public:
	LinkedList() {
		size = 0;
	}
	void addNode(ListNode *toAdd) {
		if (size == 0) {
			head = toAdd;
			tail = toAdd;
			head->setNext(tail);
			tail->setPrev(head);
		}
		else {
			tail->setNext(toAdd);
			toAdd->setPrev(tail);
			tail = toAdd;
		}
		size += 1;
	}
	int getSize() {
		return size;
	}
	void print() {
		ListNode *temp = head;
		for (int i = 0; i < size; i++) {
			cout << temp->getValue() << '\t';
			temp = temp->getNext();
		}
		cout << endl;
	}
	void replaceNodeValue(int n, int val) {
		ListNode *temp = head;
		for (int i = 0; i < n; i++) {
			temp = temp->getNext();
		}
		if (temp != NULL) {
			temp->setValue(val);
		}
	}
	int operator [](int n) {
		ListNode *temp = head;
		for (int i = 0; i < n; i++) {
			temp = temp->getNext();
		}
		if (temp != NULL) {
			return temp->getValue();
		}
		return NULL;
	}
};

void merge(LinkedList toSort, int l, int m, int r);

int min(int x, int y) {
	return (x<y) ? x : y; 
}

void mergeSort(LinkedList toSort, int n) {
	cout << "Called on \t";
	toSort.print();
	cout << "With size " << n << endl;
	int curr_size, left_start;
	for (curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size)
	{
		for (left_start = 0; left_start<n - 1; left_start += 2 * curr_size)
		{
			int mid = left_start + curr_size - 1;
			int right_end = min(left_start + 2 * curr_size - 1, n - 1);
			cout << "\tHalves: LS[" << left_start << "]\tMid[" << mid << "]\tRE[" << right_end << "]" << endl;
			merge(toSort, left_start, mid, right_end);
		}
	}
}

void merge(LinkedList toSort, int l, int m, int r) {
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;
	cout << "\t\tLeft Side: " << n1 << " elements from " << l << " to " << l + n1 << endl;
	cout << "\t\tRight Side: " << n2 << " elements from " << m+1 << " to " << m + 1 + n2 << endl;
	LinkedList L;
	LinkedList R;

	cout << "Left  values: ";
	for (i = 0; i < n1; i++) {
		int toSetVal = toSort[l + i];
		cout << toSetVal <<  " ";
		ListNode *temp = new ListNode(toSetVal);
		L.addNode(temp);
	}
	cout << endl;
	L.print();
	cout << "Right  values: ";
	for (j = 0; j < n2; j++) {
		int toSetVal = toSort[m + 1 + j];
		cout << toSetVal << " ";
		ListNode *temp = new ListNode(toSetVal);
		R.addNode(temp);
	}
	cout << endl;
	R.print();
	
	i = 0;
	j = 0;
	k = l;

	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			toSort.replaceNodeValue(k, L[i]);
			i++;
		}
		else {
			toSort.replaceNodeValue(k, R[j]);
			j++;
		}
		k++;
	}

	while (i < n1) {
		toSort.replaceNodeValue(k, L[i]);
		i++;
		k++;
	}
	while (j < n2) {
		toSort.replaceNodeValue(k, R[j]);
		j++;
		k++;
	}
}

int main() {
	LinkedList myList;
	for (int i = 5; i > 0; i--) {
		ListNode *temp = new ListNode(i);
		myList.addNode(temp);
	}
	myList.print();
	mergeSort(myList, myList.getSize());
	cout << "\nSorted List\n";
	myList.print();
	return 0;
}