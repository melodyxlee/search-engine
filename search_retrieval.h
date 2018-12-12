#ifndef SEARCH_RETRIEVAL_H
#define SEARCH_RETRIEVAL_H

#include "hashmap.h"


struct rank {
	double score;	// The actual relevance score.
	int doc_num;	// The document number.
};


double* read_query(struct hashmap* doc_hm, double* scores);
void rank(double* scores);
void sort(struct rank arr[]);
void swap(struct rank* a, struct rank* b);


#endif 