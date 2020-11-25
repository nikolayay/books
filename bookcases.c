
#include "bookcase.h"

enum
{
    RED,
    BLACK,
    GREEN,
    YELLOW,
    BLUE,
    MAGNETA,
    CYAN,
    WHITE,
    EMPTY
};

int main(int argc, char const *argv[])
{

    test();

    bookcase_t *p = read_bookcase("tests/p0.txt");

    // a lot of babies
    int count = 0;

    for (int shelf_from = 0; shelf_from < p->h; shelf_from++)
    {

        for (int shelf_to = 0; shelf_to < p->h; shelf_to++)
        {

            if (!is_shelf_full(p, shelf_to) && !is_shelf_empty(p, shelf_from) && shelf_from != shelf_to)
            {

                bookcase_t *baby = make_baby(p, shelf_from, shelf_to);
                count++;
                print_bookcase(baby);
                free(baby);
            }
        }
    }

    printf("offspring count: %d\n", count);

    return 0;
}
