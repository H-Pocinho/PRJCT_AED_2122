#include <stdio.h>

void main(){

    FILE *fp;
    int i;

    fp=fopen("test.in", "w+");

    fprintf(fp,"11001 11001\n");
    fprintf(fp,"11001 11001\n");
    fprintf(fp,"11001\n");

    for ( i = 1; i < 11001; i++)
    {
        if(i==5500) fprintf(fp, "%d 5500 1\n", i);
        else
        fprintf(fp, "%d 5500 -1\n", i);
    }
}