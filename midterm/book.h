#define MAX 24
#define START_ID 1

struct book {
	int id;
	char bookname[MAX];
	char author[MAX];
	int year;
	int numofborrow;
	int borrow;
};
