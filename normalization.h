#ifndef NORMALISATION_NORMALIZATION_H
#define NORMALISATION_NORMALIZATION_H

double * normalizeMinMax(double *array, double new_min, double new_max, unsigned int n_elements);
double * normalizeZScore(double *array, unsigned int n_elements);

#endif //NORMALISATION_NORMALIZATION_H
