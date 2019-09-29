#include "dictionary.h"
#include <stdlib.h>
#include <stdio.h>

void freenode(node *tobereleased) {
	if (tobereleased == NULL){
		return;
	}
	freenode(tobereleased->next);
	free(tobereleased);
}

int main(int argc, char *argv[]) {
	
	hashmap_t hashtable[HASH_SIZE];
	load_dictionary(argv[2], hashtable);
	FILE *fp = fopen(argv[1], "r");
	char *misspelled[MAX_MISSPELLED];
	if (fp == NULL) {printf("File pointer is NULL"); exit(1);}
	int num_misspelled = check_words(fp, hashtable, misspelled);
	printf("Test1.txt contains %d misspelled words.\n", num_misspelled);
	
	node* start = malloc(sizeof(node));

	for(int i = 0; i < HASH_SIZE; i++){
	start = hashtable[i];
	freenode(start);
	}
	
	return 1;
}
