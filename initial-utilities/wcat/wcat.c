/**
 * ostep-projects/initial-utilities/wcat/wcat.c
 * Concatenates the contents of file specified by the command-line
 * arguments to standard output. 
 * by: Leomar Duran <https://github.com/lduran2>
 * for: CIS 3207 Assignment 0
 * date: 2020-01-23
 * due: 2020-01-30
 */
#include <stdlib.h> /* malloc */
#include <stdio.h> /* FILE, fopen, fgets, fprintf, fclose */
#include <stdbool.h> /* bool */

int
main(int argc, char** argv)
{
	/* prototypes */
	void wcpf(FILE*, FILE*, const size_t, char*); /* file-to-file copy */

	size_t k; /* file counter */
	FILE* file; /* the file to read */
	bool is_open = true; /* whether the file was opened, initially true */

	const size_t CBUFF_LEN = 4096; /* number of characters to read at a time */
	/* character buffer */
	char* cbuff = ((char*) malloc(CBUFF_LEN * sizeof(char)));

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
			/* concatenate the current file */
			wcpf(file, stdout, CBUFF_LEN, cbuff);
			/* close the current file */
			fclose(file);
		} /* end if (is_open) */

		else {
			/* print an error message */
			fprintf(stderr, "wcat: cannot open file\n");
		} /* end (is_open) else */
	} /* end for (; (is_open && (k < argc)); ); */

	/* deallocate the character buffer */
	free(cbuff);

	/* no errors if last file opened, error code 1 otherwise */
	return ((is_open) ? 0 : 1);
} /* end main(int, char**); */

/**
 * Copies the contents of infile to outfile.
 * params:
 *   infile    : FILE*        = wherefrom to read
 *   outfile   : FILE*        = whereto to write
 *   CBUFF_LEN : const size_t = size of the character buffer
 *   cbuff     : char*        = the character buffer
 */
void wcpf(FILE* infile, FILE* outfile, const size_t CBUFF_LEN, char* cbuff)
{
	/* read to line buffer while not EOF */
	while (NULL != fgets(cbuff, CBUFF_LEN, infile))
	{
		/* print the line to the outfile */
		fprintf(outfile, "%s", cbuff);
	} /* end while (NULL != fgets(, , infile); */
} /* end wcpf(FILE*, FILE*); */

