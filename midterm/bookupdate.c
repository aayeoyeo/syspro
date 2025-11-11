#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "book.h"

int main(int argc, char *argv[])
{
	int fd, id;
	int c, c2;
	struct book record;
	if (argc < 2) {
		fprintf(stderr, "How to use : %s file\n", argv[0]);
		exit(1);
	}
	if ((fd = open(argv[1], O_RDWR)) == -1) {
		perror(argv[1]);
		exit(2);
	}
	printf("--bookupdate--\n");
	do {
		printf("0 bookId: borrow book, 1 bookId return book ) ");
		scanf("%d %d", &c, &c2);
		lseek(fd, 0L, SEEK_SET);
		while (read(fd, (char *)&record, sizeof(record)) > 0) {
			if (record.id == c2) {
				if (c == 0) {
					if (record.borrow == 0) {
						record.borrow = 1;
						record.numofborrow++;
						printf("You've got bellow book..\n");
						printf("%4s %11s %11s %7s %11s %6s\n", "id", "bookname", "author", "year", "numofborrow", "borrow");
						printf("%4d %11s %11s %7d %11d %6s\n", record.id, record.bookname, record.author, record.year, record.numofborrow, (record.borrow ? "True" : "False"));
						lseek(fd, (long)-sizeof(record), SEEK_CUR);
						write(fd, (char *)&record, sizeof(record));
					}
					else {
						printf("You cannot borrow below book since it has benn booked.\n");
						printf("%4s %11s %11s %7s %11s %6s\n", "id", "bookname", "author", "year", "numofborrow", "borrow");
						printf("%4d %11s %11s %7d %11d %6s\n", record.id, record.bookname, record.author, record.year, record.numofborrow, (record.borrow ? "True" : "False"));
						lseek(fd, (long)-sizeof(record), SEEK_CUR);
						write(fd, (char *)&record, sizeof(record));
					}
				}
				else if (c == 1) {
					if (record.borrow == 1) {
						record.borrow = 0;
						printf("You've returned bellow book..\n");
						printf("%4s %11s %11s %7s %11s %6s\n", "id", "bookname", "author", "year", "numofborrow", "borrow");
						printf("%4d %11s %11s %7d %11d %6s\n", record.id, record.bookname, record.author, record.year, record.numofborrow, (record.borrow ? "True" : "False"));
						lseek(fd, (long)-sizeof(record), SEEK_CUR);
						write(fd, (char *)&record, sizeof(record));
					}
				}
			}
		}
	printf("\n");
	} while(1);
	close(fd);
	exit(0);
}
