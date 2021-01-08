#include "matrix_operations.h"


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
void matrix_mult_d8 (   const uint32_t   SrcA_nRows,
                        const uint32_t   SrcA_nColumns,
                        const uint32_t   SrcB_nRows,
                        const uint32_t   SrcB_nColumns,
                        int8_t    SrcA[SrcA_nRows][SrcA_nColumns],
                        int8_t    SrcB[SrcB_nRows][SrcB_nColumns],
                        int8_t          Dst[SrcA_nRows][SrcB_nColumns]     ){

	int32_t dotProduct;

    for (uint32_t i = 0; i < SrcA_nRows; i++){
        for(uint32_t j = 0; j < SrcB_nColumns; j++){
           vect_dotProduct_stride_vec2(SrcA_nColumns,SrcA[i],&SrcB[0][j],&dotProduct,SrcB_nColumns);
           Dst[i][j]=saturate_32bit_to_8bit( dotProduct );
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
void matrix_add_d8 (    const uint32_t   Src_nRows,
                        const uint32_t   Src_nColumns,
                        int8_t    SrcA[Src_nRows][Src_nColumns],
                        int8_t    SrcB[Src_nRows][Src_nColumns],
                        int8_t          Dst[Src_nRows][Src_nColumns]     ){

    for (uint32_t i = 0; i < Src_nRows; i++){
       vect_add(Src_nRows,SrcA[i],SrcB[i],Dst[i]);
    }
}




