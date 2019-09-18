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
	for (int i = 0; i<HASH_SIZE; i++){
		   hashtable[i] = NULL;
		}	
//Open dict_file from path stored in dictionary. 
	FILE *dict_file = fopen(dictionary_file, "r");

	if (dict_file == NULL) {
		printf("Failed to open file.");
		return -1;
		}
//If dict_file is NULL: 
//return false.
	if (dict_file == NULL){
		printf("Failed to open file.");
		return 0;
	}
//While word in dict_file is not EOF (end of file):
	char word[LENGTH+1];
	while (fscanf(dict_file, "%s", word) > 0) {
//Set hashmap_t new_node to a new node.
		node* new_node = malloc(sizeof(node));
//Set new_node->next to NULL. 
		new_node->next = NULL;
//Set new_node->word equal to word. 
		strncpy(new_node->word, word, LENGTH+1);
//Set int bucket to hash_function(word). 
		int bucket = hash_function(new_node->word);
//if hashtable[bucket] is NULL: 
		if(hashtable[bucket] == NULL){		
//Set hashtable[bucket] to new_node. 
			hashtable[bucket] = new_node;
		}		
//else: 
		else {
//Set new_node->next to hashtable[bucket]. 
			new_node->next = hashtable[bucket];
//Set hashtable[bucket] to new_node. 
			hashtable[bucket] = new_node;
		}	
	}
	//Close dict_file. 
 	fclose(dict_file);
	return 1;
}	
 
int check_words(FILE* fp, hashmap_t hashtable[], char * misspelled[]) 
{ 
    //Set int num_misspelled to 0. 
	int num_misspelled = 0;
    //check if file pointer is valid
	if (fp == NULL) {
		printf("File pointer is null");
		exit(1);
	}		
	char* line_buffer[4096];
	char* word[LENGTH+1];
	int index = 0;	
    //While line in fp is not EOF (end of file):
	while ((fgets(*line_buffer, sizeof(line_buffer), fp) != NULL)) {
        //Read the line. 
        //Split the line on spaces. 
		for(int i = 0; i<sizeof(line_buffer); i++){
        //For each word in line: 
            //Remove punctuation from beginning and end of word. 
	    		if((!(isalpha(*line_buffer[i])) && index == 0) || (!(isalpha(*line_buffer[i])) && (*line_buffer[i+1] == ' '))){
			}
			else if(*line_buffer[i] == ' '){
				*word[index] = '\0';
				index = 0;
				if(!check_word(*word, hashtable)){
					misspelled[num_misspelled] = *word;
					num_misspelled++;
				}
			}
			else {
				*word[index] = *line_buffer[i];
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
