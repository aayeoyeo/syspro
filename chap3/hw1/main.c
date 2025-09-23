#include <stdio.h>
#include "copy.h"
#include <string.h>

char line[MAXLINE];
char longest[5][MAXLINE];

int main() {
	int len;
	int max;
	max = 0;
	
	int i = 0;
	while(i < 5) {
		gets(longest[i]);
		i++;
	}
	
	for (i = 0; i < 4; i++) {
		for (int j = 0; j < 4 - i; j++) {
			if (strlen(longest[j]) < strlen(longest[j + 1])) {
				char change[MAXLINE];
				copy(longest[j], change);
				copy(longest[j + 1], longest[j]);
				copy(change, longest[j + 1]);
			}
		}
	}
	for (i = 0; i < 5; i++) printf("%s\n", longest[i]);
	return 0;
}
