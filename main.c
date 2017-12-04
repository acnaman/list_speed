#include <stdio.h>
#include <time.h>
#include "env.h"

void bigmemory(int);
void littlesize(int);
void hundredtimes(int);

typedef struct {
    char str[STRUCT_SIZE];
} STTEST;

int main(void** argc)
{
    clock_t c_start, c_end;
    int list_size = 100;
    int struct_size = sizeof(STTEST);

    printf("作成するリストの要素数：%d\n", list_size);
    printf("構造体1つのサイズ：%d\n", struct_size);

   /* 開始時間の測定 */
    c_start = clock();

    bigmemory(list_size);
    
    /* 終了時間の測定 */
    c_end = clock();

    printf("アルゴリズム1でかかった時間：%f秒\n", (double)(c_end - c_start) / CLOCKS_PER_SEC);

     /* 開始時間の測定 */
    c_start = clock();

    littlesize(list_size);
    
    /* 終了時間の測定 */
    c_end = clock();
    
    printf("アルゴリズム2でかかった時間：%f秒\n", (double)(c_end - c_start) / CLOCKS_PER_SEC);
   
   /* 開始時間の測定 */
    c_start = clock();

    hundredtimes(list_size);

    /* 終了時間の測定 */
    c_end = clock();

    printf("アルゴリズム3でかかった時間：%f秒\n", (double)(c_end - c_start) / CLOCKS_PER_SEC);
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

