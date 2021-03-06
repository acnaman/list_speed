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
    int list_size = LIST_SIZE;
    int struct_size = sizeof(STTEST);
    int res1, res2, res3;
    char filename[128];
    int i;

    FILE* fp;
    sprintf(filename, "result/%d_%d.csv" , STRUCT_SIZE, LIST_SIZE);
    fp = fopen(filename, "w");
    fprintf(fp, "length : %d\n", list_size);
    fprintf(fp, "struct size : %d\n", struct_size);

    fprintf(fp, ",A.都度確保,B.一挙確保,C.折衷案\n", struct_size);

    for(i = COUNT_UP; i < list_size; i+=COUNT_UP){
        /* 都度確保 */
        c_start = clock();
        allocate_by_time(i);
        c_end = clock();
        res1 = (int)c_end - c_start;

        /* 一挙確保 */
        c_start = clock();
        allocate_bigmemory(i);
        c_end = clock();
        res2 = (int)c_end - c_start;
        
        /* 折衷案 */
        c_start = clock();
        allocate_bigmemory(i);
        c_end = clock();
        res3 = (int)c_end - c_start;

        /* ファイル出力 */
        fprintf(fp, "%d,%d,%d,%d\n", i, res1,res2,res3);
    }
    fclose(fp);

}

/* ループのたびにreallocし直す */
void allocate_by_time(int size){
    int i;
    const int sz = size;
    STTEST *ptstruct;
    
    for(i = 0; i < sz ;i++){
        if(i == 0) {
            /* 初回のみmalloc */
            ptstruct = (STTEST*)malloc(sizeof(STTEST));
        } else {
            ptstruct = (STTEST*)realloc(ptstruct, sizeof(STTEST)*(i + 1));
        }
        /* 適当な処理 */
        ptstruct[i].str[0] = '/0';
    }
    free(ptstruct);
}

/* 最初に十分なメモリサイズを取得する */
void allocate_bigmemory(int size){
    int i;
    const int sz = size;
    const int BIGSIZE = LIST_SIZE;
    STTEST *ptstruct;

    /* 最大要素数分のメモリを確保 */
    ptstruct = (STTEST*)malloc(sizeof(STTEST) * BIGSIZE);
    
    for(i = 0; i < sz ;i++){
        /* 適当な処理 */
        ptstruct[i].str[0] = '/0';
    }
    free(ptstruct);
}

/* 一定数ずつ確保する */
void allocate_by_span(int size){
    int i;
    const int sz = size;
    STTEST *ptstruct;
    
    for(i = 0; i < sz ;i++){
        if(i == 0) {
            /* 初回のみmalloc */
            ptstruct = (STTEST*)malloc(sizeof(STTEST)*ALLOC_COUNT);
        } else if (i % ALLOC_COUNT == 0){
            ptstruct = (STTEST*)realloc(ptstruct, sizeof(STTEST)*(i + ALLOC_COUNT));
        }
        /* 適当な処理 */
        ptstruct[i].str[0] = '/0';
    }
    free(ptstruct);
}

