#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


void read_header(FILE *fptr, int header[6], size_t *out_count) {
    *out_count = fread(header, sizeof(int), 6, fptr);   
}

void read_data(FILE *fptr, uint16_t *waveform, size_t n_ints, size_t *out_count) {

    *out_count = fread(waveform, sizeof(uint16_t), n_ints, fptr);
}

int main() {

    int sample_size = 2;
    // read in header, print it
    const char *filename = "../data/wave1.dat";
    FILE *fptr   = fopen(filename, "rb");

    // check if file was caught
    if (fptr == NULL)
    {
        fprintf(stderr, "Failed to open file '%s': ", filename);
        return 1;
    }
    
    // count of components in header, should be 6
    size_t count;
    int header[6];
    read_header(fptr, header, &count);
 
    for (size_t i = 0; i < count; i++) {
        printf("value[%zu] = %d\n", i, header[i]);
    }
   
    // while there are still 6 elements in the header, keep looping through the data
    while (count == 6) {
       // shift and scale by sample size following CAENs instructions
       header[0] = header[0] - 24;
       int event_size = header[0] / sample_size;
       // allocate this amount of room
       uint16_t *waveform = malloc(event_size * sizeof(uint16_t));

       if (!waveform) {
        fprintf(stderr, "Failed memory allocation\n");
        fclose(fptr);
        return 1;
       }
    
       size_t data_count;
       read_data(fptr, waveform, event_size, &data_count);
        
       // in principle, you should write it out here
       printf("Waveform read, continuing to next one\n");
       // then free the memory
       free(waveform);

       read_header(fptr, header, &count);

       for (size_t i = 0; i < count; i++) {
           printf("value[%zu] = %d\n", i, header[i]);
        }
   
    }

    fclose(fptr);
    return 0;
}

