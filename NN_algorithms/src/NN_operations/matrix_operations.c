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

#include "matrix_operations.h"


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
                        int8_t          Dst[SrcA_nRows][SrcB_nColumns]     ){

	int8_t dotProduct;
	int8_t tempVec[SrcB_nRows];

    for (uint8_t i = 0; i < SrcA_nRows; i++){
        for(uint8_t j = 0; j < SrcB_nColumns; j++){
           for(uint8_t k = 0; k < SrcA_nColumns; k++){tempVec[k]=SrcB[k][j];}
           vect_dotProduct(SrcA_nColumns,SrcA[i],tempVec,&dotProduct);
           Dst[i][j]=dotProduct;
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
                        int8_t          Dst[Src_nRows][Src_nColumns]     ){

    for (uint8_t i = 0; i < Src_nRows; i++){
       vect_add(Src_nRows,SrcA[i],SrcB[i],Dst[i]);
    }
}




