#ifndef TRAINING_H
#define TRAINING_H

#include "hashmap.h"

void stop_word(struct hashmap* hm);
struct hashmap* training(int num_buckets);

#endif
