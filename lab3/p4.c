#include<stdio.h>
int main()
{
	/* code */
	FILE *sourceFile = fopen("new.txt","r");
	FILE *destFile = fopen("destination.txt","w");
	if(sourceFile==NULL){
		printf("Error cant read source file\n");
		return 1;
	}
	if(destFile==NULL){
		printf("Error cant read destination file\n");
		return 1;
	}
	int character;
	while((character=fgetc(sourceFile))!=EOF){
		fputc(character,destFile);
	}
	printf("File copied sucessfully\n");
	fclose(sourceFile);
	fclose(destFile);

	return 0;
}