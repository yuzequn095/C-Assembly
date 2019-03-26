#
# Makefile template for CSE 30 -- PAMT1
#

HEADERS		= pamt1.h

C_SRCS		= init.c omp_init.c main.c \
		  function1.c omp_function1.c \
	          function2.c omp_function2.c

C_OBJS		= init.o omp_init.o main.o \
		  function1.o omp_function1.o \
	          function2.o omp_function2.o

OBJS		= ${C_OBJS}

EXE		= pamt1

#
# Relevant man pages:
#
# man gcc
#

GCC		= gcc
# GCC		= /usr/local/gcc/bin/gcc

GCC_FLAGS	= -c -Wall -std=c99 -fopenmp
LD_FLAGS	= -lm -fopenmp

#
# Standard rules
#

.c.o:
	@echo "Compiling each C source file separately ..."
	$(GCC) $(GCC_FLAGS) $<
	@echo ""

#
# Simply have our project target be a single default $(EXE) executable.
#

$(EXE):	$(OBJS)
	@echo "Linking all object modules ..."
	$(GCC) -o $(EXE) $(LD_FLAGS) $(OBJS)
	@echo ""
	@echo "Done."

${C_OBJS}:      ${HEADERS}

clean:
	@echo "Cleaning up project directory ..."
	rm -f *.o $(EXE) *.ln core a.out
	@echo ""
	@echo "Clean."

new:
	make clean
	make

