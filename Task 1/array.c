#include <stdio.h>
#include <stdlib.h>

#include "array.h"

array * create_row(int num){
    array * row = (array*)malloc(sizeof(array));

    printf("\nColumns count for row %d = ", num);
    scanf("%d", &row->size);

    row->data = (int *)malloc(row->size * sizeof(int));

    for(size_t i = 0; i < row->size; i++){
        printf("table[%d][%d]= ", num, (int)i);
        scanf("%d", &row->data[i]);
    }

    return row;

}

array_2d * create_array_2d(){
    array_2d * t = (array_2d *)malloc(sizeof(array_2d));

    printf("Number of columns = ");
    scanf("%d", &t->size);

    t->data = (array **)malloc(t->size * sizeof(array));

    if(t->data != NULL){
        for (size_t i = 0; i < t->size; i++)
        {
            t->data[i] = create_row(i);
        }
        
    }

    return t;
}

void free_array(array * arr){
    free(arr->data);
    free(arr);
}

void free_array_2d(array_2d * arr){
    for (size_t i = 0; i < arr->size; i++)
    {
        if (arr->data!=NULL)
        {
            free_array(arr->data[i]);
            
        }
        
    }
    free(arr->data);
    free(arr);
}

void print_array(array_2d * t){
    for (size_t i = 0; i < t->size; i++)
    {
        for (size_t j = 0; j < t->data[i]->size; j++)
        {
            printf("%d ", t->data[i]->data[j]);
        }
        printf("\n");
    }
    
}

int match_arrays(array_2d * arr1, array_2d * arr2){
    if(arr1->size != arr2->size){
        return 0;
    }

    int * used_rows = (int *)calloc(arr2->size, sizeof(int));

    for (size_t i = 0; i < arr1->size; i++)
    {
        int match_array = 0;

        for (size_t j = 0; j < arr2->size; j++)
        {
            if(used_rows[j]){
                continue;
            }

            if(arr1->data[i]->size != arr2->data[j]->size){
                continue;
            }

            int match_row = 1;

            int * used_elements = (int *)calloc(arr1->data[i]->size, sizeof(int));

            for (size_t k = 0; k < arr1->data[i]->size; k++)
            {
                int match_current = 0;

                for (size_t t = 0; t < arr2->data[j]->size; t++)
                {
                    if (arr1->data[i]->data[k] == arr2->data[j]->data[t] && used_elements[t] != 1)
                    {
                        match_current = 1;
                        used_elements[t] = 1;
                        break;
                    }
                }

                if (!match_current)
                {
                    match_row = 0;
                    break;
                }
                                
            }

            if (match_row)
            {
                free(used_elements);
                match_array = 1;
                used_rows[j] = 1;
                break;
            }
            
            free(used_elements);
        }

        if (!match_array)
        {
            free(used_rows);
            return 0;
        }
        
    }

    free(used_rows);
    return 1;
}


int main(){
    array_2d * t = create_array_2d();
    array_2d * t2 = create_array_2d();
    printf("\n\n");
    print_array(t);
    printf("\n\n");
    print_array(t2);
    printf("\n\n");
    
    printf("Match result %d \n", match_arrays(t, t2));

    free_array_2d(t);
    free_array_2d(t2);
    //system("pause");
    return 0;
}