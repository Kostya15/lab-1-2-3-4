#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Предварительное объявление
class CompositePart;

class Part {
protected:
    string partName;
    double partWeight;

    Part(const string& name, double weight)
        : partName(name), partWeight(weight) {}

public:
    virtual ~Part() = default;

    virtual void display() const {
        cout << "Деталь: " << partName << ", Вес: " << partWeight << " кг" << endl;
    }

    template<typename T>
    friend T* createPart(const string& name, double weight);
};

class CompositePart : public Part {
protected:
    vector<Part*> subParts;

    CompositePart(const string& name, double weight)
        : Part(name, weight) {}

public:
    void addSubPart(Part* p) {
        subParts.push_back(p);
    }

    void display() const override {
        cout << "Сборка: " << partName << ", Общий вес: " << partWeight << " кг" << endl;
        cout << "Состав (" << subParts.size() << " элементов):" << endl;
        for (const auto& sp : subParts) {
            cout << "  ";
            sp->display();
        }
    }

    ~CompositePart() {
        for (auto sp : subParts) {
            delete sp;
        }
    }

    template<typename T>
    friend T* createPart(const string& name, double weight);
};

// Функция-шаблон для создания объектов
template<typename T>
T* createPart(const string& name, double weight) {
    return new T(name, weight);
}

// Создание обычной детали
void createSimplePart(vector<Part*>& storage) {
    string name;
    double weight;

    cout << "Введите название детали: ";
    cin >> name;
    cout << "Введите вес детали: ";
    cin >> weight;

    storage.push_back(createPart<Part>(name, weight));
    cout << "Деталь создана!\n" << endl;
}

// Создание составной детали
void createCompositePart(vector<Part*>& storage) {
    string name;
    double weight;

    cout << "Введите название сборки: ";
    cin >> name;
    cout << "Введите общий вес сборки: ";
    cin >> weight;

    CompositePart* comp = createPart<CompositePart>(name, weight);

    int subCount;
    cout << "Сколько деталей добавить в сборку? ";
    cin >> subCount;

    for (int i = 0; i < subCount; i++) {
        string subName;
        double subWeight;

        cout << "Деталь " << i + 1 << " - название: ";
        cin >> subName;
        cout << "Деталь " << i + 1 << " - вес: ";
        cin >> subWeight;

        comp->addSubPart(createPart<Part>(subName, subWeight));
    }

    storage.push_back(comp);
    cout << "Сборка создана!\n" << endl;
}

int main() {
    setlocale(LC_ALL, "ru");
    vector<Part*> storage;
    int choice;

    do {
        cout << "1. Создать деталь" << endl;
        cout << "2. Создать сборку" << endl;
        cout << "3. Показать все объекты" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1:
            createSimplePart(storage);
            break;
        case 2:
            createCompositePart(storage);
            break;
        case 3:
            cout << "\n==== ВСЕ ОБЪЕКТЫ ====" << endl;
            for (const auto& item : storage) {
                item->display();
                cout << endl;
            }
            cout << "===================\n" << endl;
            break;
        case 0:
            cout << "Выход..." << endl;
            break;
        default:
            cout << "Неверный выбор!\n" << endl;
        }
    } while (choice != 0);

    for (auto item : storage) {
        delete item;
    }

    return 0;
}
