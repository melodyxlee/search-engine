#include "search_retrieval.h"
#include "calc.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

/* Reads in each word from query and calculates document relevance scores. */
double* read_query(struct hashmap* hm, double* scores) {
	char query_word[20];
	double idf = 0;
	double d1_rank = 0;
	double d2_rank = 0;
	double d3_rank = 0;

	// Continuously get char from stdin, fill in word_query until whitespace, reset, then repeat until newline.
	char c = getchar();		// Ignore leftover \n in buffer from previous scanf.
	c = getchar();
	while (c != '\n') {
		int i = 0;
		memset(query_word, '\0', 20);	// Fill with \0 to make sure string is null-terminated
		while (c != ' ') {				// Not a whitespace yet so fill query_word with the chars.
			query_word[i] = c;
			i++;
			c = getchar();
			if (c == '\n') {
				break;
			}
		}
		char* qword_ptr = query_word;	// Because hm_get requires a pointer to be passed in.
		struct llnode* node = hm_get(hm, qword_ptr);
		// If query word is in the hashmap of document words (hm_get did not return null).
		if (node != NULL) {
			idf = calc_idf(node);
			d1_rank += node->d1_count * idf; // Rank is sum of tf-idf scores.
			d2_rank += node->d2_count * idf;
			d3_rank += node->d3_count * idf;
		}
		if (c == '\n') {
			break;
		} 
		c = getchar();
	}

	// Fill in scores array with the calculated ranks.
	scores[0] = d1_rank;
	scores[1] = d2_rank;
	scores[2] = d3_rank;
	return scores;
}

/* Takes scores, ranks them in decreasing relevance, and prints results. */
void rank(double* scores) {
	int i = 0;
   	struct rank rank_objs[3];

   	// Transfer scores to rank_objs array to keep track of doc numbers.
   	for(i = 0; i < 3; i++) {	
     	rank_objs[i].score = scores[i];
     	rank_objs[i].doc_num = i + 1;	// Document nums start at 1, not 0.
    }

    sort(rank_objs);

	printf("Results:\n");
	if (rank_objs[0].score == 0 && rank_objs[1].score == 0 && rank_objs[2].score== 0) {
		printf("No document with a match :(\n");
	} else {
		for(i = 0; i < 3; i++) {
			// Do not output if tf for all search terms is zero (rank score of zero)
			if (rank_objs[i].score > 0) {
				printf("D%d.txt   (score: %f)\n", rank_objs[i].doc_num, rank_objs[i].score);
			}
		}
	}
}

/* Insertion sort according to rank.score */
void sort(struct rank arr[]) {
	int i = 1;
	int j;
	for (i = 1; i < 3; i++) {	// Since the array is of size 3.
		j = i;
		while (j > 0 && arr[j-1].score < arr[j].score) {
			swap(&arr[j], &arr[j-1]);
			j -= 1;
		}
	}
}

/* Helper function to swap two struct ranks */
void swap(struct rank* a, struct rank* b) {		// Must pass in addresses.
	//printf("swapping doc %d and doc %d\n", a->doc_num, b->doc_num);
	struct rank temp = *a;
	*a = *b;
	*b = temp;
}

