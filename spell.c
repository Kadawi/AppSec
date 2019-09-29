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
		if((strcmp(word, cursor->word)) == 0) {
			//free(cursor);
			return true;}
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
	//int bucketempty = 0;
	//int bucketoccupied = 0;
	while (fscanf(dict_file, "%45s", word) > 0) {
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
	return true;
}	
 
int check_words(FILE* fp, hashmap_t hashtable[], char * misspelled[]) 
{ 
	//Set int num_misspelled to 0. 
	int num_misspelled = 0;
	char modword[LENGTH+1];
	char end[] = "\0";
    //check if file pointer is valid	
	char* line;
	line = malloc(8192);
	if (line == NULL) {
		printf("Line not allocated\n");
		exit(1);
	}
	char* tmp;
	tmp = malloc((LENGTH+1)*sizeof(char));
	if (tmp == NULL) {
		printf("Tmp not allocated\n");
		exit(1);
	}
	char* word;
	word = malloc((LENGTH+1)*sizeof(char));
	if (word == NULL) {
		printf("Word not allocated\n");
		exit(1);
	}
	if (fp == NULL) {
		printf("File pointer is NULL\n");
		exit(1);
	}
    //While line in fp is not EOF (end of file):
	while ((fgets(line, 8192, fp) != NULL)) {
		//read the line
		////split the line on spaces
	// assume there exists a char * tmp and a char * word.
	if (line == NULL) {printf("Pointer not allocated.\n"); exit(1);} 
	word = strtok(line, " ");
	int number = 0;
	while(word != NULL) // explicitly, but you could also do while(word)
	{
    	// here you do some transformations on the word, such as removing punctuation and newlines. Code isn't included so as to not give away too much of the answ
		//throw away any words longer than length
		if(strlen(word) > (LENGTH+1)) {
			word = strtok(NULL, " ");
		continue;}
		//copy contents to char array
		strncpy(modword, word, strlen(word)+1);
		//check for all numeric characters
		number = 0;
		for(int n=0; n < (strlen(word)+1); n++){
			if(modword[n] == 10) {word = strtok(NULL, " "); number = 1; break;}
			if(n == strlen(word)) {word = strtok(NULL, " "); number = 1; break;}
			else if(isdigit(modword[n])) {continue;}
			else if(!isdigit(modword[n])) {break;}
		}
		if (number == 1) continue;
		//check if first character is punctuation
		if(!(isalpha(modword[0]))){
			for(int i = 0; i < (strlen(word)+1); i++){
				modword[i] = modword[i+1];
			}
		}
		//replace any ending punctuation with null char
		if(!(isalpha(modword[strlen(word)-1]))) modword[strlen(word)-1] = end[0];
		for (int i = strlen(word)-2; i < strlen(word)+1; i++) {
			if (modword[i] == '.') modword[i] = end[0];
		}
	       	//If not check_word(word)
    		if(!check_word(modword, hashtable))
    		{
                //Append word to misspelled. 
		misspelled[num_misspelled] = malloc(strlen(modword)+1);	
		strncpy(misspelled[num_misspelled], modword, strlen(modword)+1);
                //Increment num_misspelled.
		num_misspelled++;
		//printf("misspelled word is %s\n", misspelled[num_misspelled-1]);
		//printf("num_misspelled is %d\n", num_misspelled);
    		}
    		word = strtok(NULL, " "); // this will continue parsing the same string (see manual for strtok, first paragraph under description http://man7.org/linux/man-pages/man3/strtok.3.html)
	} 
}
    //Return num_misspelled. 
    free(line);
    free(tmp);
    free(word);
    fclose(fp);
    //Cannot free misspelled[] in this function, because it is needed for comparison in tests
    return num_misspelled;
}
