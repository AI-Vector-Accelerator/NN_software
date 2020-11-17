RV_COMPILER_OPTIONS = -Os -g -static -mabi=ilp32 -march=rv32imcv -Wall -pedantic 
RV_LINKING_OPTIONS = ${RV_COMPILER_OPTIONS} -nostartfiles  ${LIB_DIR}crtbegin.o
RV_LINKING_OPTIONS_SPIKE = ${RV_COMPILER_OPTIONS} 

SPIKE_SIM_FLAGS= --isa=RV32IMCV    --varch=vlen:32,elen:32,slen:32
PK_DIR=/opt/riscv/riscv32-unknown-elf/bin

LINKER_SCRIPT =  ../lib/link.ld
LIB_DIR =  ../lib/

TC_PREFIX = riscv32-unknown-elf-

CC = ${TC_PREFIX}gcc
OBJCOPY = ${TC_PREFIX}objcopy

HEADER_DIR = ../src  \ ../src/NN_operations 
SOURCE_DIR = ../src  \ ../src/NN_operations 

BUILD_DIR = riscV_build

SOURCES += $(wildcard ../src/*.c) $(wildcard ../src/NN_operations/*.c) 
ASSEM_SOURCES = $(wildcard ../src/NN_operations/*.S)
OBJECTS = $(SOURCES:../%.c=%.o)  $(ASSEM_SOURCES:../%.S=%.o) 

	

NN_algorithms_testbench-riscv.hex: NN_algorithms_testbench-riscv.elf 
	${OBJCOPY} -O verilog NN_algorithms_testbench-riscv.elf NN_algorithms_testbench-riscv.hex 

NN_algorithms_testbench-riscv.elf: $(OBJECTS) lib_build
	${CC} ${RV_LINKING_OPTIONS} -o NN_algorithms_testbench-riscv.elf   \
		 -L ${LIB_DIR} -lcv-verif -T ${LINKER_SCRIPT} $(OBJECTS)

NN_algorithms_testbench-riscv_spike.elf: $(OBJECTS) lib_build
	${CC} ${RV_LINKING_OPTIONS_SPIKE} -o NN_algorithms_testbench-riscv_spike.elf \
		 -L ${LIB_DIR} -lcv-verif -T ${LINKER_SCRIPT}  $(OBJECTS)	
		

src/%.o : ../src/%.c  object_DIR
	${CC} ${RV_COMPILER_OPTIONS}  -c -o $@ $< 		

src/NN_operations/%.o :../src/NN_operations/%.c  object_DIR
	${CC} ${RV_COMPILER_OPTIONS}   -c -o $@ $< 		

src/NN_operations/%.o :../src/NN_operations/%.S  object_DIR
	${CC} ${RV_COMPILER_OPTIONS}  -c -o $@ $< 		


object_DIR:
	make dir

lib_build:
	make lib
	
.PHONY : dir
dir:				
	mkdir -p src 
	mkdir -p src/NN_operations		
	
.PHONY : lib
lib:
	if [ ! -d  ${LIB_DIR} ]; then ../make_lib_riscv.sh; mv  lib $(LIB_DIR)  ; fi
		
.PHONY : all
all:
	make dir
	make lib
	make -j16
	# make -j16 verilator
	make -j16 spike
	make analyze_assembly
	
.PHONY : clean
clean:
	rm -f NN_algorithms_testbench-riscv.hex NN_algorithms_testbench-riscv.elf NN_algorithms_testbench-riscv_spike.elf
	rm -f $(OBJECTS) 


.PHONY : full_clean
full_clean:
	make clean
	rm -f memory_dump.bin assemblerContentsIntermixSourceCode.txt assemblerContents.txt
	rm -r -f src
	rm -r $(LIB_DIR)

.PHONY : test
test:
	@echo $(SOURCES)
	@echo $(ASSEM_SOURCES)
	@echo $(OBJECTS)
	@echo $(MAIN_DIR)
	@echo $(SOURCE_DIR)
	@echo $(HEADER_DIR)
	
	
.PHONY : analyze_assembly
analyze_assembly:
	riscv32-unknown-elf-objdump NN_algorithms_testbench-riscv_spike.elf  -d > assemblerContents.txt
	riscv32-unknown-elf-objdump NN_algorithms_testbench-riscv_spike.elf  -S > assemblerContentsIntermixSourceCode.txt

.PHONY : verilator
verilator: NN_algorithms_testbench-riscv.hex
	testbench_verilator "+firmware=./NN_algorithms_testbench-riscv.hex"
	
.PHONY : spike
spike: NN_algorithms_testbench-riscv_spike.elf
	spike  $(SPIKE_SIM_FLAGS) $(flags) $(PK_DIR)/pk NN_algorithms_testbench-riscv_spike.elf
	
	
