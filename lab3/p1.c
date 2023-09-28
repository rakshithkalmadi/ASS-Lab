#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LENGTH 1024

void grep(const char *filename,const char *search_term){
	FILE *file = fopen(filename,"r");
	if(file==NULL){
		printf("Error file not found\n");
		return;
	}
	char line[MAX_LENGTH];
	while(fgets(line,sizeof(line),file)){
		if(strstr(line,search_term)!=NULL){
			printf("%s\n",line );
		}
	}
	fclose(file);

}

int main(int argc, char const *argv[])
{
	if(argc!=3){
		printf("Usage: %s <filename> <search_term>\n",argv[0] );
	}
	else{
		const char *filename=argv[1];
		const char *search_term=argv[2];
		grep(filename,search_term);
	}
	return 0;
}