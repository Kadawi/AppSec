#include <check.h>
#include "dictionary.h"
#include <stdlib.h>
#include <stdio.h>

#define DICTIONARY "wordlist.txt"
#define TESTDICT "test_worlist.txt"

void freenode(node *tobereleased) {
	if (tobereleased == NULL){
		return;
	}
	freenode(tobereleased->next);
	free(tobereleased);
}	


START_TEST(test_dictionary_normal)
{
    hashmap_t hashtable[HASH_SIZE];
    ck_assert(load_dictionary(TESTDICT, hashtable));
    const char* first = "first";
    const char* second = "second";
    const char* third = "third";
    const char* test = "test";
    ck_assert(strcmp(hashtable[(hash_function(first))]->word, first) == 0); 
    ck_assert(strcmp(hashtable[(hash_function(second))]->word, second) == 0); 
    ck_assert(strcmp(hashtable[(hash_function(third))]->word, third) == 0); 
    ck_assert(strcmp(hashtable[(hash_function(test))]->word, test) == 0); 
    // Here we can test if certain words ended up in certain buckets
    // to ensure that our load_dictionary works as intended. I leave
    // this as an exercise.
    node* start = malloc(sizeof(node));
    for(int h = 0; h < HASH_SIZE; h++){
	    start = hashtable[h];
	    freenode(start);
    }
}
END_TEST


START_TEST(test_check_word_buffer_overflow){
	hashmap_t hashtable[HASH_SIZE];
	load_dictionary(DICTIONARY, hashtable);
	char incorrect_word[500000];
	for (int i = 0; i<499999; i++) incorrect_word[i] = 'A';
	incorrect_word[499999] = '\0';
	ck_assert(!check_word(incorrect_word, hashtable));
    node* start = malloc(sizeof(node));
    for(int h = 0; h < HASH_SIZE; h++){
	    start = hashtable[h];
	    freenode(start);
    }
}
END_TEST

START_TEST(test_check_word_normal)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    const char* correct_word = "Justice";
    const char* punctuation_word_2 = "pl.ace";
    const char* question_word = "?question?";
    ck_assert(check_word(correct_word, hashtable));
    ck_assert(!check_word(punctuation_word_2, hashtable));
    //logically, asserting the this is incorrect. Words never begin with a question mark. Can change if need be.  
    // Test here: What if a word begins and ends with "?
    ck_assert(!check_word(question_word, hashtable));
    node* start = malloc(sizeof(node));
    for(int h = 0; h < HASH_SIZE; h++){
	    start = hashtable[h];
	    freenode(start);
    }
}
END_TEST

START_TEST(test_check_words_foreign)
{
	hashmap_t hashtable[HASH_SIZE];
	load_dictionary(DICTIONARY, hashtable);
	char *misspelled[MAX_MISSPELLED];
	FILE *fp = fopen("arabic.txt", "r");
	if (fp == NULL) {printf("pointer is NULL"); exit(1);}
	int num_misspelled = check_words(fp, hashtable, misspelled);
	//Non-English words considered misspelled. Cannot be counted as spelled correctly with no dictionary for comparison.
	ck_assert(num_misspelled == 2);
	for (int i = 0; i < num_misspelled; i++){
		free(misspelled[i]);
	}
}
END_TEST

START_TEST(test_check_words_number)
{
	hashmap_t hashtable[HASH_SIZE];
	load_dictionary(DICTIONARY, hashtable);
	char *misspelled[MAX_MISSPELLED];
	FILE *fp = fopen("numbers.txt", "r");
	if (fp == NULL) {printf("pointer is NULL"); exit(1);}
	int num_misspelled = check_words(fp, hashtable, misspelled);
	//Should be no misspelled words. "Words" consisting of all numeric characters are correct.
	ck_assert(num_misspelled == 0);
	for (int i = 0; i < num_misspelled; i++){
		free(misspelled[i]);
	}
}
END_TEST


START_TEST(test_check_words_long)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    char *misspelled[MAX_MISSPELLED];
    FILE *fp = fopen("LongInput.txt", "r");
    if (fp == NULL) {printf("pointer is null\n"); exit(1);}
    int num_misspelled = check_words(fp, hashtable, misspelled);
    ck_assert(num_misspelled == 0);
    //The code after this point in this test was causing a double free error, and signal 6. 
    //node* start = malloc(sizeof(node));
    //for(int h = 0; h < HASH_SIZE; h++){
	//    start = hashtable[h];
	  //  freenode(start);
    //}
    for (int l = 0; l < num_misspelled; l++){
    free(misspelled[l]);
    }
    //fclose(fp);
}
END_TEST

START_TEST(test_check_words_normal)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    char* expected[3];
    expected[0] = "sogn";
    expected[1] = "skyn";
    expected[2] = "betta";
    char *misspelled[MAX_MISSPELLED];
    FILE *fp = fopen("test1.txt", "r");
    if (fp == NULL) {printf("pointer is null\n"); exit(1);}
    int num_misspelled = check_words(fp, hashtable, misspelled);
    ck_assert(num_misspelled == 3);
    bool test = strlen(misspelled[0]) == strlen(expected[0]);
    int len1 = strlen(misspelled[0]);
    int len2 = strlen(expected[0]);
    ck_assert_msg(test, "%d!=%d", len1, len2);
    ck_assert_msg(strcmp(misspelled[0], expected[0]) == 0);
    ck_assert_msg(strcmp(misspelled[1], expected[1]) == 0);
    ck_assert_msg(strcmp(misspelled[2], expected[2]) == 0);
    //for (int i = 0; i < 3; i++){
    //free(expected[i]);
    //}
    node* start = malloc(sizeof(node));
    for(int h = 0; h < HASH_SIZE; h++){
	    start = hashtable[h];
	    freenode(start);
    }
    //for(int m=0; m<num_misspelled; m++){
//	   free(misspelled[m]);
//	  }
    //fclose(fp);
}
END_TEST

Suite *
check_word_suite(void)
{
    Suite * suite;
    TCase * check_word_case;
    suite = suite_create("check_word");
    check_word_case = tcase_create("Core");
    tcase_add_test(check_word_case, test_check_word_normal);
    tcase_add_test(check_word_case, test_check_words_normal);
    tcase_add_test(check_word_case, test_check_words_number);
    tcase_add_test(check_word_case, test_check_words_long);
    tcase_add_test(check_word_case, test_check_words_foreign);
    tcase_add_test(check_word_case, test_dictionary_normal);
    tcase_add_test(check_word_case, test_check_word_buffer_overflow);
    suite_add_tcase(suite, check_word_case);

    return suite;
}

int main(void)
{
    int failed;
    Suite *suite;
    SRunner *runner;
    
    suite = check_word_suite();
    runner = srunner_create(suite);
    srunner_run_all(runner, CK_NORMAL);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    free(suite);
    return (failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}

