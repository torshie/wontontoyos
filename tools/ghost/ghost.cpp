#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage %s <command to execute>\n", argv[0]);
		return 1;
	}
	if (fork() == 0) {
		if (daemon(1, 0) != 0) {
			perror("daemon() failed");
			return 1;
		}
		system(argv[1]);
	} else {
		sleep(2);
	}
	return 0;
}
