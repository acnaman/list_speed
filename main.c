#include <stdio.h>
#include <time.h>

void bigmemory(int);

struct STTEST{
    char str[1000];
};

int main(void** argc)
{
    clock_t c_start, c_end;
    time_t t_start, t_end;
    int size = 10000;

    /* 開始時間の測定 */
    c_start = clock();
    t_start = time(NULL);

    bigmemory(size);

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
    struct STTEST *ptstruct;
    ptstruct = (struct STTEST*)malloc(sizeof(struct STTEST) * size);
    
    for(i = 0; i < sz ;i++){
        ptstruct[i].str[0] = '/0';
    }
    free();
}



