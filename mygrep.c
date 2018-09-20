#include <stdio.h>
#include <string.h>

int main(){
	char buffer[500];

FILE *fp = fopen("main.c", "r");
if (fp == NULL){
	printf("File is empty\n");
	return 0;
}
else{
	while(fgets(buffer, 500, fp) != NULL){
		if(strstr(buffer, "Glo")){
			puts(buffer);

		}	
	}
}
fclose(fp);
return 0;
}
