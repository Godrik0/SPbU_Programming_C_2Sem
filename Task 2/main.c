#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node Node;

struct Node{
    int value;
    int count_dividers;
    Node ** dividers;

};

Node *find_dividers(int number, Node **cache) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->value = number;

    Node **interim_dividers = (Node **)malloc(number * sizeof(Node *));
    for (int i = 0; i < number; i++) {
        interim_dividers[i] = NULL;
    }

    int count = 0;
    for (int i = 2; i <= sqrt(number); i++) {
        if (number % i == 0 && cache[i] != NULL) {
            interim_dividers[i] = cache[i];
            count++;
        } else {
            if (number % i == 0) {
                cache[i] = find_dividers(i, cache);
                interim_dividers[i] = cache[i];
                count++;
            } else {
                interim_dividers[i] = NULL;
            }
        }

        if (cache[number / i] != NULL) {
            interim_dividers[number / i] = cache[number / i];
            count++;
        } else {
            if (number % i == 0) {
                cache[number / i] = find_dividers(number / i, cache);
                interim_dividers[number / i] = cache[number / i];
                count++;
            } else {
                interim_dividers[number / i] = NULL;
            }
        }
    }
    
    node->count_dividers = count;
    node->dividers = (Node **)malloc(count * sizeof(Node));

    int j = 0;
    for (int i = 0; i < number; i++) {
        if (interim_dividers[i] != NULL) {
            node->dividers[j] = interim_dividers[i];
            j++;
        }
    }

    free(interim_dividers);

    //printf("Value:%d \tDividers:%d \n", number, count);
    return node;
}

void print(Node * n){
    printf("%d \n| \n", n->value );
    for (size_t i = 0; i < n->count_dividers; i++) { 
        printf("%d\n| \n", n->dividers[i]->value);
        
    }
    printf("%d", n->count_dividers);
    printf("\n\n");
}

int main(){
    
    int start, end;

    printf("Enter start: ");
    scanf("%d", &start);

    printf("Enter end: ");
    scanf("%d", &end);

    Node ** cache = (Node **)malloc(end * sizeof(Node));

    for (size_t i = 0; i < end; i++)
    {
        cache[i] = NULL;
    }

    for (size_t i = start; i <= end ; i++)
    {
        Node * n = find_dividers(i, cache);
        print(n);
    }
    
    return 0;
}