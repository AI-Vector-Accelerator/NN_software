#define MIN_INT8_T -128

vect_dotProduct:  #vect_dotProduct(unsigned int N, const int8_t *vec1, const int8_t *vec2, int8_t *scalarOut)
	vmv.s.x v3, x0				# set temp vector to 0
loop_vect_dotProduct:
	vsetvli t0, a0, e8      	# Set vectors to be of 8 bits
	vlb.v v0, (a1)          	# Get first vector
	  add a1, a1, t0        	# Bump pointer
	vlb.v v1, (a2)          	# Get second vector
      add a2, a2, t0        	# Bump pointer
	  sub a0, a0, t0        	# Decrement number of bytes done
	vdot.vv v2, v0, v1  		# dot product vectors
	vadd.vv v3, v3, v2			# add previous results to current
	  bnez a0, loop_vect_dotProduct	# loop back for any more 
	  vmv.x.s a5, v2			# move answer to register
	  sb	a5,0(a3)			# finished loop, store answer
	  ret						# return
	  
	  
vect_addRecursive:	#vect_addRecursive(unsigned int N, const int8_t *vec1, int8_t *scalarOut)
	vmv.s.x v3, x0					# set temp vector to 0
loop_vect_addRecursive:
	vsetvli t0, a0, e8      		# Set vectors to be of 8 bits
	vlb.v v0, (a1)          		# Get first vector
	  add a1, a1, t0        		# Bump pointer
	  sub a0, a0, t0        		# Decrement number of bytes done
	vredsum.vs v1, v0, v1  			# reduction sum vector
	  bnez a0, loop_vect_addRecursive	# loop back for any more 
	  vmv.x.s a3, v1				# move answer to register
	  sb	a3,0(a2)				# finished loop, store answer
	  ret							# return

vect_maxRecursive:	#vect_maxRecursive(unsigned int N, const int8_t *vec1, int8_t *scalarOut)
	li	a4, MIN_INT8_T				#copy min value into reg first
	vmv.s.x v3, a4					#then set temp vector to -128
loop_vect_maxRecursive:
	vsetvli t0, a0, e8      		# Set vectors to be of 8 bits
	vlb.v v0, (a1)          		# Get first vector
	  add a1, a1, t0        		# Bump pointer
	  sub a0, a0, t0        		# Decrement number of bytes done
	vredmax.vs v1, v0, v1  			# max vector
	  bnez a0, loop_vect_maxRecursive	# loop back for any more 
	  vmv.x.s a3, v1				# move answer to register
	  sb	a3,0(a2)				# finished loop, store answer
	  ret							# return

#void vect_ReLu(unsigned int N, const int8_t *vec1, int8_t *vecOut);
# appendix A.1. Vector-vector add example riscv-v-spec-0.8
# a0 = N, a1 = vec1, a3 = vecOut 
# Non-vector instructions are indented

vect_ReLu: 
vsetvli t0, a0, e8 # Set vector length based on 8-bit vectors
vlw.v v0, (a1) # Get first vector 
   sub a0, a0, t0 # Decrement number done 
   slli t0, t0, 2 # Multiply number done by 4 bytes 
   add a1, a1, t0 # Bump pointer 
vmax.vx v2, v0, 0 # max vectors 
vsw.v v2, (a3) # Store result 
  add a3, a3, t0 # Bump pointer 
  bnez a0, vect_ReLu # Loop back 
  ret # Finished


#void vect_ReLu6(unsigned int N, const int8_t *vec1, int8_t *vecOut);
# appendix A.1. Vector-vector add example riscv-v-spec-0.8
# a0 = N, a1 = vec1, a3 = vecOut 
# Non-vector instructions are indented

vect_ReLu6: vsetvli t0, a0, e8 # Set vector length based on 8-bit vectors
vlw.v v0, (a1) # Get first vector 
   sub a0, a0, t0 # Decrement number done 
   slli t0, t0, 2 # Multiply number done by 4 bytes 
   add a1, a1, t0 # Bump pointer 
vmax.vx v1, v0, 0 # max vectors 
vmin.vx v2, v1, 6 # min vectors 
vsw.v v2, (a3) # Store result 
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
   vadd.vv v2, v0, v1        # Sum vectors    
   vsw.v v2, (a3)           # Store result      
     add a3, a3, t0         # Bump pointer      
     bnez a0, vect_add    # Loop back      
     ret                    # Finished
