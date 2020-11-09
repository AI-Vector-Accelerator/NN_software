#define MIN_INT8_T -128

vect_dotProduct:  #vect_dotProduct(unsigned int N, const int8_t *vec1, const int8_t *vec2, int32_t *scalarOut)
	# a0=N, a1=*vec1, a2=*vec2, a3=*scalarOut
	# v1=vec1, v2=vec2, v3=scalarOut, v4=vec1 * vec2
	vsetvli t0, a0, e8      	# Set vectors to be of 8 bits
	vmv.v.i v3, 0				# set result vector to 0
loop_vect_dotProduct:
	vsetvli t0, a0, e8      	# Set vectors to be of 8 bits
	vle.v v1, (a1)          	# Get first vector
	  add a1, a1, t0        	# Bump pointer
	vle.v v2, (a2)          	# Get second vector
      add a2, a2, t0        	# Bump pointer
	vwmul.vv v4, v2, v1  		# multiply vectors(widening instruction)
	vsetvli t0, a0, e16, m2     # output now in 2 vector registers, update to 16-bit elements
	vwredsum.vs v3, v4, v3		# reduction sum of v1 * v2
	  sub a0, a0, t0        	# Decrement number of bytes done
	  bnez a0, loop_vect_dotProduct	# loop back for any more 
	vsetvli t0, a0, e32		    # set vector to 32-bit element
	vse.v v3, (a3)				# store result in 
	  ret						# return

	  	  
vect_addReduction:	#vect_addReduction(unsigned int N, const int8_t *vec1, int16_t *scalarOut)
	vmv.v.i v0, 0					# set temp vector to 0
loop_vect_addReduction:
	vsetvli t0, a0, e8      		# Set vectors to be of 8 bits
	vle.v v0, (a1)          		# Get first vector
	  add a1, a1, t0        		# Bump pointer
	  sub a0, a0, t0        		# Decrement number of bytes done
	vwredsum.vs v1, v0, v1  			# reduction sum vector
	  bnez a0, loop_vect_addReduction	# loop back for any more 
	vsetvli t0, a0, e16          #Set vectors to be of 16 bits
	vmv.x.s t1, v1				# move answer to register
	  sb	t1, 0(a2)				# finished loop, store answer
	  ret							# return


vect_maxReduction:	#vect_maxReduction(unsigned int N, const int8_t *vec1, int8_t *scalarOut)
	# a0=N, a1=*vec1, a2=*scalarOut
	# v1=vec1, v2=scalarOut
	vmv.v.i v2, MIN_INT8_T				#copy min value into temp vec
loop_vect_maxReduction:
	vsetvli t0, a0, e8      		# Set vectors to be of 8 bits
	vle.v v1, (a1)          		# Get first vector
	  add a1, a1, t0        		# Bump pointer
	  sub a0, a0, t0        		# Decrement number of bytes done
	vredmax.vs v2, v1, v2  			# max vector
	  bnez a0, loop_vect_maxReduction	# loop back for any more 
	vmv.x.s t1, v2				# move answer to register
	  sb	t1, 0(a2)				# finished loop, store answer
	  ret							# return





#void vect_ReLu(unsigned int N, const int8_t *vec1, int8_t *vecOut);
# appendix A.1. Vector-vector add example riscv-v-spec-0.8
# a0 = N, a1 = vec1, a3 = vecOut 
# Non-vector instructions are indented

vect_ReLu: 
vsetvli t0, a0, e8 # Set vector length based on 8-bit vectors
vlw.v v1, (a1) # Get first vector 
   sub a0, a0, t0 # Decrement number done 
   slli t0, t0, 2 # Multiply number done by 4 bytes 
   add a1, a1, t0 # Bump pointer 
   addi a2,x0,0 #set a2 to 0
vmax.vx v2, v1, a2 # max vectors 
vse.v v2, (a3) # Store result 
  add a3, a3, t0 # Bump pointer 
  bnez a0, vect_ReLu # Loop back 
  ret # Finished


#void vect_ReLu6(unsigned int N, const int8_t *vec1, int8_t *vecOut);
# appendix A.1. Vector-vector add example riscv-v-spec-0.8
# a0 = N, a1 = vec1, a3 = vecOut 
# Non-vector instructions are indented

vect_ReLu6: vsetvli t0, a0, e8 # Set vector length based on 8-bit vectors
vlw.v v1, (a1) # Get first vector 
   sub a0, a0, t0 # Decrement number done 
   slli t0, t0, 2 # Multiply number done by 4 bytes 
   add a1, a1, t0 # Bump pointer 
   addi a2, x0, 0 #set a2 to 0
   addi a4, x0, 6 #set a4 to 6
vmax.vx v2, v1, a2 # max vectors 
vmin.vx v3, v2, a4 # min vectors 
vse.v v3, (a3) # Store result 
   add a3, a3, t0 # Bump pointer 
   bnez a0, vect_ReLu6 # Loop back 
   ret # Finished






#void vect_add(unsigned int N, const int8_t *vec1, const int8_t *vec2, int8_t *vecOut);
# appendix A.1. Vector-vector add example riscv-v-spec-0.8
# a0 = N, a1 = vec1,a2,vec2 a3 = vecOut 
# Non-vector instructions are indented

vect_add:    
  vsetvli t0, a0, e8 # Set vector length based on 8-bit vectors
  vlw.v v0, (a1)           # Get first vector
	 sub a0, a0, t0         # Decrement number done
	 slli t0, t0, 2         # Multiply number done by 4 bytes
	 add a1, a1, t0         # Bump pointer
   vlw.v v1, (a2)           # Get second vector
	 add a2, a2, t0         # Bump pointer    
   vsadd.vv v2, v0, v1        # Sum vectors    
   vse.v v2, (a3)           # Store result      
     add a3, a3, t0         # Bump pointer      
     bnez a0, vect_add    # Loop back      
     ret                    # Finished

#	void void vect_mult(unsigned int N,const int8_t *vec1, const int8_t *vec2, int8_t *vecOut)
#	for(unsigned int n =0; n<N; n++){vecOut[n]= vec1[n] * vec2[n]}
# 	Non-vector instructions are indented

vec_mult:
	vsetvli t0, a0, e8 		# Set vector length based on 8-bit vectors
	vlw.v v0, (a1) 			# Get first vector
		sub a0, a0, t0 		# Decrement number done
		slli t0, t0, 2 		# Multiply number done by 4 bytes
		add a1, a1, t0 		# Bump pointer
	vle.v v1, (a2) 			# Get second vector
		add a2, a2, t0 		# Bump pointer
	vsmul.vv v2, v0, v1 		# Multiply vectors
	vse.v v2, (a3) 			# Store result
		add a3, a3, t0 		# Bump pointer
		bnez a0, vec_mult # Loop back
		ret 				# Finished
