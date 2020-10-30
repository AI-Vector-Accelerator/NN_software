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


#ifndef MATRIX_FUNCTIONS_H
#define MATRIX_FUNCTIONS_H

//-------- Includes ----------------------------------------------------------//

#include <stdint.h>
#include <stdio.h>
//-------- Defines -----------------------------------------------------------//

//-------- Constants & enums -------------------------------------------------//

//-------- Structs & typedefs ------------------------------------------------//

//-------- Global variables --------------------------------------------------//

//-------- Global function prototypes ----------------------------------------//

void matrix_mult_d8 (   const uint8_t   SrcA_nRows,
                        const uint8_t   SrcA_nColumns,
                        const uint8_t   SrcB_nRows,
                        const uint8_t   SrcB_nColumns,
                        const int8_t    SrcA[SrcA_nRows][SrcA_nColumns],
                        const int8_t    SrcB[SrcB_nRows][SrcB_nColumns],
                        int8_t          Dst[SrcA_nRows][SrcB_nColumns]     );

void matrix_add_d8 (    const uint8_t   Src_nRows,
                        const uint8_t   Src_nColumns,
                        const int8_t    SrcA[Src_nRows][Src_nColumns],
                        const int8_t    SrcB[Src_nRows][Src_nColumns],
                        int8_t          Dst[Src_nRows][Src_nColumns]     );
						
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