#include "pooling_operations.h"


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
void max_pool_d8 (	const uint32_t	Src_nRows,
					const uint32_t	Src_nColumns,
					int8_t	Src[Src_nRows][Src_nColumns],
					const uint32_t	Src_filter_nRows,
					const uint32_t	Src_filter_nColumns,
					const uint32_t	Src_Stride,
					int8_t			Dst[Src_nRows/Src_filter_nRows]  \
										[Src_nColumns/Src_filter_nColumns]	){

	uint32_t position_i,position_j,vecLength=Src_nColumns/Src_filter_nColumns;
	
	for (uint32_t i = 0; i < Src_nRows/Src_filter_nRows; i++){
		for (uint32_t j = 0; j < vecLength; j++){
			Dst[i][j] = MIN_INT8_T;
		}
	}
	for (uint32_t i = 0; i < Src_nRows/Src_filter_nRows; i++){
		for (uint32_t k = 0; k < Src_filter_nRows; k++){
			position_i = i*Src_Stride + k;
			for (uint32_t l = 0; l < Src_filter_nColumns; l++){
				position_j = l;
				vect_max_stride_vec2(vecLength, Dst[i],&Src[position_i][position_j], Dst[i],Src_filter_nColumns);
			}
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
void avg_pool_d8 (	const uint32_t	Src_nRows,
					const uint32_t	Src_nColumns,
					int8_t	Src[Src_nRows][Src_nColumns],
					const uint32_t	Src_filter_nRows,
					const uint32_t	Src_filter_nColumns,
					const uint32_t	Src_Stride,
					int8_t			Dst[Src_nRows/Src_filter_nRows]  \
										[Src_nColumns/Src_filter_nColumns]	){

	uint32_t position_i,position_j;
	uint32_t tempVecLength=Src_nColumns/Src_filter_nColumns;
	int16_t tempVec[tempVecLength];
		
	for (uint32_t i = 0; i < Src_nRows/Src_filter_nRows; i++){
		for (uint32_t j = 0; j < tempVecLength; j++){tempVec[j]=0;}
		for (uint32_t k = 0; k < Src_filter_nRows; k++){
			position_i = i*Src_Stride + k;
			for (uint32_t l = 0; l < Src_filter_nColumns; l++){
				position_j = l;
				vect_add_stride_vec2(tempVecLength, tempVec,&Src[position_i][position_j], tempVec,Src_filter_nColumns);
			}
		}
		for (uint32_t j = 0; j < tempVecLength; j++){
			Dst[i][j] = saturate_16bit_to_8bit(tempVec[j]/(int16_t)(Src_filter_nRows*Src_filter_nColumns));
		}
	}
}
