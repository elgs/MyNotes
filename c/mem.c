#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	const unsigned long size = 1<<30;
	char* src = (char*) malloc(size);
	char* dst = (char*) malloc(size);
	
	for(int i=0;i<100;++i){
		memcpy(dst, src, size);
	}
	free(src);
	free(dst);
	return 0;
}
