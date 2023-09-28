#include<stdio.h>
#include<stdlib.h>

#define LINES_PER 20

void more(const char *filename){
	FILE *file=fopen(filename,"r");
	if(!file){
		printf("Error file not found\n");
		return;
	}
	char line[1024];
	for(int line_number=1;fgets(line,sizeof(line),file);line_number++){
		printf("%s\n",line );
		if(line_number%LINES_PER==0){
			printf("Press Enter to continue and q to quit\n");
			if(getchar()=='q')
				break;
		}
	}
	fclose(file);
}

int main(int argc, char const *argv[])
{
	if(argc<2){
		printf("Usage %s <filename> [filenames...]\n",argv[0] );
		return 1;
	}
	for(int i=1;i<argc;i++){
		more(argv[i]);

	}
	return 0;
}

