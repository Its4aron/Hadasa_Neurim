#pragma once
//Include to all the structs
#include "Header.h"

extern headder head;

typedef enum {
	FAILURE, SUCCESS, INVALID_INPUT,
	DUPLICATE_RECORD, MISSING_RECORD
} statusType;

typedef enum { FALSE, TRUE } booly;

//funcs
 void insertPlayer(long playerID, char lastName[], char firstName[], int age); //Insets player into the system

 PnodePTR findPlayer(long p_ID); // finds player and returns a pointer to current players node in list

 statusType deletePlayerFromTeam(long p_ID);//Deletes a player from a team

 void deletePlayer(long p_ID);//deletes a player from the system

 void printPlayersinLeague();//prints all players in the system

 void orderInTeamArray(char team[]);//orders a teamns array of players

 void insertTeam(char team_name[]);//adds a team to the system

 void printTeamsinLeague();//prints all the teams

 teamPtr findTeam(char name[]);//finds a team in team list and returns a pointer to it

 void sortTeamListBy_Names();//sorts team linked list using bubble sort by names

 void sortTeamListBy_Num();//sorts team linked list using bubble sort by amount of players

 void deleteTeam(char name[]);// deletes a player from the system

 void addPlayertoTeam(long plyrID, char team[]); // adds player to a team in linked list of teams

 void isPlayerFree(long pID);// checks if a player currently is in a team

 void printTeaminfo(char team[]);//prints info on a team (its players)

 char* CollectStringDynamic();//collects a string from the console and makes it a dynamic string

 void exit_Program();//exits the program and frees all memory


