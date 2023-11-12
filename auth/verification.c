#include <stdio.h>

int main() {
	char *a = getenv("QUERY_STRING");
	char *name, *passwd, *confirm_passwd;

	if((name = strstr(a, "name="))) {
		sscanf(name, "name=%m[^\n&]", &name);
	}
	else {


	if((passwd = strstr(a, "passwd="))) {
		sscanf(passwd, "passwd=%m[^\n&]", &passwd);
	}
	if((confirm_passwd = strstr(a, "confirm="))) {
		sscanf(confirm_passwd, "confirm=%[^\n&]", &confirm_passwd);
	}



	return 0;

}
