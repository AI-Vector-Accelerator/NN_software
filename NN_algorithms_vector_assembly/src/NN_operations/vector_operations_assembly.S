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
 


#vect_maxReduction(unsigned int N, const int8_t *vec1, int8_t *scalarOut)
# a0=N, a1=*vec1, a2=*scalarOut
# v4=vec1, v1=scalarOut
# Non-vector instructions are indented
vect_maxReduction:	
	.globl   vect_maxReduction
	vsetvli t0, a0, e8, m1, d1      	# Set vectors to be of 8 bits
	li t1, MIN_INT8_T					# copy min value into register
	vmv.v.x v1, t1						# copy register into temp vec
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
 



#void vect_ReLu6(unsigned int N, const int8_t *vec1, int8_t *vecOut);
# a0 = N, a1 = vec1, a3 = vecOut 
# Non-vector instructions are indented

vect_ReLu6: vsetvli t0, a0, e8, m1, d1  # Set vector length based on 8-bit vectors
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
 




 


