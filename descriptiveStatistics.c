#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "descriptiveStatistics.h"

/* helper function for checking inputs */
void performCheck(unsigned int number_elements) {

    /* check if the user by any chance provided a negative number */
    int check = (int) number_elements;

    /* CASE: cannot operate on the array: display error message and terminate the program run */
    if (check <= 0) {
        fprintf(stdout, "Cannot operate on an array of negative or 0 size!\nThe function expects an array of numbers and the number of elements held by the array.\n");
        exit(EXIT_FAILURE);
    }
}

/* helper function for qsort */
int comparison(const void * p1, const void * p2) {
    /* do the casting to compare the 2 numbers */
    const double * a1 = (const double *) p1;
    const double * a2 = (const double *) p2;

    /* these are the rules for returning data expected by qsort function */
    if (*a1 < *a2) {
        return -1;
    }
    else if (*a1 == *a2) {
        return 0;
    }
    else {
        return 1;
    }
}


/* DESCRIPTIVE STATISTICS FUNCTIONS */

double findMax(double *array, unsigned int n_elements) {

    performCheck(n_elements);

    /* assume that the first number the array holds is the maximal value */
    double maximum = array[0];
    /* check if any other number in the array is greater */
    for (int i = 1; i < n_elements; i++) {
        /* if other number is greater, replace the current maximum value
         * with that number */
        if (array[i] > maximum) {
            maximum = array[i];
        }
    }
    return maximum;
}

double findMin(double *array, unsigned int n_elements) {

    performCheck(n_elements);

    /* assume that the first number the array holds is the minimal value */
    double minimum = array[0];
    /* check if any other number in the array is smaller */
    for (int i = 1; i < n_elements; i++) {
        /* if other number is smaller, replace the current minimum value
         * with that number */
        if (array[i] < minimum) {
            minimum = array[i];
        }
    }
    return minimum;
}

double findMedian(double *array, unsigned int n_elements) {

    performCheck(n_elements);

    double median = 0.0;
    int index1 = 0;
    int index2 = 0;

    /* sort the array */
    qsort(array, n_elements, sizeof(double), comparison);

    /* if the array has an even number of elements,
     * the median will be in between the middle values
     * of the array */
    if (n_elements % 2 == 0) {
        index2 = n_elements / 2;
        index1 = index2 - 1;
        median = array[index1] + (array[index2] - array[index1]) / 2.0;
    }
    /* otherwise, it will be the middle value */
    else {
        index1 = (((float) n_elements) / 2.0 + 0.5) - 1;
        median = array[index1];
    }

    return median;
}

double computeMean(double *array, unsigned int n_elements) {

    performCheck(n_elements);

    /* declare and initialize mean and cumulative sum*/
    double mean = 0.0;
    double c_sum = 0.0;
    /* arithmetic mean for a numerical array */
    for (int i = 0; i < n_elements; i++) {
        c_sum += array[i];
    }

    mean = c_sum / (double) n_elements;

    return mean;
}

struct discrepancy computeStd(double *array, unsigned int n_elements) {

    performCheck(n_elements);

    /* declare and initialize mean, squared difference, standard deviation */
    double mean = computeMean(array, n_elements);
    double squared_diff = 0.0;
    double std_biased = 0.0;
    double std_unbiased = 0.0;
    struct discrepancy standard_deviation;

    /* arithmetic mean for a numerical array */
    for (int i = 0; i < n_elements; i++) {
        squared_diff += pow((array[i] - mean), 2);
    }

    std_biased = sqrt((squared_diff) / (double) n_elements);
    std_unbiased = sqrt((squared_diff) / ((double) n_elements - 1));

    standard_deviation.biased = std_biased;
    standard_deviation.unbiased = std_unbiased;

    return standard_deviation;

}

struct discrepancy computeVar(double *array, unsigned int n_elements) {

    performCheck(n_elements);

    /* declare and initialize mean, squared difference, standard deviation */
    double mean = computeMean(array, n_elements);
    double squared_diff = 0.0;
    double var_biased = 0.0;
    double var_unbiased = 0.0;
    struct discrepancy standard_deviation;

    /* arithmetic mean for a numerical array */
    for (int i = 0; i < n_elements; i++) {
        squared_diff += pow((array[i] - mean), 2);
    }

    var_biased = squared_diff / (double) n_elements;
    var_unbiased = squared_diff / ((double) n_elements - 1);

    standard_deviation.biased = var_biased;
    standard_deviation.unbiased = var_unbiased;

    return standard_deviation;

}