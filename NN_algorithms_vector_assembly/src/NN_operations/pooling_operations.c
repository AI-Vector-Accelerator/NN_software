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

	uint32_t position_i,position_j,vecLength=Src_filter_nColumns;
	int8_t max=MIN_INT8_T;

	for (uint32_t i = 0; i < (int)Src_nRows/Src_filter_nRows; i++){
		for (uint32_t j = 0; j < (int)Src_nColumns/Src_filter_nColumns; j++){
			max=MIN_INT8_T;
			for (uint32_t k = 0; k < Src_filter_nRows; k++){
				position_i = i*Src_Stride + k;
				position_j = j*Src_Stride;
				vect_maxReduction_stride(vecLength, &Src[position_i][position_j], &max, max, 1);
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
void avg_pool_d8 (	const uint32_t	Src_nRows,
					const uint32_t	Src_nColumns,
					int8_t	Src[Src_nRows][Src_nColumns],
					const uint32_t	Src_filter_nRows,
					const uint32_t	Src_filter_nColumns,
					const uint32_t	Src_Stride,
					int8_t			Dst[Src_nRows/Src_filter_nRows]  \
										[Src_nColumns/Src_filter_nColumns]	){

	uint32_t position_i,position_j,vecLength=Src_filter_nColumns,filterElements=Src_filter_nRows*Src_filter_nColumns;
	int16_t sum;

	for (uint32_t i = 0; i < (int)Src_nRows/Src_filter_nRows; i++){
		for (uint32_t j = 0; j < (int)Src_nColumns/Src_filter_nColumns; j++){
			sum=0;
			for (uint32_t k = 0; k < Src_filter_nRows; k++){
				position_i = i*Src_Stride + k;
				position_j = j*Src_Stride;
				vect_addReduction_stride(vecLength, &Src[position_i][position_j], &sum, sum, 1);
			}
			Dst[i][j] = saturate_16bit_to_8bit( sum/(int16_t)filterElements );	//average is sum/(number of elements in filter)
		}
	}
}
