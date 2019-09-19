#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

bool check_word(const char* word, hashmap_t hashtable[]) 
{ 
    //Set int bucket to the output of hash_function(word).
    	//printf("%s ", word); 
	int bucket = hash_function(word);
    //Set hashmap_t cursor equal to hashmap[bucket].
	node* cursor = hashtable[bucket];	
    //While cursor is not NULL: 
	while(cursor != NULL){
        //If word equals cursor->word: 
		if((strcmp(word, cursor->word)) == 0) return true;
	//return True. 
	//set curosr to cursor->next
		cursor = cursor->next;
	}
    //set int bucket to the outpush of hash_function(word)
	int lower_length = strlen(word)+1;
	char lower_word[lower_length];
	for(int i = 0; i < lower_length; i++){
		lower_word[i] = tolower(word[i]);
	}
	//printf("lower word is: %s\n", lower_word);
	bucket = hash_function(lower_word);
    //set hashmap_t cursor equal to hashmap [bucket]
    	cursor = hashtable[bucket];
    //while cursor is not NULL
	while(cursor != NULL){
    	//if lower_case(word) equals curosr->word: 
            //return True. 
		if((strcmp(lower_word, cursor->word)) == 0) return true;
        //Set curosr to cursor->next. 
		cursor = cursor->next;
	}
	    	//return False. 
    return 0;
} 
 
bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[]) { 
//Initialize all values in hash table to NULL.
	//printf("initializing hash table\n");
	for (int i = 0; i<HASH_SIZE; i++){
		   hashtable[i] = NULL;
		}	
	//printf("hashtable initialized\n");
//Open dict_file from path stored in dictionary. 
	FILE* dict_file = fopen(dictionary_file, "r");
	//printf("opened dict file\n");
	//If dict_file is NULL: 
//return false.
	if (dict_file == NULL){
		printf("Failed to open file.\n");
		return false;
	}
	//While word in dict_file is not EOF (end of file):
	char word[LENGTH+1];
	//printf("created char word\n");
	//int bucketempty = 0;
	//int bucketoccupied = 0;
	while (fscanf(dict_file, "%45s", word) > 0) {
//Set hashmap_t new_node to a new node.
		//printf("%s\n", word); THIS LOOKS FINE
		//printf("entered while loop\n");
		node* new_node = malloc(sizeof(node));
		//printf("created new node\n");
//Set new_node->next to NULL. 
		new_node->next = NULL;
		//printf("set new node next to null\n");
//Set new_node->word equal to word. 
		strncpy(new_node->word, word, LENGTH+1);
		//printf("%s\n", new_node->word); THIS LOOKS FINE
		//printf("copied word to new node\n");
//Set int bucket to hash_function(word). 
		int bucket = hash_function(new_node->word);
		//printf("%d\n", bucket);
		//printf("set nucket to hash of word\n");
//if hashtable[bucket] is NULL: 
		//printf("check if bucket is empty\n");
		if(hashtable[bucket] == NULL){		
//Set hashtable[bucket] to new_node. 
			//printf("bucket was empty\n");
			//bucketempty++;			
			hashtable[bucket] = new_node;
			//printf("put newnode in nucket\n");
			//printf("%s\n", hashtable[bucket]->word); THIS LOOKS FINE
		}		
//else: 
		else {
//Set new_node->next to hashtable[bucket]. 
			//printf("bucket was not empty\n");
			//bucketoccupied++;
			new_node->next = hashtable[bucket];
//Set hashtable[bucket] to new_node. 
			//printf("pointed newnode to existing node in nucket\n");
			hashtable[bucket] = new_node;
			//printf("set bucket to newnode\n");
		}
	//printf("while loop again\n");	
	}
	//Close dict_file. 
	//printf("exited while loop\n");
	//printf("%d\n", bucketempty);
	//printf("%d\n", bucketoccupied);
 	fclose(dict_file);
	//printf("closed dict file\n"); 
	return true;
}	
 
int check_words(FILE* fp, hashmap_t hashtable[], char * misspelled[]) 
{ 
	//printf("start check words\n");
	//Set int num_misspelled to 0. 
	int num_misspelled = 0;
	char modword[LENGTH+1];
	char end[] = "\0";
	//printf("one\n");
    //check if file pointer is valid	
	char* line;
	line = malloc(4096);
	if (line == NULL) {
		printf("char array not allocated\n");
		exit(1);
	}
	char* tmp;
	tmp = malloc((LENGTH+1)*sizeof(char));
	if (tmp == NULL) {
		printf("char array not allocated\n");
		exit(1);
	}
	char* word;
	word = malloc((LENGTH+1)*sizeof(char));
	if (word == NULL) {
		printf("char array not allocated\n");
		exit(1);
	}
	/*char* checkword;
	checkword = malloc((LENGTH+1)*sizeof(char));
	if (checkword == NULL) {
		printf("char array not allocated\n");
		exit(1);
	}
	int index = 0;
	printf("two");*/
	if (fp == NULL) {
		printf("File pointer is NULL\n");
		exit(1);
	}
	//printf("three not null\n");
    //While line in fp is not EOF (end of file):
	while ((fgets(line, 4096, fp) != NULL)) {
		//printf("entered fgets loop\n");
		//read the line
		////split the line on spaces
	// assume there exists a char * tmp and a char * word.
	if (line == NULL) {printf("Pointer not allocated.\n"); exit(1);} 
	word = strtok(line, " ");
	while(word != NULL) // explicitly, but you could also do while(word)
	{
    	// here you do some transformations on the word, such as removing punctuation and newlines. Code isn't included so as to not give away too much of the answ
		strncpy(modword, word, strlen(word)+1);
		//printf("%s\n", word);
		//printf("%s\n", modword);
		if(!(isalpha(modword[0]))){
			for(int i = 0; i < (strlen(word)+1); i++){
				modword[i] = modword[i+1];
			}
		}
		//printf("%d\n", (strlen(word)+1));
		if(!(isalpha(modword[strlen(word)-1]))) modword[strlen(word)-1] = end[0];
		for (int i = strlen(word)-2; i < strlen(word)+1; i++) {
			if (modword[i] == '.') modword[i] = end[0];
		}
	       	//If not check_word(word)
		//printf("modword is now %s\n", modword);
		//strncpy(word, modword, strlen(word)+1); 
		//printf("word after strncpy is %s\n", word);
    		if(!check_word(modword, hashtable))
    		{
        	// here is more code. Again, omitted to not give away too much of the answer.
                //Append word to misspelled. 
		misspelled[num_misspelled] = malloc(strlen(word)+1);	
		strncpy(misspelled[num_misspelled], modword, strlen(word)+1);
		//printf("misspelled array is %s\n", misspelled[num_misspelled]);
                //Increment num_misspelled.
		num_misspelled++;
		//printf("misspelled count is %d\n", num_misspelled);
    		}
    		word = strtok(NULL, " "); // this will continue parsing the same string (see manual for strtok, first paragraph under description http://man7.org/linux/man-pages/man3/strtok.3.html)
	} 
}
    //Return num_misspelled. 
    return num_misspelled;
}
