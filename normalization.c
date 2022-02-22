#include <stdio.h>
#include <stdlib.h>

#include "normalization.h"
#include "descriptiveStatistics.h"

/* a function which will generate normalized values within a required interval */
double * normalizeMinMax(double *array, double new_min, double new_max, unsigned int n_elements) {

    performCheck(n_elements);
    /* find the min and max */
    double minimum = findMin(array, n_elements);
    double maximum = findMax(array, n_elements);

    /* create a new array so that the normalization is not performed "in-place",
     * modifying the original array */
    double *normalized = NULL;
    normalized = (double*) malloc(sizeof(double) * n_elements);

    /* for each element, normalize it and append it to a new array */
    for (int i = 0; i < n_elements; i++) {
        normalized[i] = ((array[i] - minimum) / (maximum - minimum)) * (new_max - new_min) + new_min;
    }

    return normalized;
}

/* standard technique for normalizing the values using Z-Score standardization */
double * normalizeZScore(double *array, unsigned int n_elements) {

    performCheck(n_elements);
    /* find the min and max */
    double mean = computeMean(array, n_elements);
    struct discrepancy std = computeStd(array, n_elements);
    /* standardize using the unbiased standard deviation */
    double standard_deviation = std.unbiased;

    /* create a new array so that the normalization is not performed "in-place",
     * modifying the original array */
    double *normalized = NULL;
    normalized = (double*) malloc(sizeof(double) * n_elements);

    /* for each element, normalize it and append it to a new array */
    for (int i = 0; i < n_elements; i++) {
        normalized[i] = ((array[i] - mean) / standard_deviation);
    }

    return normalized;
}
