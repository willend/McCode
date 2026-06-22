/****************************************************************************
*
* McStas, neutron ray-tracing package
*         Copyright 1997-2006, All rights reserved
*         Risoe National Laboratory, Roskilde, Denmark
*         Institut Laue Langevin, Grenoble, France
*
* Library: lexicon.c
*
* %Identification
* Written by: Hal Lee
* Date: October, 2023
* Origin: ESS
* Release: McStas 2.7x, 3.1x
* Version: $Revision$
*
* lexicon functions
*
* Usage: within SHARE
* %include "lexicon"
*
****************************************************************************/

#ifndef LEXICON_H
#define LEXICON_H

int isBlank (const char*line);

int validate_filename(char *filename_in, char **filename_out);

/************************************************************************************************************/
/* Convert all characters in string "str" to lower case														*/
/* return str length or -1 if error.																		*/
/* 																											*/
/* Options: 																								*/
/* to_lower_case(str, &str_copy) saves converted string in "str_copy"										*/
/* to_lower_case(str,0), saves converted string back in str. 												*/
/* to_lower_case(str, &str) saves converted string in str but str will have a new address					*/
/* 																											*/
/* Warning: 																								*/
/* char *str_copy must be initialised, e.g. char *str_copy=NULL before passing to function using &str_copy.	*/
/************************************************************************************************************/
int to_lower_case(char *str, char**str_copy);

/************************************************************************************************************/
/* Trim space from both ends of "str"																		*/
/* returns the total number of non-space characters in the char array										*/
/* 																											*/
/* Options: 																								*/
/* trim_space_from_both_ends(str, &str_copy) saves converted string in "str_copy".							*/
/* trim_space_from_both_ends(str,0), saves converted str back in str. 										*/
/* trim_space_from_both_ends(str, &str) saves converted str in str but str will have a new address.			*/
/* 																											*/
/* Warning: 																								*/
/* char *str_copy must be initialised, e.g. char *str_copy=NULL before passing to function using &str_copy.	*/
/************************************************************************************************************/
int trim_space_from_both_ends(char *str, char **str_copy);

/********************************************************************************************************************/
/* Replace keyword in a string																						*/
/* multiple occurance of keyword will all be replaced																*/
/* 																													*/
/* Warning: 																										*/
/* char *new_string must be initialised, e.g. char *new_string=NULL before passing to function using &new_string.	*/
/* 																													*/
/* Not allowed:																										*/
/* replace_keyword(old_string, old_keyword, new_keyword, 0) 														*/
/* variable "new_string" must be assigned																			*/
/* 																													*/
/* If a string may contain two lexiconly similar keywords to be replaced, 											*/
/* replace the longer keyword first, otherwise it will result in errorous outcome. 									*/
/* e.g. Replace keyword "abcdefg" to "hijk" and "abcd" to "efgh".													*/
/*      The correct order is to replace the longer "abcdefg" first, then replace "abcd".							*/
/*      Replacing "abcd" first will change "abcdefg" to "efghefg" which is not intended.							*/
/* Likewise, one should be careful about accidental sequential replacements. 										*/
/* e.g. "abcd" to "efghi" then "efg" to "jklmn" results in "jklmnhi" which may not be intended. 					*/
/********************************************************************************************************************/
int replace_keyword(const char*old_string, const char*old_keyword, const char*new_keyword, char**new_string);
int replace_separator(const char*old_string, const char*old_separators, char new_separator, char**new_string);

/****************************************************/
/* Case-insensitive comparison of two keywords 		*/
/* spaces at the start and end are ignored			*/
/* return 1 if equivalent, 0 if not, -1 if error. 	*/
/****************************************************/
int is_keyword_equivalent(char *keyword1, char *keyword2);

/********************************************************************************************************/
/* Allocate memory to *mem with size strlen(text)+1 of type char, strcpy text into mem. Returns *mem 	*/
/* returns newly allocated char*																		*/
/* if mem!=0: if *mem!=0, free(*mem). Then set *mem=newly allocated char* 								*/
/* if mem==0: mem will not be updated. Will still return newly allocated char* 							*/
/* Important: if provided, mem must be set up for dynamical memory and not static memory allocation,	*/
/* crash if statically allocated char mem[some_size] is passed to the function call. 					*/
/********************************************************************************************************/
char* store_text(char*text, char**mem);

#endif //end of LEXICON_H
