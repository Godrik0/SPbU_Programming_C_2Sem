#include "cstring.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void custom_assert(int expr)
{
    if(!expr)
    {
        printf("Error\n");
        exit(1);
    }
}

void testing_cstring_create()
{
    const char * test_mes = "Hello, World!";
    cstring * str = cstring_create(test_mes);
    custom_assert(str != NULL);
    custom_assert(str->length == strlen(test_mes));
    custom_assert(str->size_allocated_memory == strlen(test_mes) << 1);
    custom_assert(str->data != NULL);
    custom_assert(strcmp(str->data, test_mes) == 0);

    cstring_delete(str);

    printf("Testing cstring create passed!\n");
}

void testing_cstring_insert_within_capacity()
{
    const char * test_mes = "Hello, World!";
    const char * expected_mes = "Hello, my World!";

    cstring * str = cstring_create(test_mes);

    int memory_size = str->size_allocated_memory;

    cstring_insert_char(str, "my ", 7);

    custom_assert(strcmp(str->data, expected_mes) == 0);
    custom_assert(str->length == strlen(expected_mes));
    custom_assert(memory_size == str->size_allocated_memory);
    
    cstring_delete(str);

    printf("Testing cstring insert within size_allocated_memory passed!\n");
}

void testing_cstring_insert_exceed_capacity()
{
    const char * test_mes = "Hello";
    const char * expected_mes = "Hello, my World!";

    cstring * str = cstring_create(test_mes);

    cstring_insert_char(str, ", my World!", 5);

    custom_assert(strcmp(str->data, expected_mes) == 0);
    custom_assert(str->length == strlen(expected_mes));
    custom_assert(str->size_allocated_memory >= (strlen(expected_mes) + 1));
    
    cstring_delete(str);

    printf("Testing cstring insert exceed size_allocated_memory passed!\n");
}

void testing_cstring_insert_cstring()
{
    const char * test_mes = "Hello";
    const char * expected_mes = "Hello, my World!";

    cstring * str = cstring_create(test_mes);
    cstring * str2 = cstring_create(", my World!");

    cstring_insert_cstring(str, str2, 5);

    custom_assert(strcmp(str->data, expected_mes) == 0);
    custom_assert(str->length == strlen(expected_mes));
    custom_assert(str->size_allocated_memory >= (strlen(expected_mes) + 1));
    
    cstring_delete(str);
    cstring_delete(str2);

    printf("Testing cstring insert cstring\n");
}

void testing_cstring_append()
{
    const char * test_mes = "Hello";
    const char * expected_mes = "Hello my World!";

    cstring * str = cstring_create(test_mes);

    cstring_append(str, " my World!");

    custom_assert(strcmp(str->data, expected_mes) == 0);
    custom_assert(str->length == strlen(expected_mes));
    custom_assert(str->size_allocated_memory >= (strlen(expected_mes) + 1));
    
    cstring_delete(str);

    printf("Testing cstring append passed!\n");
}

void testing_cstring_concatenation()
{
    const char * test_mes_1 = "Hello";
    const char * test_mes_2 = " my World!";
    const char * expected_mes = "Hello my World!";

    cstring * str1 = cstring_create(test_mes_1);
    cstring * str2 = cstring_create(test_mes_2);

    cstring_concatenation(str1, str2);

    custom_assert(strcmp(str1->data, expected_mes) == 0);
    custom_assert(str1->length == strlen(expected_mes));
    custom_assert(str1->size_allocated_memory >= (strlen(expected_mes) + 1));
    
    cstring_delete(str1);
    cstring_delete(str2);

    printf("Testing cstring append passed!\n");
}

void test_cstring_substring() 
{
    cstring *str = cstring_create("Hello, World!");

    // Тест 1
    cstring *sub1 = cstring_substring(str, 0, 5);
    custom_assert(sub1 != NULL);
    cstring * sub1_exp = cstring_create("Hello");
    custom_assert(cstring_compare(sub1, sub1_exp) == 0);
    cstring_delete(sub1);
    cstring_delete(sub1_exp);

    // Тест 2
    cstring *sub2 = cstring_substring(str, 7, 5);
    custom_assert(sub2 != NULL);
    cstring * sub2_exp = cstring_create("World");
    custom_assert(cstring_compare(sub2, sub2_exp) == 0);
    cstring_delete(sub2);
    cstring_delete(sub2_exp);

    // Тест 3
    cstring *sub3 = cstring_substring(str, 13, 5);
    custom_assert(sub3 == NULL);

    // Test 4
    cstring *sub4 = cstring_substring(str, 10, 5);
    custom_assert(sub4 == NULL);

    printf("Testing cstring substring passed!\n");
}

void test_cstring_find() 
{
    cstring *text = cstring_create("Hello, World!");

    // Тест 1
    int pos1 = cstring_find(text, "Hello", 0);
    custom_assert(pos1 == 0);

    // Тест 2
    int pos2 = cstring_find(text, "World", 7);
    custom_assert(pos2 == 7);

    // Тест 3
    int pos3 = cstring_find(text, "World", 8);
    custom_assert(pos3 == -1);

    // Тест 4
    int pos4 = cstring_find(text, "!", 0);
    custom_assert(pos4 == 12);


    cstring_delete(text);
    printf("Testing cstring find passed!\n");
}

void test_cstring_rfind() 
{
    cstring *text = cstring_create("Hello, World!");

    // Тест 1
    int pos1 = cstring_rfind(text, 'H');
    custom_assert(pos1 == (strrchr(text->data, 'H') - text->data));

    // Тест 2
    int pos2 = cstring_rfind(text, 'q');
    custom_assert(pos2 == -1);

    cstring_delete(text);
    printf("Testing cstring rfind passed!\n");
}

void test_cstring_split() 
{
    cstring *str = cstring_create("apple,banana,orange,grape");

    // Разделение строки по запятой
    cstring **result1 = cstring_split(str, ",");
    custom_assert(result1 != NULL);

    cstring *expected1_0 = cstring_create("apple");
    cstring *expected1_1 = cstring_create("banana");
    cstring *expected1_2 = cstring_create("orange");
    cstring *expected1_3 = cstring_create("grape");

    custom_assert(cstring_compare(result1[0], expected1_0) == 0);
    custom_assert(cstring_compare(result1[1], expected1_1) == 0);
    custom_assert(cstring_compare(result1[2], expected1_2) == 0);
    custom_assert(cstring_compare(result1[3], expected1_3) == 0);
    custom_assert(result1[4] == NULL);

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
    custom_assert(result2 != NULL);

    custom_assert(cstring_compare(result2[0], str) == 0);
    custom_assert(result2[1] == NULL);

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
    testing_cstring_insert_cstring();
    testing_cstring_append();
    testing_cstring_concatenation();
    test_cstring_substring();
    test_cstring_find();
    test_cstring_rfind();
    test_cstring_split();

    return 0;
}
