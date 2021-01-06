#ifndef VECTOR_OPERATIONS_H_
#define VECTOR_OPERATIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define MAX_INT8_T 127
#define MIN_INT8_T -128

extern void vect_init(void);

extern void vect_add(unsigned int N, const int8_t *vec1, const int8_t *vec2, int8_t *vecOut);
extern void vect_add_32bits(unsigned int N,  int32_t *vec1,  int32_t *vec2, int32_t *vecOut);
extern void vect_addElementWise(unsigned int N, const int8_t *vec1, int32_t *vecOut, const int32_t vec1Offset, const int32_t scale);
extern void vect_mult(unsigned int N, const int8_t *vec1, const int8_t *vec2, int8_t *vecOut);

extern void vect_addReduction(unsigned int N, const int8_t *vec1, int16_t *scalarOut);
extern void vect_addReduction_stride(unsigned int N, const int8_t *vec1, int16_t *scalarOut, const int16_t scalarIn, uint32_t stride);
extern void vectu_addReduction_stride(unsigned int N, const uint8_t *vec1, uint16_t *scalarOut, const uint16_t scalarIn, uint32_t stride);


extern void vect_maxReduction(unsigned int N, const int8_t *vec1, int8_t *scalarOut);
extern void vect_maxReduction_stride(unsigned int N, const int8_t *vec1, int8_t *scalarOut, const int8_t scalarIn, uint32_t stride);
extern void vectu_maxReduction_stride(unsigned int N, const uint8_t *vec1, uint8_t *scalarOut, const uint8_t scalarIn, uint32_t stride);


extern void vect_dotProduct(unsigned int N, const int8_t *vec1, const int8_t *vec2, int32_t *scalarOut);
extern void vect_dotProduct_stride_vec2(unsigned int N, const int8_t *vec1, const int8_t *vec2, int32_t *scalarOut, uint32_t stride);
extern void vect_dotProduct_offset(unsigned int N, const int8_t *vec1, const int8_t *vec2, int32_t *scalarOut, const int32_t vec1Offset, const int32_t vec2Offset);
extern void vectu_dotProduct_offset(unsigned int N, const uint8_t *vec1, const uint8_t *vec2, int32_t *scalarOut, const int32_t vec1Offset, const int32_t vec2Offset);
extern void vect_dotProduct_offset_stride(unsigned int N, const int8_t *vec1, const int8_t *vec2, int32_t *scalarOut, const int32_t vec1Offset, const int32_t vec2Offset, uint32_t vec1Stride, uint32_t vec2Stride);
extern void vectu_dotProduct_offset_stride(unsigned int N, const uint8_t *vec1, const uint8_t *vec2, int32_t *scalarOut, const int32_t vec1Offset, const int32_t vec2Offset, uint32_t vec1Stride, uint32_t vec2Stride);


extern void vect_ReLu(unsigned int N, const int8_t *vec1, int8_t *vecOut);
extern void vect_ReLu_Bound(unsigned int N, const int8_t *vec1, int8_t *vecOut, int8_t lowerBound);
extern void vect_ReLu6(unsigned int N, const int8_t *vec1, int8_t *vecOut);
extern void vect_ReLu6_Bound(unsigned int N, const int8_t *vec1, int8_t *vecOut, int8_t lowerBound, int8_t upperBound);
extern void vect_ReLu6_Bound_32bits(unsigned int N,  int32_t *vec1, int32_t *vecOut, int32_t lowerBound, int32_t upperBound);
extern void vect_ReLu6_Bound_unsigned(unsigned int N, const uint8_t *vec1, uint8_t *vecOut, uint8_t lowerBound, uint8_t upperBound);

extern void vect_copy(unsigned int N,const int8_t *vec1, int8_t *vecOut);
extern void vect_copy_reg(unsigned int N,const int8_t value, int8_t *vecOut);


int8_t saturate_16bit_to_8bit(int16_t input);
int8_t saturate_32bit_to_8bit(int32_t input);


#ifdef __cplusplus
}
#endif

#endif /* VECTOR_OPERATIONS_H_ */
