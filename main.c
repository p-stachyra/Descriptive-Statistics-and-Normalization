#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "descriptiveStatistics.h"
#include "normalization.h"

int main(int argc, char **argv) {
    /* measure performance of the program */
    double exec_time = 0.0;
    clock_t start = clock();
    clock_t finish = (clock_t) NULL;

    /* set seed for random numbers */
    srand(time(0));

    /* initializations: the number of elements (n)
     * and the doubles array for which the memory allocation
     * is performed dynamically */

    if (argc != 4) {
        fprintf(stdout, "Usage: %s <number of elements> <new_min> <new_max>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    /* the first command line argument will be used as the number of array's elements */
    int n = atoi(argv[1]);
    double new_min = atof(argv[2]);
    double new_max = atof(argv[3]);

    /* variables for min, max, standard deviation, variance */
    double max_v = 0.0, min_v = 0.0, mean_v = 0.0, median = 0.0;
    /* structures for storing standard deviations and variance (biased and unbiased) */
    struct discrepancy standard_dev;
    struct discrepancy variance;

    /* file for outputting results */
    FILE *fp = NULL;

    /* dynamically allocate memory for storing the numbers */
    double *arr = NULL;
    arr = (double*) malloc(n * sizeof(double));

    /* assign random numbers as array's elements */
    for (int i = 0; i < n; i++) {
        arr[i] = rand() / 9.8;
    }

    /* declare 2 new arrays for normalized values */
    double * normalized1 = NULL;
    double * normalized2 = NULL;

    /* perform descriptive statistics computations */
    max_v = findMax(arr, n);
    min_v = findMin(arr, n);
    mean_v = computeMean(arr, n);
    variance = computeVar(arr, n);
    standard_dev = computeStd(arr, n);
    median = findMedian(arr, n);
    /* normalize the values of the array */
    /* Min-Max normalization - interval of [20.0, 80.0] */
    normalized1 = normalizeMinMax(arr, new_min, new_max, n);
    /* Z-Score normalization */
    normalized2 = normalizeZScore(arr, n);

    /* save the results to a text file */
    fp = fopen("report.txt", "w");

    if (fp == NULL) {
        perror("Could not open the report file. Error");
        exit(EXIT_FAILURE);
    }
    /* save the array contents to the file */
    for (int j = 0; j < n; j++) {
        fprintf(fp, "%lf\n", arr[j]);
    }
    /* save descriptive statistics outputs to the file */
    fprintf(fp, "\n\n");
    fprintf(fp, "Maximum value: %lf\nMinimum value: %lf\nMean value: %lf\nMedian: %lf\nPopulation variance: %lf\nSample unbiased variance: %lf\nPopulation standard deviation: %lf\nSample unbiased standard deviation: %lf\n", max_v, min_v, mean_v, median, variance.biased, variance.unbiased, standard_dev.biased, standard_dev.unbiased);

    fprintf(fp, "\nNormalized Values: Min-Max Normalization [%lf, %lf]\n", new_min, new_max);
    /* save the normalized arrays to the report file. */
    for (int k = 0; k < n; k++) {
        fprintf(fp, "%lf\n", normalized1[k]);
    }

    fprintf(fp, "\nNormalized Values: Z-Score Normalization\n");
    /* save the normalized arrays to the report file. */
    for (int l = 0; l < n; l++) {
        fprintf(fp, "%lf\n", normalized2[l]);
    }

    /* close the file */
    fclose(fp);

    /* performance measurement */
    finish = clock();
    /* elapsed time: finish - start
     * and divide by CLOCKS_PER_SEC to get seconds
     */
    exec_time += (double) (finish - start) / CLOCKS_PER_SEC;
    printf("Program finished. Execution time: %lf %s", exec_time, (exec_time == 1.0) ? "second" : "seconds");
    return 0;
}
