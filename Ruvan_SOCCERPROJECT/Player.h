#pragma once

typedef struct playerType
{
    long plyrID;

    int age;

    char *firstName;

    char *lastName;

}playerRec, * playerPtr;

typedef struct PlayerNode
{
    playerRec PL;
    struct teamType* tmptr;
    struct PlayerNode* next;
}Pnode,*PnodePTR;


