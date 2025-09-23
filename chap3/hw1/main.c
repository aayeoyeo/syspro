#include <stdio.h>
#include "copy.h"
#include <string.h>

#define MAX_LINES 5
#define MAXLINE 100

int main() {
    char lines[MAX_LINES][MAXLINE];
    int lengths[MAX_LINES];
    int i = 0;
    while (i < MAX_LINES) {
        if (fgets(lines[i], MAXLINE, stdin) == NULL) break;
        lengths[i] = strlen(lines[i]);
        i++;
    }

    for (i = 0; i < MAX_LINES - 1; i++) {
        for (int j = 0; j < MAX_LINES - 1 - i; j++) {
            if (lengths[j] < lengths[j + 1]) {
                int temp_len = lengths[j];
                lengths[j] = lengths[j + 1];
                lengths[j + 1] = temp_len;
                char temp_str[MAXLINE];
                copy(lines[j], temp_str);
                copy(lines[j + 1], lines[j]);
                copy(temp_str, lines[j + 1]);
            }
        }
    }
    for (i = 0; i < MAX_LINES; i++) printf("%s", lines[i]);
    return 0;
}
