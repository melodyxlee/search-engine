#include "training.h"
#include "calc.h"
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>  // for strcpy

/* Traverse buckets and remove stop words. */
void stop_word(struct hashmap* hm) {
	int i;
	double idf;
	// Traverse through linked list in each bucket.
	for(i = 0; i < hm->num_buckets; i++) {
		struct llnode* head = hm->map[i];
		struct llnode* curr = head;
		while (curr != NULL) {
			idf = calc_idf(curr);
			//printf("%f %s\n", idf, curr->word);
			if (idf == 0.0) {
				struct llnode* temp = curr->next;	// Save node after curr.
				hm_remove(hm, curr->word);			// Remove current node from hashmap.
				curr = temp;						// Assign curr to temp (removed node's next node).
			}
			else {
				curr = curr->next;
			}
		}
	}
}

/* Training phase: pre-process documents and add entries to hash table. Then remove stop words. */
struct hashmap* training(int num_buckets) { 
	FILE* file_ptr;
	char word[20];	// Word is max 20 characters.

	// Create the hashmap with hardcoded number of buckets.
	struct hashmap* hm = hm_create(num_buckets);

	/* READ FROM D1.txt */
	file_ptr = fopen("D1.txt", "r");
	if (file_ptr == NULL) { 
		printf("File not found\n");
		return NULL; 
	}

	// Continuously read in words and put in hashmap until end of file.
	while (fscanf(file_ptr, "%s ", word) != EOF) {
		char* word_ptr = word;
		struct llnode* node = hm_get(hm, word_ptr);
		if (node == NULL) {						// Doesn't exist in hashmap, so add with d1_count = 1.
			hm_put(hm, word_ptr, 1, 0, 0);
		} else {								// Already there, so update d1_count.
			hm_put(hm, word_ptr, node->d1_count + 1, node->d2_count, node->d3_count);
		}
	}
	fclose(file_ptr);

	/* READ FROM D2.txt */
	file_ptr = fopen("D2.txt", "r");
	if (file_ptr == NULL) { 
		printf("File not found\n");
		return NULL; 
	}
	while (fscanf(file_ptr, "%s ", word) != EOF) {
		char* word_ptr = word;
		struct llnode* node = hm_get(hm, word_ptr);
		if (node == NULL) {
			hm_put(hm, word_ptr, 0, 1, 0);
		} else {
			hm_put(hm, word_ptr, node->d1_count, node->d2_count + 1, node->d3_count);
		}
	}
	fclose(file_ptr);

	/* READ FROM D3.txt */
	file_ptr = fopen("D3.txt", "r");
	if (file_ptr == NULL) { 
		printf("File not found\n");
		return NULL; 
	}
	while (fscanf(file_ptr, "%s ", word) != EOF) {
		char* word_ptr = word;
		struct llnode* node = hm_get(hm, word_ptr);
		if (node == NULL) {
			hm_put(hm, word_ptr, 0, 0, 1);
		} else {
			hm_put(hm, word_ptr, node->d1_count, node->d2_count, node->d3_count + 1);
		}
	}
	fclose(file_ptr);

	//hm_print(hm, num_buckets);

	// Remove stop words (idf = 0, appear in all documents)
	stop_word(hm);

	//hm_print(hm, num_buckets);	

	return hm;
}