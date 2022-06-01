MAKE_FILE = ./makefile

COMPILER = g++
COMPILER_FLAGS = -c -fno-elide-constructors -I ./common -g

CXX_SRC_FILES = $(wildcard ./week*/main*.cpp) ./test/main.cpp ./test/vector_006.cpp
CXX_BIN_FILES = $(subst .cpp,,$(CXX_SRC_FILES))

C_SRC_FILES = $(wildcard ./week*/*.c)
C_BIN_FILES = $(subst .c,,$(C_SRC_FILES))

COMMON_SRC_FILES = $(wildcard ./common/*.cpp)
COMMON_OBJ_FILES = $(subst ./common/,./bins/, $(subst .cpp,.o,$(COMMON_SRC_FILES)) )

define make-target-common
$(subst ./common/,./bins/, $(subst .cpp,.o,$1) ): $1
	$(COMPILER) $(COMPILER_FLAGS) -I /usr/include/FL/ $1 -o $(subst ./common/,./bins/, $(subst .cpp,.o,$1) ) `fltk-config --ldflags --use-images` -std=c++14
endef

define make-target-main
$(subst .cpp,,$1): $1 $(MAKE_FILE)
	$(COMPILER) -I ./common -I /usr/include/FL/ -g $1 ./bins/*.o -o $(subst .cpp,,$1) `fltk-config --ldflags --use-images` -std=c++14
endef

define make-target-main-c
$(subst .c,,$1): $1 $(MAKE_FILE)
	$(COMPILER) -g $1 -o $(subst .c,,$1)
endef

run: build
	@$(foreach element,$(BIN_FILES), echo "$(element)\n----"; $(element); echo "----\n";)

./bins:
	mkdir bins

build: ./bins
	make -j6 build_common
	make -j6 build_main
	@clear
	@echo ready to run

build_main: $(COMMON_OBJ_FILES) $(CXX_BIN_FILES) $(C_BIN_FILES) $(MAKE_FILE)
build_common: $(COMMON_OBJ_FILES) $(MAKE_FILE)

purge:
	rm $(CXX_BIN_FILES) $(C_BIN_FILES) $(COMMON_OBJ_FILES)

$(foreach element, $(COMMON_SRC_FILES), $(eval $(call make-target-common,$(element))))
$(foreach element, $(CXX_SRC_FILES), $(eval $(call make-target-main,$(element))) )
$(foreach element, $(C_SRC_FILES), $(eval $(call make-target-main-c,$(element))) )