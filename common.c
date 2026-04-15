#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 101
#define HASHSIZE 07777

/* isletter macro for character testing */
#define isletter(c) (isalpha(c)) 

struct word {
    char *word;           /* the word */
    int count;            /* frequency count */
    struct word *next;    /* link to next entry */
} *hashtable[HASHSIZE+1]; /* hash table */

int total = 0; /* global count of distinct words */

/* Memory allocation with failure check */
char *alloc(int n, int size) {
    char *p;
    if ((p = calloc(n, size)) == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    return p;
}

/* getword: reads the next word from input */
int getword(char *buf, int size) {
    char *p;
    int c;
    p = buf;
    while ((c = getchar()) != EOF) {
        if (isletter(c)) {
            do {
                if (size > 1) {
                    *p++ = c;
                    size--;
                }
                c = getchar();
            } while (isletter(c));
            *p = '\0';
            return p - buf;
        }
    }
    return EOF;
}

/* addword: adds word to hashtable and increments count */
/* This version includes the move-to-front heuristic and in-line string comparison */
void addword(char *buf) {
    unsigned int h;
    int len;
    char *s, *s1, *s2;
    struct word *wp, **q, **t;

    h = 0;
    s = buf;
    /* compute hash number of buf */
    for (len = 0; *s; len++)
        h += *s++;

    t = q = &hashtable[h & HASHSIZE];
    for (wp = *q; wp; q = &wp->next, wp = wp->next) {
        /* in-line string comparison */
        for (s1 = buf, s2 = wp->word; *s1 == *s2; s2++) {
            if (*s1++ == '\0') {
                wp->count++;
                if (wp != *t) { /* move-to-front heuristic */
                    *q = wp->next;
                    wp->next = *t;
                    *t = wp;
                }
                return;
            }
        }
    }
    /* a new word */
    wp = (struct word *) alloc(1, sizeof *wp);
    wp->word = alloc(len + 1, sizeof(char));
    strcpy(wp->word, buf);
    wp->count = 1;
    *q = wp;
    total++;
}

/* printwords: sorts and prints the k most common words */
void printwords(int k) {
    int i, max;
    struct word *wp, **list, *q;

    list = (struct word **) alloc(total + 1, sizeof wp);
    max = 0;
    for (i = 0; i <= HASHSIZE; i++) {
        for (wp = hashtable[i]; wp; wp = q) {
            q = wp->next;
            wp->next = list[wp->count];
            list[wp->count] = wp;
            if (wp->count > max)
                max = wp->count;
        }
    }
    for (i = max; i >= 0 && k > 0; i--) {
        if (wp = list[i]) {
            k--;
            for (; wp; wp = wp->next)
                printf("%d %s\n", wp->count, wp->word);
        }
    }
}

/* main: program entry point */
int main(int argc, char *argv[]) {
    char buf[MAXWORD];
    int k = 22; /* default value */

    /* Initialization of k from arguments/environment would go here */

    while (getword(buf, MAXWORD) != EOF)
        addword(buf);

    printwords(k);
    return 0;
}