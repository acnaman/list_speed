#include <stdio.h>
#include <time.h>

void bigmemory(int);
void littlesize(int);

typedef struct {
    char str[10000];
} STTEST;

int main(void** argc)
{
    clock_t c_start, c_end;
    time_t t_start, t_end;
    int size = 1000;

    /* 開始時間の測定 */
    c_start = clock();
    t_start = time(NULL);

    littlesize(size);
    //bigmemory(size);

    /* 終了時間の測定 */
    c_end = clock();
    t_end = time(NULL);

    printf("%f\n", (double)(c_end - c_start) / CLOCKS_PER_SEC);
    printf("%ld\n", t_end - t_start);
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

/* 最小のサイズをalllocationし直す */
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



