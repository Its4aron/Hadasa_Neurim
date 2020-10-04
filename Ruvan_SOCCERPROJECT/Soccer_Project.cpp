#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Soccer.h"
#define TEAM_FILE "TEAM.DAT"
#define PLAYER_FILE "PLAYER.DAT"


void main()
{
	int op;
	printf("Select operation:\n");
	printf("1.Insert player\n2.Delete player\n3.Add team\n4.Delete team\n5.Add player to team\n6.Delete player from team\n");
	printf("7.Print all players\n8.Print all Teams\n9.Print team info\n10.Organize team's players by name\n11.Sort team linked list by names\n12.Sort team linked list by amount of playyers\n13.Check if player is free\n14.Exit program\n");
	scanf("%d", &op);
	while (1)
	{
		switch (op)
		{
		case 1:
		{
			system("@cls||clear");
			long playerID;  
			int age;
			printf("Enter ID =>  ");
			scanf("%ld", &playerID);
			printf("\n");
			printf("Enter first name => ");
			getchar();
			char* firstName = CollectStringDynamic();
			printf("\n");
			printf("Enter last name => ");
			char* lastName = CollectStringDynamic();
			printf("\n");
			printf("Enter age =>  ");
			scanf("%d", &age);
			printf("\n");
			insertPlayer(playerID, lastName, firstName, age);
			getchar();
			getchar();
			break;
		}
		case 2:
		{
			system("@cls||clear");
			long id=0;
			printf("Enter ID of player to delete => ");
			scanf("%ld", &id);
			printf("\n");
			deletePlayer(id);
			getchar();
			getchar();
			break;
		}
		case 3:
		{
			system("@cls||clear");
			printf("Enter team name => ");
			getchar();
			char* name = CollectStringDynamic();
			insertTeam(name);
			getchar();
			getchar();
			break;
		}
		case 4:
		{
			system("@cls||clear");
			printf("Enter team name to delete => ");
			char* name = CollectStringDynamic();
			deleteTeam(name);
			free(name);
			getchar();
			getchar();
			break;
		}
		case 5:
		{
			system("@cls||clear");
			long id = 0;
			system("@cls||clear");
			printf("Enter team name => ");
			char* name = CollectStringDynamic();
			printf("\n");
			printf("Enter player id =>  ");
			scanf("%ld", &id);
			printf("\n");
			addPlayertoTeam(id, name);
			free(name);
			getchar();
			getchar();
			break;
		}
		case 6:
		{
			system("@cls||clear");
			statusType s;
			long id = 0;
			printf("Enter player id =>  ");
			scanf("%ld", &id);
			printf("\n");
			deletePlayerFromTeam(id);
			getchar();
			getchar();
			break;

		}
		case 7:
		{
			system("@cls||clear");
			printPlayersinLeague();
			getchar();
			getchar();
			break;
		}
		case 8:
		{
			system("@cls||clear");
			printTeamsinLeague();
			getchar();
			getchar();
			break;
		}
		case 9:
		{
			//print info
		
			system("@cls||clear");
			printf("Enter team name => ");
			char* name = CollectStringDynamic();
			printf("\n");
			printTeaminfo(name);
			free(name);
			getchar();
			getchar();
			break;
		}
		case 10:
		{
		
			system("@cls||clear");
			printf("Enter team name to delete => ");
			char* name = CollectStringDynamic();
			orderInTeamArray(name);
			free(name);
			getchar();
			getchar();
			break;
		}
		case 11:
		{
			system("@cls||clear");
			sortTeamListBy_Names();
			getchar();
			getchar();
			break;
		}
		case 12:
		{
			system("@cls||clear");
			sortTeamListBy_Num();
			getchar();
			getchar();
			break;
		}
		case 13:
		{
			system("@cls||clear");
			long id = 0;
			printf("Enter player id =>  ");
			scanf("%ld", &id);
			printf("\n");
			isPlayerFree(id);
			getchar();
			getchar();
			break;
		}
		case 14:
		{
			system("@cls||clear");
			exit_Program();
			break;
		}
		default:
			break;
		}
		system("@cls||clear");
		printf("Select operation:\n");
		printf("1.Insert player\n2.Delete player\n3.Add team\n4.Delete team\n5.Add player to team\n6.Delete player from team\n");
		printf("7.Print all players\n8.Print all Teams\n9.Print team info\n10.Organize team's players by name\n11.Sort team linked list by names\n12.Sort team linked list by amount of playyers\n13.Check if player is free\n14.Exit program\n");
		scanf("%d", &op);
	}
	

	





}


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