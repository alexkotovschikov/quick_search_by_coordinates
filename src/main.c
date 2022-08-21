#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include "short.h"

int main() {
    FILE *output = NULL;
    output = fopen("../datasets/arrayA.bin", "rb+");
    FILE *outputB = NULL;
    outputB = fopen("../datasets/arrayB.bin", "rb+");
    if (output != NULL && outputB != NULL) {
        unsigned count_record_A = get_records_count_in_file(output);
        unsigned count_record_B = get_records_count_in_file(outputB);
        struct map *mapsA;
        struct map *mapsB;
        mapsA = (struct map*) malloc(count_record_A * sizeof(struct map));
        mapsB = (struct map*) malloc(count_record_B * sizeof(struct map));
        fill_in_the_array_slow(count_record_A, output, mapsA);
        fill_in_the_array_slow(count_record_B, outputB, mapsB);
        struct timeval tvBegin, tvEnd, tvDiff;
        gettimeofday(&tvBegin, NULL);
        for (unsigned i = 0; i < count_record_A; i++) {
            double min = way_in_front(mapsA[i], mapsB[0]);
            for (unsigned j = 0; j < count_record_B; j++) {
                double temp = way_in_front(mapsA[i], mapsB[j]);
                if (min  > temp + epsilon) {
                    min = temp;
                    mapsA[i].recordB = (int) j;
                }
            }
        }
        gettimeofday(&tvEnd, NULL);
        timeval_subtract(&tvDiff, &tvEnd, &tvBegin);
        printf("time long (sec) = %ld.%06ld\n", tvDiff.tv_sec, tvDiff.tv_usec);
        for (int i = 0; i < 15; i++) printf("long record = %d lat = %lf lon = %lf \n", mapsA[i].recordB, mapsB[mapsA[i].recordB].latitude, mapsB[mapsA[i].recordB].longitude);
        struct index *indexA = NULL;
        indexA = (struct index*) malloc(count_record_A * sizeof(struct index));
        struct index *indexB = NULL;
        indexB = (struct index*) malloc(count_record_B * sizeof(struct index));
        fill_in_the_array_fast(count_record_A, output, indexA);
        fill_in_the_array_fast(count_record_B, outputB, indexB);
        gettimeofday(&tvBegin, NULL);
        for (unsigned i = 0; i < count_record_A; i++) {
            long long min = cos_fast(indexA[i], indexB[0]);
            for (unsigned j = 0; j < count_record_B; j++) {
                long long temp = cos_fast(indexA[i], indexB[j]);
                if (min < temp) {
                    min = temp;
                    indexA[i].recordB = (int) j;
                }
            }
        }
        gettimeofday(&tvEnd, NULL);
        timeval_subtract(&tvDiff, &tvEnd, &tvBegin);
        printf("time short (sec) = %ld.%06ld\n", tvDiff.tv_sec, tvDiff.tv_usec);
        for (int i = 0; i < 15; i++) printf("short record = %d lat = %f lon = %f \n", indexA[i].recordB, mapsB[indexA[i].recordB].latitude, mapsB[indexA[i].recordB].longitude);
        free(mapsA);
        free(mapsB);
        fclose(outputB);
        free(indexA);
        free(indexB);
        fclose(output);
    } else {
        printf("file A and B not open");
    }
    return 0;
}

