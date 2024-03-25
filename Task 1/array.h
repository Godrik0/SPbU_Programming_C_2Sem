#ifndef ARRAY_H_
#define ARRAY_H_

typedef struct 
{
    int size;
    int * data;
} array;


typedef struct
{
    int size;
    array ** data;
} array_2d;

void print_array(array_2d t);

void free_array(array * arr);

void free_array_2d(array_2d * arr);

array * create_row(int num);

array_2d create_array_2d();

int match_arrays(array_2d * arr1, array_2d * arr2);

#endif