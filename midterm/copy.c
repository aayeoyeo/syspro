#include <stdio.h>

int zero_option = 0;
int one_option = 0;
int two_option = 0;

int main(int argc, char *argv[])
{
   char c;
   FILE *fp1, *fp2;
   
   if (argc != 4) {
      fprintf(stderr, "How to use: %s File1 File2\n", argv[0]);
      return 1;
   }

   if (strcmp(argv[1], "0") == 0)
	   zero_option = 1;
   if (strcmp(argv[1], "1") == 0)
	   one_option = 1;
   if (strcmp(argv[1], "2") == 0)
	   two_option = 1;

   fp1 = fopen(argv[2], "r");
   if (fp1 == NULL) {
      fprintf(stderr, "File %s Open Error\n", argv[1]);
      return 2;
   }
   if (zero_option) {
	   fp2 = fopen(argv[3], "w");
	   while ((c = fgetc(fp1)) != EOF)
		   fputc(c, fp2);
   }
   else if (one_option) {
	   fp2 = fopen(argv[3], "w");
	   while ((c = fgetc(fp1)) != EOF) {
		   if (c >= 'A' && c <= 'Z')
			   c += 32;
		   fputc(c, fp2);
	   }
   }
   else if (two_option) {
	   fp2 = fopen(argv[3], "w");
	   while ((c = fgetc(fp1)) != EOF) {
		   if (c >= 'a' && c <= 'z')
			   c -= 32;
		   fputc(c, fp2);
	   }
   }
   fclose(fp1);
   fclose(fp2);
   return 0;
}
