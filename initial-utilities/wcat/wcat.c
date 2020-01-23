#include <stdlib.h> /* malloc */
#include <stdio.h> /* FILE, fopen, fgets, fclose */

int
main(int argc, char** argv)
{
	/* prototypes */
	int wcatf(FILE*); /* single file concatenate */

	size_t k; /* file counter */
	FILE* file; /* the file to read */

	/* for each file */
	/* note that argv[0] is the command call of this program */
	for (k = 1, ++argv; (k < argc); ++k, ++argv)
	{
		/* concatenate the file */
		printf("reading %s . . .", *argv);
		file = fopen(*argv, "r");
		wcatf(file);
	} /* end for (; k < argc; ); */
	return 0;
} /* end main(int, char**); */

int wcatf(FILE* file)
{
	const size_t LEN = 255; /* number of chracters to read at a time */
	char* line = ((char*) malloc(LEN * sizeof(char))); /* current line */
	while (NULL != fgets(line, 255, file))
	{
		printf("%s", line);
	}
	return 0;
}

