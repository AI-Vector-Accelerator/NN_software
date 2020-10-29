#ifndef VECTOR_OPERATIONS_H_
#define VECTOR_OPERATIONS_H_

#include <stdlib.h>
#include <stdint.h>


void vect_add(unsigned int N, const int8_t *vec1, const int8_t *vec2, int8_t *vecOut);
void vect_mult(unsigned int N, const int8_t *vec1, const int8_t *vec2, int8_t *vecOut);
void vect_dotProduct(unsigned int N, const int8_t *vec1, const int8_t *vec2, int8_t *scalarOut);
void vect_ReLu(unsigned int N, const int8_t *vec1, int8_t *vecOut);
void vect_ReLu6(unsigned int N, const int8_t *vec1, int8_t *vecOut);




#endif /* VECTOR_OPERATIONS_H_ */