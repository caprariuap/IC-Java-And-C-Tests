#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *derived_lookup_table(char *);

int contains(char *, char);

int main(void) {

    char *s = "attack";

    printf("The initial word is: %s\n", s);

    char *table = derived_lookup_table(s);

    printf("Derived lookup table: %s\n\n", table);

    //Must free the result;
    free(table);

    return EXIT_SUCCESS;
}

char *derived_lookup_table(char *s) {

    char *o_out = malloc(sizeof(s));

    if (o_out == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    //Do not initialize o_end using malloc because it is changed to o_out anyway
    char *o_end;

    o_end = o_out;

    for (; *s != '\0'; ++s) {
        if (!contains(o_out, *s)) {
            *o_end++ = *s;
        }
    }

    //out gets memory from o_out not from itself (the way it was)
    char *out = realloc(o_out, o_end - o_out + 1);

    if (out == NULL) {
        perror("realloc");
        exit(EXIT_FAILURE);
    }

    return out;

}


int contains(char *s, char c) {

    for (int i = 0; i < strlen(s); i++) {
        if (s[i] == c) {
            return 1;
        }
    }

    return 0;
}
