bookcases: bookcases.c
     gcc -o -Wall -Wextra -Wfloat-equal -pedantic -std=c90 -fsanitize=address -fsanitize=undefined -g3 -lm bookcases bookcases.c -I.