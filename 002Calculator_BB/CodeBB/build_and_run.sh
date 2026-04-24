#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Remove previous compiled objects and binaries
echo "Cleaning up previous build files..."
rm -f root.o main.o calculadora.elf calculadora.bin

echo "Compiling root.s for Cortex-A8 (BeagleBone)..."
# Usamos gcc en lugar de as para poder pasarle la arquitectura específica
arm-none-eabi-gcc -c -mcpu=cortex-a8 -O0 -g root.s -o root.o

echo "Compiling main.c for Cortex-A8..."
arm-none-eabi-gcc -c -mcpu=cortex-a8 -O0 -g main.c -o main.o

echo "Linking object files..."
arm-none-eabi-ld -T linker.ld root.o main.o -o calculadora.elf

echo "Converting ELF to binary..."
arm-none-eabi-objcopy -O binary calculadora.elf calculadora.bin

echo "=========================================================="
echo "¡Compilación exitosa para BeagleBone!"
echo "El archivo 'calculadora.bin' está listo."
echo "Ahora cópialo a tu memoria MicroSD y cárgalo desde U-Boot."
echo "=========================================================="
