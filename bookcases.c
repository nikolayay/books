
#include "queue.h"

int make_happy(bookcase_t *p, int count)
{

    printf("gen: %d\n", count);
    if (count > 8)
    {
        return 0;
    }

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
                    printf("please dear god\n");
                    return count;
                }
                else
                {
                    count += make_happy(baby, count + 1);
                }
            }
        }
    }

    return count;
}

int main(int argc, char const *argv[])
{

    test();
    queue_test();

    node_t *head = NULL;
    head = (node_t *)malloc(sizeof(node_t));
    bookcase_t *p = read_bookcase("tests/p0.txt");

    head->bookcase = p;
    head->next = NULL;

    while (len(head) > 0)
    {

        if (is_case_happy(head->bookcase))
        {
            print_bookcase(head->bookcase);
            printf("%d", head->bookcase->id + 1);
            break;
        }

        bookcase_t *parent = pop(&head);

        for (int shelf_from = 0; shelf_from < parent->h; shelf_from++)
        {

            for (int shelf_to = 0; shelf_to < parent->h; shelf_to++)
            {

                if (!is_shelf_full(parent, shelf_to) && !is_shelf_empty(parent, shelf_from) && shelf_from != shelf_to)
                {
                    bookcase_t *baby = make_baby(parent, shelf_from, shelf_to);

                    if (head == NULL && len(head) == 0)
                    {

                        head = NULL;
                        head = (node_t *)malloc(sizeof(node_t));
                        head->bookcase = baby;
                        head->next = NULL;
                    }

                    if (!is_in(head, baby))
                    {
                        push(head, baby);
                    }
                }
            }
        }
    }

    return 0;
}
