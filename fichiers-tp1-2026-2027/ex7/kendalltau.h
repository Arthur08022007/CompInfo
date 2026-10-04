#ifndef _KENDALLTAU_H
#define _KENDALLTAU_H

/**
 * @brief Compute Kendall tau's coefficient between vectors x and y.
 *        The function can reorder x and y but, if so, it should keep the pairing
 *        between values unchanged. Vectors x and y can be assumed to contain
 *        only unique values.
 *
 * @param x                 first vector of values
 * @param y                 second vector of values
 * @param n                 length of both vectors
 * @return double           kendall's tau coefficient between x and y
 */
double kendallTauSlow(double x[], double y[], int n);

/**
 * @brief Compute Kendall tau's coefficient between vectors x and y.
 *        The function can reorder x and y but, if so, it should keep the pairing
 *        between values unchanged. Vectors x and y can be assumed to contain
 *        only unique values.
 *
 * @param x                 first vector of values
 * @param y                 second vector of values
 * @param n                 length of both vectors
 * @return double           kendall's tau coefficient between x and y
 */
double kendallTauFast(double x[], double y[], int n);


#endif
