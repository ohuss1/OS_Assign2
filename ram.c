/*
 * ram.c
 *
 *  Created on: Feb 24, 2020
 *      Author: Omar Yunus
 */
#include <stdio.h>
#include <string.h>
char buffer[1000];
int ram_size=1000;
char *ram[1000];
int c=0;
void clearRam()
{
    for (int i = 0; i < ram_size; i++)
    {
    	ram[i]=NULL;

    }
}
void addToRAM(FILE *p, int *start, int *end){
	//FILE *file = fopen(p, "r");
	*start=c;
	printf("inaddtoRam\n");
	//int i=0;
	while(!feof(p)){
	char buffer[1000];
	fgets(buffer,999,p);
	ram[c] = strdup(buffer);
	printf("ram %d has %s",c,ram[c]);
	if(c==33){
		memset(buffer, '\0', 999);
		clearRam();
		c=0;
		*start=c;
		*end=c;
		printf("Ram outof space");
		break;
	}
	c++;
	}
	*end=c;

}


