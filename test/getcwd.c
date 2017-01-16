#include <stdio.h>
#include <unistd.h>

int main() {
	char buf[256];
	getcwd(buf, sizeof(buf));
	printf("current directory: %s\n", buf);
	return 0;
}
