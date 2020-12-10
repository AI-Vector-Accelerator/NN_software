#include "vector_operations.h"


int8_t saturate_16bit_to_8bit(int16_t input){
	if(input>MAX_INT8_T){
		return MAX_INT8_T;
	}else if(input<MIN_INT8_T){
		return MIN_INT8_T;
	}else{
		return (int8_t)input;
	}
}

int8_t saturate_32bit_to_8bit(int32_t input){
	if(input>MAX_INT8_T){
		return MAX_INT8_T;
	}else if(input<MIN_INT8_T){
		return MIN_INT8_T;
	}else{
		return (int8_t)input;
	}
}
