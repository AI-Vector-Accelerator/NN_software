#include "convolution_operations.h"

void conv2D_multiInputChannel(
	const uint32_t height,const uint32_t width,const uint32_t channel,
	const uint32_t kernel_height,const uint32_t kernel_width,
	const uint32_t stride,
	const uint32_t outputDataHeight,const uint32_t outputDataWidth,
	int8_t data[channel][height][width],
	int8_t kernel[channel][kernel_height][kernel_width],
	int8_t output[outputDataHeight][outputDataWidth]){

	int32_t dotProduct=0,tempDotProduct;
	int32_t heightOffset=(int)((height-outputDataHeight)/stride+1-kernel_height)/2;
	int32_t widthOffset=(int)((width-outputDataWidth)/stride+1-kernel_width)/2;
	int32_t tempHeightOffset, tempWidthOffset,dataHeightPosition=0,dataWidthPosition=0;
	uint32_t kernelWidthPosition=0,vecN=kernel_width;
	
	//uint8_t padding=0;

	//if output matrix is too large, padding is required, therefore generate padded input matrix and pass this to conv function and return
	//(might)seems to be faster to make a padded matrix and run through no padding conv function than to just run matrix through padded conv function due to over head for vector extensions
	// and if padded matrix is used can use padding function which is vector accelerated
	if(outputDataHeight>(height-kernel_height )/stride+1 || outputDataWidth>(width-kernel_width )/stride+1){
		//padding=1;
		uint32_t paddedHeight, paddedWidth;
		getPaddedInputDimensionsConv2D(kernel_height,kernel_width,stride,outputDataHeight,outputDataWidth,&paddedHeight, &paddedWidth);
		int8_t paddedData[channel][paddedHeight][paddedWidth];
		padMatrix(height,width,channel,paddedHeight,paddedWidth,data,paddedData);
		conv2D_multiInputChannel(paddedHeight, paddedWidth, channel, kernel_height, kernel_width, stride,outputDataHeight, outputDataWidth, paddedData, kernel, output);
		return;
	}
	
	//if(padding==0){
		for(uint32_t heightCounter=0;heightCounter<outputDataHeight;heightCounter++){
			for(uint32_t widthCounter=0;widthCounter<outputDataWidth;widthCounter++){
				dotProduct=0;
				tempHeightOffset=heightCounter*stride+heightOffset;
				tempWidthOffset=widthCounter*stride+widthOffset;
				for(uint32_t channelCounter=0;channelCounter<channel;channelCounter++){
					for(uint32_t heightOffsetCounter=0;heightOffsetCounter<kernel_height;heightOffsetCounter++){
						dataHeightPosition=tempHeightOffset+heightOffsetCounter;
						dataWidthPosition=tempWidthOffset;
						
						vect_dotProduct(vecN,&kernel[channelCounter][heightOffsetCounter][kernelWidthPosition],&data[channelCounter][(uint32_t)dataHeightPosition][(uint32_t)dataWidthPosition],&tempDotProduct);
						dotProduct+=tempDotProduct;
					}
				}		
				output[heightCounter][widthCounter] = saturate_32bit_to_8bit( dotProduct );	
			}
		}
	/*}else{
		for(uint32_t heightCounter=0;heightCounter<outputDataHeight;heightCounter++){
			for(uint32_t widthCounter=0;widthCounter<outputDataWidth;widthCounter++){
				dotProduct=0;
				tempHeightOffset=heightCounter*stride+heightOffset;
				tempWidthOffset=widthCounter*stride+widthOffset;
				for(uint32_t channelCounter=0;channelCounter<channel;channelCounter++){
					for(uint32_t heightOffsetCounter=0;heightOffsetCounter<kernel_height;heightOffsetCounter++){
						dataHeightPosition=tempHeightOffset+heightOffsetCounter;
						dataWidthPosition=tempWidthOffset;
						
						if(dataHeightPosition<0 || dataHeightPosition>=height){continue;} 
						if(dataWidthPosition<0){
							vecN=kernel_width+dataWidthPosition;
							kernelWidthPosition=(uint32_t)-dataWidthPosition;
							dataWidthPosition=0;
						}else if((dataWidthPosition+kernel_width-1)>width){
							vecN=kernel_width-(dataWidthPosition-width);
							kernelWidthPosition=0;
						}else{
							vecN=kernel_width;
							kernelWidthPosition=0;
						}
						vect_dotProduct(vecN,&kernel[channelCounter][heightOffsetCounter][kernelWidthPosition],&data[channelCounter][(uint32_t)dataHeightPosition][(uint32_t)dataWidthPosition],&tempDotProduct);
						dotProduct+=tempDotProduct;
					}
				}		
				output[heightCounter][widthCounter] = saturate_32bit_to_8bit( dotProduct );	
			}
		}
	}	*/		
}

void conv2D_pointwise( //this is a special case, and this is why it has its own function
	const uint32_t height,const uint32_t width,const uint32_t channel,
	int8_t data[channel][height][width],
	int8_t kernel[channel],
	int8_t output[height][width]){
		
	int32_t dotProduct=0,stride=height*width;
	
	for(uint32_t heightCounter=0;heightCounter<height;heightCounter++){
		for(uint32_t widthCounter=0;widthCounter<width;widthCounter++){	
			vect_dotProduct_stride_vec2(channel,kernel,&data[0][heightCounter][widthCounter],&dotProduct,stride);
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
	conv2D_pointwise(outputDataHeight,outputDataWidth,channel,temp,kernelPointwise,output);
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

void getPaddedInputDimensionsConv2D(
	const uint32_t kernel_height,const uint32_t kernel_width,
	const uint32_t stride,
	const uint32_t outputDataHeight,const uint32_t outputDataWidth,
	uint32_t *height, uint32_t *width){

	*height=(outputDataHeight-1) * stride+kernel_height ;
	*width=(outputDataWidth-1) * stride+kernel_width ;
}

void padMatrix(
	const uint32_t height,const uint32_t width,const uint32_t channel,
	const uint32_t paddedHeight, const uint32_t paddedWidth,
	int8_t data[channel][height][width],
	int8_t paddedData[channel][paddedHeight][paddedWidth]){
		
	uint32_t rowOffset=(paddedHeight-height)/2;
	uint32_t columnOffset=(paddedWidth-width)/2;
	
	/*for(uint32_t h=0;h<paddedHeight;h++){
		if(h<rowOffset || h>=paddedHeight-rowOffset){
			for(uint32_t w=0;w<paddedWidth;w++){
				for(uint32_t c=0;c<channel;c++){paddedData[c][h][w]=0;}
			}
		}else{
			for(uint32_t w=0;w<paddedWidth;w++){
				if(w<columnOffset || w>=paddedWidth-columnOffset){
					for(uint32_t c=0;c<channel;c++){paddedData[c][h][w]=0;}
				}else{
					for(uint32_t c=0;c<channel;c++){paddedData[c][h][w]=data[c][h-rowOffset][w-columnOffset];}
				}
			}
		}	
	}	*/

	for(uint32_t c=0;c<channel;c++){
		for(uint32_t h=0;h<paddedHeight;h++){
			if(h<rowOffset || h>=paddedHeight-rowOffset){
				vect_copy_reg(paddedHeight,0,paddedData[c][h]);
			}else{
				vect_copy_reg(rowOffset,0,&paddedData[c][h][0]);
				vect_copy(width,&data[c][h-rowOffset][0],&paddedData[c][h][columnOffset]);
				vect_copy_reg(rowOffset,0,&paddedData[c][h][paddedWidth-columnOffset]);
			}
		}
	}
	
}
