#pragma once
#include "Soccer.h"
typedef struct teamType
{
    char teamName[20];

    int num;

    playerPtr* plarray;

    struct teamType* next;

}teamRec, *teamPtr;