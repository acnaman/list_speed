#ifndef STRUCT_SIZE
#define STRUCT_SIZE 1000
#endif

#ifndef LIST_SIZE
#define LIST_SIZE 10000
#endif

#if LIST_SIZE==10000
#define COUNT_UP 100
#define ALLOC_COUNT 1000
#endif
#if LIST_SIZE==1000
#define COUNT_UP 10
#define ALLOC_COUNT 100
#endif
#if LIST_SIZE==100
#define COUNT_UP 1
#define ALLOC_COUNT 10
#endif
