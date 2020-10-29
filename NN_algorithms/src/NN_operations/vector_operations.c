#include "vector_operations.h"

void vect_add(unsigned int N, const int8_t *vec1, const int8_t *vec2, int8_t *vecOut){
	for(unsigned int I = 0; I < N; I ++){
		vecOut[I]= vec1[I] + vec2[I];
	}
}

void vect_mult(unsigned int N,const int8_t *vec1, const int8_t *vec2, int8_t *vecOut){
	for(unsigned int I = 0; I < N; I ++){
		vecOut[I]= vec1[I] * vec2[I];
	}
}

void vect_dotProduct(unsigned int N, const int8_t *vec1, const int8_t *vec2, int8_t *scalarOut){
	int8_t temp=0;
	for(unsigned int I = 0; I < N; I ++){
		temp += vec1[I] * vec2[I];
	}
	*scalarOut=temp;
}

void vect_ReLu(unsigned int N, const int8_t *vec1, int8_t *vecOut){
	for(unsigned int I = 0; I < N; I ++){
		if(vec1[I]<(int8_t)0){
			vecOut[I]= 0;
		}else{
			vecOut[I]=vec1[I];
		}
	}
}

void vect_ReLu6(unsigned int N, const int8_t *vec1, int8_t *vecOut){     //maybe add another parameter to define max value; unsigned int maxValue=6
	for(unsigned int I = 0; I < N; I ++){
		if(vec1[I]<(int8_t)0){
			vecOut[I]= 0;
		}else if(vec1[I]>(int8_t) 6){
			vecOut[I]=6;
		}else{
			vecOut[I]=vec1[I];
		}
	}
}
