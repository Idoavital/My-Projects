
# make CONFIG=Debug/Release

PROJ_SRCS     =testProdCons.c
PROJ_INC_DIR  =../../utils/DList
PROJ_OBJ_DIR  =../../../arch/linux64/obj/$(CONFIG)
PROJ_BIN_DIR  =../../../arch/linux64/bin/$(CONFIG)
PROJ_OUT      =testProdCons.out
PROJ_MACROS   =XOR _BSD_SOURCE
PROJ_ADD_OBJS =DList.o
PROJ_LIBS     =pthread
PROJ_OTHERS   =../../utils/DList

include ../../Project.mak
