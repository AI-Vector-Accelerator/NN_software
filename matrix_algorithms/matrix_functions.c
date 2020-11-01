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

#include <stdio.h>
#include <stdint.h>

#include "matrix_functions.h"

//-------- Defines -----------------------------------------------------------//

//-------- Constants & enums -------------------------------------------------//

//-------- Structs & typedefs ------------------------------------------------//

//-------- Global variables --------------------------------------------------//

//-------- Static Variables --------------------------------------------------//

//-------- Static function prototypes ----------------------------------------//

//-------- Function implementations ------------------------------------------//


/* * @brief  Multiply two matrices
 *  
 *  Takes in two matrices defined by rows and columns, then multiplies them 
 *
 * @param   SrcA_nRows      Number of rows in the first matrix
 *          SrcA_nColumns   Number of columns in the first matrix
 *          SrcB_nRows      Number of rows in the second matrix
 *          SrcB_nColumns   Number of column in the second matrix
 *          SrcA            First matrix in
 *          SrcB            Second matrix in  
 *          
 * @retval  Dst             Matrix out
 */
void matrix_mult_d8 (   const uint8_t   SrcA_nRows,
                        const uint8_t   SrcA_nColumns,
                        const uint8_t   SrcB_nRows,
                        const uint8_t   SrcB_nColumns,
                        const int8_t    SrcA[SrcA_nRows][SrcA_nColumns],
                        const int8_t    SrcB[SrcB_nRows][SrcB_nColumns],
                        int8_t          Dst[SrcA_nRows][SrcB_nColumns]     )
{
    for (uint8_t i = 0; i < SrcA_nRows; i++)
    {
        for(uint8_t j = 0; j < SrcB_nColumns; j++)
        {
           for(uint8_t k = 0; k < SrcA_nColumns; k++)
           {
               Dst[i][j] += SrcA[i][k] * SrcB[k][j]; 
           }
 
        }
    }

}


/* * @brief  Add two matrices
 *  
 *  Takes in two matrices defined by rows and columns, then adds them
 *
 * @param   Src_nRows       Number of rows in the input matrices
 *          Src_nColumns    Number of columns in the input matrices
 *          SrcA            First matrix in
 *          SrcB            Second matrix in  
 *          
 * @retval  Dst             Matrix out
 */
void matrix_add_d8 (    const uint8_t   Src_nRows,
                        const uint8_t   Src_nColumns,
                        const int8_t    SrcA[Src_nRows][Src_nColumns],
                        const int8_t    SrcB[Src_nRows][Src_nColumns],
                        int8_t          Dst[Src_nRows][Src_nColumns]     )
{
    for (uint8_t i = 0; i < Src_nRows; i++)
    {
        for(uint8_t j = 0; j < Src_nColumns; j++)
        {
            Dst[i][j] = SrcA[i][j] + SrcB[i][j];
        }
    }

}

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
										[Src_nColumns/Src_filter_nColumns]	)
{
	uint8_t max = -128;
	for (uint8_t i = 0; i < (int)Src_nRows/Src_filter_nRows; i++)
	{
		for (uint8_t j = 0; j < (int)Src_nColumns/Src_filter_nColumns; j++)
		{
			for (uint8_t k = 0; k < Src_filter_nRows; k++)
			{
				for (uint8_t l = 0; l < Src_filter_nColumns; l++)
				{
					uint8_t position_i = i*Src_Stride + k;
					uint8_t position_j = j*Src_Stride + l;
					
					if (max < Src[position_i][position_j])
					{
						max = Src[position_i][position_j];
					}
				}
			}
			
			Dst[i][j] = max;
			max = -128;
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
										[Src_nColumns/Src_filter_nColumns]	)
{
	uint32_t sum = 0;
	for (uint8_t i = 0; i < (int)Src_nRows/Src_filter_nRows; i++)
	{
		for (uint8_t j = 0; j < (int)Src_nColumns/Src_filter_nColumns; j++)
		{
			for (uint8_t k = 0; k < Src_filter_nRows; k++)
			{
				for (uint8_t l = 0; l < Src_filter_nColumns; l++)
				{
					uint8_t position_i = i*Src_Stride + k;
					uint8_t position_j = j*Src_Stride + l;
					
					sum += Src[position_i][position_j];
				}
			}
			
			//average is sum/(number of elements in filter)
			Dst[i][j] = (int)(sum/(Src_filter_nRows*Src_filter_nColumns));
			sum = 0;
		}
	}
}