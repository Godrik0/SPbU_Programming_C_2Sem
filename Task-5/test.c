#include "cstring.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void testing_cstring_create()
{
    const char * test_mes = "Hello, World!";
    cstring * str = cstring_create(test_mes);
    assert(str != NULL);
    assert(str->length == strlen(test_mes));
    assert(str->capacity == strlen(test_mes) << 1);
    assert(str->data != NULL);
    assert(strcmp(str->data, test_mes) == 0);

    cstring_delete(str);

    printf("Testing cstring_create passed!\n");
}

void testing_cstring_insert_within_capacity()
{
    const char * test_mes = "Hello, World!";
    const char * expected_mes = "Hello, my World!";

    cstring * str = cstring_create(test_mes);

    cstring_insert(str, "my ", 7);

    assert(strcmp(str->data, expected_mes) == 0);
    
    cstring_delete(str);

    printf("Testing cstring insert within capacity passed!\n");
}

void testing_cstring_insert_exceed_capacity()
{
    const char * test_mes = "Hello";
    const char * expected_mes = "Hello, my World!";

    cstring * str = cstring_create(test_mes);

    cstring_insert(str, ", my World!", 5);

    assert(strcmp(str->data, expected_mes) == 0);
    assert(str->length == strlen(expected_mes));
    
    cstring_delete(str);

    printf("Testing cstring insert exceed capacity passed!\n");
}

void testing_cstring_append()
{
    const char * test_mes = "Hello";
    const char * expected_mes = "Hello my World!";

    cstring * str = cstring_create(test_mes);

    cstring_append(str, " my World!");

    assert(strcmp(str->data, expected_mes) == 0);
    assert(str->length == strlen(expected_mes));
    
    cstring_delete(str);

    printf("Testing cstring append passed!\n");
}

void test_cstring_substring() 
{
    cstring *str = cstring_create("Hello, World!");

    // Тест 1
    cstring *sub1 = cstring_substring(str, 0, 5);
    assert(sub1 != NULL);
    cstring * sub1_exp = cstring_create("Hello");
    assert(cstring_compare(sub1, sub1_exp) == 0);
    cstring_delete(sub1);
    cstring_delete(sub1_exp);

    // Тест 2
    cstring *sub2 = cstring_substring(str, 7, 5);
    assert(sub2 != NULL);
    cstring * sub2_exp = cstring_create("World");
    assert(cstring_compare(sub2, sub2_exp) == 0);
    cstring_delete(sub2);
    cstring_delete(sub2_exp);

    // Тест 3
    cstring *sub3 = cstring_substring(str, 13, 5);
    assert(sub3 == NULL);

    cstring_delete(str);

    printf("Testing cstring substring passed!\n");
}

void test_cstring_find() 
{
    cstring *text = cstring_create("Hello, World!");

    // Тест 1
    int pos1 = cstring_find(text, "Hello", 0);
    assert(pos1 == 0);

    // Тест 2
    int pos2 = cstring_find(text, "World", 7);
    assert(pos2 == 7);

    // Тест 3
    int pos3 = cstring_find(text, "World", 8);
    assert(pos3 == -1);

    // Тест 4
    int pos4 = cstring_find(text, "!", 0);
    assert(pos4 == 12);


    cstring_delete(text);
    printf("Testing cstring find passed!\n");
}

void test_cstring_split() 
{
    cstring *str = cstring_create("apple,banana,orange,grape");

    // Разделение строки по запятой
    cstring **result1 = cstring_split(str, ",");
    assert(result1 != NULL);

    cstring *expected1_0 = cstring_create("apple");
    cstring *expected1_1 = cstring_create("banana");
    cstring *expected1_2 = cstring_create("orange");
    cstring *expected1_3 = cstring_create("grape");

    assert(cstring_compare(result1[0], expected1_0) == 0);
    assert(cstring_compare(result1[1], expected1_1) == 0);
    assert(cstring_compare(result1[2], expected1_2) == 0);
    assert(cstring_compare(result1[3], expected1_3) == 0);

    cstring_delete(expected1_0);
    cstring_delete(expected1_1);
    cstring_delete(expected1_2);
    cstring_delete(expected1_3);

    for (int i = 0; result1[i] != NULL; i++) {
        cstring_delete(result1[i]);
    }
    free(result1);

    // Разделение строки по пробелу
    cstring **result2 = cstring_split(str, " ");
    assert(result2 != NULL);

    assert(cstring_compare(result2[0], str) == 0);
    assert(result2[1] == NULL);

    for (int i = 0; result2[i] != NULL; i++) {
        cstring_delete(result2[i]);
    }
    free(result2);

    cstring_delete(str);
    printf("Testing cstring split passed!\n");
}

int main()
{
    testing_cstring_create();
    testing_cstring_insert_within_capacity();
    testing_cstring_insert_exceed_capacity();
    testing_cstring_append();
    test_cstring_substring();
    test_cstring_find();
    test_cstring_split();

    return 0;
}
