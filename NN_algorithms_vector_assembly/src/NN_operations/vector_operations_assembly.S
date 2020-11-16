#define MIN_INT8_T -128



#void vect_add(unsigned int N, const int8_t *vec1, const int8_t *vec2, int8_t *vecOut);
# a0 = N, a1 = *vec1, a2 = *vec2, a3 = *vecOut 
# v1=vec1, v2=vec2, v3=vec3
# Non-vector instructions are indented
vect_add:    
	.globl   vect_add
	vsetvli t0, a0, e8, m1, d1 			# Set vector length based on 8-bit vectors
	vle.v v1, (a1)          			# Get first vector
	  add a1, a1, t0         			# Bump pointer
	vle.v v2, (a2)          			# Get second vector
	  add a2, a2, t0       			  	# Bump pointer    
	vsadd.vv v3, v1, v2     			# Sum vectors    
	  sub a0, a0, t0        		 	# Decrement number done
	vse.v v3, (a3)         			 	# Store result      
      add a3, a3, t0       			 	# Bump pointer      
      bnez a0, vect_add   				# Loop back      
      ret                  			  	# Finished
 



#void void vect_mult(unsigned int N,const int8_t *vec1, const int8_t *vec2, int8_t *vecOut)
# a0 = N, a1 = *vec1, a2 = *vec2, a3 = *vecOut 
# v1=vec1, v2=vec2, v3=vec3
# Non-vector instructions are indented
vect_mult:
	.globl   vect_mult
	vsetvli t0, a0, e8, m1, d1 			# Set vector length based on 8-bit vectors
	vle.v v1, (a1) 						# Get first vector
		add a1, a1, t0 					# Bump pointer
	vle.v v2, (a2) 						# Get second vector
		add a2, a2, t0 					# Bump pointer
	vmul.vv v3, v1, v2 					# Multiply vectors
		sub a0, a0, t0 					# Decrement number done
	vse.v v3, (a3) 						# Store result
		add a3, a3, t0 					# Bump pointer
		bnez a0, vect_mult  			# Loop back
		ret 							# Finished
		
		
		
  
#vect_addReduction(unsigned int N, const int8_t *vec1, int16_t *scalarOut)
# a0=N, a1=*vec1, a2=*scalarOut
# v1=vec1, v2=scalarOut
# Non-vector instructions are indented 
vect_addReduction:	
	.globl   vect_addReduction
	vsetvli t0, a0, e8, m1, d1      	# Set vectors to be of 8 bits
	vmv.v.i v2, 0						# set temp vector to 0
loop_vect_addReduction:
	vsetvli t0, a0, e8, m1, d1      	# Set vectors to be of 8 bits
	vle.v v1, (a1)          			# Get first vector
	  add a1, a1, t0        			# Bump pointer
	  sub a0, a0, t0        			# Decrement number of bytes done
	vwredsum.vs v2, v1, v2  			# reduction sum vector
	  bnez a0, loop_vect_addReduction	# loop back for any more 
	vsetvli t0, a0, e16, m1, d1         # Set vectors to be of 16 bits
	vmv.x.s t1, v2						# move answer to register
	  sh	t1, 0(a2)					# finished loop, store answer
	  ret								# return
 


#vect_maxReduction(unsigned int N, const int8_t *vec1, int8_t *scalarOut)
# a0=N, a1=*vec1, a2=*scalarOut
# v1=vec1, v2=scalarOut
# Non-vector instructions are indented
vect_maxReduction:	
	.globl   vect_maxReduction
	vsetvli t0, a0, e8, m1, d1      	# Set vectors to be of 8 bits
	li t1, MIN_INT8_T					# copy min value into register
	vmv.v.x v2, t1						# copy register into temp vec
loop_vect_maxReduction:
	vsetvli t0, a0, e8, m1, d1      	# Set vectors to be of 8 bits
	vle.v v1, (a1)          			# Get first vector
	  add a1, a1, t0        			# Bump pointer
	  sub a0, a0, t0        			# Decrement number of bytes done
	vredmax.vs v2, v1, v2  				# max vector
	  bnez a0, loop_vect_maxReduction	# loop back for any more 
	vmv.x.s t1, v2						# move answer to register
	  sb	t1, 0(a2)					# finished loop, store answer
	  ret								# return

 
#vect_dotProduct(unsigned int N, const int8_t *vec1, const int8_t *vec2, int32_t *scalarOut)
# a0=N, a1=*vec1, a2=*vec2, a3=*scalarOut
# v1=vec1, v2=vec2, v6=scalarOut, v4=vec1 * vec2
# Non-vector instructions are indented
vect_dotProduct:  
    .globl   vect_dotProduct
	vsetvli t0, a0, e32, m1, d1      	# Set scalarOutput vector to be of 32 bits
	vmv.v.i v3, 0						# set result vector to 0
loop_vect_dotProduct:
	vsetvli t0, a0, e8, m1, d1      	# Set vectors to be of 8 bits
	vle.v v1, (a1)          			# Get first vector
	  add a1, a1, t0        			# Bump pointer
	vle.v v2, (a2)          			# Get second vector
      add a2, a2, t0        			# Bump pointer
	vwmul.vv v4, v2, v1  				# multiply vectors(widening instruction)
	vsetvli t0, a0, e16, m2    			 # output now in 2 vector registers, update to 16-bit elements
	vwredsum.vs v3, v4, v3				# reduction sum of v1 * v2
	  sub a0, a0, t0        			# Decrement number of bytes done
	  bnez a0, loop_vect_dotProduct		# loop back for any more 
	vsetvli t0, a0, e32, m1, d1		    # set vector to 32-bit element
	vmv.x.s t1, v3						# move answer to register
	  sw	t1, 0(a3)					# finished loop, store answer
	  ret								# return
	  
	  
	  



#void vect_ReLu(unsigned int N, const int8_t *vec1, int8_t *vecOut);
# a0 = N, a1 = vec1, a2 = vecOut 
# Non-vector instructions are indented
vect_ReLu: 
	.globl   vect_ReLu
	li t1,0 							# set t1 to 0
loop_vect_ReLu:
	vsetvli t0, a0, e8, m1, d1			# Set vector length based on 8-bit vectors
	vle.v v1, (a1) 						# Get first vector 
	  add a1, a1, t0 					# Bump pointer 
    vmax.vx v1, v1, t1 					# max vectors 
	vse.v v1, (a2) 						# Store result 
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
	vsetvli t0, a0, e8, m1, d1      	# Set vectors to be of 8 bits
	vle.v v1, (a1) 						# Get first vector 
      add a1, a1, t0 					# Bump pointer 
	vmax.vx v1, v1, t1 					# max vectors 
	vmin.vx v1, v1, t2 					# min vectors 
	vse.v v1, (a2) 						# Store result 
      add a2, a2, t0 					# Bump pointer 
	  sub a0, a0, t0 					# Decrement number done
      bnez a0, loop_vect_ReLu6 			# Loop back 
      ret 								# Finished
 




 


