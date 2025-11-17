#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;


class Human {
protected:
    string name;

public:
    Human(const string& n) : name(n) {}
    virtual void info() const { cout << "Человек: " << name << endl; }
    virtual ~Human() {}
};

class Preschooler : public Human {
public:
    Preschooler(const string& n) : Human(n) {}
    void info() const override { cout << "Дошкольник: " << name << endl; }
};

class Schoolboy : public Human {
public:
    Schoolboy(const string& n) : Human(n) {}
    void info() const override { cout << "Школьник: " << name << endl; }
};

class Student : public Human {
public:
    Student(const string& n) : Human(n) {}
    void info() const override { cout << "Студент: " << name << endl; }
};

class Worker : public Human {
public:
    Worker(const string& n) : Human(n) {}
    void info() const override { cout << "Работающий: " << name << endl; }
};


template <class T>
class PointerArray {
private:
    T** arr;
    int size;

public:
    // Конструктор с проверкой корректности размера
    PointerArray(int s) {
        if (s <= 0)
            throw invalid_argument("Размер массива должен быть положительным!");

        size = s;
        arr = new T * [size];
        for (int i = 0; i < size; i++) {
            arr[i] = nullptr;
        }
    }

    // Перегрузка оператора [], + защита от неправильного индекса
    T*& operator[](int index) {
        if (index < 0 || index >= size)
            throw out_of_range("Ошибка: индекс вне диапазона!");
        return arr[index];
    }

    // Метод для демонстрации runtime_error
    void checkArrayIntegrity() const {
        for (int i = 0; i < size; i++) {
            if (arr[i] == nullptr)
                throw runtime_error("Ошибка: элемент массива не инициализирован!");
        }
    }

    int getSize() const { return size; }

    // Деструктор — полностью освобождает память
    ~PointerArray() {
        for (int i = 0; i < size; i++) {
            delete arr[i];
        }
        delete[] arr;
    }
};


int main() {
    setlocale(LC_ALL, "ru");

    try {
        cout << "-------Работа шаблонного класса с Human-------\n";

        PointerArray<Human> humans(4);

        // Показ работы оператора [] — присваивание в массив
        humans[0] = new Preschooler("Артем");
        humans[1] = new Schoolboy("Иван");
        humans[2] = new Student("Олег");
        humans[3] = new Worker("Николай");

        // Показ работы оператора [] — чтение из массива
        for (int i = 0; i < humans.getSize(); i++) {
            humans[i]->info();
        }


        cout << "\n-------Исключение out_of_range-------\n";
        try {
            humans[10]->info();   // намеренно неверный индекс
        }
        catch (const out_of_range& e) {
            cout << "Поймано исключение: " << e.what() << endl;
        }



        cout << "\n-------Работа шаблонного класса с int-------\n";

        PointerArray<int> numbers(3);

        numbers[0] = new int(10);
        numbers[1] = new int(20);
        numbers[2] = new int(30);

        for (int i = 0; i < numbers.getSize(); i++) {
            cout << *numbers[i] << " ";
        }
        cout << endl;



        cout << "\n-------runtime_error (доп задание)-------\n";

        PointerArray<int> broken(3);
        broken[0] = new int(100);
        broken[1] = nullptr;    // намеренно создаём ошибку
        broken[2] = new int(300);

        try {
            broken.checkArrayIntegrity(); // здесь возникнет runtime_error
        }
        catch (const runtime_error& e) {
            cout << "Поймано исключение: " << e.what() << endl;
        }

    }
    catch (const exception& e) {
        cout << "ГЛОБАЛЬНАЯ ОШИБКА: " << e.what() << endl;
    }

    return 0;
}
