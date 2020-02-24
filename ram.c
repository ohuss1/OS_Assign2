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
void addToRAM(FILE *p, int *start, int *end){
	//FILE *file = fopen(p, "r");
	*start=c;
	//int i=0;
	while(!feof){
	char buffer[1000];
	fgets(buffer,999,p);
	ram[c] = strdup(buffer);
	c++;
	}
	*end=c;

}


