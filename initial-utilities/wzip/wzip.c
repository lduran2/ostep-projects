/**
 * ostep-projects/initial-utilities/wcat/wcat.c
 * Concatenates the contents of file specified by the command-line
 * arguments to standard output. 
 * by: Leomar Duran <https://github.com/lduran2>
 * for: CIS 3207 Assignment 0
 * date: 2020-01-29
 * due: 2020-01-30
 */
#include <stdlib.h> /* malloc */
#include <stdio.h> /* FILE, fopen, fscanf, fwrite, fclose */
#include <stdbool.h> /* bool */

int
main(int argc, char** argv)
{
	/* prototypes */
	void wzipf(FILE*, FILE*); /* compression */

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
			/* concatenate the current file */
			wzipf(file, stdout);
			/* close the current file */
			fclose(file);
		} /* end if (is_open) */

		else {
			/* print an error message */
			fprintf(stderr, "wcat: cannot open file\n");
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
wzipf(FILE* infile, FILE* outfile)
{
	/* prototypes */
	int readc(FILE*, char*);                  /* read single character */
	void wcntch(unsigned int*, char*, FILE*); /* write count and character */

	const unsigned int INIT_COUNT = 1; /* the initial count */

	char
		c,             	/* current character */
		nextc;         	/* next character */
	unsigned int count;	/* count of current chracter */
	int n_read;        	/* number of characters read in last read */

	/* initial conditions */
	n_read = fscanf(infile, "%c", &nextc);
	count = INIT_COUNT;

	/* read to line buffer while not EOF */
	while (EOF != n_read)
	{
		/* update character reads */
		c = nextc;
		n_read = readc(infile, &nextc);

		/* check if the same character as follows */
		if (c == nextc) {
			++count;
		} /* end if (c == nextc) */
		else {
			/* write count and character */
			wcntch(&count, &c, outfile);
			count = INIT_COUNT;
		} /* end if (c != nextc) */
	} /* end while (EOF != n_read); */

	--count; /* remove extra count */

	/* write count and character */
	wcntch(&count, &c, outfile);
} /* end wzipf(FILE*, FILE*); */

/**
 * Reads a single character from a file.
 *
 * params:
 *   infile : FILE* = file to read from
 *   pc     : FILE* = character pointer
 *
 * return:
 *   1 if successful, 0 if next is not a character,
 *   or EOF if the end of input is reached
 */
int
readc(FILE* infile, char* pc)
{
	return fscanf(infile, "%c", pc);
} /* end readc(FILE*, char*) */

/**
 * Writes the count as a binary integer and character as a character to
 * a file.
 *
 * param:
 *   count   : unsigned int = count of the character to write
 *   c       : char         = character to write
 *   outfile : FILE*        = whereto to write
 */
void
wcntch(unsigned int* pcount, char* pc, FILE* outfile)
{
	fwrite(pcount, sizeof(unsigned int), 1, outfile); /* write the count */
	fwrite(pc, sizeof(char), 1, outfile); /* write the character */
} /* end wcntch(unsigned int, char, FILE*) */
