#ifndef NN_ALGORITHMS_TESTBENCH_H_
#define NN_ALGORITHMS_TESTBENCH_H_


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "NN_operations/convolution_operations.h"
#include "Matrix_IO.h"

int main(void);

void testbench_conv2D_multiInputChannel();
void testbench_conv2D();
void testbench_conv2D_multiOutputChannel();
void testbench_conv2D_multiIOChannel();
void testbench_conv2D_depthwise();
void testbench_conv2D_depthwiseSeparable();
void testbench_conv2D_depthwiseSeparable_multiOutputChannel();

void testbench_dotProduct();
void testbench_vectorAdd();
void testbench_vectorReLu();
void testbench_vectorReLu6();
void testbench_vectorMult();


#endif /* NN_ALGORITHMS_TESTBENCH_H_ */
