/**
 * ostep-projects/initial-utilities/wgrep/wgrep.c
 * Finds an expression in the file specified by the command-line
 * arguments.
 * by: Leomar Duran <https://github.com/lduran2>
 * for: CIS 3207 Assignment 0
 * date: 2020-01-28
 * due: 2020-01-30
 */
#include <stdlib.h> /* malloc */
#include <stdio.h> /* FILE, fopen, getline, fprintf, fclose */
#include <stdbool.h> /* bool */
#include <string.h> /* strstr */

int
main(int argc, char** argv)
{
	/* prototypes */
	bool wgrpnl(char*, int, char**); /* file-to-file copy */

	/* constants */
	const int I_KEY = 1; /* index of key in the argv */
	const int FILE_OFF = 2; /* offset of first file name in argv */

	bool has_error; /* whether any error occured */

	/* check if enough arguments */
	has_error = (FILE_OFF > argc);
	if (!has_error) {
		/* if so, loop through the file names and perform wgrepf */
		has_error = wgrpnl(
			argv[I_KEY], (argc - FILE_OFF), (argv + FILE_OFF));
	} /* end if (!has_error) */

	else {
		/* if not, then print the usage statement */
		fprintf(stderr, "wgrep: searchterm [file...]\n");
	} /* end if (has_error) */

	/* no errors if last file opened, error code 1 otherwise */
	return ((has_error) ? 0 : 1);
} /* end main(int, char**); */

/**
 * Loops through the file names specified by (N_NAMES, names) and
 * performs a grep using the specified key.
 *
 * params:
 *   key     : char*     = the search string
 *   N_NAMES : const int = number of file names
 *   names   : char**    = array of file names
 *
 * returns: true if all files were opened; false otherwise
 */
bool
wgrpnl(char* key, const int N_NAMES, char** names) {
	/* prototypes */
	void wgrepf(char*, FILE*, FILE*); /* file-to-file copy */

	size_t k; /* file counter */
	FILE* file; /* the file to read */
	bool is_open = true; /* whether the file was opened, initially true */

	/* for each file */
	/* note that argv[0] is the command call of this program */
	/* thus ignored */
	for (k = 0; (is_open && (k != N_NAMES)); ++k)
	{
		/* open the current file */
		file = fopen(names[k], "r");
		/* check if able to open file */
		is_open = (NULL != file);

		/* if able to open */
		if (is_open) {
			/* concatenate the current file */
			wgrepf(key, file, stdout);
			/* close the current file */
			fclose(file);
		} /* end if (is_open) */

		else {
			/* print an error message */
			fprintf(stderr, "wgrep: cannot open file\n");
		} /* end if (!is_open) */
	} /* end for (; (is_open && (k < argc)); ); */

	return is_open;
}

/**
 * Copies each line in infile to outfile, containing the specified key.
 * params:
 *   key     : char* = the search string
 *   infile  : FILE* = wherefrom to read
 *   outfile : FILE* = whereto to write
 */
void
wgrepf(char* key, FILE* infile, FILE* outfile)
{
	/* end of file flag */
	const int EOFF = -1;

	size_t len; /* number of characters read */
	/* current line buffer */
	char* line;
	/* pointer to the substring where the key is found at each line */
	char *substr;

	/* read to line buffer while not EOF */
	while (EOFF != getline(&line, &len, infile))
	{
		/* search for the key */
		substr = strstr(line, key);
		/* if it's found */
		if (NULL != substr) {
			/* print the line to the outfile */
			fprintf(outfile, "%s", line);
		} /* end if (NULL != substr) */
	} /* end while (NULL != fgets(, , infile); */
	/* deallocate the line buffer */
	free(line);
} /* end wcpf(char*, FILE*, FILE*); */

