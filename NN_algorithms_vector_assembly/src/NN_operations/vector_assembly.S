

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


