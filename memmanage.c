#include <stdio.h>
#include <stdlib.h>

typedef enum { CHAR, INT, DOUBLE, FLOAT, LONG } type;

#define ptr  (void**)&

struct ptr_table {
	void** ptrs;
	size_t free;
	size_t size;
};

struct ptr_table PTR_TABLE;

void meminit() {
	PTR_TABLE.ptrs = malloc(sizeof(void*) * 100);
	PTR_TABLE.free = 100;
	PTR_TABLE.size = 0;
}

void memexit() {
	for (int i = 0; i < PTR_TABLE.size; i++){
		free(PTR_TABLE.ptrs[i]);
	}
	free(PTR_TABLE.ptrs);
}

void alloc(void** p, size_t size, type ptype) {
	switch (ptype) {
	case CHAR:   *p = (char*) malloc(size); break;
	case INT:    *p = (int*) malloc(size*sizeof(int)); break;
	case DOUBLE: *p = (double*) malloc(size*sizeof(double)); break;
	case FLOAT:  *p = (float*) malloc(size*sizeof(float)); break;
	case LONG:   *p = (long*) malloc(size*sizeof(long)); break;
	}
	
	if (*p) {
		if (!PTR_TABLE.free) {
			PTR_TABLE.ptrs = realloc(PTR_TABLE.ptrs, PTR_TABLE.size*2 * sizeof(void*));
		}
		PTR_TABLE.ptrs[PTR_TABLE.size++] = *p;
		PTR_TABLE.free--;
	}
}


char* read_file(const char* file) {
	char* buffer = NULL;
	FILE* fp = fopen(file, "r");
	if (fp) {
		fseek(fp, 0, SEEK_END);
		long flen = ftell(fp);
		alloc(ptr buffer, flen, CHAR);
		fseek(fp, 0, SEEK_SET);
		if (buffer) {
			fread(buffer, 1, flen, fp);
		}
		fclose(fp);
	}
	return buffer;
}

int main() {
	meminit();
	
	char* str = read_file("field.txt");
	if (!str) {
		fprintf(stderr, "could not read file");
		exit(1);
	}
	puts(str);
    
	memexit();
	return 0;
}
