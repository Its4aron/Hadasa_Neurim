#pragma once
//Include to all the structs
#include "Header.h"

extern headder head;
extern int fal;

typedef enum {
	FAILURE, SUCCESS, INVALID_INPUT,
	DUPLICATE_RECORD, MISSING_RECORD
} statusType;

typedef enum { FALSE, TRUE } booly;

//funcs
 statusType insertPlayer(long playerID, char lastName[], char firstName[], int age);
 PnodePTR findPlayer(long p_ID);
 statusType deletePlayerFromTeam(long p_ID);
 void deletePlayer(long p_ID);
 void printPlayersinLeague();
 void orderInTeamArray(char team[]);
 void insertTeam(char team_name[]);
 void printTeamsinLeague();
 teamPtr findTeam(char name[]);
 void sortTeamListBy_Names();
 void sortTeamListBy_Num();
 void exit_Program();


