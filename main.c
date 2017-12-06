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

    fprintf(fp, ",A.�s�x�m��,B.�ꋓ�m��,C.�ܒ���\n", struct_size);

    for(i = COUNT_UP; i < list_size; i+=COUNT_UP){
        /* �s�x�m�� */
        c_start = clock();
        allocate_by_time(i);
        c_end = clock();
        res1 = (int)c_end - c_start;

        /* �ꋓ�m�� */
        c_start = clock();
        allocate_bigmemory(i);
        c_end = clock();
        res2 = (int)c_end - c_start;
        
        /* �ܒ��� */
        c_start = clock();
        allocate_bigmemory(i);
        c_end = clock();
        res3 = (int)c_end - c_start;

        /* �t�@�C���o�� */
        fprintf(fp, "%d,%d,%d,%d\n", i, res1,res2,res3);
    }
    fclose(fp);

}

/* ���[�v�̂��т�realloc������ */
void allocate_by_time(int size){
    int i;
    const int sz = size;
    STTEST *ptstruct;
    
    for(i = 0; i < sz ;i++){
        if(i == 0) {
            /* ����̂�malloc */
            ptstruct = (STTEST*)malloc(sizeof(STTEST));
        } else {
            ptstruct = (STTEST*)realloc(ptstruct, sizeof(STTEST)*(i + 1));
        }
        /* �K���ȏ��� */
        ptstruct[i].str[0] = '/0';
    }
    free(ptstruct);
}

/* �ŏ��ɏ\���ȃ������T�C�Y���擾���� */
void allocate_bigmemory(int size){
    int i;
    const int sz = size;
    const int BIGSIZE = LIST_SIZE;
    STTEST *ptstruct;

    /* �ő�v�f�����̃��������m�� */
    ptstruct = (STTEST*)malloc(sizeof(STTEST) * BIGSIZE);
    
    for(i = 0; i < sz ;i++){
        /* �K���ȏ��� */
        ptstruct[i].str[0] = '/0';
    }
    free(ptstruct);
}

/* ��萔���m�ۂ��� */
void allocate_by_span(int size){
    int i;
    const int sz = size;
    STTEST *ptstruct;
    
    for(i = 0; i < sz ;i++){
        if(i == 0) {
            /* ����̂�malloc */
            ptstruct = (STTEST*)malloc(sizeof(STTEST)*ALLOC_COUNT);
        } else if (i % ALLOC_COUNT == 0){
            ptstruct = (STTEST*)realloc(ptstruct, sizeof(STTEST)*(i + ALLOC_COUNT));
        }
        /* �K���ȏ��� */
        ptstruct[i].str[0] = '/0';
    }
    free(ptstruct);
}

