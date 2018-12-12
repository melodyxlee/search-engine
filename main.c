#include "hashmap.h"
#include "calc.h"
#include "training.h"
#include "search_retrieval.h"
#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 


int main(void){
	int num_buckets = 0;
	char prompt;
	double scores[3];	// To store the document relevance scores.


    printf("Enter number of buckets: ");
    scanf("%d", &num_buckets);

    // The hashmap of the document words created in the training phase. 
    struct hashmap* doc_hm = training(num_buckets);

    while(1) {
    	printf("Enter S for search or X to exit: ");
    	scanf(" %c", &prompt);
    	switch(prompt) {
    		// Either upper or lower case.
    		case 's': case 'S':
    			printf("Enter search query: \n"); 
    			read_query(doc_hm, scores);
    			rank(scores);
    			break;

    		case 'x': case 'X':
    			printf("Exiting...\n");
    			return 0;

    		// If user enters character other than s or x.
    		default:	
         		printf("Please just follow the instructions.\n");
         		break;
    	} 
    }

    return 0;
}
