#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

bool check_word(const char* word, hashmap_t hashtable[]) 
{ 
    //Set int bucket to the output of hash_function(word). 
	int bucket = hash_function(word);
    //Set hashmap_t cursor equal to hashmap[bucket].
	node* cursor = hashtable[bucket];	
    //While cursor is not NULL: 
	while(cursor != NULL){
        //If word equals cursor->word: 
		if(word == cursor->word) return 1;
	//return True. 
	//set curosr to cursor->next
		cursor = cursor->next;
	}
    //set int bucket to the outpush of hash_function(word)
	int lower_length = strlen(word);
	char lower_word[lower_length];
	for(int i = 0; i < lower_length; i++){
		lower_word[i] = tolower(word[i]);
	}
	bucket = hash_function(lower_word);
    //set hashmap_t cursor equal to hashmap [bucket]
    	cursor = hashtable[bucket];
    //while cursor is not NULL
	while(cursor != NULL){
    	//if lower_case(word) equals curosr->word: 
            //return True. 
		if(lower_word == cursor->word) return 1;
        //Set curosr to cursor->next. 
		cursor = cursor->next;
	}
	    	//return False. 
    return 0;
} 
 
bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[]) { 
//Initialize all values in hash table to NULL.
	printf("initializing hash table");
	for (int i = 0; i<HASH_SIZE; i++){
		   hashtable[i] = NULL;
		}	
	printf("hashtable initialized");
//Open dict_file from path stored in dictionary. 
	FILE* dict_file = fopen(dictionary_file, "r");
	printf("opened dict file");
	//If dict_file is NULL: 
//return false.
	if (dict_file == NULL){
		printf("Failed to open file.");
		return false;
	}
	//While word in dict_file is not EOF (end of file):
	char word[LENGTH+1];
	printf("created char word");
	//int bucketempty = 0;
	//int bucketoccupied = 0;
	while (fscanf(dict_file, "%s", word) > 0) {
//Set hashmap_t new_node to a new node.
		//printf("%s", word); THIS LOOKS FINE
		//printf("entered while loop");
		node* new_node = malloc(sizeof(node));
		//printf("created new node");
//Set new_node->next to NULL. 
		new_node->next = NULL;
		//printf("set new node next to null");
//Set new_node->word equal to word. 
		strncpy(new_node->word, word, LENGTH+1);
		//printf("%s", new_node->word); THIS LOOKS FINE
		//printf("copied word to new node");
//Set int bucket to hash_function(word). 
		int bucket = hash_function(new_node->word);
		//printf("%d", bucket);
		//printf("set nucket to hash of word");
//if hashtable[bucket] is NULL: 
		//printf("check if bucket is empty");
		if(hashtable[bucket] == NULL){		
//Set hashtable[bucket] to new_node. 
			//printf("bucket was empty");
			//bucketempty++;			
			hashtable[bucket] = new_node;
			//printf("put newnode in nucket");
			//printf("%s\n", hashtable[bucket]->word); THIS LOOKS FINE
		}		
//else: 
		else {
//Set new_node->next to hashtable[bucket]. 
			//printf("bucket was not empty");
			//bucketoccupied++;
			new_node->next = hashtable[bucket];
//Set hashtable[bucket] to new_node. 
			//printf("pointed newnode to existing node in nucket");
			hashtable[bucket] = new_node;
			//printf("set bucket to newnode");
		}
	//printf("while loop again");	
	}
	//Close dict_file. 
	printf("exited while loop");
	//printf("%d\n", bucketempty);
	//printf("%d\n", bucketoccupied);
 	fclose(dict_file);
	printf("closed dict file"); 
	return true;
}	
 
int check_words(FILE* fp, hashmap_t hashtable[], char * misspelled[]) 
{ 
    //Set int num_misspelled to 0. 
	int num_misspelled = 0;
	printf("one");
    //check if file pointer is valid	
	char* line;
	line = malloc(4096);
	if (line == NULL) {
		printf("char array not allocated");
		exit(1);
	}
	char* tmp;
	tmp = malloc((LENGTH+1)*sizeof(char));
	if (tmp == NULL) {
		printf("char array not allocated");
		exit(1);
	}
	char* word;
	word = malloc((LENGTH+1)*sizeof(char));
	if (word == NULL) {
		printf("char array not allocated");
		exit(1);
	}
	char* checkword;
	checkword = malloc((LENGTH+1)*sizeof(char));
	if (checkword == NULL) {
		printf("char array not allocated");
		exit(1);
	}
	int index = 0;
	printf("two");
	if (fp == NULL) {
		printf("File pointer is NULL");
		exit(1);
	}
	printf("three not null");
    //While line in fp is not EOF (end of file):
	while ((fgets(line, sizeof(*line), fp) != NULL)) {
		printf("entered fgets loop");
		//read the line
		////split the line on spaces
		if(line[strlen(line)-1]=='\n') line [strlen(line)-1]='\0';
        	tmp = strtok(line, " ");
		strcpy(word, tmp);
        	for(int i = 0; i<sizeof(word); i++){
        //For each word in line: 
            //Remove punctuation from beginning and end of word. 
	    		if((!(isalpha(word[i])) && index == 0) || (!(isalpha(word[i])) && (word[i+1] == ' '))){
			}
			else if(word[i] == ' '){
				checkword[i] = '\0';
				index = 0;
				if(!check_word(checkword, hashtable)){
					misspelled[num_misspelled] = word;
					num_misspelled++;
				}
			}
			else {
				checkword[index] = word[i];
				index++;
			}
		}
	}
            //If not check_word(word): 
                //Append word to misspelled. 
                //Increment num_misspelled. 
    //Return num_misspelled. 
    return num_misspelled;
}
