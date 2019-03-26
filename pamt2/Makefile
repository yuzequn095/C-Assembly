#
# Makefile for CSE 30 -- PAMT2 
#

HEADERS		= pamt2.h

C_SRCS		= function1.c main.c omp_function1.c

C_OBJS		= function1.o main.o omp_function1.o

OBJS		= ${C_OBJS}

EXE		= pamt2

#
# Relevant man pages:
#
# man -M /software/common/gnu/man g++
#

GCC		= gcc

GCC_FLAGS	= -c -Wall -std=c99 -fopenmp
LD_FLAGS	= -fopenmp

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

${C_OBJS}:      $(HEADERS)

clean:
	@echo "Cleaning up project directory ..."
	rm -f *.o $(EXE) *.ln core a.out
	@echo ""
	@echo "Clean."

new:
	make clean
	make

