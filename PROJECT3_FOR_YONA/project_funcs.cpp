#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "project3.h"

//Add person to array PA
Person* add_Person(int n, Person* PA, const char name[], const int* date)
{

    Person *p=(Person*)malloc(sizeof(Person));
    if (p == NULL)exit(1);
    Date* d = (Date*)malloc(sizeof(date));
    if (d == NULL)exit(1);
    //Adds info into p
    p->serial_num = n;
    strcpy(p->full_name, name);
    d->day = date[0];
    d->month = date[1];
    d->year = date[2];
    p->ptrDate = d;
    //reallocate memory for Array
    PA = (Person*)realloc(PA, sizeof(Person) * n);
    if (PA != NULL)
    {
        PA[n - 1] = *p;
    }
    else exit(1);
    //return array
    return PA;
}

//Saves data in PA to person.txt
void save_File(FILE* fp, Person* PA,int n)
{
    for (int i = 0; i < n; i++)
    {
        fprintf(fp, "%d %-20s %d %d %d\n", PA[i].serial_num, PA[i].full_name, PA[i].ptrDate->day, PA[i].ptrDate->month, PA[i].ptrDate->year);
    }
}

//prints an array
void print_Array(Person* PA,int size)
{
    printf("Current list:\n");
    printf("\n");
    for (int i = 0; i < size; i++)
    {
        printf("%d %-20s %d %d %d\n", PA[i].serial_num, PA[i].full_name, PA[i].ptrDate->day, PA[i].ptrDate->month, PA[i].ptrDate->year);
    }
}

//Frees PA and copies Person.txt into PA 
void copy_fromFile(FILE* fp, int *size, Person** PA)
{
    free(*PA);
    *PA = NULL;
    *size = 0;
    Person* ptr = (Person*)malloc(sizeof(Person));
    Date* dptr = (Date*)malloc(sizeof(Date));
        while (fscanf(fp, "%d %s %d %d %d", &ptr->serial_num, &ptr->full_name, &dptr->day, &dptr->month, &dptr->year)!=EOF)
        {
            if (ptr == NULL || dptr == NULL)exit(1);
            (*size)++;
            ptr->ptrDate = dptr;
            (*PA) = (Person*)realloc((*PA), sizeof(Person) * (*size));
            if ((*PA) != NULL)
            {
                (*PA)[*size - 1] = *ptr;
            }
            ptr = (Person*)malloc(sizeof(Person));
            dptr = (Date*)malloc(sizeof(Date));
        }
    }

//sort so youngest will be last
void sortBy_age(Person* PA, int size)
{
    int swaped=0;
    Person tmp;
    //Using bubblesort
    for (int i = 0; i < size-1; i++)
    {
        swaped = 0;
        for (int k = 0; k < size - 1 - i; k++)
        {
            //checks year
            if (PA[k].ptrDate->year > PA[k + 1].ptrDate->year)
            {
                tmp = PA[k];
                PA[k] = PA[k + 1];
                PA[k + 1] = tmp;
                swaped = 1;
            }
            //checks month
            else if (PA[k].ptrDate->year == PA[k + 1].ptrDate->year)
            {
                if (PA[k].ptrDate->month > PA[k + 1].ptrDate->month)
                {
                    tmp = PA[k];
                    PA[k] = PA[k + 1];
                    PA[k + 1] = tmp;
                    swaped = 1;
                }
                //checks day
                else if (PA[k].ptrDate->month == PA[k + 1].ptrDate->month)
                {
                    if (PA[k].ptrDate->day > PA[k + 1].ptrDate->day)
                    {
                        tmp = PA[k];
                        PA[k] = PA[k + 1];
                        PA[k + 1] = tmp;
                        swaped = 1;
                    }

                }
            }
        }
        if (!swaped) break;
    }
   print_Array(PA, size);
 
}