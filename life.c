#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

#define BUFSIZE 1000
#define NAMELEN 10
#define PATHLEN 100 // Implicit: Path to directory must be <= 90 characters

void mutate(unsigned int *buf) {
	int i;
	for (i = 0; i < BUFSIZE; i++) {
		if (rand() < RAND_MAX / 2000) { // 1/2000 chance
			int index = (int)((float) rand() / RAND_MAX * sizeof(unsigned int));
			unsigned int mutator = 0b1 << index;
			buf[i] ^= mutator;
		}
	}
}

void reproduce(char *parent_name) {
	char child_name[NAMELEN];
	unsigned int buf[BUFSIZE];

	snprintf(child_name, NAMELEN, "%d", rand());

	FILE *parent = fopen(parent_name, "rb");
	FILE *child = fopen(child_name, "wb");

	while (!feof(parent)) {
		fread(buf, sizeof(unsigned int), BUFSIZE, parent);
		mutate(buf);
		fwrite(buf, sizeof(unsigned int), BUFSIZE, child);
	}

	fclose(parent);
	fclose(child);

	pid_t my_pid = fork();
	if (my_pid == 0) { // Child
		printf("Starting %s\n", child_name);

		// Get path to containing directory
		char full_path[PATHLEN];
		getcwd(full_path, PATHLEN);
		strcat(full_path, "/");

		// Append child's name
		int current_length = strlen(full_path);
		strncat(full_path, child_name, PATHLEN - current_length);

		// Make child executable
		chmod(full_path, S_IXUSR | S_IWUSR | S_IRUSR);

		// Attempt to start child
		char *args[2] = { full_path, NULL };
		if (execvp(args[0], args) == -1) {
			printf("%s was not born\n", child_name);
		}
	}
}

int main(int argv, char **argc) {
	srand(time(0));

	while (1) {
		reproduce(argc[0]);
		sleep(1);
	}

	return 0;
}
