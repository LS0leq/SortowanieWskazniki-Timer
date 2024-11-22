#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>   
using namespace std;

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

void checker(int* arr, int n) {
    int i = 0;
    int checkBool = true;
    while (i <= n) {
        if (arr[i] < arr[i + 1]) {
            checkBool = false;
        }
       
        i++;
     
    }
    cout << "Posortowane?: ";
    if (checkBool == 1) {
        cout << "True";
    }
    else {
        cout << "False";
    }

}

int main() {
    srand(time(NULL));
    int n = 10;  
    int arr[10];
   //Tablica For For
    for (int x = 0; x < 4;x++) {
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 100;
        }

        cout << "Nieposortowana tablica: ";
        for (int i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }
        checker(arr, n);

        cout << endl;
        cout << "Sortowanie for for: ";
        bubblesort_for_for_index_cursor(arr, n);

        for (int i = 0; i < n; i++) {
            std::cout << arr[i] << " ";
        }
        checker(arr, n);
        cout << endl;
    }
    cout << "-----------" << endl;

    //Tablica while for 
    for (int x = 0;x < 4; x++) {
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 100;
        }

        cout << "Nieposortowana tablica: ";
        for (int i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }
        checker(arr, n);

        cout << endl;
        cout << "Sortowanie while for : ";
        bubblesort_while_for_index_cursor(arr, n);

        for (int i = 0; i < n; i++) {
            std::cout << arr[i] << " ";
        }
        checker(arr, n);
        cout << endl;

    }

    cout << "-----------" << endl;
    //Tablica while shorten for 
    for (int x = 0;x < 4; x++) {
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 100;
        }

        cout << "Nieposortowana tablica: ";
        for (int i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }
        checker(arr, n);

        cout << endl;
        cout << "Sortowanie while shorten for: ";
        bubblesort_while_shorten_for_index_cursor(arr, n);

        for (int i = 0; i < n; i++) {
            std::cout << arr[i] << " ";
        }
        checker(arr, n);
        cout << endl;

    }


    return 0;
}