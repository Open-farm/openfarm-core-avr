include ../properties.mk

###############################################################################
# Library includes.
# 
# Eg:
# 
# -I$(BASECORE_DIR)/core-avr-ds/src
#
INC=
###############################################################################

###############################################################################
# Name of the library. This will automatically be prefixed by 'lib'.
# 
# Eg:
# 
# core-avr-data
# 
LIBNAME=
###############################################################################

###############################################################################
# All source files.
# 
# Eg:
# 
# Foo.cpp Bar.cpp
# 
SOURCES=
###############################################################################

###############################################################################
# All test source files.
# 
# Eg:
# 
# Foo.cpp Bar.cpp
# 
TEST_SOURCES=\
	test/main_core-avr-ds.cpp\
	test/linked_list_tests.cpp
###############################################################################

###############################################################################
# Archive dependencies to resolve.
# 
# Eg:
# 
# Foo.cpp Bar.cpp
#
ARCHIVE_INCLUDES=
###############################################################################

# object file directories
AVR_OBJ_DIR=build/avr/obj
x86_OBJ_DIR=build/x86/obj

# Temporary build files.
AVR_OBJS=$(addprefix $(AVR_OBJ_DIR)/, $(notdir $(SOURCES:.cpp=.o)))
x86_OBJS=$(addprefix $(x86_OBJ_DIR)/, $(notdir $(SOURCES:.cpp=.o)))
TEST_OBJS=$(addprefix $(x86_OBJ_DIR)/, $(notdir $(TEST_SOURCES:.cpp=.o)))

build/Test.exe: $(x86_OBJS) $(TEST_OBJS)
	$(x86_CC) $(INC_ARCHIVES) -o build/Test.exe $(x86_OBJS) $(TEST_OBJS) -L$(LIB_DIR)/x86 $(ARCHIVE_INCLUDES)
	@mkdir -p $(LIB_DIR)/x86

$(AVR_OBJ_DIR)/%.o: src/%.cpp
	@mkdir -p $(AVR_OBJ_DIR)
	$(AVR_CC) $(AVR_CFLAGS) $(AVR_INCLUDES) $(INC) -c $< -o $(AVR_OBJ_DIR)/$(@F)

$(x86_OBJ_DIR)/%.o: src/%.cpp
	@mkdir -p $(x86_OBJ_DIR)
	$(x86_CC) $(x86_CFLAGS) $(x86_INCLUDES) $(INC) -c $< -o $(x86_OBJ_DIR)/$(@F)

$(x86_OBJ_DIR)/%.o: test/%.cpp
	@mkdir -p $(x86_OBJ_DIR)
	$(x86_CC) $(x86_CFLAGS) $(TEST_INCLUDES) $(INC) -Isrc -c $< -o $(x86_OBJ_DIR)/$(@F)