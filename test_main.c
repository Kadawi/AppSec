#include <check.h>
#include "dictionary.h"
#include <stdlib.h>
#include <stdio.h>

#define DICTIONARY "wordlist.txt"
#define TESTDICT "test_worlist.txt"

/*
START_TEST(test_dictionary_normal)
{
    hashmap_t hashtable[HASH_SIZE];
    ck_assert(load_dictionary(TESTDICT, hashtable));
    // Here we can test if certain words ended up in certain buckets
    // to ensure that our load_dictionary works as intended. I leave
    // this as an exercise.
}
END_TEST
*/

START_TEST(test_check_word_buffer_overflow){
	hashmap_t hashtable[HASH_SIZE];
	load_dictionary(DICTIONARY, hashtable);
	char incorrect_word[500000];
	for (int i = 0; i<499999; i++) incorrect_word[i] = 'A';
	incorrect_word[499999] = '\0';
	ck_assert(!check_word(incorrect_word, hashtable));
	free(hashtable);
	free(incorrect_word);
}
END_TEST

START_TEST(test_check_word_normal)
{
    //printf("begin check word test\n");
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    const char* correct_word = "Justice";
    const char* punctuation_word_2 = "pl.ace";
    //const char* question_word = "?howdy?";
    ck_assert(check_word(correct_word, hashtable));
    ck_assert(!check_word(punctuation_word_2, hashtable));
    //ck_assert(check_word(question_word, hashtable));
    // Test here: What if a word begins and ends with "?
    //printf("end of check word test\n");
    free(hashtable);
    free(correct_word);
    free(punctuation_word_2);
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
    printf("misspelled is %d\n", num_misspelled);
    ck_assert(num_misspelled == 0);
    free(hashtable);
    free(misspelled);
    fclose(fp);
    free(num_misspelled);
}
END_TEST

START_TEST(test_check_words_normal)
{
    //printf("one\n");	
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    //printf("two\n");
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
    free(hashtable);
    free(expected);
    free(misspelled);
    fclose(fp);
    free(num_misspelled);
    free(test);
    free(len1);
    free(len2);
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
    tcase_add_test(check_word_case, test_check_words_long);
    tcase_add_test(check_word_case, test_check_word_buffer_overflow);
    suite_add_tcase(suite, check_word_case);

    return suite;
}

int main(void)
{
    //fflush(stdout);
    //printf("Main\n");	
    int failed;
    Suite *suite;
    SRunner *runner;
    
    suite = check_word_suite();
    runner = srunner_create(suite);
    srunner_run_all(runner, CK_NORMAL);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    free(suite);
    free(runner);
    free(check_word_suite);
    return (failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}

