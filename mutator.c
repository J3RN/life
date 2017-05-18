#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 1000
#define PATHLEN 100		/* Implicit: Argument must be < 90 characters */
#define MUTATION_PROB 0.0005	/* The probability each bit has of being flipped */

void mutate_buffer(char *buf)
{
	int i, j;

	for (i = 0; i < BUFSIZE; i++) { /* For each byte... */
		unsigned int mutator = 0b1;

		for (j = 0; j < 8; j++) { /* For each bit in that byte... */
			if (((float) rand() / RAND_MAX) < MUTATION_PROB) {
				buf[i] ^= mutator;
			}

			mutator = mutator << 1;
		}
	}
}

void mutate_file(char* dirname, char *filename)
{
	char buffer[BUFSIZE], full_path[PATHLEN];
	FILE *file;

	snprintf(full_path, PATHLEN, "%s/%s", dirname, filename);

	if (!(file = fopen(full_path, "rb+"))) {
		perror("fopen()");
		return;
	}

	while (!feof(file)) {
		size_t ret_code = fread(buffer, sizeof(*buffer), BUFSIZE, file);
		if (ret_code != BUFSIZE) {
			printf("Presumably an error?\n");
		}
		mutate_buffer(buffer);
		fwrite(buffer, sizeof(*buffer), BUFSIZE, file);
	}

	fclose(file);
}

void mutate_in_dir(char *dirname)
{
	DIR *dp;
	struct dirent *ep;

	if ((dp = opendir(dirname))) {
		while ((ep = readdir(dp))) {
			if (ep->d_type == DT_REG) {
				mutate_file(dirname, ep->d_name);
			}
		}

		closedir(dp);
	}
	else
	{
		perror("opendir()");
	}

}

int main(int argv, char **argc)
{
	if (argv != 2)
	{
		printf("Usage: mutator <target directory>\n");
		exit(1);
	}

	while (1)
	{
		mutate_in_dir(argc[1]);
		sleep(1);
	}
}
