#include "hashmap.h"
#include <stdlib.h>
#include <stdio.h> 
#include <string.h> 

/* Allocates a new HashMap with the specified number of buckets. */
struct hashmap* hm_create(int num_buckets){
	struct hashmap* new_hm = (struct hashmap*) malloc(sizeof(struct hashmap));
	new_hm->num_buckets = num_buckets;
	new_hm->num_elements = 0;
	new_hm->map = (struct llnode**) malloc(sizeof(struct llnode*) * num_buckets);
	return new_hm; 
}

/* Returns the node containing the word. */
struct llnode* hm_get(struct hashmap* hm, char* word){
	int bucket = hash(hm, word);
	struct llnode* head = hm->map[bucket];
	// No nodes in bucket to return.
	if (head == NULL) {
		return NULL;
	}
	// Traverse list and try to find match.
	else {
		struct llnode* curr = head;
		while (curr != NULL) {
			if (strcmp(curr->word, word) == 0) {
				return curr;
			}
			curr = curr->next;
		}
		return NULL;
	}
}

/* Puts the key value pair into the HashMap that is passed in. */
void hm_put(struct hashmap* hm, char* word, int d1_count, int d2_count, int d3_count){
	int bucket = hash(hm, word);
	struct llnode* head = hm->map[bucket];
	char* word_copy = malloc(20);			// Allocate space for 20 chars on the heap.
	memset(word_copy, '\0', 20);			// Fill the 20 bytes of word_copy with '/0'.
	strcpy(word_copy, word);				// Copy string pointed to by word to word_copy.
	
	// If no node in bucket, make the head node and set its values.
	if (head == NULL) {
		struct llnode* new_node = (struct llnode*) malloc(sizeof(struct llnode));
		hm->map[bucket] = new_node;
		new_node->word = word_copy;
		new_node->d1_count = d1_count;
		new_node->d2_count = d2_count;
		new_node->d3_count = d3_count;
	}
	// Else traverse list and find match to update, or add new node to end of list. 
	else {
		struct llnode* curr = head;
		struct llnode* prev = head;
		while (curr != NULL) {
			if (strcmp(curr->word, word) == 0) {
				curr->d1_count = d1_count;
				curr->d2_count = d2_count;
				curr->d3_count = d3_count;
				return;
			}
			prev = curr;
			curr = curr->next;
		}
		// Add node to end of list.
		struct llnode* end_node = (struct llnode*) malloc(sizeof(struct llnode));
		end_node->word = word_copy;
		prev->next = end_node;
		end_node->d1_count = d1_count;
		end_node->d2_count = d2_count;
		end_node->d3_count = d3_count;
	}
	// Increment num_elements.
	hm->num_elements += 1;
}

/* Removes the key value pair in the HashMap that is associated with the given key. */
void hm_remove(struct hashmap* hm, char* word){
	int bucket = hash(hm, word);
	struct llnode* head = hm->map[bucket];

	if (head == NULL) {
		printf("Key value pair not found\n");
		return;
	}

	// Create two pointers to traverse through list.
	struct llnode* ptr1 = head;
	struct llnode* ptr2 = head->next;
	
	// If the list has only one node and that node should be deleted.
	if (ptr2 == NULL && strcmp(ptr1->word, word) == 0) {
	    hm->map[bucket] = NULL;
	    free(head);
	    // Decrement num_elements.
		hm->num_elements -= 1;
	    return;
	}

	// If the node to be deleted is the head node: delete it and free the memory.
	else if (strcmp(ptr1->word, word) == 0) {
	    ptr1->next = NULL;
	    free(ptr1);
	    hm->map[bucket] = ptr2;
	    // Decrement num_elements.
		hm->num_elements -= 1;
	    return;
	}

	while (ptr2 != NULL) {
	    // Remove the node and free memory if keys match.
	    if (strcmp(ptr2->word, word) == 0) {
	      	ptr1->next = ptr2->next;
	      	ptr2->next = NULL;
	      	free(ptr2);
	      	// Decrement num_elements.
		    hm->num_elements -= 1;
	      	return;
	    }
	    // Keep traversing until found or reached end of list.
	    ptr1 = ptr1->next;
	    ptr2 = ptr2->next;
	}
	// After reaching end of list, node not found.
	printf("Key value pair not found\n");
	return;
}

/* Deallocates (frees) the HashMap that is passed in and all of its elements. */
void hm_destroy(struct hashmap* hm){
	int i;
	// Free the llnodes.
	for (i = 0; i < hm->num_buckets; i++) {
		struct llnode* ptr = hm->map[i];
		struct llnode* temp;
		while (ptr != NULL) {
			temp = ptr;
			ptr = ptr->next;
			free(temp->word); // Because we malloc'd.
			free(temp);
		}
	}
	// Free the map.
	free(hm->map);
	// Free the hashmap itself.
	free(hm);
	printf("Destroyed\n");
}

/* Prints the contents of hashmap */
void hm_print(struct hashmap* hm, int num_buckets) {
	int i;
	for (i = 0; i < num_buckets; i++) {
		struct llnode* head = hm->map[i];
		struct llnode* curr = head;
		while (curr != NULL) {
			printf("bucket %d: %s %d %d %d\n", i, curr->word, curr->d1_count, curr->d2_count, curr->d3_count);
			curr = curr->next;
		}
	}
	printf("\n");
}

/* Takes the given word and maps it to a bucket in the HashMap. */
int hash(struct hashmap* hm, char* word){
	// Sum the ASCII codes of all of the characters then modulo by the number of buckets.
	char* ptr;
	int sum = 0;
	for (ptr = word; *ptr != '\0'; ptr++) {
		int ascii = (int) *ptr;			// Casting to int yields ASCII value.
		sum += ascii;
	}
	int bucket = sum % hm->num_buckets;
	return bucket;
}
