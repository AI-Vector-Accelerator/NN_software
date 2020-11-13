#!/bin/bash
export RISCV_LINK_LIB=${PWD}/lib

mkdir $RISCV_LINK_LIB 

cd /opt/core-v-verif/cv32/bsp
make
cp libcv-verif.a $RISCV_LINK_LIB/libcv-verif.a
cp link.ld $RISCV_LINK_LIB/link.ld

cd $RISCV_LINK_LIB
cp /opt/riscv/lib/gcc/riscv32-unknown-elf/9.2.0/crtbegin.o crtbegin.o

ls
