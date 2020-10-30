/*
 *****************************************************************************
 * @file        matrix_functions.h
 * @brief       Header for matrix_functions.c
 * 
 *****************************************************************************
 * @author      Aaryaman
 *
 *****************************************************************************
 * 
 */


#ifndef POOLING_OPERATIONS_H
#define POOLING_OPERATIONS_H

//-------- Includes ----------------------------------------------------------//

#include <stdint.h>
#include "vector_operations.h"
//-------- Defines -----------------------------------------------------------//

//-------- Constants & enums -------------------------------------------------//

//-------- Structs & typedefs ------------------------------------------------//

//-------- Global variables --------------------------------------------------//

//-------- Global function prototypes ----------------------------------------//

						
void max_pool_d8 (	const uint8_t	Src_nRows,
					const uint8_t	Src_nColumns,
					const int8_t	Src[Src_nRows][Src_nColumns],
					const uint8_t	Src_filter_nRows,
					const uint8_t	Src_filter_nColumns,
					const uint8_t	Src_Stride,
					int8_t			Dst[Src_nRows/Src_filter_nRows]  \
										[Src_nColumns/Src_filter_nColumns]	);
					
void avg_pool_d8 (	const uint8_t	Src_nRows,
					const uint8_t	Src_nColumns,
					const int8_t	Src[Src_nRows][Src_nColumns],
					const uint8_t	Src_filter_nRows,
					const uint8_t	Src_filter_nColumns,
					const uint8_t	Src_Stride,
					int8_t			Dst[Src_nRows/Src_filter_nRows]  \
										[Src_nColumns/Src_filter_nColumns]	);					
//----------------------------------------------------------------------------//

#endif
