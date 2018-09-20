
#include <stdio.h>

int main ()
{	
	
    int buffer;

    FILE * fp = fopen("main.c", "r");
    if (fp == NULL) {
        return (-1);
                    }
    if (fp) {
        while ((buffer = getc(fp)) != EOF)
        putchar(buffer);
            }
    
    fclose(fp);

    return 0;

}
