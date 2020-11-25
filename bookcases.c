
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

    // for (int y = 0; y < h; y++)
    // {
    //     /* code */
    //     if (!checkShelf(b.shelves[y], w))
    //     {
    //         printf("shelf %d needs re-arranging\n", y);

    //         // copy of shelf
    //         char *carr = (char *)malloc(w * sizeof(char));
    //         memcpy(carr, b.shelves[y], w);

    //         // take book last book off shelf
    //         char lastBook;
    //         lastBook = takeLastBook(carr, w);
    //         printf("last book is %c\n", lastBook);

    //         memcpy(b.shelves[y], carr, w);

    //         break;

    //         // move the last book on shelf to every other available shell
    //         for (int y1 = 0; y1 < h; y1++)
    //         {
    //             if (y1 != y)
    //             { // dont move to itself
    //                 //bookcase_t b = putDownBook(b, lastBook, h, w);
    //                 print_bookcase(b);
    //             }
    //         }

    //         for (int x = 0; x < w; x++)
    //         {
    //             /* code */
    //         }
    //     }
    // }

    //print_bookcase(b);

    /* ALGO
    1. You will use a list of bookcases(here list could either be an array, or a linked list).
    2. The initial bookcase is put into the front of this list.
    3. Take a bookcase from the front of the list.
    4. For this(parent) bookcase, find the resulting(child) bookcases which can be created from all the valid possible single book moves.
       Put each of these bookcases into the end of the list.There may be as many as height ×(height −1)of these.
       If you have found a happy bookcase, stop.
       Else, go to 3.
    */

    return 0;
}
