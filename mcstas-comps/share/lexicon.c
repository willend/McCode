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
* Date: May, 2025
* Origin: ESS
* Release: McStas 2.7x, 3.x.x
* Version: $Revision$
*
* lexicon functions
*
* Usage: within SHARE
* %include "lexicon"
*
****************************************************************************/

#ifndef LEXICON_H
#include "lexicon.h"
#endif

#ifndef LEXICON_C
#define LEXICON_C

int isBlank(const char *str) {
    if (!str) return 1;

    // isspace() returns 0 for '\0', so the loop naturally stops 
    // at the end of the string OR at the first non-space character.
    while (isspace((unsigned char)*str)) {
        str++;
    }

    // If we stopped because we hit the end, it's blank.
    // If we stopped because we hit a character, it's NOT blank.
    return *str == '\0';
}

int validate_filename(char *filename_in, char **filename_out) {

	char *fname = NULL;
    int fname_len = trim_space_from_both_ends(filename_in,&fname);
	
	if (fname_len != 0) { 
		// Reject relative navigation paths
		if (strcmp(fname, ".") != 0 && strcmp(fname, "..") != 0) {
			int i; char c;
			// Scan for illegal characters and control characters
			for (i = 0; fname[i] != '\0'; i++) {
				c = fname[i];
				if (c == '/' || c == '\\' || c == ':' || c == '*' || 
					c == '?' || c == '"'  || c == '<' || c == '>' || 
					c == '|' || iscntrl((unsigned char)c)) {
						break;
				}
			}
			if (i == fname_len) {
				if (filename_out) {
					if (*filename_out) free(*filename_out);
					*filename_out = fname;
					fname = NULL;
				}
				return fname_len;
			}
		}
	}

	free(fname); 
	return 0;
}

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
int to_lower_case(char *str, char**str_copy) {

	int str_len = (str ? strlen(str) : 0);
	char *ptr;
		
	if (str_copy) {
		
		if (str_len > 0) {
			char *to;
			to = ptr =(char*)malloc((str_len + 1) * sizeof(char));
			if (!to) return -1;
			
			for (; *str != '\0'; str++, ptr++) {
				unsigned char c = (unsigned char)*str;
				//Efficiency: Only call the function if it's an uppercase letter.
				if (c >= 'A' && c <= 'Z') {
					*ptr = (char)tolower(c);
				}
				else {
					*ptr = c;
				}
			}
			*ptr = '\0';
			
			if (*str_copy) free(*str_copy);
			*str_copy = to;
		}
		else {
			if (*str_copy) free(*str_copy);
			*str_copy = (char*)calloc(1, sizeof(char));
			if (!(*str_copy)) return -1;
		}
	}			
	else {	
		if (str) {
			for (ptr = str; *ptr != '\0'; ptr++) {
				unsigned char c = (unsigned char)*ptr;
				//Efficiency: Only call the function if it's an uppercase letter.
				if (c >= 'A' && c <= 'Z') {
					*ptr = (char)tolower(c);
				}
			}
		}
	}

	return str_len;
}


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
int trim_space_from_both_ends(char *str, char **str_copy) {
	
	if (str_copy) {

		int len = (str ? (int)strlen(str) : 0);
		
		if (len > 0) {
			
			char *start = str;
			char *end = str + len - 1;
			
			// Pass 2: Find the first non-space character
			// we use the fact that isspace returns 0 for null terminator '\0'
			while (isspace((unsigned char)*start)) {
				start++;
			}

			// If the string is not all spaces, continue
			if (*start != '\0') {

				// Pass 3: Find the last non-space character
				// We start from 'end' which we already calculated from the first strlen
				while (end > start && isspace((unsigned char)*end)) {
					end--;
				}
				
				//Calculate the new length
				//We add 1 because 'end' points to the last character, not the terminator
				len = (int)(end - start + 1);
				
				//malloc add 1 for null terminator
				char *to = (char*)malloc((len + 1) * sizeof(char)); 
				if (!to) return -1;
				strncpy(to, start, len);
				to[len] = '\0';
				
				if (*str_copy) free(*str_copy);
				*str_copy = to;
				
				return len;
			}
		}

		if (*str_copy) free(*str_copy);
		*str_copy=(char*)calloc(1, sizeof(char));
		if (!(*str_copy)) return -1; //something is wrong, fail to allocate memory
		return 0;

	}
	else {
		// Pass 1: Get the initial length
		int len = (str ? (int)strlen(str) : 0);
		if (len == 0) return 0;

		char *start = str;
		char *end = str + len - 1;
		
		// Pass 2: Find the first non-space character
		// we use the fact that isspace returns 0 for null terminator '\0'
		while (isspace((unsigned char)*start)) {
			start++;
		}

		// If the string is all spaces, empty it and return 0
		if (*start == '\0') {
			*str = '\0';
			return 0;
		}

		// Pass 3: Find the last non-space character
		// We start from 'end' which we already calculated from the first strlen
		while (end > start && isspace((unsigned char)*end)) {
			end--;
		}
		
		//Calculate the new length
		//We add 1 because 'end' points to the last character, not the terminator
		len = (int)(end - start + 1);

		// Shift the content to the front if there were leading spaces
		// memmove is safer than strcpy for overlapping memory
		if (start != str) {
			memmove(str, start, len);
		}
		
		// Null-terminate the trimmed string
		str[len] = '\0';

		return len;
	}
}


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
int replace_keyword(const char *old_string, const char *old_keyword, const char *new_keyword, char **new_string) {
						
	if (!new_string) return -1; // Error: destination pointer is invalid

	int old_str_len = (old_string ? strlen(old_string) : 0);
	
	// 1. Handle Empty Input
	if (old_str_len == 0) {
		//create empty new_string
		if (*new_string) free(*new_string);
		*new_string=(char*)calloc(1, sizeof(char));
		if (!(*new_string)) return -1; //something is wrong, fail to allocate memory
		return 0;
	}
	
	//new string will not be zero, prepare intermediate storage 
	char *intermediate; 
		
	int old_kw_len = (old_keyword? strlen(old_keyword) : 0);
	if (old_kw_len > 0) {
		
		// Count old_keyword occurrences
		int count = 0;
		const char *ptr = old_string;
		while ((ptr = strstr(ptr, old_keyword)) != NULL) {
			count++;
			ptr += old_kw_len;
		}
		
		if (count > 0) {
			int new_kw_len = (new_keyword ? strlen(new_keyword) : 0);

			int new_str_len = old_str_len + count * (new_kw_len - old_kw_len);
			
			// Build the new string in intermediate memory
			intermediate = (char *)malloc((new_str_len + 1)*sizeof(char));
			if (!intermediate) return -1; //something is wrong, fail to allocate memory
			
			// Build the result
			char *dest = intermediate;
			const char *src = old_string;
			const char *next_match;
			int before_len;
			while ((next_match = strstr(src, old_keyword)) != NULL) {
				before_len = (int)(next_match - src);
				if (before_len > 0) {
					memcpy(dest, src, before_len);
					dest += before_len;
				}
				if (new_kw_len > 0) {
					memcpy(dest, new_keyword, new_kw_len);
					dest += new_kw_len;
				}
				src = next_match + old_kw_len;
			}
			
			//remaining
			strcpy(dest, src);
			 
			// Free previous allocation if it exists
			if (*new_string) free(*new_string);
			
			// Assign the new string
			*new_string = intermediate;

			return new_str_len;
		}
	}
	
	//Either old_kw_len == 0 or no replacement, copy old string to new string
	intermediate = (char *)malloc((old_str_len + 1)*sizeof(char));
	if (!intermediate) return -1; //something is wrong, fail to allocate memory
	strcpy(intermediate, old_string);
	
	// Free previous allocation if it exists
	if (*new_string) free(*new_string);

	// Assign the new string
	*new_string = intermediate;

	return old_str_len;
}

int replace_separator(const char*old_string, const char*old_separators, char new_separator, char**new_string) {
	if (!new_string) return -1;
	
	int old_string_len = (old_string ? (int)strlen(old_string) : 0);
	
	if (old_string_len == 0) {
		if (*new_string) free(*new_string);
		*new_string = (char*)calloc(1, sizeof(char));
		if (!(*new_string)) return -1;
		return 0;
	}

	char *intermediate = (char*)malloc((old_string_len + 1) * sizeof(char));
	if (!intermediate) return -1;

	if ((old_separators ? strlen(old_separators) : 0) == 0) {
		strcpy(intermediate, old_string);
		if (*new_string) free(*new_string);
		*new_string = intermediate;
		return old_string_len;
	}
	
	//old_string exists, old_separators length > 0
	if (new_separator != '\0') {
		// Case 1: Replacing characters (Length remains the same)
		for (int i = 0; i < old_string_len; i++) {
			char c = old_string[i];
			// strchr returns a pointer if 'c' is found in 'old_separators', else NULL
			if (strchr(old_separators, c)) {
				intermediate[i] = new_separator;
			}
			else {
				intermediate[i] = c;
			}
		}
		intermediate[old_string_len] = '\0';

		if (*new_string) free(*new_string);
		*new_string = intermediate;

		return old_string_len;
	}
	else {
		int new_string_len = 0;
		for (int i = 0; i < old_string_len; i++) {
			char c = old_string[i];
			// strchr returns a pointer if 'c' is found in 'old_separators', else NULL
			if (strchr(old_separators, c) == NULL) {
				intermediate[new_string_len++] = c;
			}
		}
		intermediate[new_string_len] = '\0';
		
		if (*new_string) free(*new_string);
		*new_string = intermediate;
		
		return new_string_len;
	}
}

/****************************************************/
/* Case-insensitive comparison of two keywords 		*/
/* spaces at the start and end are ignored			*/
/* return 1 if equivalent, 0 if not, -1 if error. 	*/
/****************************************************/
int is_keyword_equivalent(char *keyword1, char *keyword2) {

	if (keyword1 == 0 || keyword2 == 0) return 0;
	
	int outcome = 0; 
	
	char *lc1 = NULL;
	char *lc2 = NULL;
	
	int len1 = trim_space_from_both_ends(keyword1, &lc1);
	int len2 = trim_space_from_both_ends(keyword2, &lc2);
	
	if (len1 == 0 || len2 == 0) return 0;
	
	if (len1 == len2) {
			
		to_lower_case(lc1, 0); 
		to_lower_case(lc2, 0);
		
		if (strcmp(lc1,lc2) == 0) outcome = 1;
			
	}
	
	if (lc1) free(lc1);
	if (lc2) free(lc2);
	
	return outcome;	
}


/********************************************************************************************************/
/* Allocate memory to *mem with size strlen(text)+1 of type char, strcpy text into mem. Returns *mem 	*/
/* returns newly allocated char*																		*/
/* if mem!=0: if *mem!=0, free(*mem). Then set *mem=newly allocated char* 								*/
/* if mem==0: mem will not be updated. Will still return newly allocated char* 							*/
/* Important: if provided, mem must be set up for dynamical memory and not static memory allocation,	*/
/* crash if statically allocated char mem[some_size] is passed to the function call. 					*/
/********************************************************************************************************/
char* store_text(char*text, char**mem) {
	int text_len = (text ? strlen(text) : 0);

	char*mem_out = (char*)calloc(text_len + 1, sizeof(char)); 
	
	if (mem_out && text_len > 0) {
		strcpy(mem_out, text);
	}
	
	if (mem) {
		if (*mem) free(*mem);
		if (mem_out) *mem = mem_out; 
		else *mem = (char*)calloc(1, sizeof(char));
	}
	
	return mem_out;
}

#endif //end of LEXICON_C
/* end of lexicon.c */
