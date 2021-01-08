#!/bin/bash
export RISCV_LINK_LIB=${PWD}/lib

mkdir -p $RISCV_LINK_LIB 

cp $CV32SIM/../../bsp/libcv-verif.a $RISCV_LINK_LIB/libcv-verif.a
cp $CV32SIM/../../bsp/link.ld $RISCV_LINK_LIB/link.ld

cp $RISCV/lib/gcc/riscv32-unknown-elf/9.2.0/crtbegin.o $RISCV_LINK_LIB/crtbegin.o

ls $RISCV_LINK_LIB 
 
