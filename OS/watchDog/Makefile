
# make CONFIG=Debug/Release

PROJ_SRCS     =app24_7.c wlib.c
PROJ_INC_DIR  =../../utils/schdular
PROJ_OBJ_DIR  =../../../arch/linux64/obj/$(CONFIG)
PROJ_BIN_DIR  =../../../arch/linux64/bin/$(CONFIG)
PROJ_OUT      =app24_7.out
PROJ_MACROS   =
PROJ_ADD_OBJS =scheduler.o vector.o heap.o pQueueHeap.o task.o
PROJ_LIBS     =pthread
PROJ_OTHERS   =../../utils/schdular

include ../../Project.mak
