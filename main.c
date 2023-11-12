#include "auth.h"

int main() {
	FILE* auth = fopen("/var/log/auth.log", "r");
	if(auth == NULL) {
		printf("Content-type: text/html\n\n");
		printf("Je ne peux pas l'ouvrir");
		exit(EXIT_FAILURE);
	}
	write_head();
	write_body(auth);
//	write_foot();
	return 0;
}

