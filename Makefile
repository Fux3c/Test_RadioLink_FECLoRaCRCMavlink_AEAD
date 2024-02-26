.PHONY: all build flash test cmake clean format doc

# OS := $(shell uname)

BUILD_DIR := build
BUILD_TYPE ?= Debug

all: build flash

${BUILD_DIR}/Makefile:
	cmake \
		-B ${BUILD_DIR} \
		-DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
		-DCMAKE_TOOLCHAIN_FILE=gcc-arm-none-eabi.cmake \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-DDUMP_ASM=OFF \
 #		-G "MinGW Makefiles"

cmake: ${BUILD_DIR}/Makefile

build: cmake
	$(MAKE) -C ${BUILD_DIR} --no-print-directory

flash: 
	STM32_Programmer_CLI -c port=SWD -w build/NRS_FC-Verification.elf 0x08008000 -rst

flash-uart:
	STM32_Programmer_CLI -c port=COM3 br=115200 -w build/NRS_FC-Verification.elf 0x08008000 -rst



# SRCS := $(shell find . -name "*.cpp")
# %.format: %
# 	clang-format -i $<
# format: $(addsuffix .format, ${SRCS})

clean:
	rmdir build /s /q 

doc:
	cd HAM/Documentation/doxygen && doxygen
