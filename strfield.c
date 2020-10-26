#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// this will always leave leaking memory, I think
char* strfield(char* src, char delim, int field) {
	size_t len = strlen(src);
	char* ret  = strdup(src);
	char *lb = ret-2, *rb = ret+len+1;

	int found = 1, mov = 1;
	if(field < 0) {
		ret += len;
		mov = -1;
	}

	char* iter = ret;
	while (iter += mov) {
		if (iter < lb || iter > rb) {
			*ret = 0;
			break;
		}

		if (iter == lb || iter == rb || *(iter-mov) == delim) {
			*(iter - mov) = 0;
			if (found++ == abs(field)) {
				if (field < 0) {
					ret = iter + 2;
				}
				break;
			}
			ret = iter;
		}
	}

	return ret;
}


int main() {
	char test[] = "ab.hello.yz";
	printf("'%s'.split('.')[-4] = '%s'\n", test, strfield(test, '.', -4));
	printf("'%s'.split('.')[-3] = '%s'\n", test, strfield(test, '.', -3));
	printf("'%s'.split('.')[-2] = '%s'\n", test, strfield(test, '.', -2));
	printf("'%s'.split('.')[-1] = '%s'\n", test, strfield(test, '.', -1));
	printf("'%s'.split('.')[1] = '%s'\n", test, strfield(test, '.', 1));
	printf("'%s'.split('.')[2] = '%s'\n", test, strfield(test, '.', 2));
	printf("'%s'.split('.')[3] = '%s'\n", test, strfield(test, '.', 3));
	printf("'%s'.split('.')[4] = '%s'\n", test, strfield(test, '.', 4));
	return 0;
}
