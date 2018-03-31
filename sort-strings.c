#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* Macro: NO_STRINGS
 * stores the number of strings a user is prompted to enter
 */
#define NO_STRINGS 10

/* Macro: NO_STRINGS
 * stores the length of each string a user is allowed to enter
 */
#define STRING_LENGTH 25

/* Macro: BUFFER_SIZE
 * stores the size of buffer for user input
 */
#define BUFFER_SIZE 65535

/* Global Variable : char *str[]
 * pointer array to store the user entered string
 */
char *str[NO_STRINGS];

void get_strings(void);
char get_sort_order(void);
bool is_duplicate(char[], int);
bool exceeds_length(char[]);
bool is_invalid(char[]);
void sort_strings(void);
void print_sorted_strings(char);

int main(void) {
    get_strings();
    char sort_order = get_sort_order(); 
    sort_strings();
    print_sorted_strings(sort_order);
    return 0;
}

/* Function : void get_strings(void)
 * Reads the strings from the user 
 * validates for duplicate, length and invalid entries
 */
void get_strings(void) {
    printf("Enter %d character strings: \n\n", NO_STRINGS);
    int i = 0;
    do {
        printf("Enter string %d:", (i+1));
        char buffer[BUFFER_SIZE];
        fgets(buffer, BUFFER_SIZE, stdin);
        if(exceeds_length(buffer)) {
            fprintf( stderr, "Error: String exceeds %d characters. Please enter again.\n", STRING_LENGTH);
        }
        else {
            str[i] = (char*)malloc(STRING_LENGTH*sizeof(char));
            strncpy(str[i], buffer, STRING_LENGTH);
            if(is_duplicate(str[i], i)) {
                fprintf( stderr, "Error: Duplicate string. Please enter again.\n");
            }
            else if(is_invalid(str[i])) {
                fprintf( stderr, "Error: Invalid string. Please enter again.\n");
            }
            else {
                i++;
            }
        }
    } while(i < NO_STRINGS);
}

/* Function : char get_sort_order(void)
 * Reads the users sorting order choice. 
 * output parameter - char -> based on the sorting order selected by user.
 */
char get_sort_order(void) {
    char order;
    do {
        printf("\nPrint character strings in Ascending(A) or Descending(D) order:");
        scanf("%c", &order);
        getchar();
    } while (order != 'A' && order != 'D');
    return order;
}

/* Function : bool is_duplicate(char s[], int n)
 * Checks if a string is already present in the str[] array.
 * input parameter - char s[] -> string to check if present.  
 * output parameter - bool -> returns true if s[] is present in str[], else false. 
 */
bool is_duplicate(char s[], int n) {
    bool flag = false;
    for(int i = 0;i < n; i++) {
        if(strcmp(s, str[i]) == 0) {
            flag = true;
            break;
        }
    }
    return flag;
}

/* Function : bool exceeds_length(char s[])
 * Checks if the length of a string is more than STRING_LENGTH. 
 * input parameter - char s[] -> string to check if exceeds STRING_LENGTH.
 * output paramter - bool -> returns true if length of s[] exceeds STRING_LENGTH, 
                                     else false. 
 */
bool exceeds_length(char s[]) {
    if(strlen(s) > STRING_LENGTH)
        return true;
    else
        return false;
}

/* Function : bool is_invalid(char s[])
 * Validates if a string has characters represented 
 * by ascii 32 (decimal) through 126 (decimal) along with a single newline
 * and if the string is composed entirely of space(s). 
 * input parameter - char s[] -> string to validate.
 * output paramter - bool -> returns false if s[] has characters represented 
 * by ascii 32 (decimal) through 126 (decimal) along with only one single newline
 * and if s[] is composed entirely of space(s) return true.
 * return true, even if the string has tabs along with printable characters,
 * as \t = 9, (which is not in the 32-126 range)  
 */
bool is_invalid(char s[]) {
    if(strchr(s, '\t' ) != NULL) {
        return true;
    }
    for( int i = 0; i < strlen(s); i++) {
        if(s[i] > 32 && s[i] < 127) {
            return false;
        }
    }
    return true;
}

/* Function : void sort_strings(void)
 * Sorts the list of strings entered by the user in ASCENDING order. 
 * Bubble Sort Algorithm based on ASCII value.
 */
void sort_strings(void) {
    for( int i = 0; i < (NO_STRINGS - 1); i++) {
        for ( int j = 0; j < (NO_STRINGS - i - 1); j++) {
            char temp[STRING_LENGTH];
                if(strcmp(str[j], str[j+1]) > 0) {
                    strcpy(temp, str[j]);
                    strcpy(str[j], str[j+1]);
                    strcpy(str[j+1], temp);
            }
        }
    }
}

/* Function : void print_sorted_strings(char sort_order)
 * Prints in the list of strings based on the sorting order selected by the user.
 * Also, prints the string with lowest and highest ASCII aalue.
 * input parameter - sort_order -> the sort order selected by the user.
 */
void print_sorted_strings(char sort_order) {
    if(sort_order == 'A') {
        printf("\nAscending Order:\n");
        for ( int i = 0; i < NO_STRINGS; i++) {
            printf("\n%s", str[i]);
        }
    }
    else {
        printf("\nDescending Order:\n");
        for ( int i = NO_STRINGS - 1; i >= 0; i--) {
            printf("\n%s", str[i]);
        }
    }

    printf("\n\nString with lowest ASCII value : %s", str[0]);
    printf("\nString with highest ASCII value : %s\n", str[NO_STRINGS-1]);
}