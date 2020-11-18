#include "convolution_operations.h"

void conv2D_multiInputChannel(
	const uint32_t height,const uint32_t width,const uint32_t channel,
	const uint32_t kernel_height,const uint32_t kernel_width,
	const uint32_t stride,
	const uint32_t outputDataHeight,const uint32_t outputDataWidth,
	int8_t data[channel][height][width],
	int8_t kernel[channel][kernel_height][kernel_width],
	int8_t output[outputDataHeight][outputDataWidth]){

	int32_t dotProduct;
	uint32_t vecCounter;
	int32_t heightOffset=(int)((height-outputDataHeight)/stride+1-kernel_height)/2;
	int32_t widthOffset=(int)((width-outputDataWidth)/stride+1-kernel_width)/2;
	int32_t tempHeightOffset, tempWidthOffset;
	uint32_t dataHeightPosition,dataWeightPosition;
	int8_t kernelVec[kernel_width*kernel_height*channel];
	int8_t tempVec[kernel_width*kernel_height*channel];
	matrix3DtoVec(kernel_height,kernel_width,channel,kernel,kernelVec);

	for(uint32_t heightCounter=0;heightCounter<outputDataHeight;heightCounter++){
		for(uint32_t widthCounter=0;widthCounter<outputDataWidth;widthCounter++){
			vecCounter=0;
			tempHeightOffset=heightCounter*stride+heightOffset;
			tempWidthOffset=widthCounter*stride+widthOffset;
			for(uint32_t channelCounter=0;channelCounter<channel;channelCounter++){
				for(int heightOffsetCounter=0;heightOffsetCounter<(int)(kernel_height);heightOffsetCounter++){
					for(int widthOffsetCounter=0;widthOffsetCounter<(int)(kernel_width);widthOffsetCounter++){
						dataHeightPosition=tempHeightOffset+heightOffsetCounter;
						dataWeightPosition=tempWidthOffset+widthOffsetCounter;
				
						if( (dataHeightPosition<0 || dataHeightPosition>=height) || (dataWeightPosition<0 || dataWeightPosition>=width) ){
							tempVec[vecCounter]=0;
						}else{
							tempVec[vecCounter]=data[channelCounter][dataHeightPosition][dataWeightPosition];
						}
						vecCounter++;
					}
				}
			}
			vect_dotProduct(vecCounter,kernelVec,tempVec,&dotProduct);
			output[heightCounter][widthCounter] = saturate_32bit_to_8bit( dotProduct );
		}
	}
}

void conv2D_multiIOChannel(
	const uint32_t batch, const uint32_t height,const uint32_t width,const uint32_t channel,
	const uint32_t kernel_height,const uint32_t kernel_width,
	const uint32_t stride,
	const uint32_t outputDataHeight,const uint32_t outputDataWidth,
	int8_t data[channel][height][width],
	int8_t kernel[batch][channel][kernel_height][kernel_width],
	int8_t output[batch][outputDataHeight][outputDataWidth]){

	for(uint32_t batchCounter=0;batchCounter<batch;batchCounter++){
		conv2D_multiInputChannel(height, width, channel, kernel_height, kernel_width, stride,outputDataHeight, outputDataWidth, data, kernel[batchCounter], output[batchCounter]);
	}
}

void conv2D(
	const uint32_t height,const uint32_t width,
	const uint32_t kernel_height,const uint32_t kernel_width,
	const uint32_t stride,
	const uint32_t outputDataHeight,const uint32_t outputDataWidth,
	int8_t data[height][width],
	int8_t kernel[kernel_height][kernel_width],
	int8_t output[outputDataHeight][outputDataWidth]){

	conv2D_multiInputChannel(height, width, 1, kernel_height, kernel_width, stride,outputDataHeight, outputDataWidth, (int8_t (*)[height][width])data, (int8_t (*)[kernel_height][kernel_width])kernel, output);
}

void conv2D_multiOutputChannel(
	const uint32_t batch, const uint32_t height,const uint32_t width,
	const uint32_t kernel_width,const uint32_t kernel_height,
	const uint32_t stride,
	const uint32_t outputDataHeight,const uint32_t outputDataWidth,
	int8_t data[height][width],
	int8_t kernel[batch][kernel_height][kernel_width],
	int8_t output[batch][outputDataHeight][outputDataWidth]){

	for(uint32_t batchCounter=0;batchCounter<batch;batchCounter++){
		conv2D(height, width, kernel_height, kernel_width, stride,outputDataHeight, outputDataWidth, data, kernel[batchCounter], output[batchCounter]);
	}
}

void conv2D_depthwise(
	const uint32_t height,const uint32_t width,const uint32_t channel,
	const uint32_t kernel_height,const uint32_t kernel_width,
	const uint32_t stride,
	const uint32_t outputDataHeight,const uint32_t outputDataWidth,
	int8_t data[channel][height][width],
	int8_t kernel[channel][kernel_height][kernel_width],
	int8_t output[channel][outputDataHeight][outputDataWidth]){

	for(uint32_t c=0;c<channel;c++){
		conv2D(height,width,kernel_height,kernel_width,stride,outputDataHeight,outputDataWidth,data[c],kernel[c],output[c]);
	}
}

void conv2D_depthwiseSeparable(
	const uint32_t height,const uint32_t width,const uint32_t channel,
	const uint32_t kernel_height,const uint32_t kernel_width,
	const uint32_t stride,
	const uint32_t outputDataHeight,const uint32_t outputDataWidth,
	int8_t data[channel][height][width],
	int8_t kernelDepthwise[channel][kernel_height][kernel_width],
	int8_t kernelPointwise[channel],
	int8_t output[outputDataHeight][outputDataWidth]){

	int8_t temp[channel][outputDataHeight][outputDataWidth];

	conv2D_depthwise(height,width,channel,kernel_height,kernel_width,stride,outputDataHeight,outputDataWidth,data,kernelDepthwise,temp);
	conv2D_multiInputChannel(outputDataHeight,outputDataWidth,channel,1,1,stride,outputDataHeight,outputDataWidth,temp,(int8_t (*)[1][1])kernelPointwise,output);
}

void conv2D_depthwiseSeparable_multiOutputChannel(
	const uint32_t batch, const uint32_t height,const uint32_t width,const uint32_t channel,
	const uint32_t kernel_height,const uint32_t kernel_width,
	const uint32_t stride,
	const uint32_t outputDataHeight,const uint32_t outputDataWidth,
	int8_t data[channel][height][width],
	int8_t kernelDepthwise[channel][kernel_height][kernel_width],
	int8_t kernelPointwise[batch][channel],
	int8_t output[batch][outputDataHeight][outputDataWidth]){

	for(uint32_t batchCounter=0;batchCounter<batch;batchCounter++){
		conv2D_depthwiseSeparable(height, width, channel, kernel_height, kernel_width, stride,outputDataHeight, outputDataWidth, data, kernelDepthwise, kernelPointwise[batchCounter], output[batchCounter]);
	}
}

void matrix3DtoVec(
	const uint32_t height,const uint32_t width,const uint32_t channel,
	int8_t matrix[channel][height][width], int8_t *vec){

	uint32_t vecCounter=0;
	for(uint32_t channelCounter=0;channelCounter<channel;channelCounter++){
		for(uint32_t heightCounter=0;heightCounter<height;heightCounter++){
			for(uint32_t widthCounter=0;widthCounter<width;widthCounter++){
				vec[vecCounter]=matrix[channelCounter][heightCounter][widthCounter];
				vecCounter++;
			}
		}
	}
}

void matrix2DtoVec(
	const uint32_t height,const uint32_t width,
	int8_t matrix[height][width], int8_t *vec){

	uint32_t vecCounter=0;
	for(uint32_t heightCounter=0;heightCounter<height;heightCounter++){
		for(uint32_t widthCounter=0;widthCounter<width;widthCounter++){
			vec[vecCounter]=matrix[heightCounter][widthCounter];
			vecCounter++;
		}
	}
}

void getOutputDimensionsConv2D(
	const uint32_t kernel_height,const uint32_t kernel_width,
	const uint32_t height,const uint32_t width,
	const uint32_t stride,
	uint32_t *outputDataHeight,uint32_t *outputDataWidth){

	*outputDataHeight=(height-kernel_height )/stride+1;
	*outputDataWidth=(width-kernel_width )/stride+1;
}
