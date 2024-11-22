#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>   
#include <windows.h>
#include <fstream>
using namespace std;

//funkcje sortujace
void bubblesort_for_for_index(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void bubblesort_for_for_index_cursor(int* arr, int n) {
    int* w1, * w2, temp;
    for (int i = 0;i < n;i++) {
        for (int j = 0;j < n - 1;j++) {
            w1 = arr + j;
            w2 = w1 + 1;
            if (*w2 > *w1) {
                temp = *w1;
                *w1 = *w2;
                *w2 = temp;
            }
        }
    }
}

void bubblesort_while_for_index(int* arr, int n) {
    int i = 0;
    while (i < n) {
        for (int j = 0; j < n - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
        i++;
    }
}

void bubblesort_while_for_index_cursor(int* arr, int n) {
    int* w1, * w2, temp;
    int i = 0;
    while (i < n) {
        for (int j = 0; j < n - 1; j++) {
            w1 = arr + j;
            w2 = w1 + 1;
            if (*w2>*w1) {
                int temp = *w1;
                *w1 = *w2;
                *w2 = temp;

            }
        }
        i++;
    }
}

void bubblesort_while_shorten_for_index(int* arr, int n) {
    int i = 0;
    while (i < n) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
        i++;
    }
}

void bubblesort_while_shorten_for_index_cursor(int* arr, int n) {
    int* w1, * w2, temp;
    int i = 0;
    while (i < n) {

       
        for (int j = 0; j < n - 1 - i; j++) {
            w1 = arr + j;
            w2 = w1 + 1;

            if (*w2 > *w1) {
                int temp = *w1;
                *w1 = *w2;
                *w2 = temp;
            }
        }
        i++;
    }
}

//funkcja sprawdzajaca czy tablica jest posortowana
void checker(int* arr, int n) {
    bool checkBool = true;

    for (int i = 0; i < n - 1; i++) {
        if (arr[i] < arr[i + 1]) {
            checkBool = false;
            break;
        }
    }

    cout << "Posortowane?: " << (checkBool ? "True" : "False") << endl;
}

//funkcja liczaca czas sortowania
double timer(void (*sortFunc)(int*, int), int* arr, int n) {
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
void results(double fastForFor, double fastWhileFor, double fastWhileShort) {
    cout << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "| Sortowanie                    | Czas (ms)   |" << endl;
    cout << "------------------------------------------" << endl;
    cout << "| Sortowanie for for z kursorem  | " << fastForFor << "    |" << endl;
    cout << "| Sortowanie while for z kursorem| " << fastWhileFor << "    |" << endl;
    cout << "| Sortowanie while shorten for   | " << fastWhileShort << "    |" << endl;
    cout << "-----------------------------------------------" << endl;
	if (fastForFor < fastWhileFor && fastForFor < fastWhileShort) {
		cout << "| Najszybsze sortowanie: for for z kursorem   |" << endl;
	}
    else if (fastWhileFor < fastForFor && fastWhileFor < fastWhileShort) {
		cout << "| Najszybsze sortowanie: while for z kursorem |" << endl;
	}
    else if (fastWhileShort < fastForFor && fastWhileShort < fastWhileFor) {
		cout << "| Najszybsze sortowanie: while shorten for    |" << endl;
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
        outFile << "| Sortowanie for for z kursorem  | " << fastForFor << "    |\n";
        outFile << "| Sortowanie while for z kursorem| " << fastWhileFor << "    |\n";
        outFile << "| Sortowanie while shorten for   | " << fastWhileShort << "    |\n";
        outFile << "-----------------------------------------------\n";
        if (fastForFor < fastWhileFor && fastForFor < fastWhileShort) {
            outFile << "| Najszybsze sortowanie: for for z kursorem   |\n";
        }
        else if (fastWhileFor < fastForFor && fastWhileFor < fastWhileShort) {
            outFile << "| Najszybsze sortowanie: while for z kursorem |\n";
        }
        else if (fastWhileShort < fastForFor && fastWhileShort < fastWhileFor) {
            outFile << "| Najszybsze sortowanie: while shorten for    |\n";
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

//main
int main() {
    srand(time(NULL));
    int n = 10000;  
    int arr[10000];
    int repeater = 2;

    double ms;
    double s;
    double fastForFor = 0;
    double fastWhileFor = 0;
    double fastWhileShort = 0;


   //Tablica for for
	cout << "---------------------------------" << endl;
	cout << "| Sortowanie for for z kursorem |" << endl;
	cout << "---------------------------------" << endl;
    for (int x = 0; x < repeater;x++) {
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 100;
        }

        cout << "Ilosc elementow w nieposortowanej tablicy: "<<n<<endl;
       
        checker(arr, n);

        cout << endl;
        cout << "Czas trwania sortowania for for z kursorem: ";
        ms = timer(bubblesort_for_for_index_cursor, arr, n);
		s = ms / 1000;
		cout << "Czas w milisekundach: " << ms << ", a w sekundach: "<<s<< endl;
		if (fastForFor == 0 || ms < fastForFor) {
			fastForFor = ms;
		}
        bubblesort_for_for_index_cursor(arr, n);
        
        checker(arr, n);
        cout << endl;
        cout << "***" << endl;

    }
	cout << "Najszybszy czas: " << fastForFor << " ms" << endl;
    cout << "-----------"  << endl;
    
    //Tablica For For
    cout << "-----------------------------------------" << endl;
    cout << "| Sortowanie while for index z kursorem |" << endl;
    cout << "-----------------------------------------" << endl;
    for (int x = 0; x < repeater;x++) {
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 100;
        }

        cout << "Ilosc elementow w nieposortowanej tablicy: " << n << endl;

        checker(arr, n);

        cout << endl;
        cout << "Czas trwania sortowania while for index z kursorem: ";
        ms = timer(bubblesort_while_for_index_cursor, arr, n);
        s = ms / 1000;
        cout << "Czas w milisekundach: " << ms << ", a w sekundach: " << s << endl;
        if (fastWhileFor == 0 || ms < fastWhileFor) {
            fastWhileFor = ms;
        }
        bubblesort_while_for_index_cursor(arr, n);

        checker(arr, n);
        cout << endl;
        cout << "***" << endl;

    }
    cout << "Najszybszy czas: " << fastWhileFor << " ms" << endl;

    cout << "-----------" << endl<<endl;


    //Tablica while shorten for index z kursorem
    cout << "-------------------------------------------------" << endl;
    cout << "| Sortowanie while shorten for index z kursorem |" << endl;
    cout << "-------------------------------------------------" << endl;
    for (int x = 0; x < repeater;x++) {
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 100;
        }

        cout << "Ilosc elementow w nieposortowanej tablicy: " << n << endl;

        checker(arr, n);

        cout << endl;
        cout << "Czas trwania sortowania while shorten for index z kursorem: ";
        ms = timer(bubblesort_while_shorten_for_index_cursor, arr, n);
        s = ms / 1000;
        cout << "Czas w milisekundach: " << ms << ", a w sekundach: " << s << endl;
        if (fastWhileShort == 0 || ms < fastWhileShort) {
            fastWhileShort = ms;
        }
        bubblesort_while_shorten_for_index_cursor(arr, n);

        checker(arr, n);
        cout << endl;
        cout << "***" << endl;

    }
    cout << "Najszybszy czas: " << fastWhileShort <<" ms"<< endl;

    cout << "-----------" << endl<<endl << endl << endl << endl;
	cout << "Chcesz wyswietlic w tabelce wyniki? [T/N]: ";
    string odp;
	cin >> odp;
    for (auto& c : odp) {
        c = toupper(c);
    }

    if (odp == "T") {
        cout << "Wyniki zostana wyswietlone w tabelce." << endl;
		results(fastForFor, fastWhileFor, fastWhileShort);
    }
    else if (odp == "N") {
        cout << "Wyniki nie beda wyswietlone." << endl;
    }
    else {
        cout << "Niepoprawna odpowiedz." << endl;
    }

    

    return 0;
}