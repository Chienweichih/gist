/*
 * File name: main.c
 * Description: This is the main program to be used in the course project of Advanced Computer Networks, NTNU-CSIE, 2014
 *
 * Note that there is NO need to edit this program!!
 *
 * Author: Ling-Jyh Chen (cclljj@gmail.com)
 * Version: 2014/10/23
 */
#include <stdio.h>
#include <string.h>
#include "ACN.h"
/*===========================================*/
#include <time.h>
/*===========================================*/

FILE *fh;
int flag = 0;

int read_line(char *buf){
int len;
	if (flag==1) return 0;
	fgets(buf,1000,fh);
	len = strlen(buf);
	buf[len-1] = '\0';
	if (buf[0]=='@'){
		flag = 1;
		return 0;
	} else return 1;
}

int main(){
char buf[1001];
int value, len;
/*===========================================*/
        clock_t t1, t2;
        t1 = clock();
/*===========================================*/
	fh = fopen("input.txt","r");

	input();

	while (fgets(buf,1000,fh)){
		len = strlen(buf);
		buf[len-1] = '\0';
		value = lookup(buf);
		printf("%d\n",value);
	}

	fclose(fh);
/*===========================================*/
        free_node();
        t2 = clock();
        printf("%lf sec\n", (t2-t1)/(double)(CLOCKS_PER_SEC));
/*===========================================*/
	return 0;
}