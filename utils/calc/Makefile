
# make CONFIG=Debug/Release

PROJ_SRCS     = calc.c testCalc.c
PROJ_INC_DIR  = ../stack
PROJ_OBJ_DIR  = ../../../arch/linux64/obj/$(CONFIG)
PROJ_BIN_DIR  = ../../../arch/linux64/bin/$(CONFIG)
PROJ_OUT      = testCalc.out
PROJ_MACROS   = _BSD_SOURCE
PROJ_ADD_OBJS = stack.o
PROJ_LIBS     = m
PROJ_OTHERS   = ../stack

include ../../Project.mak
