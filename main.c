#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

typedef struct cache {
    long int tag;
    bool is_empty;
    int inserted_at;
    int access_at;
} CACHE;

void associative(FILE *file, int n_ways, int n_sets, int n_bits_offset, int n_bits_index, int flag_out,
                 char subst);

void getStatistics(int output_flag, int access_number, float compulsory_miss, float hit, float capacity_miss,
                   float conflict_miss);

void randomReplacement(CACHE **c, int n_ways, long int index, long int tag, int access_number);

void fifoReplacement(CACHE **c, int n_ways, long int index, long int tag, int access_number);

void lruReplacement(CACHE **c, int n_ways, long int index, long int tag, int access_number);

void deallocateCache(CACHE **c, int n_sets);

int main(int argc, char *argv[]) {
    int n_sets = atoi(argv[1]);
    int b_size = atoi(argv[2]);
    int assoc = atoi(argv[3]);
    char *subst = argv[4];
    int flag_out = atoi(argv[5]);
    char *filename = argv[6];

    srand(time(NULL));

    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("\nThe file of Input is unable to open!\n\n");
        return -1;
    }

    int n_bits_offset = (int) log2(b_size);
    int n_bits_index = (int) log2(n_sets);

    associative(file, assoc, n_sets, n_bits_offset, n_bits_index, flag_out, *subst);
    free(argv);

    return 0;
}

void associative(FILE *file, int n_ways, int n_sets, int n_bits_offset, int n_bits_index, int flag_out,
                 char subst) {
    char temp_char;
    int access_number = 0, compulsory_miss = 0, hit = 0, capacity_miss = 0, conflict_miss = 0;

    CACHE **cache = NULL;
    cache = (CACHE **) malloc((n_sets) * sizeof(CACHE *));

    for (int i = 0; i < n_sets; i++) {
        cache[i] = (CACHE *) malloc(n_ways * sizeof(CACHE));
        if (cache[i] == NULL)
            printf("Not Allocated");
    }

    for (int first_loop = 0; first_loop < n_sets; first_loop++) {
        for (int second_loop = 0; second_loop < n_ways; second_loop++) {
            cache[first_loop][second_loop].is_empty = true;
        }
    }

    while ((temp_char = getc(file)) != EOF) {
        access_number++;

        long int address = 0;

        address |= temp_char << 24;
        address |= getc(file) << 16;
        address |= getc(file) << 8;
        address |= getc(file);

        long int tag = address >> (n_bits_offset + n_bits_index);
        long int index = (address & ((1 << n_bits_index) - 1) << n_bits_offset) >> n_bits_offset;

        int way = 0;
        bool is_found = false;

        while (n_ways > way && is_found == false) {
            if (cache[index][way].is_empty == true) {
                cache[index][way].tag = tag;
                cache[index][way].is_empty = false;
                cache[index][way].inserted_at = access_number;
                cache[index][way].access_at = access_number;
                compulsory_miss++;
                is_found = true;
            } else if (cache[index][way].tag == tag) {
                hit++;
                cache[index][way].access_at = access_number;
                is_found = true;
            } else {
                way++;
            }
        }

        if (is_found == false) {

            int cache_space_free = 0;

            for (int first_loop = 0; first_loop < n_sets; first_loop++) {
                for (int second_loop = 0; second_loop < n_ways; second_loop++) {
                    if (cache[first_loop][second_loop].is_empty) {
                        cache_space_free++;
                    }
                }
            }

            if (cache_space_free > 0) {
                conflict_miss++;
            } else {
                capacity_miss++;
            }

            if (subst == 'R') {
                randomReplacement(cache, n_ways, index, tag, access_number);
            }
            if (subst == 'F') {
                fifoReplacement(cache, n_ways, index, tag, access_number);
            }
            if (subst == 'L') {
                lruReplacement(cache, n_ways, index, tag, access_number);
            }
        }
    }

    getStatistics(flag_out, access_number, (float) compulsory_miss, (float) hit, (float) capacity_miss,
                  (float) conflict_miss);

    deallocateCache(cache, n_sets);
}

void randomReplacement(CACHE **c, int n_ways, long int index, long int tag, int access_number) {
    int random_number = rand() % n_ways;

    c[index][random_number].tag = tag;
    c[index][random_number].is_empty = false;
    c[index][random_number].inserted_at = access_number;
    c[index][random_number].access_at = access_number;
}

void fifoReplacement(CACHE **c, int n_ways, long int index, long int tag, int access_number) {
    int count = 0;

    for (int i = 1; i < n_ways; i++) {
        if (c[index][i].inserted_at < c[index][count].inserted_at) {
            count = i;
        }
    }

    c[index][count].tag = tag;
    c[index][count].is_empty = false;
    c[index][count].inserted_at = access_number;
    c[index][count].access_at = access_number;
}

void lruReplacement(CACHE **c, int n_ways, long int index, long int tag, int access_number) {
    int count = 0;
    for (int i = 1; i < n_ways; i++) {
        if (c[index][i].access_at < c[index][count].access_at) {
            count = i;
        }
    }

    c[index][count].tag = tag;
    c[index][count].is_empty = false;
    c[index][count].inserted_at = access_number;
    c[index][count].access_at = access_number;
}

void getStatistics(int output_flag, int access_number, float compulsory_miss, float hit, float capacity_miss,
                   float conflict_miss) {
    float hit_rate, miss_rate, compulsory_miss_rate, capacity_miss_rate, conflict_miss_rate;
    hit_rate = hit / access_number;
    miss_rate = (compulsory_miss + capacity_miss + conflict_miss) / access_number;
    compulsory_miss_rate = (compulsory_miss / miss_rate) / access_number;
    capacity_miss_rate = (capacity_miss / miss_rate) / access_number;
    conflict_miss_rate = (conflict_miss / miss_rate) / access_number;

    if (output_flag == 0) {
        printf("Access number: %d \n", access_number);
        printf("Hit rate: %.2f \n", hit_rate);
        printf("Miss rate: %.2f \n", miss_rate);
        printf("Compulsory miss rate: %.2f \n", compulsory_miss_rate);
        printf("Capacity miss rate: %.2f \n", capacity_miss_rate);
        printf("Conflict miss rate: %.2f \n", conflict_miss_rate);
        return;
    }
    printf("%d %.2f %.2f %.2f %.2f %.2f", access_number, hit_rate, miss_rate, compulsory_miss_rate, capacity_miss_rate,
           conflict_miss_rate);
}

void deallocateCache(CACHE **c, int n_sets) {
    if (c != NULL) {
        for (int i = 0; i < n_sets; i++) {
            free(c[i]);
        }
        free(c);
    }
}
