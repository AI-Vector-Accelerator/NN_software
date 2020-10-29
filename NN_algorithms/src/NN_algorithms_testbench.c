#include "NN_algorithms_testbench.h"


//matrix width goes across ->, height goes down
int main(void) {

	testbench_vectorAdd();
	testbench_vectorMult();
	testbench_dotProduct();
	testbench_vectorReLu();
	testbench_vectorReLu6();

	testbench_conv2D_multiInputChannel();
	testbench_conv2D();
	testbench_conv2D_multiIOChannel();
	testbench_conv2D_multiOutputChannel();
	testbench_conv2D_depthwise();
	testbench_conv2D_depthwiseSeparable();
	testbench_conv2D_depthwiseSeparable_multiOutputChannel();

	return EXIT_SUCCESS;
}




void testbench_conv2D_multiInputChannel(){
	const uint32_t height=10,width=10,channel=3, kernel_height=3, kernel_width=3, stride=1;
	uint32_t outputDataHeight, outputDataWidth;
	getOutputDimensionsConv2D(kernel_height,kernel_width, height, width, stride, &outputDataHeight, &outputDataWidth);
	int8_t data[channel][height][width];
	int8_t kernel[channel][kernel_height][kernel_width];
	int8_t output[outputDataHeight][outputDataWidth];

	printf("\ntestbench_conv2D_multiInputChannel  \n");
	randFillMatrix3D(height,width,channel,data);
	fillMatrix3D(kernel_height,kernel_width,channel,kernel,0);
	//kernel[0][1][1]=1;
	//kernel[1][1][1]=1;
	kernel[2][1][1]=1;

	printf("\nData:\n");
	printMatrix3D(height,width,channel,data);
	printf("\n\nkernel:\n");
	printMatrix3D(kernel_height,kernel_width,channel,kernel);

	conv2D_multiInputChannel(height,width,channel,kernel_height,kernel_width,stride,outputDataHeight, outputDataWidth,data,kernel,output);

	printf("\n\nOutput:\n");
	printMatrix2D(outputDataHeight,outputDataWidth,output);
	printf("\n");
}

void testbench_conv2D_multiIOChannel(){
	const uint32_t batch=3, height=6,width=6,channel=3, kernel_height=4, kernel_width=4, stride=1;
	uint32_t outputDataHeight, outputDataWidth;
	getOutputDimensionsConv2D(kernel_height,kernel_width, height, width, stride, &outputDataHeight, &outputDataWidth);
	int8_t data[channel][height][width];
	int8_t kernel[batch][channel][kernel_height][kernel_width];
	int8_t output[batch][outputDataHeight][outputDataWidth];

	printf("\ntestbench_conv2D_multiIOChannel  \n");
	randFillMatrix3D(height,width,channel,data);
	randFillMatrix4D(batch,kernel_height,kernel_width,channel,kernel);
	//fillMatrix4D(batch,kernel_height,kernel_width,channel,kernel,1);

	printf("\nData:\n");
	printMatrix3D(height,width,channel,data);
	printf("\n\nkernel:\n");
	printMatrix4D(batch,kernel_height,kernel_width,channel,kernel);

	conv2D_multiIOChannel(batch,height,width,channel,kernel_height,kernel_width,stride,outputDataHeight, outputDataWidth,data,kernel,output);

	printf("\n\nOutput:   \n");
	printMatrix3D(outputDataHeight,outputDataWidth,batch,output);
	printf("\n");
}

void testbench_conv2D(){
	const uint32_t height=7,width=7, kernel_height=4, kernel_width=4, stride=2;
	uint32_t outputDataHeight, outputDataWidth;
	getOutputDimensionsConv2D(kernel_height,kernel_width, height, width, stride, &outputDataHeight, &outputDataWidth);
	int8_t data[height][width];
	int8_t kernel[kernel_height][kernel_width];
	int8_t output[outputDataHeight][outputDataWidth];

	printf("\ntestbench_conv2D  \n");
	randFillMatrix2D(height,width,data);
	randFillMatrix2D(kernel_height,kernel_width,kernel);

	printf("\nData:\n");
	printMatrix2D(height,width,data);
	printf("\n\nkernel:\n");
	printMatrix2D(kernel_height,kernel_width,kernel);

	conv2D(height,width,kernel_height,kernel_width,stride,outputDataHeight, outputDataWidth,data,kernel,output);

	printf("\n\nOutput:\n");
	printMatrix2D(outputDataHeight,outputDataWidth,output);
	printf("\n");
}

void testbench_conv2D_multiOutputChannel(){
	const uint32_t batch=4, height=5,width=5, kernel_height=3, kernel_width=3, stride=1;
	uint32_t outputDataHeight, outputDataWidth;
	getOutputDimensionsConv2D(kernel_height,kernel_width, height, width, stride, &outputDataHeight, &outputDataWidth);
	int8_t data[height][width];
	int8_t kernel[batch][kernel_height][kernel_width];
	int8_t output[batch][outputDataHeight][outputDataWidth];

	printf("\ntestbench_conv2D_multiOutputChannel  \n");
	randFillMatrix2D(height,width,data);
	randFillMatrix3D(kernel_height,kernel_width,batch,kernel);
	fillMatrix2D(kernel_height,kernel_width,kernel[0],0);
	fillMatrix2D(kernel_height,kernel_width,kernel[1],1);
	fillMatrix2D(kernel_height,kernel_width,kernel[2],2);
	fillMatrix2D(kernel_height,kernel_width,kernel[3],3);

	printf("\nData:\n");
	printMatrix2D(height,width,data);
	printf("\n\nkernel:\n");
	printMatrix3D(kernel_height,kernel_width,batch,kernel);

	conv2D_multiOutputChannel(batch,height,width,kernel_height,kernel_width,stride,outputDataHeight, outputDataWidth,data,kernel,output);

	printf("\n\nOutput:\n");
	printMatrix3D(outputDataHeight,outputDataWidth,batch,output);
	printf("\n");
}


void testbench_conv2D_depthwise(){
	const uint32_t height=9,width=9,channel=3, kernel_height=3, kernel_width=3, stride=1;
	uint32_t outputDataHeight, outputDataWidth;
	getOutputDimensionsConv2D(kernel_height,kernel_width, height, width, stride, &outputDataHeight, &outputDataWidth);
	int8_t data[channel][height][width];
	int8_t kernel[channel][kernel_height][kernel_width];
	int8_t output[channel][outputDataHeight][outputDataWidth];

	printf("\ntestbench_conv2D_depthwise  \n");
	randFillMatrix3D(height,width,channel,data);
	fillMatrix3D(kernel_height,kernel_width,channel,kernel,0);
	kernel[0][1][1]=1;
	kernel[1][1][1]=1;
	kernel[2][1][1]=1;

	printf("\nData:\n");
	printMatrix3D(height,width,channel,data);
	printf("\n\nkernel:\n");
	printMatrix3D(kernel_height,kernel_width,channel,kernel);

	conv2D_depthwise(height,width,channel,kernel_height,kernel_width,stride,outputDataHeight, outputDataWidth,data,kernel,output);

	printf("\n\nOutput:\n");
	printMatrix3D(outputDataHeight,outputDataWidth,channel,output);
	printf("\n");
}

void testbench_conv2D_depthwiseSeparable(){
	const uint32_t height=9,width=9,channel=3, kernel_height=3, kernel_width=3, stride=1;
	uint32_t outputDataHeight, outputDataWidth;
	getOutputDimensionsConv2D(kernel_height,kernel_width, height, width, stride, &outputDataHeight, &outputDataWidth);
	int8_t data[channel][height][width];
	int8_t kernelDepthWise[channel][kernel_height][kernel_width];
	int8_t kernelPointwise[channel];
	int8_t output[outputDataHeight][outputDataWidth];

	printf("\ntestbench_conv2D_depthwiseSeparable  \n");
	randFillMatrix3D(height,width,channel,data);
	fillMatrix3D(kernel_height,kernel_width,channel,kernelDepthWise,0);
	kernelDepthWise[0][1][1]=1;
	kernelDepthWise[1][1][1]=1;
	kernelDepthWise[2][1][1]=1;
	randFillVector(channel,kernelPointwise);
	kernelPointwise[0]=0;
	kernelPointwise[1]=1;
	kernelPointwise[2]=0;

	printf("\nData:\n");
	printMatrix3D(height,width,channel,data);
	printf("\n\nkernelDepthWise:\n");
	printMatrix3D(kernel_height,kernel_width,channel,kernelDepthWise);
	printf("\nkernelPointwise:\n");
	printVector(channel,kernelPointwise);

	conv2D_depthwiseSeparable(height,width,channel,kernel_height,kernel_width,stride,outputDataHeight, outputDataWidth,data,kernelDepthWise,kernelPointwise,output);

	printf("\n\nOutput:\n");
	printMatrix2D(outputDataHeight,outputDataWidth,output);
	printf("\n");
}

void testbench_conv2D_depthwiseSeparable_multiOutputChannel(){
	const uint32_t batch=10, height=6,width=6,channel=3, kernel_height=3, kernel_width=3, stride=1;
	uint32_t outputDataHeight, outputDataWidth;
	getOutputDimensionsConv2D(kernel_height,kernel_width, height, width, stride, &outputDataHeight, &outputDataWidth);
	int8_t data[channel][height][width];
	int8_t kernelDepthWise[channel][kernel_height][kernel_width];
	int8_t kernelPointwise[batch][channel];
	int8_t output[batch][outputDataHeight][outputDataWidth];

	printf("\ntestbench_conv2D_depthwiseSeparable_multiOutputChannel  \n");
	randFillMatrix3D(height,width,channel,data);
	randFillMatrix3D(kernel_height,kernel_width,channel,kernelDepthWise);
	for(uint32_t b=0;b<batch;b++){fillVector(channel,kernelPointwise[b],b);}


	printf("\nData:\n");
	printMatrix3D(height,width,channel,data);
	printf("\n\nkernelDepthWise:\n");
	printMatrix3D(kernel_height,kernel_width,channel,kernelDepthWise);
	printf("\nkernelPointwise:\n");
	printMatrix2D(batch,channel,kernelPointwise);

	conv2D_depthwiseSeparable_multiOutputChannel(batch,height,width,channel,kernel_height,kernel_width,stride,outputDataHeight, outputDataWidth,data,kernelDepthWise,kernelPointwise,output);

	printf("\n\nOutput:\n");
	printMatrix3D(outputDataHeight,outputDataWidth,batch,output);
	printf("\n");
}

void testbench_dotProduct(){
	const uint32_t N=5;
	int8_t A[N],B[N],output;
	printf("\ntestbench_dotProduct\n\n");
	randFillVector(N,A);
	randFillVector(N,B);
	printf("Vector A:");
	printVector(N,A);
	printf("Vector B:");
	printVector(N,B);

	vect_dotProduct(N,A,B, &output);

	printf("\nOutput: %d\n\n\n",output);
}

void testbench_vectorAdd(){
	const uint32_t N=10;
	int8_t A[N],B[N],C[N];
	printf("\ntestbench_vecAdd\n\n");
	randFillVector(N,A);
	randFillVector(N,B);
	printf("Vector A:");
	printVector(N,A);
	printf("Vector B:");
	printVector(N,B);

	vect_add(N,A,B, C);

	printf("\nOutput:\n");
	printVector(N,C);
	printf("\n\n");
}

void testbench_vectorMult(){
	const uint32_t N=10;
	int8_t A[N],B[N],C[N];
	printf("\ntestbench_vecMult\n\n");
	fillVector(N,A,2);
	randFillVector(N,B);
	printf("Vector A:");
	printVector(N,A);
	printf("Vector B:");
	printVector(N,B);

	vect_mult(N,A,B, C);

	printf("\nOutput:\n");
	printVector(N,C);
	printf("\n\n");
}

void testbench_vectorReLu(){
	const uint32_t N=20;
	int8_t A[N],C[N];
	printf("\ntestbench_ReLu\n\n");
	randFillVector(N,A);
	printf("Vector A:");
	printVector(N,A);

	vect_ReLu(N,A, C);

	printf("\nOutput:\n");
	printVector(N,C);
	printf("\n\n");
}

void testbench_vectorReLu6(){
	const uint32_t N=20;
	int8_t A[N],C[N];
	printf("\ntestbench_ReLu6\n\n");
	randFillVector(N,A);
	printf("Vector A:");
	printVector(N,A);

	vect_ReLu6(N,A, C);

	printf("\nOutput:\n");
	printVector(N,C);
	printf("\n\n");
}

