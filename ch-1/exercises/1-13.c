#include <stdio.h>

#define IN  1    // inside a word
#define OUT 0    // outside a word

// Write a program to print a histogram of words lengths in its input; vertical is harder than horizontal.
int main()
{
    int i, c, word_length, state;
    int words[11]; // 0 through 9, then 10+

    word_length = 0;
    state = OUT;

    for (i = 0; i <= 11; i++)
        words[i] = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            state = OUT;
            if (word_length >= 10)
                words[10]++;
            else
                words[word_length]++;
            word_length = 0;
        } else if (state == OUT)
            state = IN;
        if (state == IN)
            ++word_length;
    }

    /* 
    printf("Word Lengths contents\n0: %4d\n1: %4d\n2: %4d\n3: %4d\n4: %4d\n5: %4d\n6: %4d\n7: %4d\n8: %4d\n9: %4d\n10: %4d\n\n", 
            words[0], words[1], words[2], words[3], words[4], words[5], 
            words[6], words[7], words[8], words[9], words[10]);
    */

    printf("%4d%4d%4d%4d%4d%4d%4d%4d%4d%4d%4d+\n", 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    int curr_column, curr_row, more_rows;
    char hist_row[11];
    curr_column = curr_row = 0;
    more_rows = 1;
    while (more_rows) {
        more_rows = 0;
        for(curr_column = 0; curr_column <= 10; curr_column++) {
            if (words[curr_column] > curr_row) {
                more_rows = 1;
                hist_row[curr_column] = 'X';
            }
            else {
                hist_row[curr_column] = ' ';
            }
        }
        ++curr_row;

        printf("%4c%4c%4c%4c%4c%4c%4c%4c%4c%4c%4c\n", hist_row[0], hist_row[1], hist_row[2],
        hist_row[3], hist_row[4], hist_row[5], hist_row[6], hist_row[7], hist_row[8], hist_row[9], hist_row[10]);    
    }
   
    return 0;
}