#ifndef NN_ALGORITHMS_TESTBENCH_H_
#define NN_ALGORITHMS_TESTBENCH_H_


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "NN_operations/vector_operations.h"
#include "NN_operations/convolution_operations.h"
#include "NN_operations/matrix_operations.h"
#include "NN_operations/pooling_operations.h"
#include "Matrix_IO.h"


int main(void);

unsigned long getCycles(void);

void testbench_dotProduct(unsigned long *Cycles_NN_operations);
void testbench_vectorAdd(unsigned long *Cycles_NN_operations);
void testbench_addReduction(unsigned long *Cycles_NN_operations);
void testbench_vectorReLu(unsigned long *Cycles_NN_operations);
void testbench_vectorReLu6(unsigned long *Cycles_NN_operations);
void testbench_vectorMult(unsigned long *Cycles_NN_operations);

void testbench_matrix_mult_d8(unsigned long *Cycles_NN_operations);
void testbench_matrix_add_d8(unsigned long *Cycles_NN_operations);
void testbench_max_pool_d8(unsigned long *Cycles_NN_operations);
void testbench_avg_pool_d8(unsigned long *Cycles_NN_operations);

void testbench_conv2D_multiInputChannel(unsigned long *Cycles_NN_operations);
void testbench_conv2D(unsigned long *Cycles_NN_operations);
void testbench_conv2D_multiOutputChannel(unsigned long *Cycles_NN_operations);
void testbench_conv2D_multiIOChannel(unsigned long *Cycles_NN_operations);
void testbench_conv2D_depthwise(unsigned long *Cycles_NN_operations);
void testbench_conv2D_depthwiseSeparable(unsigned long *Cycles_NN_operations);
void testbench_conv2D_depthwiseSeparable_multiOutputChannel(unsigned long *Cycles_NN_operations);



#endif /* NN_ALGORITHMS_TESTBENCH_H_ */
