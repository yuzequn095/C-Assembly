#
# Makefile template for CSE 30 -- debug1
#

#
# You need to change these next lines for each assignment
#

HEADERS		= debug.h

C_SRCS		= main.c

ASM_SRCS	= reverse.s swapChars.s findEnd.s

C_OBJS		= main.o

ASM_OBJS	= reverse.o swapChars.o findEnd.o

OBJS		= $(C_OBJS) $(ASM_OBJS)

EXE		= reverseString

#
# You should not need to change anything below this line
#

#
# Relevant man pages:
#
# man gcc
# man as
# man lint
#

GCC		= gcc
ASM		= $(GCC)
RM		= rm

DEBUG_FLAGS	= -g
GCC_FLAGS	= -c $(DEBUG_FLAGS) -std=c99 -pedantic -Wall -D__EXTENSIONS__
ASM_FLAGS	= -c -g
LD_FLAGS	= -g -Wall

#
# Standard rules
#

.s.o:
	@echo "Assembling each assembly source file separately ..."
	$(ASM) $(ASM_FLAGS) $<
	@echo ""

.c.o:
	@echo "Compiling each C source file separately ..."
	$(GCC) $(GCC_FLAGS) $<
	@echo ""

#
# Simply have our project target be a single default $(EXE) executable.
#

$(EXE):	$(OBJS)
	@echo "Linking all object modules ..."
	$(GCC) $(LD_FLAGS) -o $(EXE) $(OBJS)
	@echo ""
	@echo "Done."

${C_OBJS}: ${HEADERS}


clean:
	@echo "Cleaning up project directory ..."
	$(RM) -f *.o $(EXE) core a.out
	@echo ""
	@echo "Clean."

new:
	make clean
	make
