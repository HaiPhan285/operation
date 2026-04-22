#!/bin/bash
set -xeu

QEMU=qemu-system-riscv32
CXX=clang  # Ubuntu users: use CC=clang

CXXFLAGS="-std=c++17 -O2 -g3 -Wall -Wextra --target=riscv32-unknown-elf -fuse-ld=lld -fno-stack-protector -ffreestanding -nostdlib -fno-exceptions -fno-rtti"

# Build the kernel
$CXX $CXXFLAGS \
  -Wl,-Tkernel.ld \
  -Wl,-Map=kernel.map \
  -o kernel.elf \
  kernel.cpp
# Start QEMU
$QEMU \
  -machine virt \
  -bios default \
  -nographic \
  -serial mon:stdio \
  --no-reboot \
  -kernel kernel.elf