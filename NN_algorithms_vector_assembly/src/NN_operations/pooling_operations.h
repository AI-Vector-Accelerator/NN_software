#ifndef POOLING_OPERATIONS_H
#define POOLING_OPERATIONS_H

#include <stdint.h>
#include "vector_operations.h"

						
void max_pool_d8 (	const uint32_t	Src_nRows,
					const uint32_t	Src_nColumns,
					int8_t	Src[Src_nRows][Src_nColumns],
					const uint32_t	Src_filter_nRows,
					const uint32_t	Src_filter_nColumns,
					const uint32_t	Src_Stride,
					int8_t			Dst[Src_nRows/Src_filter_nRows]  \
										[Src_nColumns/Src_filter_nColumns]	);
					
void avg_pool_d8 (	const uint32_t	Src_nRows,
					const uint32_t	Src_nColumns,
					int8_t	Src[Src_nRows][Src_nColumns],
					const uint32_t	Src_filter_nRows,
					const uint32_t	Src_filter_nColumns,
					const uint32_t	Src_Stride,
					int8_t			Dst[Src_nRows/Src_filter_nRows]  \
										[Src_nColumns/Src_filter_nColumns]	);					


#endif
