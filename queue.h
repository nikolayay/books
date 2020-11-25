#include "bookcase.h"

typedef struct node
{
    bookcase_t *bookcase;
    struct node *next;

} node_t;

void push(node_t *head, bookcase_t *b)
{

    node_t *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = (node_t *)malloc(sizeof(node_t));
    current->next->bookcase = b;
    current->next->next = NULL;
}

bookcase_t *pop(node_t **head)
{
    bookcase_t *retval;
    node_t *next_node = NULL;

    if (*head == NULL)
    {
        printf("kekkeke");
        exit(EXIT_FAILURE);
    }

    next_node = (*head)->next;
    retval = (*head)->bookcase;
    free(*head);
    *head = next_node;

    return retval;
}

int len(node_t *head)
{
    node_t *current = head;

    int count = 0;

    while (current != NULL)
    {
        current = current->next;

        count++;
    }

    return count;
}

void print_queue(node_t *head)
{
    node_t *current = head;

    int count = 0;

    while (current != NULL)
    {
        print_bookcase(current->bookcase);
        current = current->next;
    }
}

bool check(node_t *head)
{
    node_t *current = head;
    int count = 0;

    while (current != NULL)
    {

        if (is_case_happy(current->bookcase))
        {

            return true;
        }

        current = current->next;
        count++;
    }

    printf("everyoin out of %d cases is depressed\n", count);

    return false;
}

bool is_in(node_t *head, bookcase_t *b)
{
    node_t *current = head;
    int count = 0;

    while (current != NULL)
    {

        if (is_equal(current->bookcase, b))
        {
            return true;
        }

        current = current->next;
        count++;
    }

    return false;
}

void queue_test()
{
    bookcase_t *t0 = read_bookcase("tests/h0.txt");
    bookcase_t *t1 = read_bookcase("tests/h1.txt");
    bookcase_t *t2 = read_bookcase("tests/h2.txt");

    node_t *head = NULL;
    head = (node_t *)malloc(sizeof(node_t));

    bookcase_t *h0 = read_bookcase("tests/h0.txt");

    head->bookcase = t0;
    head->next = NULL;

    assert(len(head) == 1);
    push(head, t1);
    assert(len(head) == 2);
    push(head, t2);
    assert(len(head) == 3);

    bookcase_t *out = pop(&head);
    assert(is_equal(t0, out));
}