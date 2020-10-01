#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Soccer.h"
//funcs

headder head;
int fal;


PnodePTR findPlayer(long p_ID);
teamPtr findTeam(char name[]);

//do bubblesort shit tommrow

//Need to rebuild funcs. FUCK go over func func and fix it cause playernode and player are diffrent type of structs.
//find player fixed
//insert player fixed
//deletePlayerfromteam fixed
//delete player fixed
//findteam Fixed
//fixed insert team
//fixed Delete team
//fixed add Player Team
//fixed print teams in leauge
//fixed print players in leauge
//fixed print team info
//fixed print player
//fixed is player free


statusType insertPlayer(long playerID, char lastName[], char firstName[], int age)
{
    statusType status = SUCCESS;
    playerPtr p;
    PnodePTR q = findPlayer(playerID);
    q = findPlayer(playerID); 
    if (q)
    {
        status = FAILURE;
        return status;
    }
    p = (playerPtr)malloc(sizeof(playerRec));
   q = (Pnode*)malloc(sizeof(Pnode));
    p->plyrID = playerID;
    strcpy(p->firstName, firstName);
    strcpy(p->lastName, lastName); 
    p->age = age;
    q->tmptr = NULL;
    q->PL = *p;
    q->next = head.playerlist;
    head.playerlist = q;
    return status;
}
//find a player
PnodePTR findPlayer(long p_ID)
{
    PnodePTR q = head.playerlist;
    while (q)
    {
        if (q->PL.plyrID == p_ID) return q;
        q = q->next;
    }
    return NULL;
}


statusType deletePlayerFromTeam(long p_ID)
{
    PnodePTR p;
    teamPtr t;
    int i,k;
    statusType status = SUCCESS;
    p = findPlayer(p_ID);
    if (p == NULL || p->tmptr == NULL)  status=FAILURE;
    else 
    {
        t = p->tmptr;
        p->tmptr = NULL;
        for (i = 0; i < t->num; i++)
        {
            if (t->plarray[i]->plyrID == p_ID) k = i;  break;
        }
        for (i = k + 1; i < t->num; i++)
        {
            t->plarray[i - 1] = t->plarray[i];
        }
        t->num--;
        //pointer to a pointer
        t->plarray = (playerPtr*)realloc(t->plarray, sizeof(playerPtr) * t->num);
    }
    return status;
}


void deletePlayer(long p_ID)
{
    PnodePTR q;
    PnodePTR p;
    statusType status = SUCCESS;
    p = findPlayer(p_ID);
    if (p == NULL) status=  FAILURE ;
    else
    {
        if (p->tmptr) status = deletePlayerFromTeam(p_ID);
        q = head.playerlist;
        if (head.playerlist == p)
        {
            head.playerlist = q->next;
            free(p);
        }
        else
        {
            while (q->next)
            {
                if (q->next == p)
                {
                    q->next = p->next;
                    free(p);
                    break;
                }
                q = q->next;
            }
        }
    }
    if (status)printf("SUCCESS MANGED TO DELETE PLAYER\n");
    else printf("FAILURE\n");

}

teamPtr findTeam(char name[])
{
    teamPtr q = head.teamlist;
    while (q)
    {
        if (q->teamName == name) return q;
        q = q->next;
    }
    return NULL;
}

void insertTeam(char team_name[])
{
    teamPtr new_team;
    new_team = (teamRec*)malloc(sizeof(teamRec));
    teamPtr p = findTeam(team_name);
    if (p == NULL) printf("EROROR\n");
    else
    {
        strcpy(new_team->teamName, team_name);
        new_team->num = 0;
        new_team->plarray = NULL;
        p = head.teamlist;
        head.teamlist = new_team;
        head.teamlist->next = p;
        printf("SUCCESS\n");
    }
}



void deleteTeam(char name[])
{
    statusType status = SUCCESS;
    int i;
    long ID;
    teamPtr t, s;
    PnodePTR pl;
    t = findTeam(name);
    if (t == NULL) status = FAILURE;
    else
    {
        //if there are players lets delete them.
        if (t->plarray)
        {
            for (i = 0; i < t->num; i++)
            {
                ID = t->plarray[i]->plyrID;
                pl = findPlayer(ID);
                if (pl)pl->tmptr = NULL;
            }
            if (head.teamlist == t)
            {
                head.teamlist = t->next;
            }
            else
            {
                s = head.teamlist;
                while (s->next != t)
                {
                    s = s->next;
                }
                s->next = t->next;
            }
            free(t);
        }
    }
    if (status)printf("SUCCESS\n");
    else printf("FAILURE\n");
}

void addPlayertoTeam(long plyrID, char team[])
{
    playerPtr pll;
    statusType status = SUCCESS;
    PnodePTR p;
    teamPtr t;
    p = findPlayer(plyrID);
    t = findTeam(team);
    if ((p == NULL) || (t == NULL)) status = FAILURE;
    else if (!p->tmptr) status = FAILURE;
    else
    {
        p->tmptr = t;
        if (t->num == 0)
        {
            pll = &p->PL;
            t->plarray = (playerPtr*)realloc(t->plarray, sizeof(playerPtr));
            t->plarray[0] = pll;
        }
        else
        {
            pll = &p->PL;
            t->plarray = (playerPtr*)realloc(t->plarray, (t->num + 1) * sizeof(playerPtr));
            t->plarray[t->num] = pll;
            t->num++;
        }
    }
    if (status)printf("SUCCESS\n");
    else printf("FAILURE\n");
}

void printPlayersinLeague()
{
    PnodePTR p = head.playerlist;
    if (p == NULL)printf("No Players\n");
    else
    {
        printf("-----Player info in league----\n");
        while (p)
        {
            printf("ID: %d, ", p->PL.plyrID);
            printf("Name: %s, ", p->PL.firstName);
            printf("Family name: %s, ", p->PL.lastName);
            printf("Age: %d.\n", p->PL.age);
            p = p->next;
        }
    }
}

void printPlayer(playerPtr p)
{
    if (p == NULL)printf("ERROR PLAYER DOESNT EXSIST\n");
    else
    {
            printf("-----Player info----\n");
            printf("ID: %d, ", p->plyrID);
            printf("Name: %s, ", p->firstName);
            printf("Family name: %s, ", p->lastName);
            printf("Age: %d.\n", p->age);
    }
}



void printTeamsinLeague()
{
    teamPtr t=head.teamlist;
    if (t == NULL)printf("No Teams\n");
    else
    {
        printf("-----Teams in league----\n");
        while (t)
        {
            printf("Team name: %s\n", t->teamName);
            t = t->next;
        }
    }
}

void printTeaminfo(char team[])
{
    teamPtr t;
    t = findTeam(team);
    if (team == NULL) printf("ERROR\n");
    else
    {
        if (t->num)
        {
            printf("-----Player info on team----\n");
            for (int i = 0; i < t->num; i++)
            {
                printPlayer(t->plarray[i]);
            }
        }
        else printf("0\n");
    }
}



void isPlayerFree(long pID)
{
    PnodePTR p = findPlayer(pID);
    if (p == NULL)printf("ERROR\n");
    else
    {
        if (p->tmptr == NULL) printf("Player is free!\n");
        else
        {
            printf("Team name: %s\n", p->tmptr->teamName);
            printf("-----Player info on team----\n");
            printTeaminfo(p->tmptr->teamName);
        }

    }
}

void exit_Program()
{
    PnodePTR *q;
    teamPtr* d;
    PnodePTR p = head.playerlist;
    teamPtr t = head.teamlist;
    while (p)
    {
        q = &p;
        p = p->next;
        free(*q);
    }
    while (t)
    {
        d = &t;
        t = t->next;
        free(*d);
    }
    printf("BYE!!!!!\n");
    exit(1);
}