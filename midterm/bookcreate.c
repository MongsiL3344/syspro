#include <stdio.h>

typedef struct Book {
    int id;
    char bookname[50];
    char author[50];
    int year;
    int numofborrow;
    int borrow;
}Book;

int main(int argc, char *argv[]) {
	FILE *fp;
    Book book; 

	if (argc != 2) {
		fprintf(stderr, "How to use: %s FileName\n", argv[0]);
		return 1;
	}

	fp = fopen(argv[1], "w");
	printf("%-4s %-11s %-8s %-8s %-8s %-8s\n", "id", "bookname", "author", "year", "numofborrow", "borrow");
	while (scanf("%d %s %s %d %d %d", &book.id, book.bookname, book.author, &book.year, &book.numofborrow, &book.borrow) == 6) {
		fprintf(fp, "%d %s %s %d %d %d\n", book.id, book.bookname, book.author, book.year, book.numofborrow, book.borrow);
	}

	fclose(fp);
	return 0;
}
