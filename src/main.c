#include <stdio.h>
#include <stdlib.h>

int main() {
    // read in header, print it
    const char *filename = "../data/wave1.dat";
    FILE *fptr   = fopen(filename, "rb");

    // check if file was caught
    if (fptr == NULL)
    {
        fprintf(stderr, "Failed to open file '%s': ", filename);
        return 1;
    }

    int header[6];
    size_t read = fread(&header, sizeof(int), 6, fptr);
    fclose(fptr);

    for (size_t i = 0; i < read; i++) {
        printf("value[%zu] = %d\n", i, header[i]);
    }
    return 0;
}

