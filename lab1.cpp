#include <iostream>
#include <ctime>
using namespace std;

int main() {
    setlocale(LC_ALL, "RU");

    int a;
    cout << "Введите размер массива a: ";
    cin >> a;

    int* arr = new int[a]; 

    srand(time(0));

    
    for (int i = 0; i < a; i++) {
        arr[i] = rand() % 20;
    }

    cout << "\nМассив: ";
    for (int i = 0; i < a; i++) {
        cout << arr[i] << " ";
    }

    cout << "\n\nАдрес начала массива: " << arr << "\n\n";

    // Выводим адреса и смещения
    for (int i = 0; i < a; i++) {
        size_t d_bytes = i * sizeof(int);  // смещение в байтах
        cout << "Элемент [" << i << "] = " << arr[i]
            << "   адрес: " << &arr[i]
            << "   смещение от начала: " << d_bytes << " байт\n";
    }

    delete[] arr;
    return 0;
}
