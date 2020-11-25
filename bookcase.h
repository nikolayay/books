
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

bool is_shelf_empty(bookcase_t *b, int shelf)
{
    int w = b->w;

    for (int x = 0; x < w; x++)
    {
        char cur_book = b->shelves[shelf * w + x];
        if (cur_book != '.')
        {
            return false;
        }
    }
    return true;
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

bool is_equal(bookcase_t *a, bookcase_t *b)
{
    int w, h;
    if (a->w != b->w || a->h != b->h)
    {
        return false;
    }

    w = b->w;
    h = b->h;

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            char book_a = a->shelves[y * w + x];
            char book_b = b->shelves[y * w + x];
            if (book_a != book_b)
            {
                return false;
            }
        }
    }

    return true;
}

// find the last book on shelf
char find_book(bookcase_t *b, int shelf)
{
    int w = b->w;
    char book = 'Z';

    for (int x = 1; x < w; x++)
    {
        if (b->shelves[shelf * w + x] == '.')
        {
            book = b->shelves[shelf * w + (x - 1)];
        }
    }

    return book;
}

// returns copy of b without the last book on specified shelf
bookcase_t *pop_book(bookcase_t *b, int shelf)
{
    return b;
}

// returns copy of b with speicified book on the end of shelf
bookcase_t *push_book(bookcase_t *b, int shelf, char book)
{
    return b;
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
    bookcase_t *empty = readBookcase("tests/empty.txt");
    assert(is_shelf_empty(empty, 0));
    assert(!is_shelf_empty(empty, 1));

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

    // ! manipulation
    bookcase_t *before = readBookcase("tests/before.txt");
    bookcase_t *popped = readBookcase("tests/popped.txt");
    bookcase_t *after = readBookcase("tests/after.txt");

    assert(is_equal(before, before));
    assert(!is_equal(before, after));

    // test pop book
    char book = find_book(before, 1);
    assert(book == 'R');
    bookcase_t *before_pop = pop_book(before, 1);
    assert(is_equal(before_pop, popped));

    // test push book
    bookcase_t *before_push = push_book(before_pop, 0, book);
    assert(is_equal(before_push, after));

    // test make baby case from parent case

    // test some sort of flow

    printf("all test pass\n");
}
