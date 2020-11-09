RV_COMPILER_OPTIONS = -Os -g -static -mabi=ilp32 -march=rv32imcv -Wall -pedantic 
RV_LINKING_OPTIONS = ${RV_COMPILER_OPTIONS} -nostartfiles

LINKER_SCRIPT =  ../lib/link.ld
LIB_DIR =  ../lib/

TC_PREFIX = riscv32-unknown-elf-

CC = ${TC_PREFIX}gcc
OBJCOPY = ${TC_PREFIX}objcopy

SPIKE_OPTIONS = --isa=RV32GCV

HEADER_DIR = ../src  \ ../src/NN_operations 
SOURCE_DIR = ../src  \ ../src/NN_operations 

BUILD_DIR = riscV_build

SOURCES += $(wildcard ../src/*.c) $(wildcard ../src/NN_operations/*.c) 
ASSEM_SOURCES = $(wildcard ../src/NN_operations/*.S)
OBJECTS = $(SOURCES:../%.c=%.o)  $(ASSEM_SOURCES:../%.S=%.o) 

	

NN_algorithms_testbench-riscv.hex: NN_algorithms_testbench-riscv.elf 
	${OBJCOPY} -O verilog NN_algorithms_testbench-riscv.elf NN_algorithms_testbench-riscv.hex 

NN_algorithms_testbench-riscv.elf: $(OBJECTS) 
	${CC} ${RV_LINKING_OPTIONS} -o NN_algorithms_testbench-riscv.elf   \
		 -L ${LIB_DIR} -lcv-verif -T ${LINKER_SCRIPT} $(OBJECTS)
	
		
%.o : %.c
	${CC} ${RV_COMPILER_OPTIONS}   -c -o $@ $< 

src/%.o : ../src/%.c  object_DIR
	${CC} ${RV_COMPILER_OPTIONS}  -c -o $@ $< 		

src/NN_operations/%.o :../src/NN_operations/%.c  object_DIR
	${CC} ${RV_COMPILER_OPTIONS}   -c -o $@ $< 		

src/NN_operations/%.o :../src/NN_operations/%.S  object_DIR
	${CC} ${RV_COMPILER_OPTIONS}   -c -o $@ $< 		


object_DIR:
	make dir
	
.PHONY : dir
dir:				
	mkdir -p src 
	mkdir -p src/NN_operations		
		
.PHONY : all
all:
	make dir
	make
	make analyze_assembly
	make run

.PHONY : run
run: 
	testbench_verilator "+firmware=./NN_algorithms_testbench-riscv.hex"

.PHONY : clean
clean:
	rm -f NN_algorithms_testbench-riscv.hex NN_algorithms_testbench-riscv.elf 
	rm -f $(OBJECTS) 


.PHONY : full_clean
full_clean:
	make clean
	rm -f memory_dump.bin assemblerContentsIntermixSourceCode.txt assemblerContents.txt
	rm -r -f src

.PHONY : test
test:
	@echo $(SOURCES)
	@echo $(ASSEM_SOURCES)
	@echo $(OBJECTS)
	@echo $(MAIN_DIR)
	@echo $(SOURCE_DIR)
	@echo $(HEADER_DIR)
	
	
.PHOMY : analyze_assembly
analyze_assembly:
	riscv32-unknown-elf-objdump NN_algorithms_testbench-riscv.elf  -d > assemblerContents.txt
	riscv32-unknown-elf-objdump NN_algorithms_testbench-riscv.elf  -S > assemblerContentsIntermixSourceCode.txt

	
	
	