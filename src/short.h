#ifndef _SRC_SHORT_H
#define _SRC_SHORT_H
    
#define pow2in10    4294967296    
#define pow2in5     8388608
#define M_PI        3.14159265358979323846
#define epsilon     0.00001

struct map {
    double longitude;
    double latitude;
    int recordB;
    char name[30];
};

struct index {
    long long sin_longitude;
    long long cos_longitude;
    long long sin_latitude;
    long long cos_latitude;
    int count;
    int recordB;
};

int get_records_count_in_file(FILE *pfile);
int get_file_size_in_bytes(FILE *pfile);
struct map read_record_from_file(FILE *pfile, int index);
unsigned gip(int x1, int x0, int y1, int y0);
void fill_in_the_array_fast(unsigned count_record, FILE *pfile, struct index *index_in);
void fill_in_the_array_slow(unsigned count_record, FILE *pfile, struct map *maps);
long long cos_fast(struct index indexA, struct index indexB);
double way_in_front(struct map mapsA, struct map mapsB);
int timeval_subtract(struct timeval *result, struct timeval *t2, struct timeval *t1);
void refil_file(FILE *pfile, int count);

#endif  // _SRC_SHORT_H
