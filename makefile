RV_COMPILER_OPTIONS = -Os -g -static -mabi=ilp32 -march=rv32imc -Wall -pedantic 
RV_LINKING_OPTIONS = ${RV_COMPILER_OPTIONS} -nostartfiles

LINKER_SCRIPT = ./lib/link.ld
LIB_DIR = ./lib/

SOURCE_FILES = $(wildcard source/*.c)
HEADER_FILES = $(wildcard header/*.h)
OBJ_FILES = $(SOURCE_FILES:source/%.c=build/%.o)

OBJ_FILES += NN_algorithms_testbench.o

TC_PREFIX = riscv32-unknown-elf-

CC = ${TC_PREFIX}gcc
OBJCOPY = ${TC_PREFIX}objcopy

SPIKE_OPTIONS = --isa=RV32GC

build/NN_algorithms_testbench-riscv.hex: build/NN_algorithms_testbench-riscv.elf 
	${OBJCOPY} -O verilog NN_algorithms_testbench-riscv.elf NN_algorithms_testbench-riscv.hex 

build/NN_algorithms_testbench-riscv.elf: ${OBJ_FILES} ${HEADER_FILES}
	${CC} ${RV_LINKING_OPTIONS} -o NN_algorithms_testbench-riscv.elf -I./header \
		-L ${LIB_DIR} -lcv-verif -T ${LINKER_SCRIPT} ${OBJ_FILES}

build/%.o : source/%.c
	${CC} ${RV_COMPILER_OPTIONS} -I./header -c -o $@ $< 

%.o : %.c
	${CC} ${RV_COMPILER_OPTIONS} -I./header -c -o $@ $<


.PHONY : all
all:
	make
	make run

.PHONY : run
run: 
	testbench_verilator "+firmware=./NN_algorithms_testbench-riscv.hex"

.PHONY : clean
clean:
	-rm NN_algorithms_testbench-riscv.hex NN_algorithms_testbench-riscv.elf
	-rm -r build
	-rm -r NN_algorithms_testbench.o
	mkdir build 
