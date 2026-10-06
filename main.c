#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include "red_black_tree.h"

int main(void){
    struct RedBlackTreeNode *root = NULL;
    char buf[64];

    while (1) {
        printf("Enter integer to insert (q to quit): ");
        fflush(stdout);
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            printf("\n");
            break;
        }
        buf[strcspn(buf, "\n")] = '\0';

        if (strcmp(buf, "q") == 0) {
            break;
        }

        if (buf[0] == '\0') {
            continue;
        }

        char *endptr;
        errno = 0;
        long val = strtol(buf, &endptr, 10);
        if (errno == ERANGE) {
            perror("strtol");
            continue;
        }
        if (endptr == buf || *endptr != '\0') {
            fprintf(stderr, "Invalid integer: %s\n", buf);
            continue;
        }
        if (val > INT_MAX || val < INT_MIN){
            fprintf(stderr, "Provide values between %d and %d\n", INT_MIN, INT_MAX);
            continue;
        }

        if (root == NULL) {
            root = create_node((int)val);
            if (root == NULL) {
                fprintf(stderr, "malloc failed\n");
                return EXIT_FAILURE;
            }
            root->color = BLACK;
        } else {
            struct RedBlackTreeNode *node = create_node((int)val);
            if (node == NULL) {
                fprintf(stderr, "malloc failed\n");
                return EXIT_FAILURE;
            }
            root = insertNode(node, root);
        }

        printf("After inserting %ld:\n", val);
        print_tree(root);
        printf("\n");
    }

    return 0;
}
