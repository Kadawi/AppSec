#include "dictionary.h"
#include <stdlib.h>
#include <stdio.h>

#define DICTIONARY "wordlist.txt"

void freenode(node *tobereleased) {
	if (tobereleased == NULL){
		return;
	}
	freenode(tobereleased->next);
	free(tobereleased);
}

int main(void) {
	
	hashmap_t hashtable[HASH_SIZE];
	load_dictionary(DICTIONARY, hashtable);
	FILE *fp = fopen("test1.txt", "r");
	char *misspelled[MAX_MISSPELLED];
	if (fp == NULL) {printf("File pointer is NULL"); exit(1);}
	int num_misspelled = check_words(fp, hashtable, misspelled);
	printf("Test1.txt contains %d misspelled words.\n", num_misspelled);
	
	node* start = malloc(sizeof(node));

	for(int i = 0; i < HASH_SIZE; i++){
	start = hashtable[i];
	freenode(start);
	}

	//free(start->next);	

	//free(hashtable);
	fclose(fp);
//	free(misspelled);
	
	return 1;
}
