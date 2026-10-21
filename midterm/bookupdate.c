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
	FILE *fp_to_edit;
    Book book; 

    int mode, input_id;


	if (argc != 2) {
		fprintf(stderr, "How to use: %s FileName\n", argv[0]);
		return 1;
	}

    printf("--bookupdate--\n");

    while(1) {
        printf("0 bookId: borrow book, 1 bookId: return book ) ");
        scanf("%d%d", &mode, &input_id);

        if (mode == 0) {
	        fp = fopen(argv[1], "r");
            fp_to_edit = fopen(argv[1], "w");
	    

	        while (fscanf(fp, "%d %s %s %d %d %d", &book.id, book.bookname, book.author, &book.year, &book.numofborrow, &book.borrow) == 6) {
                if (book.id == input_id && book.borrow == 1) {
                    printf("You've got bellow book...\n");
                    printf("%4s %11s %8s %8s %8s %8s\n", "id", "bookname", "author", "year", "numofborrow", "borrow");
		            printf("%4d %11s %8s %8d %8d %8d\n", book.id, book.bookname, book.author, book.year, book.numofborrow, book.borrow);

                    book.borrow = 0;
                    book.numofborrow++;

		            fprintf(fp_to_edit, "%d %s %s %d %d %d\n", book.id, book.bookname, book.author, book.year, book.numofborrow, book.borrow);
                } else {
		            fprintf(fp_to_edit, "%d %s %s %d %d %d\n", book.id, book.bookname, book.author, book.year, book.numofborrow, book.borrow);
                }
            }
	        fclose(fp);
        } else if (mode == 1) {
	        fp = fopen(argv[1], "r");
            fp_to_edit = fopen(argv[1], "w");

	        while (fscanf(fp, "%d %s %s %d %d %d", &book.id, book.bookname, book.author, &book.year, &book.numofborrow, &book.borrow) == 6) {
                if (book.id == input_id && book.borrow == 0) {
                    printf("You've returned bellow book...\n");
                    printf("%4s %11s %8s %8s %8s %8s\n", "id", "bookname", "author", "year", "numofborrow", "borrow");
		            printf("%4d %11s %8s %8d %8d %8d\n", book.id, book.bookname, book.author, book.year, book.numofborrow, book.borrow);

		            fprintf(fp_to_edit, "%d %s %s %d %d %d\n", book.id, book.bookname, book.author, book.year, book.numofborrow, book.borrow);
                } else {
		            fprintf(fp_to_edit, "%d %s %s %d %d %d\n", book.id, book.bookname, book.author, book.year, book.numofborrow, book.borrow);
                }
            }
	        fclose(fp);
        }
    }
	return 0;
}
