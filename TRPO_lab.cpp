#include <iostream>
#include<iomanip>
#include<cmath>
#include <fstream>
using namespace std;

//Вариант 2 (10 баллов).Используя паттерн Strategy запрограммируйте следующую
//ситуацию.Имеется класс(или шаблон класса) Array(массив), который(массив) можно
//заполнять различным образом : используя стратегию заполнения массива из файла, стратегию
//заполнения значениями элементов по умолчанию.Продемонстрируйте работу паттерна.


//Доп.задания:
//(5 баллов) В существующую иерархию необходимо добавить стратегию, позволяющую
//заполнить массив целых чисел случайными значениями в диапазоне от 0 до randMax.
//Внесите необходимые изменения в код, продемонстрируйте работу паттерна.


///Предварительно описание стратегии
class Fill;

class Fill {
public:
    virtual void FillArray(int* array, string file_name) = 0;
};


///Базовая стратегия
///Стратегия заполнения с начала
class FillDefault : public Fill {
public:
    virtual void FillArray(int* array,string file_name) {
        cout << "Заполняем массив с начала\n";
        ifstream in(file_name);
        if (in.is_open()) {
            int size;
            in >> size;
            for (int i = 0; i < size; i++) {
                in >> array[i];
            }
        }
        else cout << "Файл не открыт";
        in.close();
    }
};

///Стратегия заполнения с конца
class FillBackwards : public Fill {
public:
    virtual void FillArray(int* array,string file_name) {
        cout << "Заполняем массив с конца\n";
        ifstream in(file_name);
        if (in.is_open()) {
            int size;
            in >> size;
            for (int i = size; i > 0; i--) {
                in >> array[i - 1];
            }
        }
        else cout << "Файл не открыт";
        in.close();
    }
};

///Стратегия заполнения рандомно
class FillRandom : public Fill {
private:
    int randMax;
public:
    FillRandom(int randMax) {
        this->randMax = randMax;
    }
    FillRandom() {
        this->randMax = 20;
    }
    virtual void FillArray(int* array,string file_name) {
        cout << "Заполняем массив рандомно\n";
        ifstream in(file_name);
        int size;
        in >> size;
        for (int i = 0; i < size; i++) {
            array[i] = rand() % this->randMax + 1;
        }
        in.close();
    }
};


class Array {
private:
    int *array;
    int size;
    string file_name;
public:
    Fill*p;/// указатель на стратегию

    Array(string file_name) {
        ifstream in(file_name);
        in >> this->size;
        this->array = new int[this->size];
        this->file_name = file_name;
        this->p = new FillDefault();
        in.close();
    }

    Array(Fill* p, string file_name) {
        ifstream in(file_name);
        in >> this->size;
        this->array = new int[this->size];
        this->file_name = file_name;
        this->p = p;
    }

    void print() {
        for (int i = 0; i < size; i++) {
            cout << array[i] << " ";
        }
        cout << endl;
    }

    void setStrategy(Fill* p) {
        this->p = p;
    }
    void FillArray() {
        p->FillArray(array,file_name);
    }
};

///ПРограмма-клиент
int main()
{
    setlocale(LC_ALL, "Russian");

    std::ifstream in;      
    std::ifstream in2;

    string file_name1 = "array1.txt";
    string file_name2 = "array2.txt";
    int size1, size2;

    in.open(file_name1);
    in2.open(file_name2);

    in >> size1;
    in2 >> size2;

    in.close();
    in2.close();

    Fill* s1 = new FillRandom(100);
    Fill* s2 = new FillBackwards();
    Fill* s3 = new FillRandom();

    Array n1(s1,file_name1);
    Array n2(file_name2);

    n1.FillArray();
    n1.print();
    n2.FillArray();
    n2.print();

    n1.setStrategy(s2); ///замена cтратегий
    n2.setStrategy(s3);

    n1.FillArray();
    n1.print();
    n2.FillArray();
    n2.print();


    
   
    return 0;
}