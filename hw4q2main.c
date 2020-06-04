/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define KEY_SIZE 52
#define WORDS_ARRAY_SIZE 100
#define MAX_STR_LEN 50
#define UPPERCASE_A 'A'
#define UPPERCASE_Z 'Z'
#define LOWERCASE_A 'a'
#define LOWERCASE_Z 'z'

/* Function Declarations */
char encrypt(unsigned char key[KEY_SIZE], char ch);

int read_words(char *words[], int size, int max_str_len);

void encrypt_words(char *words[], int num_words, unsigned char key[KEY_SIZE]);

void release_memory(char *words[], int num_words);

void print_words(char *words[], int num_words);

int get_string_length(char *word);


/* Implementation */
void print_words(char *words[], int num_words) {
    int i;
    for (i = 0; i < num_words; i++) {
        printf("%s\n", words[i]);
    }
}


int main() {
    //setbuf(stdout, 0);
    unsigned char key[KEY_SIZE] = {

            '>', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '~', 'S', 'D',
            'F', 'G', '*', 'J', 'K', 'L', 'Z', 'X', 'C', 'V', 'B', '+', 'M',
            'm', 'b', 'n', 'v', 'z', 'c', '@', 'q', 'r', 'u', 'i', 'e', 'r',
            't', 'o', 'p', 'w', '$', 'j', 'g', 'd', '%', 's', 'f', 'h', 'k'
    };
    int num_words = 0, i;
    char *words[WORDS_ARRAY_SIZE];

    for (i = 0; i < WORDS_ARRAY_SIZE; i++) {
        words[i] = NULL;
    }

    num_words = read_words(words, WORDS_ARRAY_SIZE, MAX_STR_LEN);
    if (num_words == -1) {
        printf("Failed to read words.\n");
        return 0;
    }

    encrypt_words(words, num_words, key);
    print_words(words, num_words);
    release_memory(words, num_words);
    return 0;
}

char encrypt(unsigned char key[KEY_SIZE], char ch) {
    if (ch >= UPPERCASE_A && ch <= UPPERCASE_Z) {
        return key[ch - UPPERCASE_A];
    } else {
        return key[ch - LOWERCASE_A - (LOWERCASE_A - UPPERCASE_Z) + 1];
    }
}

int read_words(char *words[], int size, int max_str_len) {
    int count = 0;
    int currNum = 0;
    char *temp = malloc(sizeof(char) * max_str_len);
    *temp = 0;
    if (!temp) {
        return -1;
    }
    char ch;
    while (scanf("%c", &ch) && count < size) {
        if (ch == ' ' || ch == '\n') {
            // This is the end of a word or the end of input
            int numLetters = get_string_length(temp);
            char *nWord = malloc(sizeof(char) * (numLetters + 1));
            if (!nWord) {
                free(temp);
                for (int i = 0; i < count; ++i) {
                    free(words[i]);
                }
                return -1;
            }
            for (int i = 0; i < numLetters; ++i) {
                nWord[i] = temp[i];
            }
            // adding terminating zero
            nWord[numLetters] = 0;
            words[count] = nWord;
            count++;
            currNum = 0;
            if (ch == '\n') {
                // We are done taking words as input
                break;
            }
        } else {
            // This is not the end of a word, and also not the end of input,
            // adding new char to the current word
            temp[currNum] = ch;
            currNum++;
        }
    }
//    while (scanf("%s", temp) && count < size) {
//        printf("%s",temp);
//        if (temp[0] == '\n') {
//            printf("empty");
//            count--;
//            break;
//        }
//        int numLetters = get_string_length(temp);
//        words[count] = malloc(sizeof(char) * (numLetters + 1));
//        if (!words[count]) {
//            free(temp);
//            for (int i = 0; i < count; ++i) {
//                free(words[i]);
//            }
//            return -1;
//        }
//        for (int i = 0; i < numLetters; ++i) {
//            words[count][i] = temp[i];
//        }
//        // adding terminating zero
//        words[count][numLetters] = 0;
//        count++;
//    }
    free(temp);
    return count;
}

void encrypt_words(char *words[], int num_words, unsigned char key[KEY_SIZE]) {
    for (int i = 0; i < num_words; ++i) {
        int letter = 0;
        while (words[i][letter]) {
            words[i][letter] = encrypt(key, words[i][letter]);
            letter++;
        }
    }
}

int get_string_length(char *word) {
    int length = 0;
    while (word[length]) {
        length++;
    }
    return length;
}

void release_memory(char *words[], int num_words) {
    for (int i = 0; i < num_words; ++i) {
        free(words[i]);
    }
}