#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

#define BUFSIZE 1000
#define NAMELEN 10
#define PATHLEN 100 // Implicit: Path to directory must be <= 90 characters

void copy_file(char * parent_name, char * child_name) {
	unsigned int buf[BUFSIZE];
	FILE *parent, *child;

	snprintf(child_name, NAMELEN, "%d", rand());

	parent = fopen(parent_name, "rb");
	child = fopen(child_name, "wb");

	while (!feof(parent)) {
		fread(buf, sizeof(unsigned int), BUFSIZE, parent);
		fwrite(buf, sizeof(unsigned int), BUFSIZE, child);
	}

	fclose(parent);
	fclose(child);
}

void reproduce(char *parent_name) {
	pid_t my_pid;
	char child_name[NAMELEN];

	copy_file(parent_name, child_name);

	my_pid = fork();
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
