#
# Makefile template for CSE 30 -- debug2
#

#
# You need to change these next lines for each assignment
#

HEADERS		= debug2.h

C_SRCS		= debug2.c parsePlay.c checkWin.c printBoard.c

ASM_SRCS	= checkMove.s 

C_OBJS		= debug2.o parsePlay.o checkWin.o printBoard.o

ASM_OBJS	= checkMove.o

OBJS		= ${C_OBJS} ${ASM_OBJS}

EXE		= debug2

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

GCC_FLAGS	= -c -g -Wall -D__EXTENSIONS__ -std=c99
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
	$(GCC) -o $(EXE) $(LD_FLAGS) $(OBJS)
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
