/*
 * ram.c
 *
 *  Created on: Feb 24, 2020
 *      Author: Omar Yunus
 */
#include <stdio.h>
#include <string.h>
char buffer[1000];
char *ram[1000];
int c=0;
int firstAv;
int Slotavailable()
{
    for (int i = 0; i < 1000; i++)
    {
        if (!ram[i])
        {
            return i;
        }
    }
    return -1;
}
void addToRAM(FILE *p, int *start, int *end){
	//FILE *file = fopen(p, "r");
	printf("inaddtoRam");
	firstAv=Slotavailable();
	c=firstAv;
	*start=c;
	//int i=0;
	char buffer[1000];
	while(!feof(p)){
		if(c>999){
				printf("error out of ramspace");
				*start=-1;
				*end=-1;
				return;
			}
	fgets(buffer,999,p);
	if(strstr(ram[c],"NULL")!=NULL){
	ram[c] = strdup(buffer);
	printf("ram %d has %s",c,ram[c]);
	}
	else{
		continue;
	}

	c++;
	}
	*end=c;

}


