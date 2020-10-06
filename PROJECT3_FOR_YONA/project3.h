#pragma once
#define MAX 7
#define COLS 3
#define LENGTH 30

typedef struct
{
    int day;
    int month;
    int year;
}Date;


typedef struct personType
{
    int serial_num;
    char full_name[LENGTH];
    Date* ptrDate;
}Person;

Person* add_Person(int n, Person* PA, const char name[], const int* date);
void save_File(FILE* fp, Person* PA, int n);
void print_Array(Person* PA, int size);
void copy_fromFile(FILE* fp, int* size, Person** PA);
void sortBy_age(Person* PA, int size);