#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	int c, lineNum = 1;

	if (argc > 1 && strcmp(argv[1], "-n") == 0) {
		for (int i = 2; i < argc; i++) {
			if (argc < 2)
				fp = stdin;
			else fp = fopen(argv[i], "r");
			
			printf("%3d ", lineNum);
			lineNum++;

			c = getc(fp);
			while (c != EOF) {
				putc(c, stdout);
				c = getc(fp);
			}
			fclose(fp);
		}
	}
	else {
		for (int i = 1; i < argc; i++) {
			fp = fopen(argv[i], "r");
	
			c = getc(fp);
			while (c != EOF) {
				putc(c, stdout);
				c = getc(fp);
			}
			fclose(fp);
		}
	}
	return 0;
}
