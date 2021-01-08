#ifndef MATRIX_FUNCTIONS_H
#define MATRIX_FUNCTIONS_H


#include <stdint.h>
#include "vector_operations.h"


void matrix_mult_d8 (   const uint32_t   SrcA_nRows,
                        const uint32_t   SrcA_nColumns,
                        const uint32_t   SrcB_nRows,
                        const uint32_t   SrcB_nColumns,
                        int8_t    SrcA[SrcA_nRows][SrcA_nColumns],
                        int8_t    SrcB[SrcB_nRows][SrcB_nColumns],
                        int8_t          Dst[SrcA_nRows][SrcB_nColumns]     );

void matrix_add_d8 (    const uint32_t   Src_nRows,
                        const uint32_t   Src_nColumns,
                        int8_t    SrcA[Src_nRows][Src_nColumns],
                        int8_t    SrcB[Src_nRows][Src_nColumns],
                        int8_t          Dst[Src_nRows][Src_nColumns]     );
						


#endif
