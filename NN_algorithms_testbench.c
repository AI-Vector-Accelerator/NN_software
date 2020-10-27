#include "source/NN_algorithms_testbench.h"


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

/*	printf("\n");
	char temp;
	scanf("%c",temp);
	printf("Exiting\n");*/

	return EXIT_SUCCESS;
}




void testbench_conv2D_multiInputChannel(){
	const unsigned int height=10,width=10,channel=3, kernal_height=3, kernal_width=3, stride=1;
	unsigned int outputDataHeight, outputDataWidth;
	getOutputDimensionsConv2D(kernal_height,kernal_width, height, width, stride, &outputDataHeight, &outputDataWidth);
	int8_t data[channel][height][width];
	int8_t kernal[channel][kernal_height][kernal_width];
	int8_t output[outputDataHeight][outputDataWidth];

	printf("\ntestbench_conv2D_multiInputChannel %d \n",outputDataHeight);
	randFillMatrix3D(height,width,channel,data);
	fillMatrix3D(kernal_height,kernal_width,channel,kernal,0);
	//kernal[0][1][1]=1;
	//kernal[1][1][1]=1;
	kernal[2][1][1]=1;

	printf("\nData:\n");
	printMatrix3D(height,width,channel,data);
	printf("\n\nKernal:\n");
	printMatrix3D(kernal_height,kernal_width,channel,kernal);

	conv2D_multiInputChannel(height,width,channel,kernal_height,kernal_width,stride,outputDataHeight, outputDataWidth,data,kernal,output);

	printf("\n\nOutput:\n");
	printMatrix2D(outputDataHeight,outputDataWidth,output);
	printf("\n");
}

void testbench_conv2D_multiIOChannel(){
	const unsigned int batch=3, height=6,width=6,channel=3, kernal_height=4, kernal_width=4, stride=1;
	unsigned int outputDataHeight, outputDataWidth;
	getOutputDimensionsConv2D(kernal_height,kernal_width, height, width, stride, &outputDataHeight, &outputDataWidth);
	int8_t data[channel][height][width];
	int8_t kernal[batch][channel][kernal_height][kernal_width];
	int8_t output[batch][outputDataHeight][outputDataWidth];

	printf("\ntestbench_conv2D_multiIOChannel  \n");
	randFillMatrix3D(height,width,channel,data);
	randFillMatrix4D(batch,kernal_height,kernal_width,channel,kernal);
	//fillMatrix4D(batch,kernal_height,kernal_width,channel,kernal,1);

	printf("\nData:\n");
	printMatrix3D(height,width,channel,data);
	printf("\n\nKernal:\n");
	printMatrix4D(batch,kernal_height,kernal_width,channel,kernal);

	conv2D_multiIOChannel(batch,height,width,channel,kernal_height,kernal_width,stride,outputDataHeight, outputDataWidth,data,kernal,output);

	printf("\n\nOutput:   \n");
	printMatrix3D(outputDataHeight,outputDataWidth,batch,output);
	printf("\n");
}

void testbench_conv2D(){
	const unsigned int height=7,width=7, kernal_height=4, kernal_width=4, stride=2;
	unsigned int outputDataHeight, outputDataWidth;
	getOutputDimensionsConv2D(kernal_height,kernal_width, height, width, stride, &outputDataHeight, &outputDataWidth);
	int8_t data[height][width];
	int8_t kernal[kernal_height][kernal_width];
	int8_t output[outputDataHeight][outputDataWidth];

	printf("\ntestbench_conv2D  \n");
	randFillMatrix2D(height,width,data);
	randFillMatrix2D(kernal_height,kernal_width,kernal);

	printf("\nData:\n");
	printMatrix2D(height,width,data);
	printf("\n\nKernal:\n");
	printMatrix2D(kernal_height,kernal_width,kernal);

	conv2D(height,width,kernal_height,kernal_width,stride,outputDataHeight, outputDataWidth,data,kernal,output);

	printf("\n\nOutput:\n");
	printMatrix2D(outputDataHeight,outputDataWidth,output);
	printf("\n");
}

void testbench_conv2D_multiOutputChannel(){
	const unsigned int batch=4, height=5,width=5, kernal_height=3, kernal_width=3, stride=1;
	unsigned int outputDataHeight, outputDataWidth;
	getOutputDimensionsConv2D(kernal_height,kernal_width, height, width, stride, &outputDataHeight, &outputDataWidth);
	int8_t data[height][width];
	int8_t kernal[batch][kernal_height][kernal_width];
	int8_t output[batch][outputDataHeight][outputDataWidth];

	printf("\ntestbench_conv2D_multiOutputChannel  \n");
	randFillMatrix2D(height,width,data);
	randFillMatrix3D(kernal_height,kernal_width,batch,kernal);
	fillMatrix2D(kernal_height,kernal_width,kernal[0],0);
	fillMatrix2D(kernal_height,kernal_width,kernal[1],1);
	fillMatrix2D(kernal_height,kernal_width,kernal[2],2);
	fillMatrix2D(kernal_height,kernal_width,kernal[3],3);

	printf("\nData:\n");
	printMatrix2D(height,width,data);
	printf("\n\nKernal:\n");
	printMatrix3D(kernal_height,kernal_width,batch,kernal);

	conv2D_multiOutputChannel(batch,height,width,kernal_height,kernal_width,stride,outputDataHeight, outputDataWidth,data,kernal,output);

	printf("\n\nOutput:\n");
	printMatrix3D(outputDataHeight,outputDataWidth,batch,output);
	printf("\n");
}


void testbench_conv2D_depthwise(){
	const unsigned int height=9,width=9,channel=3, kernal_height=3, kernal_width=3, stride=1;
	unsigned int outputDataHeight, outputDataWidth;
	getOutputDimensionsConv2D(kernal_height,kernal_width, height, width, stride, &outputDataHeight, &outputDataWidth);
	int8_t data[channel][height][width];
	int8_t kernal[channel][kernal_height][kernal_width];
	int8_t output[channel][outputDataHeight][outputDataWidth];

	printf("\ntestbench_conv2D_depthwise  \n");
	randFillMatrix3D(height,width,channel,data);
	fillMatrix3D(kernal_height,kernal_width,channel,kernal,0);
	kernal[0][1][1]=1;
	kernal[1][1][1]=1;
	kernal[2][1][1]=1;

	printf("\nData:\n");
	printMatrix3D(height,width,channel,data);
	printf("\n\nKernal:\n");
	printMatrix3D(kernal_height,kernal_width,channel,kernal);

	conv2D_depthwise(height,width,channel,kernal_height,kernal_width,stride,outputDataHeight, outputDataWidth,data,kernal,output);

	printf("\n\nOutput:\n");
	printMatrix3D(outputDataHeight,outputDataWidth,channel,output);
	printf("\n");
}

void testbench_conv2D_depthwiseSeparable(){
	const unsigned int height=9,width=9,channel=3, kernal_height=3, kernal_width=3, stride=1;
	unsigned int outputDataHeight, outputDataWidth;
	getOutputDimensionsConv2D(kernal_height,kernal_width, height, width, stride, &outputDataHeight, &outputDataWidth);
	int8_t data[channel][height][width];
	int8_t kernalDepthWise[channel][kernal_height][kernal_width];
	int8_t kernalSeparable[channel];
	int8_t output[outputDataHeight][outputDataWidth];

	printf("\ntestbench_conv2D_depthwiseSeparable  \n");
	randFillMatrix3D(height,width,channel,data);
	fillMatrix3D(kernal_height,kernal_width,channel,kernalDepthWise,0);
	kernalDepthWise[0][1][1]=1;
	kernalDepthWise[1][1][1]=1;
	kernalDepthWise[2][1][1]=1;
	randFillVector(channel,kernalSeparable);
	kernalSeparable[0]=0;
	kernalSeparable[1]=1;
	kernalSeparable[2]=0;

	printf("\nData:\n");
	printMatrix3D(height,width,channel,data);
	printf("\n\nkernalDepthWise:\n");
	printMatrix3D(kernal_height,kernal_width,channel,kernalDepthWise);
	printf("\nkernalSeparable:\n");
	printVector(channel,kernalSeparable);

	conv2D_depthwiseSeparable(height,width,channel,kernal_height,kernal_width,stride,outputDataHeight, outputDataWidth,data,kernalDepthWise,kernalSeparable,output);

	printf("\n\nOutput:\n");
	printMatrix2D(outputDataHeight,outputDataWidth,output);
	printf("\n");
}

void testbench_dotProduct(){
	const unsigned int N=5;
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
	const unsigned int N=10;
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
	const unsigned int N=10;
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
	const unsigned int N=20;
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
	const unsigned int N=20;
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

