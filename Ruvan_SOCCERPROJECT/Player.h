#pragma once

typedef struct playerType
{
    long plyrID;

    int age;

    char firstName[15];

    char lastName[20];


}playerRec, * playerPtr;

typedef struct PlayerNode
{
    playerRec PL;
    struct teamType* tmptr;
    struct PlayerNode* next;
}Pnode,*PnodePTR;


