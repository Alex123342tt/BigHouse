﻿#include <iostream>
#include <cstring>
#include <Windows.h>
using namespace std;

class Person {
    char* name;
    int age;

public:
    Person() : name(nullptr), age(0) {}

    Person(const char* n, int a) : age(a)
    {
        size_t len = strlen(n) + 1;
        name = new char[len];
        strcpy_s(name, len, n);
    }

    Person(const Person& other) : age(other.age)
    {
        if (other.name)
        {
            size_t len = strlen(other.name) + 1;
            name = new char[len];
            strcpy_s(name, len, other.name);
        }
        else name = nullptr;
    }


    Person(Person&& other) noexcept : name(other.name), age(other.age)
    {
        other.name = nullptr;
        other.age = 0;
        cout << "Move constructor Person\n";
    }

    ~Person()
    {
        delete[] name;
    }

    void print() const
    {
        cout << "Ім'я: " << (name ? name : "Невідомо") << ", Вік: " << age << endl;
    }
};

class Apartment
{
    Person* people;
    int size;

public:
    Apartment(int s = 0) : size(s)
    {
        people = (size > 0) ? new Person[size] : nullptr;
    }

    Apartment(const Apartment& other) : size(other.size)
    {
        if (size > 0)
        {
            people = new Person[size];
            for (int i = 0; i < size; i++)
                new (&people[i]) Person(other.people[i]);
        }
        else people = nullptr;
    }


    Apartment(Apartment&& other) noexcept : people(other.people), size(other.size)
    {
        other.people = nullptr;
        other.size = 0;
        cout << "Move constructor Apartment\n";
    }

    ~Apartment()
    {
        delete[] people;
    }

    void setPerson(int index, const Person& p)
    {
        if (index >= 0 && index < size)
            new (&people[index]) Person(p);
    }

    void print() const
    {
        cout << "Квартира (" << size << " мешканців):" << endl;
        for (int i = 0; i < size; i++)
            people[i].print();
    }
};

class House
{
    Apartment* apartments;
    int count;

public:
    House(int c = 0) : count(c)
    {
        apartments = (count > 0) ? new Apartment[count] : nullptr;
    }

    House(const House& other) : count(other.count)
    {
        if (count > 0)
        {
            apartments = new Apartment[count];
            for (int i = 0; i < count; i++)
                new (&apartments[i]) Apartment(other.apartments[i]);
        }
        else apartments = nullptr;
    }


    House(House&& other) noexcept : apartments(other.apartments), count(other.count)
    {
        other.apartments = nullptr;
        other.count = 0;
        cout << "Move constructor House\n";
    }

    ~House()
    {
        delete[] apartments;
    }

    void setApartment(int index, const Apartment& a)
    {
        if (index >= 0 && index < count)
            new (&apartments[index]) Apartment(a); 
    }

    void print() const
    {
        cout << "Будинок (" << count << " квартир):" << endl;
        for (int i = 0; i < count; i++)
        {
            cout << "  Квартира №" << i + 1 << ":" << endl;
            apartments[i].print();
        }
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Person p1("Іван Петров", 30);
    Person p2("Марія Іванова", 25);
    Person p3("Олег Сидоров", 40);

    Apartment a1(2);
    a1.setPerson(0, p1);
    a1.setPerson(1, p2);

    Apartment a2(1);
    a2.setPerson(0, p3);

    House h(2);
    h.setApartment(0, a1);
    h.setApartment(1, a2);

    h.print();

  
    cout << "\n Демонстрація переміщення \n";
    House movedHouse = std::move(h);
    movedHouse.print();
}