#ifndef NN_OPERATIONS_H_
#define NN_OPERATIONS_H_

#include <stdlib.h>
#include <stdint.h>
#include "vector_operations.h"

void conv2D_multiInputChannel(
	const uint32_t height,const uint32_t width,const uint32_t channel,
	const uint32_t kernel_height,const uint32_t kernel_width,
	const uint32_t stride,
	const uint32_t outputDataHeight,const uint32_t outputDataWidth,
	int8_t data[channel][height][width],
	int8_t kernel[channel][kernel_height][kernel_width],
	int8_t output[outputDataHeight][outputDataWidth]);
	
void conv2D_pointwise(//this is a special case, and this is why it has its own function
	const uint32_t height,const uint32_t width,const uint32_t channel,
	int8_t data[channel][height][width],
	int8_t kernel[channel],
	int8_t output[height][width]);

void conv2D_multiIOChannel(
	const uint32_t batch, const uint32_t height,const uint32_t width,const uint32_t channel,
	const uint32_t kernel_height,const uint32_t kernel_width,
	const uint32_t stride,
	const uint32_t outputDataHeight,const uint32_t outputDataWidth,
	int8_t data[channel][height][width],
	int8_t kernel[batch][channel][kernel_height][kernel_width],
	int8_t output[batch][outputDataHeight][outputDataWidth]);

void conv2D(
	const uint32_t height,const uint32_t width,
	const uint32_t kernel_height,const uint32_t kernel_width,
	const uint32_t stride,
	const uint32_t outputDataHeight,const uint32_t outputDataWidth,
	int8_t data[height][width],
	int8_t kernel[kernel_height][kernel_width],
	int8_t output[outputDataHeight][outputDataWidth]);

void conv2D_multiOutputChannel(
	const uint32_t batch, const uint32_t height,const uint32_t width,
	const uint32_t kernel_width,const uint32_t kernel_height,
	const uint32_t stride,
	const uint32_t outputDataHeight,const uint32_t outputDataWidth,
	int8_t data[height][width],
	int8_t kernel[batch][kernel_height][kernel_width],
	int8_t output[batch][outputDataHeight][outputDataWidth]);

void conv2D_depthwise(
	const uint32_t height,const uint32_t width,const uint32_t channel,
	const uint32_t kernel_height,const uint32_t kernel_width,
	const uint32_t stride,
	const uint32_t outputDataHeight,const uint32_t outputDataWidth,
	int8_t data[channel][height][width],
	int8_t kernel[channel][kernel_height][kernel_width],
	int8_t output[channel][outputDataHeight][outputDataWidth]);

void conv2D_depthwiseSeparable(
	const uint32_t height,const uint32_t width,const uint32_t channel,
	const uint32_t kernel_height,const uint32_t kernel_width,
	const uint32_t stride,
	const uint32_t outputDataHeight,const uint32_t outputDataWidth,
	int8_t data[channel][height][width],
	int8_t kernelDepthwise[channel][kernel_height][kernel_width],
	int8_t kernelPointwise[channel],
	int8_t output[outputDataHeight][outputDataWidth]);

void conv2D_depthwiseSeparable_multiOutputChannel(
	const uint32_t batch, const uint32_t height,const uint32_t width,const uint32_t channel,
	const uint32_t kernel_height,const uint32_t kernel_width,
	const uint32_t stride,
	const uint32_t outputDataHeight,const uint32_t outputDataWidth,
	int8_t data[channel][height][width],
	int8_t kernelDepthwise[channel][kernel_height][kernel_width],
	int8_t kernelPointwise[batch][channel],
	int8_t output[batch][outputDataHeight][outputDataWidth]);

void matrix3DtoVec(
	const uint32_t height,const uint32_t width,const uint32_t channel,
	int8_t matrix[channel][height][width], int8_t *vec);

void matrix2DtoVec(
	const uint32_t height,const uint32_t width,
	int8_t matrix[height][width], int8_t *vec);

void getOutputDimensionsConv2D(
	const uint32_t kernel_height,const uint32_t kernel_width,
	const uint32_t height,const uint32_t width,
	const uint32_t stride,
	uint32_t *outputDataHeight,uint32_t *outputDataWidth);

void getPaddedInputDimensionsConv2D(
	const uint32_t kernel_height,const uint32_t kernel_width,
	const uint32_t stride,
	const uint32_t outputDataHeight,const uint32_t outputDataWidth,
	uint32_t *height, uint32_t *width);

void padMatrix(
	const uint32_t height,const uint32_t width,const uint32_t channel,
	const uint32_t paddedHeight, const uint32_t paddedWidth,
	int8_t data[channel][height][width],
	int8_t paddedData[channel][paddedHeight][paddedWidth]);


#endif /* NN_OPERATIONS_H_ */
