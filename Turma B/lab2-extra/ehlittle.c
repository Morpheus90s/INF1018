#include <stdio.h>

int is_little() {
    unsigned int i = 1;
    
    unsigned char *p = ((unsigned char *) &i);

    if (*p == 1) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    if (is_little()) {
        printf("Little-endian.\n");
    } else {
        printf("Big-endian.\n");
    }
    return 0;
}
