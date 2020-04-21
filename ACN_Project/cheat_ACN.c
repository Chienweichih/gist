/* * File name: ACN.c
 * Description: This is the sample submission codes for the course project of Advanced Computer Networks, NTNU-CSIE, 2014
 *
 * Author: Ling-Jyh Chen (cclljj@gmail.com)
 * Version: 2014/10/23
 */

#include <stdio.h>
#include <string.h>
#include "cheat_ACN.h"

#include "city.h"
#include "city.cc"
#include "citycrc.h"
#include "config.h"

struct Node* data_head = NULL;
struct Node* data_current = NULL;
struct Node* data_prev = NULL;

struct Node* magic_table[104729] = {NULL};

void input() {
char buf[1001];
int i;

	while (1){
		i = read_line(buf);

		/* end of the input data */
		if(i <= 0) {
			break;
		}

		/* there are input data available, and you may want to insert your codes here */

		data_current = (struct Node *)malloc(sizeof(struct Node));

		if(data_current == NULL)
			exit(EXIT_FAILURE);

		data_current->next = NULL;
		data_current->magic_pointer = NULL;

		//take token
		char* front = strtok(buf, " ");
		char* back = strtok (NULL, " ");

		//store data
		data_current->data = (char *)malloc((strlen(front)+1)*sizeof(char));
		strcpy(data_current->data, front);
		data_current->data[strlen(front)] = '\0';
		
		//value
		data_current->value = atoi(back);

		//magic
		int a = CityHash32(data_current->data, strlen(data_current->data)) % 104729;

		if(magic_table[a] == NULL) {
			magic_table[a] = data_current;
		}
		else {
			struct Node* ptr = magic_table[a];
			while(ptr->magic_pointer != NULL)
				ptr = ptr->magic_pointer;
			ptr->magic_pointer = data_current;
		}

		//chain linked list
		if(data_head == NULL)
			data_head = data_current;
		else
			data_prev->next = data_current;

		data_prev = data_current;
	}
}

int lookup(const char *url) {

	/* please insert your codes about data lookup here */

	char buf[1001];
	strncpy(buf,url,sizeof(buf));

	//magic
	int a = CityHash32(buf, strlen(buf)) % 104729;
	
	//Search
	struct Node* itor = magic_table[a];
	for( ; itor != NULL; itor = itor->magic_pointer)
		if(0 == strcmp(itor->data, buf))
			return itor->value;

	return -1;
}

void free_node() {
	struct Node* itor = data_head;
	while(itor != NULL) {
		struct Node* temp = itor;
		itor = itor->next;

		free(temp->data);
		free(temp);
	}
}