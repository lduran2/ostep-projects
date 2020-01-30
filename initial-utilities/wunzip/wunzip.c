/**
 * ostep-projects/initial-utilities/wzip/wunzip.c
 * Decompresses a file into standard output.
 * by: Leomar Duran <https://github.com/lduran2>
 * for: CIS 3207 Assignment 0
 * date: 2020-01-29
 * due: 2020-01-30
 */
#include <stdlib.h> /* malloc */
#include <stdio.h> /* FILE, fopen, fread, fprintf, fclose */
#include <stdbool.h> /* bool */

int
main(int argc, char** argv)
{
	/* prototypes */
	void wuzf(FILE*, FILE*); /* decompression */

	size_t k; /* file counter */
	FILE* file; /* the file to read */
	bool is_open = true; /* whether the file was opened, initially true */

	/* for each file */
	/* note that argv[0] is the command call of this program */
	/* thus ignored */
	for (k = 1; (is_open && (k != argc)); ++k)
	{
		/* open the current file */
		file = fopen(argv[k], "r");
		/* check if able to open file */
		is_open = (NULL != file);

		/* if able to open */
		if (is_open) {
			/* decompress the current file */
			wuzf(file, stdout);
			/* close the current file */
			fclose(file);
		} /* end if (is_open) */

		else {
			/* print an error message */
			fprintf(stderr, "wunzip: cannot open file\n");
		} /* end (is_open) else */
	} /* end for (; (is_open && (k < argc)); ); */

	/* no errors if last file opened, error code 1 otherwise */
	return ((is_open) ? 0 : 1);
} /* end main(int, char**); */

/**
 * Compresses the contents of infile and writes them to outfile.
 * params:
 *   infile    : FILE*        = to compress
 *   outfile   : FILE*        = whereto to write
 */
void
wuzf(FILE* infile, FILE* outfile)
{
	/* prototypes */
	void chrmul(FILE*, int, char); /* string multiplier */

	char
		c;             	/* current character */
	unsigned int count;	/* count of current chracter */
	int n_read;        	/* number of characters read in last read */

	while (0 != n_read) {
		n_read = fread(&count, sizeof(unsigned int), 1, infile); /* read count */
		n_read = n_read && fread(&c, sizeof(char), 1, infile); /* read character if (n_read != 0) */
		if (0 != n_read) {
			chrmul(outfile, count, c);
		} /* end if (0 != n_read) */
	} /* end while (0 != n_read) */
} /* end wuzf(FILE*, FILE*); */

/**
 * Writes a number of repetitions of the given character to a file.
 * params:
 *   outfile : FILE* = whereto to write
 *   count   : int   = number of repetitions of the string
 *   c       : char = to write
 */
void
chrmul(FILE* outfile, int count, char c)
{
	/* loop for (count) times */
	int k;
	for (k = count; 0 < k; --k) {
		/* print the string each time */
		fprintf(outfile, "%c", c);
	} /* end for (; 0 < k;) */
} /* end strmul(FILE*, int, char*) */
