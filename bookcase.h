
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

struct Bookcase
{
    int id;
    int w;
    int h;
    char *shelves; // contigious in memory
};

typedef struct Bookcase bookcase_t;
bookcase_t *readBookcase(char *filename);
bookcase_t *makeBookcase(char *arr, int id, int w, int h);
void print_bookcase(bookcase_t *b);

bookcase_t *readBookcase(char *filename)
{
    FILE *fp;
    char buff[255];

    int h, w, max;

    fp = fopen(filename, "r");
    fscanf(fp, "%d %d %d", &h, &w, &max);

    // allocate space for the bookcase
    char *arr = (char *)malloc(w * h * sizeof(char));

    for (int y = 0; y < h; y++)
    {
        char buf[w];
        fscanf(fp, "%s", buf);
        for (int x = 0; x < w; x++)
        {
            arr[y * w + x] = buf[x];
        }
    }

    bookcase_t *b = makeBookcase(arr, 0, w, h);

    fclose(fp);

    return b;
}

bookcase_t *
makeBookcase(char *arr, int id, int w, int h)
{
    bookcase_t *b = (bookcase_t *)malloc(sizeof(struct Bookcase));

    b->id = id;

    b->w = w;
    b->h = h;
    b->shelves = arr; // point shelves pointer to arr

    return b;
}

bool is_shelf_happy(bookcase_t *b, int shelf)
{
    int w = b->w;
    char first = b->shelves[shelf * w + 0];
    for (int x = 1; x < w; x++)
    {
        char cur_book = b->shelves[shelf * w + x];
        if (cur_book != first && cur_book != '.')
        {
            return false;
        }
    }

    return true;
}

bool is_case_happy(bookcase_t *b)
{
    int h = b->h;
    for (int y = 0; y < h; y++)
    {
        if (!is_shelf_happy(b, y))
        {
            return false;
        }
    }

    return true;
}

void print_bookcase(bookcase_t *b)
{
    printf("[");
    int h = b->h;
    int w = b->w;

    printf("%d, %d", h, w);

    for (int y = 0; y < h; y++)
    {
        printf("\n[");

        for (int x = 0; x < w; x++)
        {
            printf("%c, ", b->shelves[y * w + x]);
        }
        printf("]\n ");
    }
    printf("]\n");
}

void test()
{
    // ! happy

    bookcase_t *happy = readBookcase("tests/happy.txt");
    // test happy shelf
    assert(is_shelf_happy(happy, 0));
    assert(is_shelf_happy(happy, 1));

    // test happy case
    assert(is_case_happy(happy));

    free(happy);

    // ! unhappy
    bookcase_t *sad = readBookcase("tests/sad.txt");

    // test unhappy shelf
    assert(!is_shelf_happy(sad, 0));
    assert(is_shelf_happy(sad, 1));
    assert(!is_shelf_happy(sad, 2));

    // test unhappy case
    assert(!is_case_happy(sad));

    free(sad);

    // ! test pop book
    bookcase_t *before = readBookcase("tests/sad.txt");
    bookcase_t *after = readBookcase("tests/sad.txt");

    // test push book

    // test make baby case from parent case

    // test some sort of flow

    printf("all test pass\n");
}
