#include <iostream>
#include <ctime>
using namespace std;

int main() {
    setlocale(LC_ALL, "RU");

    const int A = 10;
    double* arr = new double[A];

    srand(time(0));


    for (int i = 0; i < A; i++) {
        arr[i] = rand() % 20;
    }

    cout << "Массив: ";
    for (int i = 0; i < A; i++) {
        cout << arr[i] << " ";
    }

    cout << "\n\nАдрес начала массива: " << arr << "\n\n";

    // Выводим адреса и смещения
    for (int i = 0; i < A; i++) {
        size_t d_bytes = i * sizeof(double);  // смещение в байтах
        cout << "Элемент [" << i << "] = " << arr[i]
            << "   адрес: " << &arr[i]
            << "   смещение от начала: " << d_bytes << " байт\n";
    }

    delete[] arr;
    return 0;
}
