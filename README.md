# Application Security Assignment 1

[![Build Status](https://travis-ci.com/Kadawi/AppSec.svg?token=3qzfQJBTFZ2WnexojRKT&branch=master)](https://travis-ci.com/Kadawi/AppSec)

This repository holds my work for the first assignment in the Application Security class I attended as part of my M.S. studies. 

Run with: `$ ./spell_check words_to_check.txt dictionary.txt`

## Goals:

* Gain hands on experience with secure coding and application development techniques. 
* Develop a spell checker system in C.
* Write tests for and fuzz the developed program.
* Fix any discovered bugs.

## Spell Checker Requirements:

* Take as arguments a text file to check and dictionary file.
* Create a function to check the words provided based on hash maps. 
* The prototypes for these functions were provided in dictionary.h (required to make autograder happy)
  * load_dictionary - to load words into the hash map
  
    `bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[]);`
  * check_word - to check if a word is spelled correctly
  
    `bool check_word(const char* word, hashmap_t hashtable[]);`
  * check_words - to tie the two functions together
  
    `int check_words(FILE* fp, hashmap_t hashtable[], char* misspelled[]);`
* All of my spell-checker code in spell.c 

## Part 2: Testing and Fuzzing

* Check for bugs using Valgrind
* Develop functional tests for both common and edge cases
  *  For example, when a the spell checker is called on a string of characters that are all numeric, this word should be determined as spelled correctly.
  * When a bug is found, test should be written to check for similar cases in the future.
* Integrate the tests into Travis
* Run AFL fuzzer against the program
* Report all bugs found by tests/fuzzing and how they were fixed (Not in this repo)
