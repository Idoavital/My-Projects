
ECHO      = 0
ECHOON    = $(ECHO:0=@)
ECHO_FLAG = $(ECHOON:1=)

# Set the default target (before any external file import)
default_target: all

MAKE = make
CC   = gcc
CPP  = g++
AR   = ar

CONFIG     = Debug
CC_INCLUDE = $(PROJ_INC_DIR:%=-I%)
CC_DEFINES = $(PROJ_MACROS:%=-D%)
CFLAGS     = -ansi -pedantic -Wall -Werror
#CPPFLAGS   = -ansi -pedantic -Wall
LDFLAGS    = -L$(PROJ_BIN_DIR)

ifeq ($(CONFIG), Debug)
CFLAGS += -g -DDEBUG -UNDEBUG
else
CFLAGS += -O2 -UDEBUG -DNDEBUG
endif

ifeq ($(suffix $(PROJ_OUT)), .out)
PROJ_OBJS = $(PROJ_SRCS:%.c=$(PROJ_OBJ_DIR)/%.o)
else
LIB_OBJS = $(filter-out $(wildcard $(PROJ_OBJ_DIR)/*_test.o), $(wildcard $(PROJ_OBJ_DIR)/*.o))
endif

ifneq ($(MAKECMDGOALS), clean)
-include $(PROJ_OBJS:.o=.d)
endif

.DELETE_ON_ERROR:

$(PROJ_OBJ_DIR)/%.d $(PROJ_OBJ_DIR)/%.o: %.c
	@echo Creating dependencies and object files for $<
	$(ECHO_FLAG)$(CC) $(CFLAGS) $(CC_DEFINES) $(CC_INCLUDE) -MMD -c -o $(@D)/$(*F).o $<

#$(PROJ_OBJ_DIR)/%.d $(PROJ_OBJ_DIR)/%.obj: %.cpp
#	@echo Creating dependencies and object files for $<
#	$(ECHO_FLAG)$(CPP) $(CPPFLAGS) -MMD -c -o $(@D)/$(*F).obj $<

##################################################################
#  Rules  --------------------------------------------------------
##################################################################

all: $(PROJ_OTHERS) $(PROJ_BIN_DIR)/$(PROJ_OUT)
	@echo All targets made

$(PROJ_BIN_DIR)/$(basename $(PROJ_OUT)).out: $(PROJ_OBJS)
	@echo Creating application $(@F)
	$(ECHO_FLAG)$(CC) $(PROJ_OBJS) $(PROJ_ADD_OBJS:%=$(PROJ_OBJ_DIR)/%) $(LDFLAGS) $(PROJ_LIBS:%=-l%) -o $(@)

$(PROJ_BIN_DIR)/$(basename $(PROJ_OUT)).a: $(LIB_OBJS)
	@echo Creating library $(@F)
	$(ECHO_FLAG)$(AR) -crs $(@) $(LIB_OBJS)

clean: $(PROJ_OTHERS)
	@echo Deleting dependencies and object files
	$(ECHO_FLAG)if [ ! -d "$(PROJ_OBJ_DIR)" ]; then \
		mkdir $(PROJ_OBJ_DIR); fi
	$(ECHO_FLAG)if [ ! -d "$(PROJ_BIN_DIR)" ]; then \
		mkdir $(PROJ_BIN_DIR); fi
	$(ECHO_FLAG)rm -f $(PROJ_OBJS) $(PROJ_OBJS:.o=.d) $(PROJ_BIN_DIR)/$(PROJ_OUT)

.PHONY: $(PROJ_OTHERS)
$(PROJ_OTHERS):
	$(ECHO_FLAG)$(MAKE) -C $@ $(MAKECMDGOALS) CONFIG=$(CONFIG) ECHO=$(ECHO)
