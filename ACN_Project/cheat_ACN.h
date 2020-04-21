/*
 * File name: ACN.h
 * Description: This is the header file to be used in the course project of Advanced Computer Networks, NTNU-CSIE, 2014
 *
 * Note that there is NO need to edit this program!!
 *
 * Author: Ling-Jyh Chen (cclljj@gmail.com)
 * Version: 2014/10/23
 */

#ifndef _ACN_H_
#define _ACN_H_

int read_line(char *buf);

void input();
int lookup(const char *url);
void free_node();

struct Node
{
	char* data;
	int value;

	struct Node* next;
	struct Node* magic_pointer;
};

#endif