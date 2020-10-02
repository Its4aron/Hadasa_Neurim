#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Soccer.h"
#define TEAM_FILE "TEAM.DAT"
#define PLAYER_FILE "PLAYER.DAT"


void main()
{
    /*FILE* player_file = fopen(PLAYER_FILE, "w+b");
	
    char firstName[15] = {'\0'};
    char lastName[20] = { '\0' };
	
	playerRec d;
	for (int i = 0; i < 5 ; i++)
	{
		printf("Enter ID:\n");
		scanf("%ld", &d.plyrID);
  
		printf("Enter age:\n");
		scanf("%d", &d.age);

		printf("Enter NAME:\n");
        scanf("%s", firstName);

        strcpy(d.firstName, firstName);
		printf("Enter last Name:\n");

        scanf("%s", lastName);
        strcpy(d.lastName, lastName);
		
		fwrite(&d, sizeof(playerRec), 1, player_file);
	}
	fclose(player_file);
	player_file = fopen(PLAYER_FILE, "rb");
	while (!feof(player_file))
	{
		fread(&d, sizeof(playerRec), 1, player_file);
		printf("%s <-----\n", d.lastName);
	}
	fclose(player_file);*/
	char name[]="MEOW";
	insertTeam(name);
	//printTeamsinLeague();
	/*teamPtr q = findTeam(name);*/
	//printf("ttt %s\n", head.teamlist->teamName);
	orderInTeamArray(name);
}
