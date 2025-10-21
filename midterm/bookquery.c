#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "book.h"

int main(int argc, char *argv[])
{
	int fd, id;
	char c; 
	struct book record;
	if (argc < 2) {
		fprintf(stderr, "How to use : %s file\n", argv[0]);
		exit(1);
	}
	if ((fd = open(argv[1], O_RDONLY)) == -1) {
		perror(argv[1]);
		exit(2);
	}

	printf("--bookquery--\n");
	id = 1;
	while(id != 4) {
		printf("0: list of all books, 1: list of available books ) ");
		scanf ("%c", &c);
		printf("%-4s %-11s %-11s %-7s %-11s %-6s\n", "id", "bookname", "author", "year", "numofborrow", "borrow");
		lseek(fd, (id-START_ID)*sizeof(record), SEEK_SET);
		if ((read(fd, (char *) &record, sizeof(record)) > 0 && (record.id != 0))
			printf("%-4d %-11s %-11s %-7d %-11d %-6d\n", record.id, record.bookname, record.author, record.year, record.numofborrow, record.borrow);
		id++;
	}
	close(fd);
	exit(0);
}
