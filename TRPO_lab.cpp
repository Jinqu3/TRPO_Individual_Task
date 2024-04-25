﻿#include <iostream>
#include<iomanip>
#include<cmath>
using namespace std;

//Вариант 2 (10 баллов).Используя паттерн Strategy запрограммируйте следующую
//ситуацию.Имеется класс(или шаблон класса) Array(массив), который(массив) можно
//заполнять различным образом : используя стратегию заполнения массива из файла, стратегию
//заполнения значениями элементов по умолчанию.Продемонстрируйте работу паттерна.





///Предварительно описание стратегии
class Fill;

class Fill {
public:
    virtual void FillArray(int* array, int size) = 0;
};


///Базовая стратегия
///Стратегия заполнения с начала
class FillDefault : public Fill {
public:
    virtual void FillArray(int* array, int size) {
        cout << "Заполняем массив с начала\n";
        for (int i = 1; i <= size; i++) {
            cout << "Введи " << i << " элемент массива: ";
            cin >> array[i - 1];
        }
    }
};

///Стратегия заполнения с конца
class FillBackwards : public Fill {
public:
    virtual void FillArray(int* array, int size) {
        cout << "Заполняем массив с конца\n";
        for (int i = size; i > 0; i--) {
            cout << "Введи " << i << " элемент массива: ";
            cin >> array[i - 1];
        }
    }
};

///Стратегия заполнения рандомно
class FillRandom : public Fill {
public:
    virtual void FillArray(int* array, int size) {
        cout << "Заполняем массив рандомно\n";
        for (int i = 0; i < size; i++) {
            array[i] = rand() % 20 + 1;
        }
    }
};


class Array {
private:
    int *array;
    int size;
public:
    Fill*p;/// указатель на стратегию

    Array(int size) {
        this->array = new int[size];
        this->size = size;
        this->p = new FillDefault();
    }

    Array(int size, Fill* p) {
        this->array = new int[size];
        this->size = size;
        this->p = p;
    }

    void print() {
        for (int i = 0; i < size; i++) {
            cout << array[i] << " ";
        }
        cout << endl << endl;
    }

    void setStrategy(Fill* p) {
        this->p = p;
    }
    void FillArray() {
        p->FillArray(array, size);
    }
};

///ПРограмма-клиент
int main()
{
    setlocale(LC_ALL, "Russian");
    int size1, size2;
    cout << "Введите размер 1 массива: ";
    cin >> size1;
    cout << "Введите размер 2 массива: ";
    cin >> size2;

    Array n1(size1);
    Array n2(size2);

    n1.FillArray();
    n1.print();
    n2.FillArray(); 
    n2.print();

    Fill * s = new FillBackwards();
    Fill * s1 = new FillRandom();
    n1.setStrategy(s); ///замена cтратегий
    n2.setStrategy(s1);

    n1.FillArray();
    n1.print();
    n2.FillArray();
    n2.print();


    return 0;
}