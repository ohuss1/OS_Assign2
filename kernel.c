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
	int beg;
	int end;
	FILE *ptr=fopen(filename,"r");
	printf("file open");
	if(ptr==NULL){
		printf("filenotfound");
	}
	addToRAM(ptr,&beg,&end);
	//return 0;
}

