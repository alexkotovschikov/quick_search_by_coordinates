#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include "short.h"

int get_records_count_in_file(FILE *pfile) {
    return get_file_size_in_bytes(pfile) / sizeof(struct map);
}

int get_file_size_in_bytes(FILE *pfile) {
    int size = 0;
    fseek(pfile, 0, SEEK_END);
    size = ftell(pfile);
    rewind(pfile);
    return size;
}

struct map read_record_from_file(FILE *pfile, int index) {
    int offset = index * sizeof(struct map);
    fseek(pfile, offset, SEEK_SET);
    struct map record;
    fread(&record, sizeof(struct map), 1, pfile);
    rewind(pfile);
    return record;
}

void fill_in_the_array_fast(unsigned count_record, FILE *pfile, struct index *index_in) {
    struct map mapsA;
    for (unsigned i = 0; i < count_record; i++) {
        mapsA = read_record_from_file(pfile, i);
        index_in[i].count++;
        index_in[i].cos_latitude = pow2in5 * cos(mapsA.latitude * M_PI / 180);
        index_in[i].sin_latitude = pow2in5 * sin(mapsA.latitude * M_PI / 180);
        index_in[i].cos_longitude = pow2in5 * cos(mapsA.longitude * M_PI / 180);
        index_in[i].sin_longitude = pow2in5 * sin(mapsA.longitude * M_PI / 180);
    }
}

void fill_in_the_array_slow(unsigned count_record, FILE *pfile, struct map *maps) {
    for (unsigned i = 0; i < count_record; i++) {
        maps[i] = read_record_from_file(pfile, i);
    }  
}

long long cos_fast(struct index indexA, struct index indexB) {
    long long cos = indexA.sin_latitude * indexB.sin_latitude + (indexA.cos_latitude * indexB.cos_latitude / (long long) pow2in5)
                * ((indexA.cos_longitude * indexB.cos_longitude + indexA.sin_longitude * indexB.sin_longitude) / (long long) pow2in5);
    return cos;
}

double way_in_front(struct map mapsA, struct map mapsB) {
    double rad = M_PI / 180;
    double way = acos(sin(mapsA.latitude * rad) * sin(mapsB.latitude * rad) + cos(mapsA.latitude * rad) * cos(mapsB.latitude * rad)
                    * cos(mapsB.longitude * rad - mapsA.longitude * rad));
    return way;
}

int timeval_subtract(struct timeval *result, struct timeval *t2, struct timeval *t1) {
    long int diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec + 1000000 * t1->tv_sec);
    result->tv_sec = diff / 1000000;
    result->tv_usec = diff % 1000000;
    return (diff<0);
}

void refil_file(FILE *pfile, int count) {
    srand(time(NULL) - count);
    struct map maps;
    for (int i = 0; i < count; i++) {
        maps.latitude = rand() % 90 * pow(-1, rand() % 3) + rand() % 100000 / (double) 100000 ;
        maps.longitude = rand() % 180 * pow(-1, rand() % 2) + rand() % 100000 / (double) 100000;
        maps.recordB = -1;
        sprintf(maps.name, "name%d", i);
        fwrite(&maps, sizeof(struct map), 1, pfile);
    }
    printf("array full -> %d record| \n", count);
}
