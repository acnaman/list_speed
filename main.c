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
    double res1, res2, res3;
    char filename[128];
    int i;

    FILE* fp;
    sprintf(filename, "result/%d_%d.txt" , STRUCT_SIZE, LIST_SIZE);
    fp = fopen(filename, "w");
    fprintf(fp, "length : %d\n", list_size);
    fprintf(fp, "struct size : %d\n", struct_size);

    for(i = COUNT_UP; i < list_size; i+=COUNT_UP){
        /* �]���^ */
        c_start = clock();
        littlesize(i);
        c_end = clock();
        res1 = (double)c_end - c_start;

        /* �m�ی^ */
        c_start = clock();
        bigmemory(i);
        c_end = clock();
        res2 = (double)c_end - c_start;
        
        /* �ܒ��� */
        c_start = clock();
        hundredtimes(i);
        c_end = clock();
        res3 = (double)c_end - c_start;

        fprintf(fp, "%d,%f,%f,%f\n", i, res1,res2,res3);
    }
    fclose(fp);

}

/* ���[�v�̂��т�realloc������ */
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

/* �Ƃɂ����ŏ��ɑ傫�ȃ������T�C�Y���擾���� */
void bigmemory(int size){
    int i;
    const int sz = size;
    const int BIGSIZE = LIST_SIZE;
    STTEST *ptstruct;

    ptstruct = (STTEST*)malloc(sizeof(STTEST) * BIGSIZE);
    
    for(i = 0; i < sz ;i++){
        ptstruct[i].str[0] = '/0';
    }
    free(ptstruct);
}

/* ��萔���m�ۂ��� */
void hundredtimes(int size){
    int i;
    const int sz = size;
    STTEST *ptstruct;
    
    for(i = 0; i < sz ;i++){
        if(i == 0) {
            ptstruct = (STTEST*)malloc(sizeof(STTEST)*ALLOC_COUNT);
        } else if (i % ALLOC_COUNT == 0){
            ptstruct = (STTEST*)realloc(ptstruct, sizeof(STTEST)*(i + ALLOC_COUNT));
        }
        ptstruct[i].str[0] = '/0';
    }
    free(ptstruct);
}

