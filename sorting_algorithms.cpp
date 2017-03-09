#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;
ofstream file;
int COMPARISON_COUNT, SWAP_COUNT;

void swapElement(int *_array, int _currentPos, int _newPos) {
	int _storedValue = _array[_newPos];	//Saves value of the new position
	_array[_newPos] = _array[_currentPos];	//Put value into new position
	_array[_currentPos] = _storedValue;	//Puts saved value into old position
}

void straightInsertionSort(int *_array, int _sizeOfArray) {
	int _currentPointer=0, _comparePointer;
	for (int follow = 1; follow < _sizeOfArray; follow++) {
		COMPARISON_COUNT++;
		if (_array[follow] < _array[follow - 1]) { 
			SWAP_COUNT++;
			swapElement(_array, follow, follow - 1);
			_currentPointer = follow - 1; 
			while (_currentPointer > 0) { 
				COMPARISON_COUNT += 2;
				if (_array[_currentPointer] < _array[_currentPointer - 1]) {
					SWAP_COUNT++;
					swapElement(_array, _currentPointer, _currentPointer - 1);
					_currentPointer--;
				}
				else {
					_currentPointer = 0;
				}
			}
			
		}		
	}
}

void merge(int *_array, int _left, int _middle, int _right) {

	int _leftSubArraySize = _middle - _left + 1, _rightSubArraySize = _right - _middle;
	int *_leftSubArray, *_rightSubArray;
	_leftSubArray = new int[_leftSubArraySize];
	_rightSubArray = new int[_rightSubArraySize];

	for (int i = 0; i < _leftSubArraySize; i++) {
		_leftSubArray[i] = _array[_left + i];
	}
	for (int j = 0; j < _rightSubArraySize; j++) {
		_rightSubArray[j] = _array[_middle + 1 + j];
	}

	int _leftCursor=0, _rightCursor=0, _mergedCursor=_left;
	while (_leftCursor < _leftSubArraySize && _rightCursor < _rightSubArraySize) {
		COMPARISON_COUNT += 2;
		if (_leftSubArray[_leftCursor] < _rightSubArray[_rightCursor]) {
			_array[_mergedCursor] = _leftSubArray[_leftCursor];
			_leftCursor++;
			SWAP_COUNT++;
		}
		else {
			_array[_mergedCursor] = _rightSubArray[_rightCursor];
			_rightCursor++;
			SWAP_COUNT++;
		}
		_mergedCursor++;
	}
	while (_leftCursor < _leftSubArraySize)	{
		COMPARISON_COUNT++;
		_array[_mergedCursor] = _leftSubArray[_leftCursor];
		_leftCursor++;
		_mergedCursor++;
	}
	while (_rightCursor < _rightSubArraySize) {
		COMPARISON_COUNT++;
		_array[_mergedCursor] = _rightSubArray[_rightCursor];
		_rightCursor++;
		_mergedCursor++;
	}


}

void mergeSort(int *_array, int _left, int _right, bool withIndexed = false) {
	COMPARISON_COUNT++;
	if (_left < _right) {
		int _middle = (_left + (_right - 1)) / 2;
		COMPARISON_COUNT++;
		if ((_right - _left) < 40 && withIndexed) {
			straightInsertionSort(_array, _right + 1);
		}
		else {
			mergeSort(_array, _left, _middle, withIndexed);
			mergeSort(_array, _middle + 1, _right, withIndexed);
		}
		merge(_array, _left, _middle, _right);
	}
}

void quickSort(int *_array, int left, int right, bool withInsertion = false) {
	COMPARISON_COUNT++;
	if (right - left <= 4 && withInsertion) {
		straightInsertionSort(_array, right+1);
	}
	else {
		int i = left, j = right;
		int tmp;
		int pivot = _array[(left + right) / 2];
		while (i <= j) {
			while (_array[i] < pivot) { 
				i++; 
				COMPARISON_COUNT++;
			}
			while (_array[j] > pivot) { 
				j--;
				COMPARISON_COUNT++;
			}
			if (i <= j) {
				tmp = _array[i];
				_array[i] = _array[j];
				_array[j] = tmp;
				i++;
				j--;
				SWAP_COUNT++;
			}
			COMPARISON_COUNT++;
		}
		COMPARISON_COUNT += 2;
		if (left < j) quickSort(_array, left, j, withInsertion);
		if (i < right) quickSort(_array, i, right, withInsertion);
	}
}

void heapify(int *_array, int n, int i) {
	int largest = i;  
	int l = 2 * i + 1; 
	int r = 2 * i + 2; 
	COMPARISON_COUNT += 3;
	if (l < n && _array[l] > _array[largest]) largest = l;
	if (r < n && _array[r] > _array[largest]) largest = r;
	if (largest != i) {
		SWAP_COUNT++;
		swap(_array[i], _array[largest]);
		heapify(_array, n, largest);
	}
}
void heapSort(int *_array, int n) {
	for (int i = n / 2 - 1; i >= 0; i--) heapify(_array, n, i);
	for (int i = n - 1; i >= 0; i--) {
		SWAP_COUNT++;
		swap(_array[0], _array[i]);
		heapify(_array, i, 0);
	}
}

void cycle(int exp) {
	int _arraySize, _sizeExp, *_searchThroughArray, *_1to_N, *_N_to1;

	_sizeExp = exp;
	_arraySize = pow(10, _sizeExp);

	//Initializing Arrays
	_searchThroughArray = new int[_arraySize]; //Array of Random Integers
	_1to_N = new int[_arraySize];	//Ascending array from 1 to n
	_N_to1 = new int[_arraySize]; //Descending array from n to 1

	// STRAIGHT INSERTION SORT ============================================
	cout << "\n\nSTRAIGHT INSERTION SORT ============================================\n";
	file << "\n\nSTRAIGHT INSERTION SORT ============================================\n";

	for (int i = 0, j = _arraySize; i < _arraySize; i++, j--) {
		_searchThroughArray[i] = rand() % 9 + 1 * rand() + rand();
		_1to_N[i] = i + 1;
		_N_to1[i] = j;
	}

	COMPARISON_COUNT = 0;
	SWAP_COUNT = 0;
	straightInsertionSort(_searchThroughArray, _arraySize);

	file << "\n::::: RANDOM :::::\n"
		<< "Comparisons made = " << COMPARISON_COUNT
		<< "\nSwaps made = " << SWAP_COUNT;

	COMPARISON_COUNT = 0;
	SWAP_COUNT = 0;
	straightInsertionSort(_1to_N, _arraySize);

	file << "\n::::: 1 TO N :::::\n"
		<< "Comparisons made = " << COMPARISON_COUNT
		<< "\nSwaps made = " << SWAP_COUNT;

	COMPARISON_COUNT = 0;
	SWAP_COUNT = 0;
	straightInsertionSort(_N_to1, _arraySize);

	file << "\n::::: N TO 1 :::::\n"
		<< "Comparisons made = " << COMPARISON_COUNT
		<< "\nSwaps made = " << SWAP_COUNT;

	// MERGE SORT ==========================================================
	cout << "\n\nMERGE SORT ==========================================================\n";

	file << "\n\nMERGE SORT ==========================================================\n";

	for (int i = 0, j = _arraySize; i < _arraySize; i++, j--) {
		_searchThroughArray[i] = rand() % 9 + 1 * rand() + rand();
		_1to_N[i] = i + 1;
		_N_to1[i] = j;
	}

	COMPARISON_COUNT = 0;
	SWAP_COUNT = 0;
	mergeSort(_searchThroughArray, 0, _arraySize - 1);

	file << "\n::::: RANDOM :::::\n"
		<< "Comparisons made = " << COMPARISON_COUNT
		<< "\nSwaps made = " << SWAP_COUNT;

	COMPARISON_COUNT = 0;
	SWAP_COUNT = 0;
	mergeSort(_1to_N, 0, _arraySize - 1);

	file << "\n::::: 1 TO N :::::\n"
		<< "Comparisons made = " << COMPARISON_COUNT
		<< "\nSwaps made = " << SWAP_COUNT;

	COMPARISON_COUNT = 0;
	SWAP_COUNT = 0;
	mergeSort(_N_to1, 0, _arraySize - 1);

	file << "\n::::: N TO 1 :::::\n"
		<< "Comparisons made = " << COMPARISON_COUNT
		<< "\nSwaps made = " << SWAP_COUNT;

	// MERGE SORT WITH INSERTION SORT ======================================
	cout << "\n\nMERGE SORT WITH INSERTION SORT ======================================\n";

	file << "\n\nMERGE SORT WITH INSERTION SORT ======================================\n";

	for (int i = 0, j = _arraySize; i < _arraySize; i++, j--) {
		_searchThroughArray[i] = rand() % 9 + 1 * rand() + rand();
		_1to_N[i] = i + 1;
		_N_to1[i] = j;
	}

	COMPARISON_COUNT = 0;
	SWAP_COUNT = 0;
	mergeSort(_searchThroughArray, 0, _arraySize - 1, true);

	file << "\n::::: RANDOM :::::\n"
		<< "Comparisons made = " << COMPARISON_COUNT
		<< "\nSwaps made = " << SWAP_COUNT;

	COMPARISON_COUNT = 0;
	SWAP_COUNT = 0;
	mergeSort(_1to_N, 0, _arraySize - 1, true);

	file << "\n::::: 1 TO N :::::\n"
		<< "Comparisons made = " << COMPARISON_COUNT
		<< "\nSwaps made = " << SWAP_COUNT;

	COMPARISON_COUNT = 0;
	SWAP_COUNT = 0;
	mergeSort(_N_to1, 0, _arraySize - 1, true);

	file << "\n::::: N TO 1 :::::\n"
		<< "Comparisons made = " << COMPARISON_COUNT
		<< "\nSwaps made = " << SWAP_COUNT;

	// QUICK SORT ==========================================================
	cout << "\n\nQUICK SORT ==========================================================\n";

	file << "\n\nQUICK SORT ==========================================================\n";

	for (int i = 0, j = _arraySize; i < _arraySize; i++, j--) {
		_searchThroughArray[i] = rand() % 9 + 1 * rand() + rand();
		_1to_N[i] = i + 1;
		_N_to1[i] = j;
	}

	COMPARISON_COUNT = 0;
	SWAP_COUNT = 0;
	quickSort(_searchThroughArray, 0, _arraySize - 1);

	file << "\n::::: RANDOM :::::\n"
		<< "Comparisons made = " << COMPARISON_COUNT
		<< "\nSwaps made = " << SWAP_COUNT;

	COMPARISON_COUNT = 0;
	SWAP_COUNT = 0;
	quickSort(_1to_N, 0, _arraySize - 1);

	file << "\n::::: 1 TO N :::::\n"
		<< "Comparisons made = " << COMPARISON_COUNT
		<< "\nSwaps made = " << SWAP_COUNT;

	COMPARISON_COUNT = 0;
	SWAP_COUNT = 0;
	quickSort(_N_to1, 0, _arraySize - 1);

	file << "\n::::: N TO 1 :::::\n"
		<< "Comparisons made = " << COMPARISON_COUNT
		<< "\nSwaps made = " << SWAP_COUNT;

	// QUICK SORT WITH INSERTION SORT ======================================
	cout << "\n\nQUICK SORT WITH INSERTION SORT ======================================\n";

	file << "\n\nQUICK SORT WITH INSERTION SORT ======================================\n";

	for (int i = 0, j = _arraySize; i < _arraySize; i++, j--) {
		_searchThroughArray[i] = rand() % 9 + 1 * rand() + rand();
		_1to_N[i] = i + 1;
		_N_to1[i] = j;
	}

	COMPARISON_COUNT = 0;
	SWAP_COUNT = 0;
	quickSort(_searchThroughArray, 0, _arraySize - 1, true);

	file << "\n::::: RANDOM :::::\n"
		<< "Comparisons made = " << COMPARISON_COUNT
		<< "\nSwaps made = " << SWAP_COUNT;

	COMPARISON_COUNT = 0;
	SWAP_COUNT = 0;
	quickSort(_1to_N, 0, _arraySize - 1, true);

	file << "\n::::: 1 TO N :::::\n"
		<< "Comparisons made = " << COMPARISON_COUNT
		<< "\nSwaps made = " << SWAP_COUNT;

	COMPARISON_COUNT = 0;
	SWAP_COUNT = 0;
	quickSort(_N_to1, 0, _arraySize - 1, true);

	file << "\n::::: N TO 1 :::::\n"
		<< "Comparisons made = " << COMPARISON_COUNT
		<< "\nSwaps made = " << SWAP_COUNT;

	// HEAP SORT ===========================================================
	cout << "\n\nHEAP SORT ===========================================================\n";

	file << "\n\nHEAP SORT ===========================================================\n";

	for (int i = 0, j = _arraySize; i < _arraySize; i++, j--) {
		_searchThroughArray[i] = rand() % 9 + 1 * rand() + rand();
		_1to_N[i] = i + 1;
		_N_to1[i] = j;
	}

	COMPARISON_COUNT = 0;
	SWAP_COUNT = 0;
	heapSort(_searchThroughArray, _arraySize);

	file << "\n::::: RANDOM :::::\n"
		<< "Comparisons made = " << COMPARISON_COUNT
		<< "\nSwaps made = " << SWAP_COUNT;

	COMPARISON_COUNT = 0;
	SWAP_COUNT = 0;
	heapSort(_1to_N, _arraySize);

	file << "\n::::: 1 TO N :::::\n"
		<< "Comparisons made = " << COMPARISON_COUNT
		<< "\nSwaps made = " << SWAP_COUNT;

	COMPARISON_COUNT = 0;
	SWAP_COUNT = 0;
	heapSort(_N_to1, _arraySize);

	file << "\n::::: N TO 1 :::::\n"
		<< "Comparisons made = " << COMPARISON_COUNT
		<< "\nSwaps made = " << SWAP_COUNT;
}

int main() {
	srand(time(NULL));
	int _sizes[3] = {2,4,6};

	for (int i = 0; i < 1; i++) {
		string _fileName = to_string(_sizes[i]) + ".txt";
		file.open(_fileName);
		for (int j = 0; j < 1; j++) {
			file << "\n=========================================================================\n RUN " 
				<< j << "\n=========================================================================\n";
			cout << "\nRunning:\n\tSize : " << i << "\n\tRun : " << j << endl;
			cycle(_sizes[i]);
		}
		file.close();
	}

	return 0;
}