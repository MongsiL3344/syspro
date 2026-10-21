#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	FILE *fp1;
    FILE* fp2;
    char c;

    // 0 : original cat (to other file)
	if (argc > 1 && strcmp(argv[1], "0") == 0) {

		fp1 = fopen(argv[2], "r");
        fp2 = fopen(argv[3], "w");

        if (fp1 == NULL || fp2 == NULL) {
            fprintf(stderr, "Cannot open file T.T");
            return -1;
        }

	    c = getc(fp1);

    	while (c != EOF) {
	    	putc(c, fp2);
	    	c = getc(fp1);
	    }

        fclose(fp1);
        fclose(fp2);
	}

    // 1 : Upper -> Lower
	if (argc > 1 && strcmp(argv[1], "1") == 0) {

		fp1 = fopen(argv[2], "r");
        fp2 = fopen(argv[3], "w");

        if (fp1 == NULL || fp2 == NULL) {
            fprintf(stderr, "Cannot open file T.T");
            return -1;
        }

	    c = getc(fp1);

    	while (c != EOF) {
            if (c >= 65 && c <= 90) {
                c += 32;
	    	    putc(c, fp2);
            } else {
	    	    putc(c, fp2);
            }
	    	c = getc(fp1);
	    }

        fclose(fp1);
        fclose(fp2);
	}


    // 2 : Lower -> Upper
	if (argc > 1 && strcmp(argv[1], "2") == 0) {

		fp1 = fopen(argv[2], "r");
        fp2 = fopen(argv[3], "w");

        if (fp1 == NULL || fp2 == NULL) {
            fprintf(stderr, "Cannot open file T.T");
            return -1;
        }

	    c = getc(fp1);

    	while (c != EOF) {
            if (c >= 97 && c <= 122) {
                c -= 32;
	    	    putc(c, fp2);
            } else {
	    	    putc(c, fp2);
            }
	    	c = getc(fp1);
	    }

        fclose(fp1);
        fclose(fp2);
	}

	return 0;
}
