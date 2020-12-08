#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

void RightMatrix (int* mas, int m, int n);

int ConnectedGr (int ver, int reb);


int main(void){
    int* a;
    int* mesr;
    int i, j, n, m;
    int o = 0;
    int oo = 0;
    int k = 0;
    int MIN = 0;

    FILE* fl;

    printf("Ammount of peaks:\n");
    scanf("%d", &m);
    printf("Ammount of connections:\n");
    scanf("%d", &n);

    a = (int*)malloc(m*n * sizeof(int));
    mesr = (int*)calloc(m, sizeof(int));

    for (i = 0; i<n; i++)
    {
        for (j = 0; j<m; j++)
        {
            printf("String %d - Peak %d\n", i+1, j+1);
            scanf("%d", (a + i*m + j));
        }
    }

    RightMatrix(a, m, n);

    if (ConnectedGr(m, n) == 1) printf("Connected (only if simple)");
    else printf("Not connected (only if simple)");

    fl = fopen("DZ2.dot", "w+");

    if(fl == NULL) exit(000);

    fputs("graph G {\n", fl);

    for (k=1; k<m+1; k++)
    {
        char str[2];
        sprintf(str, "%d", k);
        fputs(str, fl);
        fputs(";\n", fl);
    }

    for (i = 0; i<n; i++)
    {
        for (j = 0; j<m; j++)
        {
            if (*(a + i*m + j) == 1){
                if(o == 0) o = j+1;
                else if(oo == 0){
                    oo = j+1;
                    *(mesr+o-1) = *(mesr+o-1)+1;
                    *(mesr+oo-1) = *(mesr+oo-1)+1;
                }
            }
        }
        if (oo == 0) fprintf(fl, "%d -- %d;\n", o, o);
        else fprintf(fl, "%d -- %d;\n", o, oo);
        o = 0;
        oo = 0;
    }

    fputs("}", fl);
    fclose(fl);

    MIN = m;

    for(int c=0; c<m; c++){
        if(*(mesr+c)<MIN) MIN = *(mesr+c);
    }

    if(m>=3){
        if(MIN>=m/2) printf("\nYay! H4m1lt0n joins the chat");
        else printf("No Hamilton spinning around tonight");
    }
    else printf("No Hamilton spinning around tonight");


    system("dot -Tpng DZ2.dot -o DZ2.PNG");
    system("DZ2.png");

    free(a);
    return 0;
}


void RightMatrix (int* mas, int m, int n){
    int k, l;
    int sch = 0;
    for (k = 0; k<n; k++)
    {
        for (l = 0; l<m; l++)
        {
           if (*(mas + k*m + l) == 1){
               sch = sch +1;
           }
        }
        if (sch >= 3){
            printf("Wrong Matrix");
            exit(228);
        }
        sch = 0;
    }
}

int ConnectedGr (int ver, int reb){
    int p = 0;
    p = ((ver-1)*(ver-2))/2;
    if (reb > p) return 1;
    else return 0;
}
