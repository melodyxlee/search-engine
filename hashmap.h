#ifndef HASHMAP_H
#define HASHMAP_H
 
#define NUM_DOCUMENTS 3

struct llnode {
    char* word;
    int d1_count;	// Num occurrences of word in document 1. 
    int d2_count;
    int d3_count;
    struct llnode* next;
};


struct hashmap {
    struct llnode** map;
    int num_buckets;
    int num_elements;
};
 
struct hashmap* hm_create(int num_buckets);
struct llnode* hm_get(struct hashmap* hm, char* word);
void hm_put(struct hashmap* hm, char* word, int d1_count, int d2_count, int d3_count);
void hm_remove(struct hashmap* hm, char* word);
void hm_destroy(struct hashmap* hm);
void hm_print(struct hashmap* hm, int num_buckets);
int hash(struct hashmap* hm, char* word);

#endif 
