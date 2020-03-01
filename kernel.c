/*
 * kernel.c
 *
 *  Created on: Feb 22, 2020
 *      Author: Omar Yunus
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "shell.h"
#include "ram.h"

int main(int argc, const char *argv[]){
shellUI();
}
void myinit(char *filename){
	printf("in myinit\n");
	int beg;
	int end;
	FILE *ptr=fopen(filename,"r");
	if(ptr==NULL){
		printf("file not Found");
		return;
	}
	addToRAM(ptr,&beg,&end);
	//return 0;
}

