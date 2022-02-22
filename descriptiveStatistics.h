#ifndef NORMALISATION_DESCRIPTIVESTATISTICS_H
#define NORMALISATION_DESCRIPTIVESTATISTICS_H

struct discrepancy {
    double biased;
    double unbiased;
};

void performCheck(unsigned int number_elements);
int comparison(const void * p1, const void * p2);
double findMax(double *array, unsigned int n_elements);
double findMin(double *array, unsigned int n_elements);
double findMedian(double *array, unsigned int n_elements);
double computeMean(double *array, unsigned int n_elements);
struct discrepancy computeStd(double *array, unsigned int n_elements);
struct discrepancy computeVar(double *array, unsigned int n_elements);

#endif //NORMALISATION_DESCRIPTIVESTATISTICS_H
