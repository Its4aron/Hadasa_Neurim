#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <string>




char* CollectString();
void main()
{
	printf("\n enter id of player you want to search\n");
	char* firstName = CollectString();
	printf(" %s", firstName);

}



char* CollectString()
{
	char c;
	int n = 1;
	char* str=NULL;
	str = (char*)realloc(str, sizeof(char) * n+1);
	c = getchar();
	str[n - 1] = c;
	while (c != '\n')
	{
		c = getchar();
		n++;
		str = (char*)realloc(str, sizeof(char) * n+1);
		str[n - 1] = c;
	}
	str[n - 1] = '\0';
	return str;
}