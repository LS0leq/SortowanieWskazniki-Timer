#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>   
#include <windows.h>
#include <fstream>
using namespace std;

//funkcje sortujace
// dziala, ale nie jest optymalna, poniewaz nie skraca zakresu sortowania z kazdym przebiegiem sortowania powinno sie zmniejszac zakres porowan,poniewaz ostatni element w kazdym przebiegu jest juz posortowany
template <typename T>
void bubblesort_for_for_index(T* arr, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				T temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

// dziala, uzywa wskaznikow, ale nie jest optymalna, poniewaz nie skraca zakresu sortowania, kazde porownanie i zamiana wykonywane sa na pelnym zakresie tablicy
template <typename T>
void bubblesort_for_for_with_pointers(T* arr, int n) {
	T* w1, * w2, temp;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - 1; j++) {
			w1 = arr + j;
			w2 = w1 + 1;
			if (*w2 < *w1) {
				temp = *w1;
				*w1 = *w2;
				*w2 = temp;
			}
		}
	}
}

// dziala, jest bardziej optymalna niz poprzednie, poniewaz uzywa  `sorted` do przerwania sortowania, gdy tablica jest juz posortowana, jednak nadal nie skraca zakresu sortowania po kazdym przebiegu
template <typename T>
void bubblesort_while_for(T* arr, int n) {
	bool sorting = true;
	while (sorting) {
		bool sorted = false;
		for (int j = 0; j < n - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				T temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				sorted = true;
			}
		}
		if (!sorted) {
			sorting = false;
		}
	}
}

// dziala, uzywa wskaznikow, jest bardziej optymalna niz poprzednie, poniewaz sprawdza `sorted` i przerywa sortowanie, gdy tablica jest juz posortowana, jednak nie skraca zakresu sortowania po kazdym przebiegu
template <typename T>
void bubblesort_with_while_with_pointers(T* arr, int n) {
	T* w1, * w2, temp;
	bool sorting = true;
	while (sorting) {
		bool sorted = false;
		for (int j = 0; j < n - 1; j++) {
			w1 = arr + j;
			w2 = w1 + 1;
			if (*w2 < *w1) {
				temp = *w1;
				*w1 = *w2;
				*w2 = temp;
				sorted = true;

			}
		}
		if (!sorted) {
			sorting = false;
		}
	}
}

//dziala, jest optymalna, poniewaz skraca zakres sortowania po kazdym przebiegu (elementy na koncu sa juz posortowane), a takze uzywa `sorted` do przerwania sortowania, jesli tablica jest juz posortowana
template <typename T>
void bubblesort_while_with_optimized_for(T* arr, int n) {
	int i = 0;
	bool sorting = true;
	while (sorting) {
		bool sorted = false;

		for (int j = 0; j < n - 1 - i; j++) {
			if (arr[j] > arr[j + 1]) {
				T temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				sorted = true;

			}
		}
		if (!sorted) {
			sorting = false;
		}
		i++;
	}
}

//dziala, uzywa wskaznikow, jest optymalna, poniewaz skraca zakres sortowania po kazdym przebiegu i uzywa `sorted` do przerwania sortowania, jesli tablica jest juz posortowana
template <typename T>
void bubblesort_while_optimized_for_with_pointers(T* arr, int n) {
	T* w1, * w2, temp;
	int i = 0;
	bool sorting = true;
	while (sorting) {
		bool sorted = false;
		for (int j = 0; j < n - 1 - i; j++) {
			w1 = arr + j;
			w2 = w1 + 1;
			if (*w2 > *w1) {
				temp = *w1;
				*w1 = *w2;
				*w2 = temp;
				sorted = true;

			}
		}
		if (!sorted) {
			sorting = false;
		}
		i++;
	}
}

//funkcja sprawdzajaca czy tablica jest posortowana
template <typename T>
bool checker(T* arr, int n) {
	bool checkBool = true;

	for (int i = 0; i < n - 1; i++) {
		if (arr[i] > arr[i + 1]) {
			checkBool = false;
			break;
		}
	}

	return checkBool;
}


//funkcja liczaca czas sortowania ZMIENIC INACZEJ
template <typename T>
double timer(void (*sortFunc)(T*, int), T* arr, int n) {
	LARGE_INTEGER start, end, frequency;

	//pobieram czestotliwosc z zegara
	QueryPerformanceFrequency(&frequency);

	//pobieram czas przed wykonaniem funkcji
	QueryPerformanceCounter(&start);

	//wywoluje funkcje ktora mierze
	sortFunc(arr, n);

	//pobieram czas po wykonaniu funkcji
	QueryPerformanceCounter(&end);

	//licze roznice czas
	long long elapsed = end.QuadPart - start.QuadPart;

	//zapisuje w jednostkach
	double elapsedInMicroseconds = (elapsed * 1000000.0) / frequency.QuadPart;
	double elapsedInMilliseconds = elapsedInMicroseconds / 1000.0;
	return elapsedInMilliseconds;
}

//funkcja pokazujaca wyniki
void results(double fastForFor, double fastWhileFor, double fastWhileOpt,double fastForForPoint, double fastWhileForPoint, double fastWhileOptPoint) {
	cout << endl;
	cout << "-------------------------------------------------------------------" << endl;
	cout << "| Sortowanie                                           | Czas (ms) |" << endl;
	cout << "-------------------------------------------------------------------" << endl;
	cout << "| Sortowanie for for                                   | " << fastForFor << "    |" << endl;
	cout << "| Sortowanie for for ze wskaznikiem                    | " << fastForForPoint << "    |" << endl;
	cout << "| Sortowanie while for                                 | " << fastWhileFor << "    |" << endl;
	cout << "| Sortowanie while for ze wskaznikiem                  | " << fastWhileForPoint << "    |" << endl;
	cout << "| Sortowanie while for zoptymalizowany                 | " << fastWhileOpt << "    |" << endl;
	cout << "| Sortowanie while for zoptymalizowany ze wskaznikiem  | " << fastWhileOptPoint << "    |" << endl;
	cout << "-------------------------------------------------------------------" << endl;
	if (fastForForPoint < fastWhileForPoint && fastForForPoint < fastWhileOptPoint && fastForForPoint < fastWhileFor && fastForForPoint < fastWhileOpt) {
		cout << "| Najszybsze sortowanie: for for ze wskaznikiem   |" << endl;
	}
	else if (fastWhileForPoint < fastForForPoint && fastWhileForPoint < fastWhileOptPoint && fastWhileForPoint < fastForFor && fastWhileForPoint < fastWhileOpt) {
		cout << "| Najszybsze sortowanie: while for ze wskaznikiem |" << endl;
	}
	else if (fastWhileOptPoint < fastForForPoint && fastWhileOptPoint < fastWhileForPoint && fastWhileOptPoint < fastForFor && fastWhileOptPoint < fastWhileFor) {
		cout << "| Najszybsze sortowanie: while for zoptymalizowany    |" << endl;
	}
	
	else if (fastForFor == fastForForPoint && fastForFor < fastWhileForPoint && fastForFor < fastWhileOptPoint && fastForFor < fastWhileFor) {
		cout << "| Najszybsze sortowanie: for for oraz for for ze wskaznikiem  |" << endl;
	}
	else if (fastWhileForPoint == fastWhileFor && fastWhileForPoint < fastForForPoint && fastWhileForPoint < fastWhileOptPoint && fastWhileForPoint < fastWhileOpt) {
		cout << "| Najszybsze sortowanie: while for oraz while for ze wskaznikiem |" << endl;
	}
	else if (fastWhileOptPoint == fastWhileOpt && fastWhileOptPoint < fastForForPoint && fastWhileOptPoint < fastWhileForPoint && fastWhileOptPoint < fastForFor) {
		cout << "| Najszybsze sortowanie: while for zoptymalizowany oraz while for zoptymalizowany ze wskaznikiem |" << endl;
	}
	else if (fastForForPoint == fastWhileForPoint && fastForForPoint < fastForFor && fastForForPoint < fastWhileOptPoint && fastForForPoint < fastWhileOpt) {
		cout << "| Najszybsze sortowanie: for for ze wskaznikiem oraz while for ze wskaznikiem |" << endl;
	}
	else if (fastForFor == fastWhileOptPoint && fastForFor < fastWhileForPoint && fastForFor < fastWhileOpt) {
		cout << "| Najszybsze sortowanie: for for oraz while for zoptymalizowany ze wskaznikiem |" << endl;
	}
	else if (fastWhileFor == fastWhileOptPoint && fastWhileFor < fastForForPoint && fastWhileFor < fastForFor) {
		cout << "| Najszybsze sortowanie: while for oraz while for zoptymalizowany ze wskaznikiem |" << endl;
	}
	else if (fastWhileOpt == fastForForPoint && fastWhileOpt < fastForFor && fastWhileOpt < fastWhileForPoint) {
		cout << "| Najszybsze sortowanie: while for zoptymalizowany oraz for for ze wskaznikiem |" << endl;
	}
	else {
		cout << "| Wszystkie sortowania maja taki sam czas     |" << endl;
	}
	cout << "-----------------------------------------------" << endl;


	ofstream outFile("results.txt", ios::trunc);
	if (outFile.is_open()) {
		outFile << "-----------------------------------------------\n";
		outFile << "| Sortowanie                    | Czas (ms)   |\n";
		outFile << "-----------------------------------------------\n";
		outFile << "| Sortowanie for for                                   | " << fastForFor << "    |\n";
		outFile << "| Sortowanie for for ze wskaznikiem                    | " << fastForForPoint << "    |\n";
		outFile << "| Sortowanie while for                                 | " << fastWhileFor << "    |\n";
		outFile << "| Sortowanie while for ze wskaznikiem                  | " << fastWhileForPoint << "    |\n";
		outFile << "| Sortowanie while for zoptymalizowany                 | " << fastWhileOpt << "    |\n";
		outFile << "| Sortowanie while for zoptymalizowany ze wskaznikiem  | " << fastWhileOptPoint << "    |\n";
		outFile << "-----------------------------------------------\n";

		// Porównanie czasów
		if (fastForForPoint < fastWhileForPoint && fastForForPoint < fastWhileOptPoint && fastForForPoint < fastForFor && fastForForPoint < fastWhileFor && fastForForPoint < fastWhileOpt) {
			outFile << "| Najszybsze sortowanie: for for ze wskaznikiem   |\n";
		}
		else if (fastWhileForPoint < fastForForPoint && fastWhileForPoint < fastWhileOptPoint && fastWhileForPoint < fastForFor && fastWhileForPoint < fastWhileOpt) {
			outFile << "| Najszybsze sortowanie: while for ze wskaznikiem |\n";
		}
		else if (fastWhileOptPoint < fastForForPoint && fastWhileOptPoint < fastWhileForPoint && fastWhileOptPoint < fastForFor && fastWhileOptPoint < fastWhileFor) {
			outFile << "| Najszybsze sortowanie: while for zoptymalizowany    |\n";
		}
		else if (fastForFor == fastForForPoint && fastForFor == fastWhileForPoint && fastForFor == fastWhileOptPoint && fastForFor == fastWhileFor && fastForFor == fastWhileOpt) {
			outFile << "| Wszystkie sortowania maja taki sam czas     |\n";
		}
		else if (fastForFor == fastForForPoint && fastForFor < fastWhileForPoint && fastForFor < fastWhileOptPoint && fastForFor < fastWhileFor) {
			outFile << "| Najszybsze sortowanie: for for oraz for for ze wskaznikiem  |\n";
		}
		else if (fastWhileForPoint == fastWhileFor && fastWhileForPoint < fastForForPoint && fastWhileForPoint < fastWhileOptPoint && fastWhileForPoint < fastWhileOpt) {
			outFile << "| Najszybsze sortowanie: while for oraz while for ze wskaznikiem |\n";
		}
		else if (fastWhileOptPoint == fastWhileOpt && fastWhileOptPoint < fastForForPoint && fastWhileOptPoint < fastWhileForPoint && fastWhileOptPoint < fastForFor) {
			outFile << "| Najszybsze sortowanie: while for zoptymalizowany oraz while for zoptymalizowany ze wskaznikiem |\n";
		}
		else if (fastForForPoint == fastWhileForPoint && fastForForPoint < fastForFor && fastForForPoint < fastWhileOptPoint && fastForForPoint < fastWhileOpt) {
			outFile << "| Najszybsze sortowanie: for for ze wskaznikiem oraz while for ze wskaznikiem |\n";
		}
		else if (fastForFor == fastWhileOptPoint && fastForFor < fastWhileForPoint && fastForFor < fastWhileOpt) {
			outFile << "| Najszybsze sortowanie: for for oraz while for zoptymalizowany ze wskaznikiem |\n";
		}
		else if (fastWhileFor == fastWhileOptPoint && fastWhileFor < fastForForPoint && fastWhileFor < fastForFor) {
			outFile << "| Najszybsze sortowanie: while for oraz while for zoptymalizowany ze wskaznikiem |\n";
		}
		else if (fastWhileOpt == fastForForPoint && fastWhileOpt < fastForFor && fastWhileOpt < fastWhileForPoint) {
			outFile << "| Najszybsze sortowanie: while for zoptymalizowany oraz for for ze wskaznikiem |\n";
		}
		else {
			outFile << "| Wszystkie sortowania maja taki sam czas     |\n";
		}
		outFile << "-----------------------------------------------\n";

		outFile.close();
		cout << "Wyniki zostaly zapisane do pliku 'results.txt'.\n";
	}
	else {
		cout << "Nie udalo sie otworzyc pliku do zapisu.\n";
	}

}

//polega na znajdowaniu najmniejszego elementu i umieszczaniu go na poczatku
void selectionSort(int* arr, int n) {
	for (int i = 0; i < n - 1; i++) {
		int minIndex = i;
		for (int j = i + 1; j < n; j++) {
			if (arr[j] < arr[minIndex]) {
				minIndex = j;
			}
		}
		swap(arr[i], arr[minIndex]);
	}
}

//polega na wstawianiu elementu na odpowiednie miejsce w posortowanej czesci tablicy
void insertionSort(int* arr, int n) {
	for (int i = 1; i < n; i++) {
		int key = arr[i];
		int j = i - 1;

		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}

//funkcja dodatkowa z dodatkowymi testami
template <typename T>
void otherTests(int repeater, T* arr, int n) {
	double ms;
	double s;
	int reap = repeater;
	int n2 = n;
	int* arr2 = new int[n2];
	double fastSelectSort = 0;
	double fastInsertionSort = 0;
	
	srand(time(NULL));
	cout << "-----------------------------" << endl;
	cout << "| Sortowanie  selection sort |" << endl;
	cout << "------------------------------" << endl;
	for (int x = 0; x < reap;x++) {
		for (int i = 0; i < n2; i++) {
			arr2[i] = rand() % 100;
		}

		cout << "Ilosc elementow w nieposortowanej tablicy: " << n2 << endl;

		checker(arr2, n2);

		cout << endl;
		cout << "Czas trwania sortowania selection sort: ";
		ms = timer(selectionSort, arr2, n2);
		s = ms / 1000;
		cout << "Czas w milisekundach: " << ms << ", a w sekundach: " << s << endl;
		if (fastSelectSort == 0 || ms < fastSelectSort) {
			fastSelectSort = ms;
		}
		
		selectionSort(arr2, n2);

		checker(arr2, n2);
		cout << endl;
		cout << "***" << endl;

	}

	cout << "Najszybszy czas: " << fastSelectSort << " ms" << endl;

	cout << "-----------" << endl << endl << endl << endl << endl;
	
	cout << "-----------------------------" << endl;
	cout << "| Sortowanie  insertion sort |" << endl;
	cout << "------------------------------" << endl;
	for (int x = 0; x < reap;x++) {
		for (int i = 0; i < n2; i++) {
			arr2[i] = rand() % 100;
		}

		cout << "Ilosc elementow w nieposortowanej tablicy: " << n2 << endl;

		checker(arr2, n2);

		cout << endl;
		cout << "Czas trwania sortowania insertion sort: ";
		ms = timer(insertionSort, arr2, n2);
		s = ms / 1000;
		cout << "Czas w milisekundach: " << ms << ", a w sekundach: " << s << endl;
		if (fastInsertionSort == 0 || ms < fastInsertionSort) {
			fastInsertionSort = ms;
		}
		
		insertionSort(arr2, n2);

		checker(arr2, n2);
		cout << endl;
		cout << "***" << endl;

	}

	cout << "Najszybszy czas: " << fastInsertionSort << " ms" << endl;

	cout << "-----------" << endl << endl << endl << endl << endl;




	delete[] arr2;
}

//main
int main() {
	bool repeat = true;
	while (repeat) {
		cout << "Witaj w testerze wydajnosciowym sortowania babelkowego!" << endl << "Wprowadz wartosc ile elementow w tablicy ma zostac wygenerowanych i posortowanych: ";
		int odp;
		cin >> odp;
		if (odp) {
			//
			cout << "Ile ma byc powtorzen sortowania jednej funkcji?: ";
			int counter;
			cin >> counter;
			if (counter) {
				int n = odp;
				int* arr = new int[n];
				int repeater = counter;
				//

				srand(time(NULL));
				double ms;
				double s;
				double fastForFor = 0;
				double fastForForPoint = 0;
				double fastWhileFor = 0;
				double fastWhileForPoint = 0;
				double fastWhileOpt = 0;
				double fastWhileOptPoint = 0;

				//Tablica for for z indeksem
				cout << "-------------------------------------" << endl;
				cout << "| Sortowanie for for z indeksem      |" << endl;
				cout << "-------------------------------------" << endl;
				for (int x = 0; x < repeater;x++) {
					for (int i = 0; i < n; i++) {
						arr[i] = rand() % 100;
					}

					cout << "Ilosc elementow w nieposortowanej tablicy: " << n << endl;

					cout << "Czy posortowano?: ";
					bool checkBool = checker(arr, n);
					if (checkBool == true) {
						cout << "true" << endl;
					}
					else {
						cout << "false" << endl;
					}


					cout << endl;
					cout << "Czas trwania sortowania for for z indeksem: ";
					ms = timer(bubblesort_for_for_index, arr, n);
					s = ms / 1000;
					cout << "Czas w milisekundach: " << ms << ", a w sekundach: " << s << endl;
					if (fastForFor == 0 || ms < fastForFor) {
						fastForFor = ms;
					}
					bubblesort_for_for_index(arr, n);

					cout << "Czy posortowano?: ";
					checkBool = checker(arr, n);
					if (checkBool == true) {
						cout << "true" << endl;
					}
					else {
						cout << "false" << endl;
					}
					cout << endl;
					cout << "***" << endl;

				}
				cout << "Najszybszy czas: " << fastForFor << " ms" << endl;
				cout << "-----------" << endl;
				//Tablica while for
				cout << "-------------------------------------" << endl;
				cout << "| Sortowanie while for               |" << endl;
				cout << "-------------------------------------" << endl;
				for (int x = 0; x < repeater;x++) {
					for (int i = 0; i < n; i++) {
						arr[i] = rand() % 100;
					}

					cout << "Ilosc elementow w nieposortowanej tablicy: " << n << endl;

					cout << "Czy posortowano?: ";
					bool checkBool = checker(arr, n);
					if (checkBool == true) {
						cout << "true" << endl;
					}
					else {
						cout << "false" << endl;
					}


					cout << endl;
					cout << "Czas trwania sortowania while for: ";
					ms = timer(bubblesort_while_for, arr, n);
					s = ms / 1000;
					cout << "Czas w milisekundach: " << ms << ", a w sekundach: " << s << endl;
					if (fastWhileFor == 0 || ms < fastWhileFor) {
						fastWhileFor = ms;
					}
					bubblesort_while_for(arr, n);

					cout << "Czy posortowano?: ";
					checkBool = checker(arr, n);
					if (checkBool == true) {
						cout << "true" << endl;
					}
					else {
						cout << "false" << endl;
					}
					cout << endl;
					cout << "***" << endl;

				}
				cout << "Najszybszy czas: " << fastWhileFor << " ms" << endl;
				cout << "-----------" << endl;

				//Tablica for for ze wskaznikami
				cout << "---------------------------------------" << endl;
				cout << "| Sortowanie for for ze wskaznikami |" << endl;
				cout << "---------------------------------------" << endl;
				for (int x = 0; x < repeater;x++) {
					for (int i = 0; i < n; i++) {
						arr[i] = rand() % 100;
					}

					cout << "Ilosc elementow w nieposortowanej tablicy: " << n << endl;

					cout << "Czy posortowano?: ";
					bool checkBool = checker(arr, n);
					if (checkBool == true) {
						cout << "true" << endl;
					}
					else {
						cout << "false" << endl;
					}


					cout << endl;
					cout << "Czas trwania sortowania for for ze wskaznikami: ";
					ms = timer(bubblesort_for_for_with_pointers, arr, n);
					s = ms / 1000;
					cout << "Czas w milisekundach: " << ms << ", a w sekundach: " << s << endl;
					if (fastForForPoint == 0 || ms < fastForForPoint) {
						fastForForPoint = ms;
					}
					bubblesort_for_for_with_pointers(arr, n);

					cout << "Czy posortowano?: ";
					checkBool = checker(arr, n);
					if (checkBool == true) {
						cout << "true" << endl;
					}
					else {
						cout << "false" << endl;
					}
					cout << endl;
					cout << "***" << endl;

				}
				cout << "Najszybszy czas: " << fastForForPoint << " ms" << endl;
				cout << "-----------" << endl;

				//Tablica while for ze wskaznikami
				cout << "---------------------------------------" << endl;
				cout << "| Sortowanie while for ze wskaznikami  |" << endl;
				cout << "---------------------------------------" << endl;
				for (int x = 0; x < repeater;x++) {
					for (int i = 0; i < n; i++) {
						arr[i] = rand() % 100;
					}

					cout << "Ilosc elementow w nieposortowanej tablicy: " << n << endl;

					cout << "Czy posortowano?: ";
					bool checkBool = checker(arr, n);
					if (checkBool == true) {
						cout << "true" << endl;
					}
					else {
						cout << "false" << endl;
					}


					cout << endl;
					cout << "Czas trwania sortowania while for ze wskaznikami: ";
					ms = timer(bubblesort_with_while_with_pointers, arr, n);
					s = ms / 1000;
					cout << "Czas w milisekundach: " << ms << ", a w sekundach: " << s << endl;
					if (fastWhileForPoint == 0 || ms < fastWhileForPoint) {
						fastWhileForPoint = ms;
					}
					bubblesort_with_while_with_pointers(arr, n);

					cout << "Czy posortowano?: ";
					checkBool = checker(arr, n);
					if (checkBool == true) {
						cout << "true" << endl;
					}
					else {
						cout << "false" << endl;
					}
					cout << endl;
					cout << "***" << endl;

				}
				cout << "Najszybszy czas: " << fastWhileForPoint << " ms" << endl;
				cout << "-----------" << endl;


				//Tablica zoptymalizowana while for
				cout << "---------------------------------------" << endl;
				cout << "| Sortowanie zoptymalizowany while for |" << endl;
				cout << "---------------------------------------" << endl;
				for (int x = 0; x < repeater;x++) {
					for (int i = 0; i < n; i++) {
						arr[i] = rand() % 100;
					}

					cout << "Ilosc elementow w nieposortowanej tablicy: " << n << endl;

					checker(arr, n);

					cout << endl;
					cout << "Czas trwania sortowania zoptymalizowany while form: ";
					ms = timer(bubblesort_while_with_optimized_for, arr, n);
					s = ms / 1000;
					cout << "Czas w milisekundach: " << ms << ", a w sekundach: " << s << endl;
					if (fastWhileOpt == 0 || ms < fastWhileOpt) {
						fastWhileOpt = ms;
					}
					bubblesort_while_with_optimized_for(arr, n);

					checker(arr, n);
					cout << endl;
					cout << "***" << endl;

				}
				cout << "Najszybszy czas: " << fastWhileOpt << " ms" << endl;

				cout << "-----------" << endl << endl << endl << endl << endl;

				//Tablica zoptymalizowana while for ze wskaznikami
				cout << "-------------------------------------------------------" << endl;
				cout << "| Sortowanie zoptymalizowany while for  ze wskaznikami|" << endl;
				cout << "-------------------------------------------------------" << endl;
				for (int x = 0; x < repeater;x++) {
					for (int i = 0; i < n; i++) {
						arr[i] = rand() % 100;
					}

					cout << "Ilosc elementow w nieposortowanej tablicy: " << n << endl;

					checker(arr, n);

					cout << endl;
					cout << "Czas trwania sortowania while for ze wskaznikami: ";
					ms = timer(bubblesort_while_optimized_for_with_pointers, arr, n);
					s = ms / 1000;
					cout << "Czas w milisekundach: " << ms << ", a w sekundach: " << s << endl;
					if (fastWhileOptPoint == 0 || ms < fastWhileOptPoint) {
						fastWhileOptPoint = ms;
					}
					bubblesort_while_optimized_for_with_pointers(arr, n);

					checker(arr, n);
					cout << endl;
					cout << "***" << endl;

				}
				cout << "Najszybszy czas: " << fastWhileOptPoint << " ms" << endl;

				cout << "-----------" << endl << endl << endl << endl << endl;
				cout << "Chcesz wyswietlic w tabelce wyniki? [T/N]: ";
				string odp;
				cin >> odp;
				for (auto& c : odp) {
					c = toupper(c);
				}

				if (odp == "T") {
					cout << "Wyniki zostana wyswietlone w tabelce z tablicy " << n << " elementowej." << endl;

					results(fastForFor, fastWhileFor, fastWhileOpt, fastForForPoint, fastWhileForPoint, fastWhileOptPoint);
				}
				else if (odp == "N") {
					cout << "Wyniki nie beda wyswietlone." << endl;
				}
				else {
					cout << "Niepoprawna odpowiedz." << endl;
				}
				

				cout << "--------------" << endl << endl << endl;
				cout << "Chcesz wykonac testy dla tych samych wartosci ale na innych typach sortowan? [T/N]: ";
				string odp3;
				cin >> odp3;
				for (auto& c : odp3) {
					c = toupper(c);
				}
				if (odp3 == "T") {
					otherTests(repeater, arr, n);
				}
				
				cout << "Chcesz wykonac test ponownie [T/N]: ";
				string odp2;
				cin >> odp2;
				for (auto& c : odp2) {
					c = toupper(c);
				}
				if (odp2 == "N") {
					repeat = false;
				}
				delete[] arr;
			}
		}
	}
		return 0;
	}