#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "project3.h"


void main()
{
    //Names of all the ppl
    const char* names[] = { "Sasson_Sassoni","Pooh","James_Bond","Elvis_is_Alive!","Shilgiya","Cleopatra","Sissoo_VeSimmhoo" };
    //Matrix of dates of birth
    const int dates[MAX][COLS] =
    {
        {10,1,1988},
        {12,12,1948},
        {4,12,1970},
        {11,11,1890},
        {11,11,1948},
        {12,11,1948}
    };
    //The file name 

    const char* f_name = "Person.txt";

    //new list.
    Person* PArray = NULL;
    //amount of ppl in the new list;
    int n = 0;
    char choice;
    printf("Choose\n");
    scanf("%c", &choice);
    getchar();
    while (1)
    {
        switch (choice)
        {
        case '1':
        {
            PArray = add_Person(n + 1, PArray, names[n], dates[n]);
            n++;
            break;
        }
        case '2':
        {
            print_Array(PArray, n);
            break;
        }
        case '3':
        {
            sortBy_age(PArray, n);
            break;
        }
        case '4':

        {
            FILE* fp = fopen(f_name, "w");
            save_File(fp, PArray, n);
            fclose(fp);
            break;
        }
        
        case '5':
        {
            FILE* fp = fopen(f_name, "r");
            copy_fromFile(fp, &n, &PArray);
            fclose(fp);
            break;
        }
        case 'e':
        {
            exit(1);
            break;
        }
        case 'E':
        {
            exit(1);
            break;
        }
       
        default:
            break;
        }
        printf("Choose\n");
        scanf("%c", &choice);
        getchar();
    }


}