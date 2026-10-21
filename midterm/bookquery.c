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

    int mode;


	if (argc != 2) {
		fprintf(stderr, "How to use: %s FileName\n", argv[0]);
		return 1;
	}


    while(1) {
        printf("--bookquery--\n");
        printf("0: list of all books, 1: list of available books ) ");
        scanf("%d", &mode);

        if (mode == 0) {
	        fp = fopen(argv[1], "r");
	    
            printf("%4s %11s %8s %8s %8s %8s\n", "id", "bookname", "author", "year", "numofborrow", "borrow");

	        while (fscanf(fp, "%d %s %s %d %d %d", &book.id, book.bookname, book.author, &book.year, &book.numofborrow, &book.borrow) == 6) {
		        printf("%4d %11s %8s %8d %8d %8d\n", book.id, book.bookname, book.author, book.year, book.numofborrow, book.borrow);
	        }
	        fclose(fp);
        } else if (mode == 1) {
	        fp = fopen(argv[1], "r");
	    
            printf("%4s %11s %8s %8s %8s %8s\n", "id", "bookname", "author", "year", "numofborrow", "borrow");

	        while (fscanf(fp, "%d %s %s %d %d %d", &book.id, book.bookname, book.author, &book.year, &book.numofborrow, &book.borrow) == 6) {
		        if (book.borrow != 0)
                    printf("%4d %11s %8s %8d %8d %8s\n", book.id, book.bookname, book.author, book.year, book.numofborrow, "True");
	        }
	        fclose(fp);
        }


    }
	return 0;
}
