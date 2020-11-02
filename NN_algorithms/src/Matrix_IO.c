#include "Matrix_IO.h"

int8_t getRandomNumber(){
	return rand()%32-16;
}

void randFillMatrix4D(const uint32_t batch,const uint32_t height,const uint32_t width,const uint32_t channel, int8_t matrix[batch][channel][height][width]){
	for(uint32_t b=0;b<batch;b++){
		for(uint32_t c=0;c<channel;c++){
			for(uint32_t h=0;h<height;h++){
				for(uint32_t w=0;w<width;w++){
					matrix[b][c][h][w]= getRandomNumber();
				}
			}
		}
	}
}

void randFillMatrix3D(const uint32_t height,const uint32_t width,const uint32_t channel, int8_t matrix[channel][height][width]){
	for(uint32_t c=0;c<channel;c++){
		for(uint32_t h=0;h<height;h++){
			for(uint32_t w=0;w<width;w++){
				matrix[c][h][w]= getRandomNumber();
			}
		}
	}
}

void randFillMatrix2D(const uint32_t height,const uint32_t width, int8_t matrix[height][width]){
	for(uint32_t h=0;h<height;h++){
		for(uint32_t w=0;w<width;w++){
			matrix[h][w]= getRandomNumber();
		}
	}
}

void fillMatrix4D(const uint32_t batch,const uint32_t height,const uint32_t width,const uint32_t channel, int8_t matrix[batch][channel][height][width],int8_t number){
	for(uint32_t b=0;b<batch;b++){
		for(uint32_t c=0;c<channel;c++){
			for(uint32_t h=0;h<height;h++){
				for(uint32_t w=0;w<width;w++){
					matrix[b][c][h][w]= number;
				}
			}
		}
	}
}

void fillMatrix3D(const uint32_t height,const uint32_t width,const uint32_t channel, int8_t matrix[channel][height][width],int8_t number){
	for(uint32_t c=0;c<channel;c++){
		for(uint32_t h=0;h<height;h++){
			for(uint32_t w=0;w<width;w++){
				matrix[c][h][w]= number;
			}
		}
	}
}

void fillMatrix2D(const uint32_t height,const uint32_t width, int8_t matrix[height][width],int8_t number){
	for(uint32_t h=0;h<height;h++){
		for(uint32_t w=0;w<width;w++){
			matrix[h][w]= number;
		}
	}
}

void randFillVector(const uint32_t N, int8_t vector[N]){
	for(uint32_t n=0;n<N;n++){
		vector[n]= getRandomNumber();
	}
}

void fillVector(const uint32_t N, int8_t vector[N],int8_t number){
	for(uint32_t n=0;n<N;n++){
		vector[n]= number;
	}
}

void printMatrix4D(const uint32_t batch,const uint32_t height,const uint32_t width,const uint32_t channel, int8_t matrix[batch][channel][height][width]){
	for(uint32_t b=0;b<batch;b++){
		printf("\nBatch %3u ",(int)b);
		for(uint32_t w=0;w<width*channel+channel-1;w++){printf("------");}
		printMatrix3D(height,width,channel,matrix[b]);
	}
	printf("   -");
	for(uint32_t w=0;w<(width+1)*channel;w++){printf("------");}
	printf("\n");
}

void printMatrix3D(const uint32_t height,const uint32_t width,const uint32_t channel, int8_t matrix[channel][height][width]){
	printf("\n");
	printf("Channel:");
	for(uint32_t c=0;c<channel;c++){
		printf("%4u",(int)c);
		for(uint32_t w=0;w<width-1;w++){
			printf("      ");
		}
		printf("       ");

	}
	printf("\n");
	for(uint32_t h=0;h<height;h++){
		printf("   |    ");
		for(uint32_t c=0;c<channel;c++){
			for(uint32_t w=0;w<width;w++){
				printf(" %4d ",matrix[c][h][w]);
			}
			printf("     ");
		}
		printf("\n");
	}
}

void printMatrix2D(const uint32_t height,const uint32_t width, int8_t matrix[height][width]){
	printf("\n");
	for(uint32_t h=0;h<height;h++){
		for(uint32_t w=0;w<width;w++){
			printf(" %4d ",matrix[h][w]);
		}
		printf("\n");
	}
	printf("\n");
}

void printVector(const uint32_t N, int8_t vector[N]){
	printf("\n");
	for(uint32_t n=0;n<N;n++){
		printf(" %4d ",vector[n]);
	}
	printf("\n");
}
