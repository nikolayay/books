
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

bookcase_t *copy_bookcase(bookcase_t *b)
{
    bookcase_t *cb = (bookcase_t *)malloc(sizeof(struct Bookcase));

    cb->id = b->id;

    cb->w = b->w;
    cb->h = b->h;
    char *arr = (char *)malloc(b->w * b->h * sizeof(char));
    memcpy(arr, b->shelves, cb->w * cb->h);
    cb->shelves = arr;

    return cb;
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
int find_last_book_ix(bookcase_t *b, int shelf)
{
    int w = b->w;
    int book_ix = -1;

    if (is_shelf_empty(b, shelf))
    {
        return book_ix;
    }

    for (int x = 1; x < w; x++)
    {
        if (b->shelves[shelf * w + x] == '.')
        {
            book_ix = shelf * w + (x - 1);
            break;
        }
    }

    return book_ix;
}

// find free space, return -1 if none found
int find_free_space(bookcase_t *b, int shelf)
{
    int last_book_ix = find_last_book_ix(b, shelf);
    return last_book_ix ? last_book_ix < b->w : -1;
}

// find the last book on shelf
char find_book(bookcase_t *b, int shelf)
{
    return b->shelves[find_last_book_ix(b, shelf)];
}

// returns copy of b without the last book on specified shelf
bookcase_t *pop_book(bookcase_t *b, int shelf)
{
    // make copy of b
    bookcase_t *cb = copy_bookcase(b);

    // get last book on shelf and replace it with a dot
    int last_book_ix = find_last_book_ix(cb, shelf);

    cb->shelves[last_book_ix] = '.';

    return cb;
}

// returns copy of b with speicified book on the end of shelf
bookcase_t *push_book(bookcase_t *b, int shelf, char book)
{
    // make copy of b
    bookcase_t *cb = copy_bookcase(b);

    // get last free space on shelf and replace it with the book
    int free_space_ix = find_free_space(cb, shelf);

    cb->shelves[free_space_ix] = book;

    return cb;

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

    // test copy
    bookcase_t *after_copy = copy_bookcase(after);
    assert(is_equal(after_copy, after));

    // test pop book
    char book = find_book(before, 1);
    assert(book == 'R');
    bookcase_t *before_pop = pop_book(before, 1);
    print_bookcase(before_pop);
    print_bookcase(popped);
    assert(is_equal(before_pop, popped));

    // test push book
    bookcase_t *before_push = push_book(before_pop, 0, book);
    assert(is_equal(before_push, after));

    // test make baby case from parent case

    // test some sort of flow

    printf("all test pass\n");
}
