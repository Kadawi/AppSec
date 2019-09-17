#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

bool check_word(const char* word, hashmap_t hashtable[]) 
{ 
    //Set int bucket to the output of hash_function(word). 
    //Set hashmap_t cursor equal to hashmap[bucket]. 
    //While cursor is not NULL: 
        //If word equals cursor->word: 
            //return True. 
        //Else if lower_case(word) equals curosr->word: 
            //return True. 
        //Set curosr to cursor->next. 
    //return False. 
    return 1;
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
    //While line in fp is not EOF (end of file): 
        //Read the line. 
        //Split the line on spaces. 
        //For each word in line: 
            //Remove punctuation from beginning and end of word. 
            //If not check_word(word): 
                //Append word to misspelled. 
                //Increment num_misspelled. 
    //Return num_misspelled. 
    return 1;
}
