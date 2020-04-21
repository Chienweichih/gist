/* * File name: ACN.c
 * Description: This is the sample submission codes for the course project of Advanced Computer Networks, NTNU-CSIE, 2014
 *
 * Author: Ling-Jyh Chen (cclljj@gmail.com)
 * Version: 2014/10/23
 */

#include <stdio.h>
#include <string.h>
#include "ACN.h"

#include "city.h"
#include "city.cc"
#include "citycrc.h"
#include "config.h"

struct Node* data_head = NULL;
struct Node* data_current = NULL;
struct Node* data_prev = NULL;

struct Node* magic_table[997][997][10] = {NULL};

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
		data_current->token = 0;

		//take token
		char* front = strtok(buf, " ");
		char* back = strtok (NULL, " ");
		
		//value
		data_current->value = atoi(back);

		//count front token
		char * temp_buf[100];

		char *pch = strtok(front , "/");
		while (pch != NULL)
		{
			temp_buf[data_current->token] = pch;
			++data_current->token;
			pch = strtok (NULL, "/");
		}

		//store data
		data_current->data = (char **)malloc(data_current->token*sizeof(char *));

		int token_count = 0;
		for(token_count = 0; token_count < data_current->token; ++token_count)
		{
			data_current->data[token_count] =
						(char *)malloc((strlen(temp_buf[token_count])+1)*sizeof(char));

			strcpy(data_current->data[token_count], temp_buf[token_count]);

			data_current->data[token_count][strlen(temp_buf[token_count])] = '\0';
		}

		//magic
		int a = (CityHash32(data_current->data[1%data_current->token],
					strlen(data_current->data[1%data_current->token])) % 997);
		int b = (CityHash32(data_current->data[3%data_current->token],
					strlen(data_current->data[3%data_current->token])) % 997);

		int j = 0;
		j = data_current->token;
		if(j > 9) j = 10;
		if(magic_table[a][b][j-1] == NULL) {
			magic_table[a][b][j-1] = data_current;
		}
		else {
			struct Node* ptr = magic_table[a][b][j-1];
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

int lookup(const char *url){

	/* please insert your codes about data lookup here */

	char buf[1001];
	strncpy(buf,url,sizeof(buf));

	//pre operate url
	int token_count = 0;
	char * temp_buf[100];

	char *pch = strtok(buf, "/");
	while (pch != NULL)
	{
		temp_buf[token_count] = pch;
		++token_count;
		pch = strtok (NULL, "/");
	}

	//magic
	int a = (CityHash32(temp_buf[1%token_count], strlen(temp_buf[1%token_count])) % 997);
	int b = (CityHash32(temp_buf[3%token_count], strlen(temp_buf[3%token_count])) % 997);

	int j = token_count;
	if(j > 9) j = 10;

	//Search
	struct Node* itor = magic_table[a][b][j-1];
	for( ; itor != NULL; itor = itor->magic_pointer)
	{
		if(j != itor->token)
			continue;
		
		int i = 0;
		for(; i < itor->token; ++i)
		{
			if(0 != strcmp(itor->data[i], temp_buf[i]))
				break;
		}

		if(i == itor->token)
			return itor->value;
	}

	return -1;
}

void free_node()
{
	struct Node* itor = data_head;
	while(itor != NULL) {
		struct Node* temp = itor;
		itor = itor->next;

		int i;
		for(i = 0; i < temp->token; ++i)
			free(temp->data[i]);
		free(temp->data);

		free(temp);
	}
}