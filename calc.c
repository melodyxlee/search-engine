#include "calc.h"
#include <stdio.h> 
#include <math.h> // for log10()


/* Compute document frequency: # docs word appears at least once in. */ 
int calc_df(struct llnode* node) {
	int df = 0;
	if (node != NULL) {
		if (node->d1_count > 0) {
			df += 1;
		}
		if (node->d2_count > 0) {
			df += 1;
		}
		if (node->d3_count > 0) {
			df += 1;
		}
		return df;
	}
	return 0;
}

/* Compute inverse document frequency: log(N/df) */
double calc_idf(struct llnode* node) {
	int df = calc_df(node);
	double idf; 
	if (df == 0) {
		idf = log10(NUM_DOCUMENTS/(double)(df + 1));	// Add 1 to denominator to handle divide by zero.
	} else {
		idf = log10(NUM_DOCUMENTS/(double) df); 
	}
	return idf;
}
