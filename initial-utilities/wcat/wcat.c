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

int
main(int argc, char** argv)
{
	/* prototypes */
	void wcpf(FILE*, FILE*); /* file-to-file copy */

	size_t k; /* file counter */
	FILE* file; /* the file to read */

	//FILE* outstream;
	//outstream = fopen("outstream", "a");

	/* for each file */
	/* note that argv[0] is the command call of this program */
	for (k = 1; (k != argc); ++k)
	{
		/* open the current file */
		file = fopen(argv[k], "r");
		/* concatenate the current file */
		wcpf(file, stdout);
		//wcpf(file, outstream);
		/* close the current file */
		fclose(file);
	} /* end for (; k < argc; ); */

	//fclose(outstream);

	/* no errors */
	return 0;
} /* end main(int, char**); */

/**
 * Copies the contents of infile to outfile.
 * params:
 *   infile  : FILE* = wherefrom to read
 *   outfile : FILE* = whereto to write
 */
void wcpf(FILE* infile, FILE* outfile)
{
	const size_t LEN = 255; /* number of characters to read at a time */
	char* line = ((char*) malloc(LEN * sizeof(char))); /* current line buffer */
	/* read to line buffer while not EOF */
	while (NULL != fgets(line, 255, infile))
	{
		/* print the line to the outfile */
		fprintf(outfile, "%s", line);
	} /* while (NULL != fgets(, , infile); */
	/* deallocate the line buffer */
	free(line);
} /* end wcpf(FILE*, FILE*); */

