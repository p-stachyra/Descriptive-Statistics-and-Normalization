# Descriptive-Statistics-and-Normalization

This repository allows to compute descriptive statistics for a numeric array of random values.
The main program serves as a demo, the source and header files containing functions and structures (descriptiveStatsitcs and normalization), can be exported to another project, transformed into libraries.

## Usage 

### Compile
gcc -Wall main.c descriptiveStatistics.c normalization.c -o program
### Running the program
./program [number_of_elements_in_the_array] [minimal_value_normalization] [maximal_value_normalization]


