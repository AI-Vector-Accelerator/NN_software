#ifndef NN_OPERATIONS_H_
#define NN_OPERATIONS_H_

#include <stdlib.h>
#include <stdint.h>
#include "vector_operations.h"

void conv2D_multiInputChannel(const unsigned int height,const unsigned int width,const unsigned int channel,const unsigned int kernal_height,const unsigned int kernal_width,const unsigned int stride,const unsigned int outputDataHeight,const unsigned int outputDataWidth,int8_t data[channel][height][width], int8_t kernal[channel][kernal_height][kernal_width], int8_t output[outputDataHeight][outputDataWidth]);
void conv2D_multiIOChannel(const unsigned int batch, const unsigned int height,const unsigned int width,const unsigned int channel,const unsigned int kernal_height,const unsigned int kernal_width,const unsigned int stride,const unsigned int outputDataHeight,const unsigned int outputDataWidth, int8_t data[channel][height][width], int8_t kernal[batch][channel][kernal_height][kernal_width], int8_t output[batch][outputDataHeight][outputDataWidth]);
void conv2D(const unsigned int height,const unsigned int width,const unsigned int kernal_height,const unsigned int kernal_width,const unsigned int stride,const unsigned int outputDataHeight,const unsigned int outputDataWidth,int8_t data[height][width], int8_t kernal[kernal_height][kernal_width], int8_t output[outputDataHeight][outputDataWidth]);
void conv2D_multiOutputChannel(const unsigned int batch, const unsigned int height,const unsigned int width,const unsigned int kernal_width,const unsigned int kernal_height,const unsigned int stride,const unsigned int outputDataHeight,const unsigned int outputDataWidth, int8_t data[height][width], int8_t kernal[batch][kernal_height][kernal_width], int8_t output[batch][outputDataHeight][outputDataWidth]);
void conv2D_depthwise(const unsigned int height,const unsigned int width,const unsigned int channel,const unsigned int kernal_height,const unsigned int kernal_width,const unsigned int stride,const unsigned int outputDataHeight,const unsigned int outputDataWidth,int8_t data[channel][height][width], int8_t kernal[channel][kernal_height][kernal_width], int8_t output[channel][outputDataHeight][outputDataWidth]);
void conv2D_depthwiseSeparable( const unsigned int height,const unsigned int width,const unsigned int channel,const unsigned int kernal_height,const unsigned int kernal_width,const unsigned int stride,const unsigned int outputDataHeight,const unsigned int outputDataWidth,int8_t data[channel][height][width], int8_t kernalDepthwise[channel][kernal_height][kernal_width],int8_t kernalSeparable[channel], int8_t output[outputDataHeight][outputDataWidth]);
void matrix3DtoVec(const unsigned int height,const unsigned int width,const unsigned int channel, int8_t matrix[channel][height][width], int8_t *vec);
void matrix2DtoVec(const unsigned int height,const unsigned int width, int8_t matrix[height][width], int8_t *vec);
void getOutputDimensionsConv2D(unsigned int kernal_height,unsigned int kernal_width,unsigned int height,unsigned int width, unsigned int stride,unsigned int *outputDataHeight,unsigned int *outputDataWidth);



#endif /* NN_OPERATIONS_H_ */
