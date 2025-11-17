#include <iostream>
#include <string>
using namespace std;

// --- Класс Publication ---
class Publication {
protected:
    string title;
    float price;
public:
    void getdata() {
        cout << "Введите название книги: ";
        getline(cin, title);
        cout << "Введите цену книги: ";
        cin >> price;
    }

    void putdata() {
        cout << "Название книги: " << title << endl;
        cout << "Цена книги: " << price << " руб." << endl;
    }
};

// --- Класс Sales ---
class Sales {
protected:
    float sales[3]; // общая стоимость за 3 месяца
public:
    void putdata() {
        float total = 0;
        cout << "Продажи за последние 3 месяца:" << endl;
        for (int i = 0; i < 3; i++) {
            cout << "Месяц " << i + 1 << ": " << sales[i] << " руб." << endl;
            total += sales[i];
        }
        cout << "Общая сумма продаж: " << total << " руб." << endl;
    }
};

// --- Класс Book ---
class Book : public Publication, public Sales {
private:
    int pages;
    int sold[3]; // количество проданных книг за каждый месяц
public:
    void getdata() {
        cout << "\n=== Ввод данных о книге ===" << endl;
        Publication::getdata();
        cout << "Введите количество страниц: ";
        cin >> pages;

        cout << "Введите количество проданных книг за 3 месяца:" << endl;
        for (int i = 0; i < 3; i++) {
            cout << "Месяц " << i + 1 << ": ";
            cin >> sold[i];
            sales[i] = sold[i] * price; // сохраняем стоимость продаж
        }
    }

    void putdata() {
        cout << "\n=== Данные о книге ===" << endl;
        Publication::putdata(); // вывод названия и цены
        cout << "Количество страниц: " << pages << endl;
        Sales::putdata(); // вывод продаж и общей суммы
    }
};

// --- Класс Type (аудиокнига) ---
class Type : public Publication, public Sales {
private:
    float time; // время записи в минутах
    int sold[3]; // количество проданных аудиокниг за каждый месяц
public:
    void getdata() {
        cin.ignore();
        cout << "\n=== Ввод данных об аудиокниге ===" << endl;
        Publication::getdata();
        cout << "Введите время записи (в минутах): ";
        cin >> time;

        cout << "Введите количество проданных аудиокниг за 3 месяца:" << endl;
        for (int i = 0; i < 3; i++) {
            cout << "Месяц " << i + 1 << ": ";
            cin >> sold[i];
            sales[i] = sold[i] * price; // сохраняем стоимость продаж
        }
    }

    void putdata() {
        cout << "\n=== Данные об аудиокниге ===" << endl;
        Publication::putdata();
        cout << "Время записи: " << time << " минут" << endl;
        Sales::putdata();
    }
};


int main() {
    setlocale(LC_ALL, "RU");

    Book book;
    Type audiobook;

    book.getdata();
    audiobook.getdata();

    book.putdata();
    audiobook.putdata();

    return 0;
}
