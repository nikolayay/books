
#include "bookcase.h"

int make_happy(bookcase_t *p, int count)
{
    // if (count > 12)
    // {
    //     return count;
    // }
    // make babies

    for (int shelf_from = 0; shelf_from < p->h; shelf_from++)
    {

        for (int shelf_to = 0; shelf_to < p->h; shelf_to++)
        {

            if (!is_shelf_full(p, shelf_to) && !is_shelf_empty(p, shelf_from) && shelf_from != shelf_to)
            {

                bookcase_t *baby = make_baby(p, shelf_from, shelf_to);
                print_bookcase(baby);

                if (is_case_happy(baby))
                {
                    print_bookcase(baby);
                    return count + 1;
                }
                else
                {
                    return make_happy(baby, count + 1);
                }
            }
        }
    }

    //printf("offspring count: %d\n", count);
}

int main(int argc, char const *argv[])
{

    test();

    bookcase_t *p = read_bookcase("tests/p0.txt");

    // allocate max possible amount for generation
    bookcase_t *gen = (bookcase_t *)malloc(sizeof(bookcase_t *) * p->h * (p->h - 1));
    print_bookcase(p);
    int count = make_happy(p, 0);

    printf("count: %d", count);

    return 0;
}
