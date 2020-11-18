#include "NN_algorithms_testbench.h"

//matrix width goes across ->, height goes down
int main(void){
	unsigned long startCycles, endCycles, cyclesToRun, Cycles_NN_operations=0;
	unsigned long startTime, endTime, timeToRun, time_NN_operations=0;
	unsigned long Cycles_vector, Cycles_matrix_Pooling, Cycles_conv2d;	
	unsigned long time_vector, time_matrix_Pooling, time_conv2d;	
		
	startCycles=getCycles();
	startTime=getRealTime();

	testbench_vectorAdd(&Cycles_NN_operations,&time_NN_operations);
	//testbench_vectorMult(&Cycles_NN_operations,&time_NN_operations);
	testbench_addReduction(&Cycles_NN_operations,&time_NN_operations);
	testbench_dotProduct(&Cycles_NN_operations,&time_NN_operations);
	testbench_vectorReLu(&Cycles_NN_operations,&time_NN_operations);
	testbench_vectorReLu6(&Cycles_NN_operations,&time_NN_operations);
		
	Cycles_vector=Cycles_NN_operations;
	time_vector=time_NN_operations;
	Cycles_NN_operations=0;
	time_NN_operations=0;

	testbench_matrix_mult_d8(&Cycles_NN_operations,&time_NN_operations);
	testbench_matrix_add_d8(&Cycles_NN_operations,&time_NN_operations);
	testbench_max_pool_d8(&Cycles_NN_operations,&time_NN_operations);
	testbench_avg_pool_d8(&Cycles_NN_operations,&time_NN_operations);

	Cycles_matrix_Pooling=Cycles_NN_operations;
	time_matrix_Pooling=time_NN_operations;
	Cycles_NN_operations=0;
	time_NN_operations=0;	
	
	testbench_conv2D(&Cycles_NN_operations,&time_NN_operations);
	testbench_conv2D_multiInputChannel(&Cycles_NN_operations,&time_NN_operations);
	testbench_conv2D_multiIOChannel(&Cycles_NN_operations,&time_NN_operations);
	testbench_conv2D_multiOutputChannel(&Cycles_NN_operations,&time_NN_operations);
	testbench_conv2D_depthwise(&Cycles_NN_operations,&time_NN_operations);
	testbench_conv2D_depthwiseSeparable(&Cycles_NN_operations,&time_NN_operations);
	testbench_conv2D_depthwiseSeparable_multiOutputChannel(&Cycles_NN_operations,&time_NN_operations);
	
	Cycles_conv2d=Cycles_NN_operations;
	time_conv2d=time_NN_operations;
	Cycles_NN_operations=Cycles_vector+Cycles_matrix_Pooling+Cycles_conv2d;
	time_NN_operations=time_vector+time_matrix_Pooling+time_conv2d;
	
	endCycles=getCycles();
	endTime=getRealTime();
	
	cyclesToRun=endCycles-startCycles;
	timeToRun=endTime-startTime;
	
	printf("\n\n");
	printf(" Number of cycles to run just vector_operations: %lu\n",Cycles_vector);
	printf(" Time to run just vector_operations: %lu\n",time_vector);
	printf("\n");
	printf(" Number of cycles to run just matrix/pooling_operations: %lu\n",Cycles_matrix_Pooling);
	printf(" Time to run just matrix/pooling_operations: %lu\n",time_matrix_Pooling);
	printf("\n");
	printf(" Number of cycles to run just conv2D_operations: %lu\n",Cycles_conv2d);
	printf(" Time to run just conv2D_operations: %lu\n",time_conv2d);
	printf("\n");
	printf(" Number of cycles to run all NN_operations: %lu\n",Cycles_NN_operations);
	printf(" Time to run all NN_operations: %lu\n",time_NN_operations);
	printf("\n");
	printf(" Total Number of cycles to run testbenchs: %lu\n",cyclesToRun);
	printf(" Total Time to run testbenchs: %lu\n",timeToRun);
	return EXIT_SUCCESS;
}

unsigned long getCycles(void){
	unsigned long numberOfCyclesExecuted;
	asm volatile ("rdcycle %0" : "=r"(numberOfCyclesExecuted));
	return numberOfCyclesExecuted;
}

unsigned long getRealTime(void){
	unsigned long realTime;
	asm volatile ("rdtime %0" : "=r"(realTime));
	return realTime;
}

void testbench_dotProduct(unsigned long *Cycles_NN_operations,unsigned long *time_NN_operations){
	unsigned long startCycles, endCycles;
	unsigned long startTime, endTime;
		
	const uint32_t N=20;
	int8_t A[N],B[N];
	int32_t output;
	printf("\ntestbench_dotProduct\n\n");
	randFillVector(N,A);
	randFillVector(N,B);
	printf("Vector A:");
	printVector(N,A);
	printf("Vector B:");
	printVector(N,B);

	startCycles=getCycles();
	startTime=getRealTime();
	vect_dotProduct(N,A,B, &output);
	endCycles=getCycles();
	endTime=getRealTime();
	
	printf("\nOutput: %d\n\n\n",(int)output);
	*Cycles_NN_operations +=(endCycles-startCycles);
	*time_NN_operations +=(endTime-startTime);
}

void testbench_vectorAdd(unsigned long *Cycles_NN_operations,unsigned long *time_NN_operations){
	unsigned long startCycles, endCycles;
	unsigned long startTime, endTime;
	
	const uint32_t N=25;
	int8_t A[N],B[N],C[N];
	printf("\ntestbench_vecAdd\n\n");
	randFillVector(N,A);
	randFillVector(N,B);
	printf("Vector A:");
	printVector(N,A);
	printf("Vector B:");
	printVector(N,B);

	startCycles=getCycles();
	startTime=getRealTime();
	vect_add(N,A,B, C);
	endCycles=getCycles();
	endTime=getRealTime();
	
	printf("\nOutput:\n");
	printVector(N,C);
	printf("\n\n");
	*Cycles_NN_operations +=(endCycles-startCycles);
	*time_NN_operations +=(endTime-startTime);
}

void testbench_vectorMult(unsigned long *Cycles_NN_operations,unsigned long *time_NN_operations){
	unsigned long startCycles, endCycles;
	unsigned long startTime, endTime;

	const uint32_t N=25;
	int8_t A[N],B[N],C[N];
	printf("\ntestbench_vecMult\n\n");
	fillVector(N,A,2);
	randFillVector(N,A);
	randFillVector(N,B);
	printf("Vector A:");
	printVector(N,A);
	printf("Vector B:");
	printVector(N,B);

	startCycles=getCycles();
	startTime=getRealTime();
	vect_mult(N,A,B, C);
	endCycles=getCycles();
	endTime=getRealTime();
	
	printf("\nOutput:\n");
	printVector(N,C);
	printf("\n\n");
	*Cycles_NN_operations +=(endCycles-startCycles);
	*time_NN_operations +=(endTime-startTime);
}

void testbench_addReduction(unsigned long *Cycles_NN_operations,unsigned long *time_NN_operations){
	unsigned long startCycles, endCycles;
	unsigned long startTime, endTime;

	const uint32_t N=25;
	int8_t A[N];
	int16_t output;
	printf("\ntestbench_addReduction\n\n");
	randFillVector(N,A);
	printf("Vector A:");
	printVector(N,A);

	startCycles=getCycles();
	startTime=getRealTime();	
	vect_addReduction(N,A, &output);
	endCycles=getCycles();
	endTime=getRealTime();
	
	printf("\nOutput: %d\n\n\n",(int)output);
	*Cycles_NN_operations +=(endCycles-startCycles);
	*time_NN_operations +=(endTime-startTime);
}

void testbench_vectorReLu(unsigned long *Cycles_NN_operations,unsigned long *time_NN_operations){
	unsigned long startCycles, endCycles;
	unsigned long startTime, endTime;

	const uint32_t N=20;
	int8_t A[N],C[N];
	printf("\ntestbench_ReLu\n\n");
	randFillVector(N,A);
	printf("Vector A:");
	printVector(N,A);

	startCycles=getCycles();
	startTime=getRealTime();
	vect_ReLu(N,A, C);
	endCycles=getCycles();
	endTime=getRealTime();
	
	printf("\nOutput:\n");
	printVector(N,C);
	printf("\n\n");
	*Cycles_NN_operations +=(endCycles-startCycles);
	*time_NN_operations +=(endTime-startTime);
}

void testbench_vectorReLu6(unsigned long *Cycles_NN_operations,unsigned long *time_NN_operations){
	unsigned long startCycles, endCycles;
	unsigned long startTime, endTime;

	const uint32_t N=20;
	int8_t A[N],C[N];
	printf("\ntestbench_ReLu6\n\n");
	randFillVector(N,A);
	printf("Vector A:");
	printVector(N,A);

	startCycles=getCycles();
	startTime=getRealTime();
	vect_ReLu6(N,A, C);
	endCycles=getCycles();
	endTime=getRealTime();
	
	printf("\nOutput:\n");
	printVector(N,C);
	printf("\n\n");
	*Cycles_NN_operations +=(endCycles-startCycles);
	*time_NN_operations +=(endTime-startTime);
}


void testbench_matrix_add_d8(unsigned long *Cycles_NN_operations,unsigned long *time_NN_operations){
	unsigned long startCycles, endCycles;
	unsigned long startTime, endTime;

	const uint32_t height=21,width=21;
	int8_t MatA[height][width], MatB[height][width],MatC[height][width];

	printf("\ntestbench_matrix_add_d8  \n");
	randFillMatrix2D(height,width,MatA);
	randFillMatrix2D(height,width,MatB);


	printf("\nMatrix A:\n");
	printMatrix2D(height,width,MatA);
	printf("Matrix B:\n");
	printMatrix2D(height,width,MatB);

	startCycles=getCycles();
	startTime=getRealTime();
	matrix_add_d8(height,width,MatA,MatB,MatC);
	endCycles=getCycles();
	endTime=getRealTime();
	
	printf("Output:\n");
	printMatrix2D(height,width,MatC);
	printf("\n");
	*Cycles_NN_operations +=(endCycles-startCycles);
	*time_NN_operations +=(endTime-startTime);
}

void testbench_matrix_mult_d8(unsigned long *Cycles_NN_operations,unsigned long *time_NN_operations){
	unsigned long startCycles, endCycles;
	unsigned long startTime, endTime;

	const uint32_t height=15,width=15;
	int8_t MatA[height][width], MatB[height][width],MatC[height][width];

	printf("\ntestbench_matrix_mult_d8  \n");
	randFillMatrix2D(height,width,MatA);
	randFillMatrix2D(height,width,MatB);

	printf("\nMatrix A:\n");
	printMatrix2D(height,width,MatA);
	printf("Matrix B:\n");
	printMatrix2D(height,width,MatB);

	startCycles=getCycles();
	startTime=getRealTime();
	matrix_mult_d8(height,width,height,width,MatA,MatB,MatC);
	endCycles=getCycles();
	endTime=getRealTime();
	
	printf("Output:\n");
	printMatrix2D(height,width,MatC);
	printf("\n");
	*Cycles_NN_operations +=(endCycles-startCycles);
	*time_NN_operations +=(endTime-startTime);
}

void testbench_max_pool_d8(unsigned long *Cycles_NN_operations,unsigned long *time_NN_operations){
	unsigned long startCycles, endCycles;
	unsigned long startTime, endTime;

	const uint32_t height=16,width=16,stride=2,filterHeight=2,filterWidth=2;
	int8_t MatA[height][width], MatC[height/filterHeight][width/filterWidth];

	printf("\ntestbench_max_pool_d8  \n");
	randFillMatrix2D(height,width,MatA);

	printf("\nMatrix A, filter is 2x2:\n");
	printMatrix2D(height,width,MatA);

	startCycles=getCycles();
	startTime=getRealTime();
	max_pool_d8(height,width,MatA,filterHeight,filterWidth,stride,MatC);
	endCycles=getCycles();
	endTime=getRealTime();
	
	printf("Output:\n");
	printMatrix2D(height/filterHeight,width/filterWidth,MatC);
	printf("\n");
	*Cycles_NN_operations +=(endCycles-startCycles);
	*time_NN_operations +=(endTime-startTime);
}

void testbench_avg_pool_d8(unsigned long *Cycles_NN_operations,unsigned long *time_NN_operations){
	unsigned long startCycles, endCycles;
	unsigned long startTime, endTime;

	const uint32_t height=16,width=16,stride=2,filterHeight=2,filterWidth=2;
	int8_t MatA[height][width], MatC[height/filterHeight][width/filterWidth];

	printf("\ntestbench_avg_pool_d8  \n");
	randFillMatrix2D(height,width,MatA);

	printf("\nMatrix A, filter is 2x2:\n");
	printMatrix2D(height,width,MatA);

	startCycles=getCycles();
	startTime=getRealTime();
	avg_pool_d8(height,width,MatA,filterHeight,filterWidth,stride,MatC);
	endCycles=getCycles();
	endTime=getRealTime();
	
	printf("Output:\n");
	printMatrix2D(height/filterHeight,width/filterWidth,MatC);
	printf("\n");
	*Cycles_NN_operations +=(endCycles-startCycles);
	*time_NN_operations +=(endTime-startTime);
}


void testbench_conv2D_multiInputChannel(unsigned long *Cycles_NN_operations,unsigned long *time_NN_operations){
	unsigned long startCycles, endCycles;
	unsigned long startTime, endTime;

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

	startCycles=getCycles();
	startTime=getRealTime();
	conv2D_multiInputChannel(height,width,channel,kernel_height,kernel_width,stride,outputDataHeight, outputDataWidth,data,kernel,output);
	endCycles=getCycles();
	endTime=getRealTime();
	
	printf("\n\nOutput:\n");
	printMatrix2D(outputDataHeight,outputDataWidth,output);
	printf("\n");
	*Cycles_NN_operations +=(endCycles-startCycles);
	*time_NN_operations +=(endTime-startTime);
}

void testbench_conv2D_multiIOChannel(unsigned long *Cycles_NN_operations,unsigned long *time_NN_operations){
	unsigned long startCycles, endCycles;
	unsigned long startTime, endTime;

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

	startCycles=getCycles();
	startTime=getRealTime();
	conv2D_multiIOChannel(batch,height,width,channel,kernel_height,kernel_width,stride,outputDataHeight, outputDataWidth,data,kernel,output);
	endCycles=getCycles();
	endTime=getRealTime();
	
	printf("\n\nOutput:   \n");
	printMatrix3D(outputDataHeight,outputDataWidth,batch,output);
	printf("\n");
	*Cycles_NN_operations +=(endCycles-startCycles);
	*time_NN_operations +=(endTime-startTime);
}

void testbench_conv2D(unsigned long *Cycles_NN_operations,unsigned long *time_NN_operations){
	unsigned long startCycles, endCycles;
	unsigned long startTime, endTime;

	const uint32_t height=9,width=9, kernel_height=3, kernel_width=3, stride=3;
	uint32_t outputDataHeight, outputDataWidth;
	getOutputDimensionsConv2D(kernel_height,kernel_width, height, width, stride, &outputDataHeight, &outputDataWidth);
	int8_t data[height][width];
	int8_t kernel[kernel_height][kernel_width];
	int8_t output[outputDataHeight][outputDataWidth];

	printf("\ntestbench_conv2D  \n");
	randFillMatrix2D(height,width,data);
	randFillMatrix2D(kernel_height,kernel_width,kernel);
	fillMatrix2D(kernel_height,kernel_width,kernel,0);
	kernel[1][1]=1;
	
	printf("\nData:\n");
	printMatrix2D(height,width,data);
	printf("\n\nkernel:\n");
	printMatrix2D(kernel_height,kernel_width,kernel);
	printf("Stride = %u\n",(int)stride);

	startCycles=getCycles();
	startTime=getRealTime();
	conv2D(height,width,kernel_height,kernel_width,stride,outputDataHeight, outputDataWidth,data,kernel,output);
	endCycles=getCycles();
	endTime=getRealTime();
	
	printf("\n\nOutput:\n");
	printMatrix2D(outputDataHeight,outputDataWidth,output);
	printf("\n");
	*Cycles_NN_operations +=(endCycles-startCycles);
	*time_NN_operations +=(endTime-startTime);
}

void testbench_conv2D_multiOutputChannel(unsigned long *Cycles_NN_operations,unsigned long *time_NN_operations){
	unsigned long startCycles, endCycles;
	unsigned long startTime, endTime;
	
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

	startCycles=getCycles();
	startTime=getRealTime();
	conv2D_multiOutputChannel(batch,height,width,kernel_height,kernel_width,stride,outputDataHeight, outputDataWidth,data,kernel,output);
	endCycles=getCycles();
	endTime=getRealTime();
	
	printf("\n\nOutput:\n");
	printMatrix3D(outputDataHeight,outputDataWidth,batch,output);
	printf("\n");
	*Cycles_NN_operations +=(endCycles-startCycles);
	*time_NN_operations +=(endTime-startTime);
}

void testbench_conv2D_depthwise(unsigned long *Cycles_NN_operations,unsigned long *time_NN_operations){
	unsigned long startCycles, endCycles;
	unsigned long startTime, endTime;

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

	startCycles=getCycles();
	startTime=getRealTime();
	conv2D_depthwise(height,width,channel,kernel_height,kernel_width,stride,outputDataHeight, outputDataWidth,data,kernel,output);
	endCycles=getCycles();
	endTime=getRealTime();
	
	printf("\n\nOutput:\n");
	printMatrix3D(outputDataHeight,outputDataWidth,channel,output);
	printf("\n");
	*Cycles_NN_operations +=(endCycles-startCycles);
	*time_NN_operations +=(endTime-startTime);
}

void testbench_conv2D_depthwiseSeparable(unsigned long *Cycles_NN_operations,unsigned long *time_NN_operations){
	unsigned long startCycles, endCycles;
	unsigned long startTime, endTime;

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

	startCycles=getCycles();
	startTime=getRealTime();
	conv2D_depthwiseSeparable(height,width,channel,kernel_height,kernel_width,stride,outputDataHeight, outputDataWidth,data,kernelDepthWise,kernelPointwise,output);
	endCycles=getCycles();
	endTime=getRealTime();
	
	printf("\n\nOutput:\n");
	printMatrix2D(outputDataHeight,outputDataWidth,output);
	printf("\n");
	*Cycles_NN_operations +=(endCycles-startCycles);
	*time_NN_operations +=(endTime-startTime);
}

void testbench_conv2D_depthwiseSeparable_multiOutputChannel(unsigned long *Cycles_NN_operations,unsigned long *time_NN_operations){
	unsigned long startCycles, endCycles;
	unsigned long startTime, endTime;

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
	fillMatrix3D(kernel_height,kernel_width,channel,kernelDepthWise,0);
	kernelDepthWise[0][1][1]=1;
	kernelDepthWise[1][1][1]=1;
	kernelDepthWise[2][1][1]=1;
	for(uint32_t b=0;b<batch;b++){fillVector(channel,kernelPointwise[b],b);}


	printf("\nData:\n");
	printMatrix3D(height,width,channel,data);
	printf("\n\nkernelDepthWise:\n");
	printMatrix3D(kernel_height,kernel_width,channel,kernelDepthWise);
	printf("\nkernelPointwise:\n");
	printMatrix2D(batch,channel,kernelPointwise);

	startCycles=getCycles();
	startTime=getRealTime();
	conv2D_depthwiseSeparable_multiOutputChannel(batch,height,width,channel,kernel_height,kernel_width,stride,outputDataHeight, outputDataWidth,data,kernelDepthWise,kernelPointwise,output);
	endCycles=getCycles();
	endTime=getRealTime();
	
	printf("\n\nOutput:\n");
	printMatrix3D(outputDataHeight,outputDataWidth,batch,output);
	printf("\n");
	*Cycles_NN_operations +=(endCycles-startCycles);
	*time_NN_operations +=(endTime-startTime);
}

