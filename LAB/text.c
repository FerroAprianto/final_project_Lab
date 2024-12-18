#include <stdio.h>

int DisplayTitle() {
    FILE *file;
    char line[10000];

    file = fopen("text.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
    return 0;
}
