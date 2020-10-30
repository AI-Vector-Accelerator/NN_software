/*
 *****************************************************************************
 * @file        matrix_functions.c
 * @brief       Functions for matrices
 *
 *****************************************************************************
 * @author      Aaryaman
 *
 *****************************************************************************
 * 
 */

//-------- Includes ----------------------------------------------------------//


#include "pooling_operations.h"

//-------- Defines -----------------------------------------------------------//

//-------- Constants & enums -------------------------------------------------//

//-------- Structs & typedefs ------------------------------------------------//

//-------- Global variables --------------------------------------------------//

//-------- Static Variables --------------------------------------------------//

//-------- Static function prototypes ----------------------------------------//

//-------- Function implementations ------------------------------------------//



/* * @brief  Find the max pool using the input filter matrix
 *  
 *  Traverses the matrix using the input stride, and finds the max 
 *	value within sliding window of the filter and puts this value in
 *	the output matrix. 
 *
 * @param   Src_nRows       	Number of rows in the input matrices
 *          Src_nColumns    	Number of columns in the input matrices
 *          Src            		First matrix in
 *          Src_filter_nRows    Rows in input filter
 *          Src_filter_nColumns	Columns in input filter
 *          Src_Stride			Input stride
 *          Dst					Output matrix  
 *          
 * @retval  Dst             Matrix out
 */
void max_pool_d8 (	const uint8_t	Src_nRows,
					const uint8_t	Src_nColumns,
					const int8_t	Src[Src_nRows][Src_nColumns],
					const uint8_t	Src_filter_nRows,
					const uint8_t	Src_filter_nColumns,
					const uint8_t	Src_Stride,
					int8_t			Dst[Src_nRows/Src_filter_nRows]  \
										[Src_nColumns/Src_filter_nColumns]	){

	uint8_t position_i,position_j,vecCounter;
	int8_t max;
	int8_t tempVec[Src_filter_nRows*Src_filter_nColumns];

	for (uint8_t i = 0; i < (int)Src_nRows/Src_filter_nRows; i++){
		for (uint8_t j = 0; j < (int)Src_nColumns/Src_filter_nColumns; j++){
			vecCounter=0;
			for (uint8_t k = 0; k < Src_filter_nRows; k++){
				for (uint8_t l = 0; l < Src_filter_nColumns; l++){
					position_i = i*Src_Stride + k;
					position_j = j*Src_Stride + l;
					tempVec[vecCounter]=Src[position_i][position_j];
					vecCounter++;
				}
			}
			max = -128;//8-bit signed minimum
			for(vecCounter=0;vecCounter<Src_filter_nRows*Src_filter_nColumns;vecCounter++){		//is it possible to make vector instruction for this compare?
				if (max < tempVec[vecCounter]){max = tempVec[vecCounter];}
			}
			Dst[i][j] = max;
		}
	}
}

/* * @brief  Find the average pool using the input filter matrix
 *  
 *  Traverses the matrix using the input stride, and finds the average 
 *	value within sliding window of the filter and puts this value in
 *	the output matrix. 
 *
 * @param   Src_nRows       	Number of rows in the input matrices
 *          Src_nColumns    	Number of columns in the input matrices
 *          Src            		First matrix in
 *          Src_filter_nRows    Rows in input filter
 *          Src_filter_nColumns	Columns in input filter
 *          Src_Stride			Input stride
 *          Dst					Output matrix  
 *          
 * @retval  Dst             Matrix out
 */
void avg_pool_d8 (	const uint8_t	Src_nRows,
					const uint8_t	Src_nColumns,
					const int8_t	Src[Src_nRows][Src_nColumns],
					const uint8_t	Src_filter_nRows,
					const uint8_t	Src_filter_nColumns,
					const uint8_t	Src_Stride,
					int8_t			Dst[Src_nRows/Src_filter_nRows]  \
										[Src_nColumns/Src_filter_nColumns]	){

	uint8_t position_i,position_j,vecCounter;
	int8_t sum, tempVec[Src_filter_nRows*Src_filter_nColumns];

	for (uint8_t i = 0; i < (int)Src_nRows/Src_filter_nRows; i++){
		for (uint8_t j = 0; j < (int)Src_nColumns/Src_filter_nColumns; j++){
			vecCounter=0;
			for (uint8_t k = 0; k < Src_filter_nRows; k++){
				for (uint8_t l = 0; l < Src_filter_nColumns; l++){
					position_i = i*Src_Stride + k;
					position_j = j*Src_Stride + l;
					tempVec[vecCounter]=Src[position_i][position_j];
					vecCounter++;
				}
			}
			vect_addRecursive(vecCounter,tempVec,&sum);
			Dst[i][j] = sum/vecCounter;	//average is sum/(number of elements in filter)
		}
	}
}
