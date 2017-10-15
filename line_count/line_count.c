#include <stdio.h>
#include <stdlib.h>

#define SIZEBUF 65536

void Usage() 
{
	fprintf(stderr,
		"my_wc. Usage: \n"
		"my_wc  input_filename\n"
		"\n");
	exit(EXIT_FAILURE);
}

unsigned long long core(FILE *f)
{
	unsigned long long counter = 0;
	char *buf = malloc(SIZEBUF);
	while (!feof(f))
	{
		const size_t block_length = fread(buf, sizeof(char), SIZEBUF, f);
		for (size_t i = 0; i < block_length; ++i)
		{
			if (buf[i] == '\n') {
				++counter;
			}
		}
	}
	free(buf);
	return counter;
}

int main(int argc, char** argv)
{
	if (argc != 2) {
		Usage();
	}
	FILE *f = fopen(argv[1], "r");
	if (f == NULL) {
		fprintf(stderr,"my_wc: No such file or directory\n");
		return EXIT_FAILURE;
	}
	printf("%llu", core(f));
	fclose(f);
	return EXIT_SUCCESS;
}
