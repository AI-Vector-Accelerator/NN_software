#define MIN_INT8_T -128


#void vect_add(unsigned int N, const int8_t *vec1, const int8_t *vec2, int8_t *vecOut);
# a0 = N, a1 = *vec1, a2 = *vec2, a3 = *vecOut 
# v4=vec1, v8=vec2, v12=vec3
# Non-vector instructions are indented
vect_add:    
	.globl   vect_add
	vsetvli t0, a0, e8, m4, d1 			# Set vector length based on 8-bit vectors, group 4 VecReg together for efficiency 
	vle.v v4, (a1)          			# Get first vector
	  add a1, a1, t0         			# Bump pointer
	vle.v v8, (a2)          			# Get second vector
	  add a2, a2, t0       			  	# Bump pointer    
	vsadd.vv v12, v4, v8     			# Sum vectors    
	  sub a0, a0, t0        		 	# Decrement number done
	vse.v v12, (a3)         		 	# Store result      
      add a3, a3, t0       			 	# Bump pointer      
      bnez a0, vect_add   				# Loop back      
      ret                  			  	# Finished
 



#void void vect_mult(unsigned int N,const int8_t *vec1, const int8_t *vec2, int8_t *vecOut)
# a0 = N, a1 = *vec1, a2 = *vec2, a3 = *vecOut 
# v4=vec1, v8=vec2, v12=vec3
# Non-vector instructions are indented
vect_mult:
	.globl   vect_mult
	vsetvli t0, a0, e8, m4, d1 			# Set vector length based on 8-bit vectors, group 4 VecReg together for efficiency 
	vle.v v4, (a1) 						# Get first vector
		add a1, a1, t0 					# Bump pointer
	vle.v v8, (a2) 						# Get second vector
		add a2, a2, t0 					# Bump pointer
	vmul.vv v12, v4, v8 				# Multiply vectors
		sub a0, a0, t0 					# Decrement number done
	vse.v v12, (a3) 					# Store result
		add a3, a3, t0 					# Bump pointer
		bnez a0, vect_mult  			# Loop back
		ret 							# Finished
		
		
		
  
#vect_addReduction(unsigned int N, const int8_t *vec1, int16_t *scalarOut)
# a0=N, a1=*vec1, a2=*scalarOut
# v4=vec1, v1=scalarOut
# Non-vector instructions are indented 
vect_addReduction:	
	.globl   vect_addReduction
	vsetvli t0, a0, e8, m1, d1      	# Set vectors to be of 8 bits
	vmv.v.i v1, 0						# set temp vector to 0
loop_vect_addReduction:
	vsetvli t0, a0, e8, m4, d1      	# Set vectors to be of 8 bits, group 4 VecReg together for efficiency 
	vle.v v4, (a1)          			# Get first vector
	  add a1, a1, t0        			# Bump pointer
	  sub a0, a0, t0        			# Decrement number of bytes done
	vwredsum.vs v1, v4, v1  			# reduction sum vector
	  bnez a0, loop_vect_addReduction	# loop back for any more 
	vsetvli t0, a0, e16, m1, d1         # Set vectors to be of 16 bits
	vmv.x.s t1, v1						# move answer to register
	  sh	t1, 0(a2)					# finished loop, store answer
	  ret								# return
 
 
#vect_add_stride_vec2(unsigned int N, const int16_t *vec1,const int8_t *vec2, int16_t *vecOut, uint32_t stride);
# a0 = N, a1 = *vec1, a2 = *vec2, a3 = *vecOut ,a4=stride
# v4=vec1, v8=vec2, v12=vec3
# Non-vector instructions are indented
vect_add_stride_vec2:	
	.globl	vect_add_stride_vec2
loop_vect_add_stride_vec2:
	vsetvli t0, a0, e16, m4, d1      	# Set vectors to be of 16 bits, group 4 VecReg together for efficiency 
	vle.v v4, (a1)          			# Get first vector
	  slli t2, t0, 1 
	  add a1, a1, t2        			# Bump pointer
	vsetvli t0, a0, e8, m2, d1      	# Set vectors to be of 8 bits  
	vlse.v v8, (a2), a4					# Get second vector, strided load
	  mul t3, t0, a4					# multiply bump amount by stride 
	  add a2, a2, t3 					# Bump pointer
	vwadd.wv v12, v4, v8  				# add vector
	vsetvli t0, a0, e16, m4, d1      	# Set vectors to be of 16 bits, group 4 VecReg together for efficiency 
	vse.v v12, (a3) 					# Store result
	  add a3, a3, t2 					# Bump pointer
	  sub a0, a0, t0        			# Decrement number of bytes done
	  bnez a0, loop_vect_add_stride_vec2		# loop back for any more 
	  ret								# return
 


#vect_maxReduction(unsigned int N, const int8_t *vec1, int8_t *scalarOut)
# a0=N, a1=*vec1, a2=*scalarOut
# v4=vec1, v1=scalarOut
# Non-vector instructions are indented
vect_maxReduction:	
	.globl   vect_maxReduction
loop_vect_maxReduction:
	vsetvli t0, a0, e8, m4, d1      	# Set vectors to be of 8 bits, group 4 VecReg together for efficiency 
	vle.v v4, (a1)          			# Get first vector
	  add a1, a1, t0        			# Bump pointer
	  sub a0, a0, t0        			# Decrement number of bytes done
	vredmax.vs v1, v4, v1  				# max vector
	  bnez a0, loop_vect_maxReduction	# loop back for any more 
	vsetvli t0, a0, e8, m1, d1          # Set vectors to be of 8 bits  
	vmv.x.s t1, v1						# move answer to register
	  sb	t1, 0(a2)					# finished loop, store answer
	  ret								# return


#vect_max_stride_vec2(unsigned int N, const int8_t *vec1,const int8_t *vec2, int8_t *vecOut, uint32_t stride);
# a0 = N, a1 = *vec1, a2 = *vec2, a3 = *vecOut ,a4=stride
# v4=vec1, v8=vec2, v12=vec3
# Non-vector instructions are indented
vect_max_stride_vec2:	
	.globl	vect_max_stride_vec2
	vsetvli t0, a0, e8, m1, d1      	# Set vectors to be of 8 bits
	li t1, MIN_INT8_T					# copy min value into register
	vmv.v.x v8, t1						# copy register into temp vec
loop_vect_max_stride_vec2:
	vsetvli t0, a0, e8, m4, d1      	# Set vectors to be of 8 bits, group 4 VecReg together for efficiency 
	vle.v v4, (a1)          			# Get first vector
	  add a1, a1, t0        			# Bump pointer
	vlse.v v8, (a2), a4					# Get second vector, strided load
	  mul t2, t0, a4					# multiply bump amount by stride 
	  add a2, a2, t2 					# Bump pointer
	  sub a0, a0, t0        			# Decrement number of bytes done
	vmax.vv v12, v4, v8  				# max vector
	vse.v v12, (a3) 					# Store result
	  add a3, a3, t0 					# Bump pointer
	  bnez a0, loop_vect_max_stride_vec2		# loop back for any more 
	  ret								# return
	  
	  
 
#vect_dotProduct(unsigned int N, const int8_t *vec1, const int8_t *vec2, int32_t *scalarOut)
# a0=N, a1=*vec1, a2=*vec2, a3=*scalarOut
# v2=vec1, v4=vec2, v1=scalarOut, v8vec1 * vec2
# Non-vector instructions are indented
vect_dotProduct:  
    .globl   vect_dotProduct
	vsetvli t0, a0, e32, m1, d1      	# Set scalarOutput vector to be of 32 bits
	vmv.v.i v1, 0						# set result vector to 0
loop_vect_dotProduct:
	vsetvli t0, a0, e8, m2, d1      	# Set vectors to be of 8 bits, group 2 VecReg together for efficiency 
	vle.v v2, (a1)          			# Get first vector
	  add a1, a1, t0        			# Bump pointer
	vle.v v4, (a2)          			# Get second vector
      add a2, a2, t0        			# Bump pointer
	vwmul.vv v8, v2, v4  				# multiply vectors(widening instruction)
	vsetvli t0, a0, e16, m4    			# output now in 4 vector registers, update to 16-bit elements
	vwredsum.vs v1, v8, v1				# reduction sum of v1 * v2
	  sub a0, a0, t0        			# Decrement number of bytes done
	  bnez a0, loop_vect_dotProduct		# loop back for any more 
	vsetvli t0, a0, e32, m1, d1		    # set vector to 32-bit element
	vmv.x.s t1, v1						# move answer to register
	  sw	t1, 0(a3)					# finished loop, store answer
	  ret								# return

#vect_dotProduct_stride_vec2(unsigned int N, const int8_t *vec1, const int8_t *vec2, int32_t *scalarOut, uint32_t stride)
# a0=N, a1=*vec1, a2=*vec2, a3=*scalarOut, a4=stride
# v2=vec1, v4=vec2, v1=scalarOut, v8vec1 * vec2
# Non-vector instructions are indented
vect_dotProduct_stride_vec2:  
    .globl   vect_dotProduct_stride_vec2
	vsetvli t0, a0, e32, m1, d1      	# Set scalarOutput vector to be of 32 bits
	vmv.v.i v1, 0						# set result vector to 0
loop_vect_dotProduct_stride_vec2:
	vsetvli t0, a0, e8, m2, d1      	# Set vectors to be of 8 bits, group 2 VecReg together for efficiency 
	vle.v v2, (a1)          			# Get first vector
	  add a1, a1, t0        			# Bump pointer
	vlse.v v4, (a2), a4         		# Get second vector strided access
	  mul t2, t0, a4					# multiply bump amount by stride 
      add a2, a2, t2        			# Bump pointer
	vwmul.vv v8, v2, v4  				# multiply vectors(widening instruction)
	vsetvli t0, a0, e16, m4    			# output now in 4 vector registers, update to 16-bit elements
	vwredsum.vs v1, v8, v1				# reduction sum of v1 * v2
	  sub a0, a0, t0        			# Decrement number of bytes done
	  bnez a0, loop_vect_dotProduct_stride_vec2		# loop back for any more 
	vsetvli t0, a0, e32, m1, d1		    # set vector to 32-bit element
	vmv.x.s t1, v1						# move answer to register
	  sw	t1, 0(a3)					# finished loop, store answer
	  ret								# return
	  	  
	  
#void vect_dotProduct_offset(unsigned int N, const int8_t *vec1, const int8_t *vec2, int32_t *scalarOut, const int8_t vec1Offset, const int8_t vec2Offset);
# a0=N, a1=*vec1, a2=*vec2, a3=*scalarOut, a4=vec1Offset ,a5=vec2Offset
# v2=vec1, v4=vec2, v1=scalarOut, v8vec1 * vec2, v12=vec1Offset, v14=vec2Offset
# Non-vector instructions are indented
vect_dotProduct_offset:  
    .globl   vect_dotProduct_offset
	vsetvli t0, a0, e32, m1, d1      	# Set scalarOutput vector to be of 32 bits
	vmv.v.i v1, 0						# set result vector to 0
loop_vect_dotProduct_offset:
	vsetvli t0, a0, e8, m2, d1      	# Set vectors to be of 8 bits, group 2 VecReg together for efficiency 
	vle.v v2, (a1)          			# Get first vector
	  add a1, a1, t0        			# Bump pointer
	vle.v v4, (a2)          			# Get second vector
      add a2, a2, t0        			# Bump pointer
	vsadd.vx v2, v2, a4				# add offset to vectors
	vsadd.vx v4, v4, a5				# add offset to vectors
	vwmul.vv v8, v2, v4  				# multiply vectors(widening instruction)
	vsetvli t0, a0, e16, m4    			# output now in 4 vector registers, update to 16-bit elements
	vwredsum.vs v1, v8, v1				# reduction sum of v1 * v2
	  sub a0, a0, t0        			# Decrement number of bytes done
	  bnez a0, loop_vect_dotProduct_offset		# loop back for any more 
	vsetvli t0, a0, e32, m1, d1		    # set vector to 32-bit element
	vmv.x.s t1, v1						# move answer to register
	  sw	t1, 0(a3)					# finished loop, store answer
	  ret								# return
	  
#void vect_dotProduct_offset_stride(unsigned int N, const int8_t *vec1, const int8_t *vec2, int32_t *scalarOut, const int8_t vec1Offset, const int8_t vec2Offset, uint32_t vec1Stride, uint32_t vec2Stride);
# a0=N, a1=*vec1, a2=*vec2, a3=*scalarOut, a4=vec1Offset ,a5=vec2Offset, a6=vec1Stride, a7=vec2Stride
# v2=vec1, v4=vec2, v1=scalarOut, v8vec1 * vec2, v12=vec1Offset, v14=vec2Offset
# Non-vector instructions are indented
vect_dotProduct_offset_stride:  
    .globl   vect_dotProduct_offset_stride
	vsetvli t0, a0, e32, m1, d1      	# Set scalarOutput vector to be of 32 bits
	vmv.v.i v1, 0						# set result vector to 0
loop_vect_dotProduct_offset_stride:
	vsetvli t0, a0, e8, m2, d1      	# Set vectors to be of 8 bits, group 2 VecReg together for efficiency 
	vlse.v v4, (a1), a6           		# Get first vector, strided load
	  mul t2, t0, a6					# multiply bump amount by stride 
	  add a1, a1, t2        			# Bump pointer
	vlse.v v8, (a2), a7          		# Get second vector, strided load
	  add a2, a2, t2        			# Bump pointer
    vsadd.vx v4, v4, a4					# add offset to vectors
	vsadd.vx v8, v8, a5					# add offset to vectors
	vwmul.vv v12, v8, v4  				# multiply vectors(widening instruction)
	vsetvli t0, a0, e16, m4    			# output now in 4 vector registers, update to 16-bit elements
	vwredsum.vs v12, v8, v12			# reduction sum of v1 * v2
	  sub a0, a0, t0        			# Decrement number of bytes done
	  bnez a0, loop_vect_dotProduct_offset_stride		# loop back for any more 
	vsetvli t0, a0, e32, m1, d1		    # set vector to 32-bit element
	vmv.x.s t1, v1						# move answer to register
	  sw	t1, 0(a3)					# finished loop, store answer
	  ret								# return
	  
#void vectu_dotProduct_offset_stride(unsigned int N, const uint8_t *vec1, const uint8_t *vec2, int32_t *scalarOut, const int8_t vec1Offset, const int8_t vec2Offset, uint32_t vec1Stride, uint32_t vec2Stride);
# a0=N, a1=*vec1, a2=*vec2, a3=*scalarOut, a4=vec1Offset ,a5=vec2Offset, a6=vec1Stride, a7=vec2Stride
# v4=vec1, v8=vec2, v1=scalarOut, v12=vec1 * vec2
# Non-vector instructions are indented
vectu_dotProduct_offset_stride:  
    .globl   vectu_dotProduct_offset_stride
	vsetvli t0, a0, e32, m1, d1      	# Set scalarOutput vector to be of 32 bits
	vmv.v.i v1, 0						# set result vector to 0
loop_vectu_dotProduct_offset_stride:
	vsetvli t0, a0, e8, m2, d1      	# Set vectors to be of 8 bits, group 2 VecReg together for efficiency 
	vlse.v v4, (a1), a6           		# Get first vector, strided load
	  mul t2, t0, a6					# multiply bump amount by stride 
	  add a1, a1, t2        			# Bump pointer
	vlse.v v8, (a2), a7          		# Get second vector, strided load
	  add a2, a2, t2        			# Bump pointer
	vadd.vx v4, v4, a4					# add offset to vectors
	vadd.vx v8, v8, a5					# add offset to vectors
	vwmul.vv v12, v4, v8  				# multiply vectors(widening instruction)  
	vsetvli t0, a0, e16, m4    			# output now in 4 vector registers, update to 16-bit elements
	vwredsum.vs v1, v12, v1				# reduction sum of v1 * v2
	  sub a0, a0, t0        			# Decrement number of bytes done
	  bnez a0, loop_vectu_dotProduct_offset_stride		# loop back for any more 
	vsetvli t0, a0, e32, m1, d1		    # set vector to 32-bit element
	vmv.x.s t1, v1						# move answer to register
	  sw	t1, 0(a3)					# finished loop, store answer
	  ret								# return


	  



#void vect_ReLu(unsigned int N, const int8_t *vec1, int8_t *vecOut);
# a0 = N, a1 = vec1, a2 = vecOut 
# Non-vector instructions are indented
vect_ReLu: 
	.globl   vect_ReLu
	li t1,0 							# set t1 to 0
loop_vect_ReLu:
	vsetvli t0, a0, e8, m4, d1			# Set vector length based on 8-bit vectors, group 4 VecReg together for efficiency 
	vle.v v4, (a1) 						# Get first vector 
	  add a1, a1, t0 					# Bump pointer 
    vmax.vx v4, v4, t1 					# max vectors 
	vse.v v4, (a2) 						# Store result 
      add a2, a2, t0 					# Bump pointer 
	  sub a0, a0, t0 					# Decrement number done 
      bnez a0, loop_vect_ReLu 			# Loop back 
      ret 								# Finished

 
#void vect_ReLu_Bound(unsigned int N, const int8_t *vec1, int8_t *vecOut, int8_t lowerBound);
# a0 = N, a1 = vec1, a2 = vecOut, a3=lowerBound  
# Non-vector instructions are indented
vect_ReLu_Bound: 
	.globl   vect_ReLu_Bound
	vsetvli t0, a0, e8, m4, d1			# Set vector length based on 8-bit vectors, group 4 VecReg together for efficiency 
	vle.v v4, (a1) 						# Get first vector 
	  add a1, a1, t0 					# Bump pointer 
    vmax.vx v4, v4, a3 					# max vectors 
	vse.v v4, (a2) 						# Store result 
      add a2, a2, t0 					# Bump pointer 
	  sub a0, a0, t0 					# Decrement number done 
      bnez a0, vect_ReLu_Bound 			# Loop back 
      ret 								# Finished
	  
	  

#void vect_ReLu6(unsigned int N, const int8_t *vec1, int8_t *vecOut);
# a0 = N, a1 = vec1, a2 = vecOut
# Non-vector instructions are indented

vect_ReLu6: 
	.globl   vect_ReLu6
	li t1, 0 							# set t1 to 0
    li t2, 6 							# set t2 to 6
loop_vect_ReLu6:
	vsetvli t0, a0, e8, m4, d1      	# Set vectors to be of 8 bits, group 4 VecReg together for efficiency 
	vle.v v4, (a1) 						# Get first vector 
      add a1, a1, t0 					# Bump pointer 
	vmax.vx v4, v4, t1 					# max vectors 
	vmin.vx v4, v4, t2 					# min vectors 
	vse.v v4, (a2) 						# Store result 
      add a2, a2, t0 					# Bump pointer 
	  sub a0, a0, t0 					# Decrement number done
      bnez a0, loop_vect_ReLu6 			# Loop back 
      ret 								# Finished

#void vect_ReLu6_Bound(unsigned int N, const int8_t *vec1, int8_t *vecOut, int8_t lowerBound, int8_t upperBound);
# a0 = N, a1 = vec1, a3 = vecOut, a3=lowerBound, a4=upperBound   
# Non-vector instructions are indented

vect_ReLu6_Bound: 
	.globl   vect_ReLu6_Bound
	vsetvli t0, a0, e8, m4, d1      	# Set vectors to be of 8 bits, group 4 VecReg together for efficiency 
	vle.v v4, (a1) 						# Get first vector 
      add a1, a1, t0 					# Bump pointer 
	vmax.vx v4, v4, a3 					# max vectors 
	vmin.vx v4, v4, a4 					# min vectors 
	vse.v v4, (a2) 						# Store result 
      add a2, a2, t0 					# Bump pointer 
	  sub a0, a0, t0 					# Decrement number done
      bnez a0, vect_ReLu6_Bound			# Loop back 
      ret 								# Finished

 
 
 
 
 
#void vect_copy(unsigned int N,const int8_t *vec1, int8_t *vecOut);
# a0 = N, a1 = vec1, a2 = *vecOut 
vect_copy:
	.globl	vect_copy
	vsetvli t0, a0, e8, m4, d1      	# Set vectors to be of 8 bits, group 4 VecReg together for efficiency 
	vle.v v4, (a1) 						# Get first vector 
	  add a1, a1, t0 					# Bump pointer 
	vse.v v4, (a2) 						# Store vector
	  add a2, a2, t0 					# Bump pointer 
	  sub a0, a0, t0 					# Decrement number done
      bnez a0, vect_copy	 			# Loop back 
      ret 								# Finished	  
	  
#void vect_copy_reg(unsigned int N,const int8_t value, int8_t *vecOut);
# a0 = N, a1 = value, a2 = *vecOut
vect_copy_reg:
	.globl	vect_copy_reg
	vsetvli t0, a0, e8, m4, d1      	# Set vectors to be of 8 bits, group 4 VecReg together for efficiency 
	vmv.v.x v4, a1						# set vector to value
loop_vect_copy_reg:
	vsetvli t0, a0, e8, m4, d1      	# Set vectors to be of 8 bits, group 4 VecReg together for efficiency 
	vse.v v4, (a2) 						# Store vector
	  add a2, a2, t0 					# Bump pointer 
	  sub a0, a0, t0 					# Decrement number done
      bnez a0, loop_vect_copy_reg	 	# Loop back 
	  ret 								# Finished	
	
	
	
