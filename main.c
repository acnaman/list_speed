#include <stdio.h>
#include <time.h>
#include "env.h"

void bigmemory(int);
void littlesize(int);
void hundredtimes(int);

typedef struct {
    char str[STRUCT_SIZE];
} STTEST;

int main(void)
{
    clock_t c_start, c_end;
    int list_size = 10000;
    int struct_size = sizeof(STTEST);
    double res1, res2, res3;
    int i;

    FILE* fp;
    fp = fopen("result.txt", "w");
    fprintf(fp, "length : %d\n", list_size);
    fprintf(fp, "struct size : %d\n", struct_size);

    for(i = 0; i < list_size; i+=10){
        /* 従来型 */
        c_start = clock();
        littlesize(i);
        c_end = clock();
        res1 = (double)c_end - c_start;

        /* 確保型 */
        c_start = clock();
        bigmemory(i);
        c_end = clock();
        res2 = (double)c_end - c_start;
        
        /* 折衷案 */
        c_start = clock();
        hundredtimes(i);
        c_end = clock();
        res3 = (double)c_end - c_start;

        fprintf(fp, "%d,%f,%f,%f\n", i, res1,res2,res3);
    }
    fclose(fp);

}

/* ループのたびにreallocし直す */
void littlesize(int size){
    int i;
    const int sz = size;
    STTEST *ptstruct;
    
    for(i = 0; i < sz ;i++){
        if(i == 0) {
            ptstruct = (STTEST*)malloc(sizeof(STTEST));
        } else {
            ptstruct = (STTEST*)realloc(ptstruct, sizeof(STTEST)*(i + 1));
        }
        ptstruct[i].str[0] = '/0';
    }
    free(ptstruct);
}

/* とにかく最初に大きなメモリサイズを取得する */
void bigmemory(int size){
    int i;
    const int sz = size;
    const int BIGSIZE = 100000;
    STTEST *ptstruct;

    ptstruct = (STTEST*)malloc(sizeof(STTEST) * BIGSIZE);
    
    for(i = 0; i < sz ;i++){
        ptstruct[i].str[0] = '/0';
    }
    free(ptstruct);
}

/* 100ずつ確保する */
void hundredtimes(int size){
    int i;
    const int sz = size;
    STTEST *ptstruct;
    
    for(i = 0; i < sz ;i++){
        if(i == 0) {
            ptstruct = (STTEST*)malloc(sizeof(STTEST)*100);
        } else if (i % 100 == 0){
            ptstruct = (STTEST*)realloc(ptstruct, sizeof(STTEST)*(i + 100));
        }
        ptstruct[i].str[0] = '/0';
    }
    free(ptstruct);
}

