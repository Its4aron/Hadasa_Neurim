#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Soccer.h"
//funcs

headder head;


PnodePTR findPlayer(long p_ID);
teamPtr findTeam(char name[]);


//Adds player to linked list.
void insertPlayer(long playerID, char lastName[], char firstName[], int age)
{
    statusType status = SUCCESS;
    playerPtr p;
    PnodePTR q = findPlayer(playerID);
    q = findPlayer(playerID); 
    if (q)
    {
        status = FAILURE;
        printf("PLAYER ID EXSISTS\n");
    }
    else
    {
        p = (playerPtr)malloc(sizeof(playerRec));
        q = (Pnode*)malloc(sizeof(Pnode));
        p->plyrID = playerID;
        p->firstName = firstName;
        p->lastName = lastName;
        p->age = age;
        q->tmptr = NULL;
        q->PL = *p;
        q->next = head.playerlist;
        head.playerlist = q;
        printf("ADDED PLAYER: %ld\n", playerID);
    }
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

//Delete player from team
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

//Delete player from linked list
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
            free(p->PL.firstName);
            free(p->PL.lastName);
            free(p);
        }
        else
        {
            while (q->next)
            {
                if (q->next == p)
                {
                    q->next = p->next;
                    free(p->PL.firstName);
                    free(p->PL.lastName);
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
//Returns pointer to Team by name
teamPtr findTeam(char name[])
{
    teamPtr t = head.teamlist;
    while (t)
    {
        if (strcmp(t->teamName,name)==0) return t;
        t = t->next;
    }
    return NULL;
}
//Adds team to linked list of teams.
void insertTeam(char team_name[])
{
    teamPtr new_team;
    new_team = (teamRec*)malloc(sizeof(teamRec));
    teamPtr p = findTeam(team_name);
    if (p) printf("EROROR <--\n");
    else
    {
        strcpy(new_team->teamName, team_name);
        new_team->num = 0;
        new_team->plarray = NULL;
        p = head.teamlist;
        head.teamlist = new_team;
        if (p == NULL)
        {
            head.teamlist->next = NULL;
        }
        else head.teamlist->next = p;
        printf("SUCCESS\n");
    }
}


//Deletes team from linked list.
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
 
//Adds player to team.
void addPlayertoTeam(long plyrID, char team[])
{
    playerPtr pll;
    statusType status = SUCCESS;
    PnodePTR p;
    teamPtr t;
    p = findPlayer(plyrID);
    t = findTeam(team);
    if ((p == NULL) || (t == NULL)) status = FAILURE;
    else if (p->tmptr) status = FAILURE;
    else
    {
        p->tmptr = t;
        if (t->num == 0)
        {
            pll = &p->PL;
            t->plarray = (playerPtr*)realloc(t->plarray, sizeof(playerPtr));
            t->plarray[0] = pll;
            t->num++;
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
    if (t == NULL) printf("ERROR\n");
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


//Checks if a player is free or taken by a team.
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

//bubble sort.
void orderInTeamArray(char team[])
{
    playerPtr temp;
    teamPtr t = findTeam(team);
    if (t == NULL) printf("Error cant find team\n");
    else
    {
        int ar_len = t->num;
        for (int i = 0; i < ar_len - 1; i++)
        {
            for (int k = 0; k < ar_len - i - 1; k++)
            {
                if (strcmp(t->plarray[k]->firstName, t->plarray[k + 1]->firstName)>0)
                {
                    temp = t->plarray[k];
                    t->plarray[k] = t->plarray[k + 1];
                    t->plarray[k + 1] = temp;
                }
            }
        }
        printTeaminfo(team);
    }
}

//counts amount in list
int CountTeamList()
{
    teamPtr t = head.teamlist;
    int ctr=0;
    while (t)
    {
        ctr++;
        t = t->next;
    }
    return ctr;
}


//bubble sort in linked list.
void sortTeamListBy_Names()
{
        int i, j, swa;
        teamPtr temp,x,prev = head.teamlist;
        int count = CountTeamList();
        if (count) {
            for (i = 0; i < count; i++)
            {
                teamPtr t = head.teamlist;
                prev = t;
                swa = 0;
                for (j = 0; j < count - i-1; j++)
                {
                    x = t->next;
                    if (strcmp(t->teamName, x->teamName)>0)
                    {
                        if (t == head.teamlist)
                        {
                            temp = x->next;
                            head.teamlist = x;
                            head.teamlist->next = t;
                            t->next = temp;
                        }
                        else
                        {
                            temp = x->next;
                            x->next = t;
                            t->next = temp;
                            prev->next = x;
                        }
                        swa = 1;
                        prev = x;
                    }
                    if (!swa)
                    {
                        prev = t;
                        t = t->next;
                    }
                }
                if (!swa) break;
            }
        }
        else printf("ERROR NO TEAMS\n");
    }

//Bubble sort by amount of players in team from smallest to biggest
void sortTeamListBy_Num()
{
    int i, j, swa;
    teamPtr temp, x,prev = head.teamlist;
    int count = CountTeamList();
    if (count) {
        for (i = 0; i <= count; i++)
        {
            teamPtr t = head.teamlist;
            swa = 0;
            for (j = 0; j < count - i - 1; j++)
            {
                x = t->next;
                if (t->num > x->num)
                {
                    if (t == head.teamlist)
                    {
                        temp = x->next;
                        head.teamlist = x;
                        head.teamlist->next = t;
                        t->next = temp;
                    }
                    //x is the one thats being swapped
                    else
                    {
                        temp = x->next;
                        x->next = t;
                        t->next = temp;
                        prev->next = x;
                    }
                    swa = 1;
                    prev = x;
                }
                if (!swa)
                {
                    prev = t;
                    t = t->next;
                }
            }
            if (!swa) break;
        }
    }
    else printf("ERROR\n");
}
//Collects a string and puts it in dynamic 
char* CollectStringDynamic()
{
    char c;
    int n = 1;
    char* str = NULL;
    str = (char*)realloc(str, sizeof(char) * n + 1);
    c = getchar();
    str[n - 1] = c;
    while (c != '\n')
    {
        c = getchar();
        n++;
        str = (char*)realloc(str, sizeof(char) * n + 1);
        str[n - 1] = c;
        if (n == 50) break;
    }
    str[n - 1] = '\0';
    return str;
}

//exit
void exit_Program()
{
    PnodePTR p=head.playerlist;
    teamPtr t=head.teamlist;
    while (head.playerlist)
    {
        p = head.playerlist;
        head.playerlist = p->next;
        free(p);
    }
    while (head.teamlist)
    {
        t = head.teamlist;
        head.teamlist= t->next;
        free(t);
    }
    printf("BYE!!!!!\n");
    exit(1);
}