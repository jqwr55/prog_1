COMPILER = g++
COMPILER_FLAGS = -c -I ./common -g 

SRC_FILES = $(wildcard ./week*/main*.cpp)
BIN_FILES = $(subst .cpp,,$(SRC_FILES))

COMMON_SRC_FILES = $(wildcard ./common/*.cpp)
COMMON_OBJ_FILES = $(subst ./common/,./bins/, $(subst .cpp,.o,$(COMMON_SRC_FILES)) )


define make-target-common
$(subst ./common/,./bins/, $(subst .cpp,.o,$1) ): $1
	$(COMPILER) $(COMPILER_FLAGS) -I /usr/include/FL/ $1 -o $(subst ./common/,./bins/, $(subst .cpp,.o,$1) ) `fltk-config --ldflags --use-images` -std=c++14
endef

define make-target-main
$(subst .cpp,,$1): $1
	$(COMPILER) -I ./common -I /usr/include/FL/ -g $1 ./bins/*.o -o $(subst .cpp,,$1) `fltk-config --ldflags --use-images` -std=c++14
endef

run: build
	@$(foreach element,$(BIN_FILES), echo "$(element)\n----"; $(element); echo "----\n";)

build:
	make -j6 build_common
	make -j6 build_main
	@clear
	@echo ready to run

build_main: $(COMMON_OBJ_FILES) $(BIN_FILES)
build_common: $(COMMON_OBJ_FILES)

clean:
	rm $(BIN_FILES) $(COMMON_OBJ_FILES)

$(foreach element, $(COMMON_SRC_FILES), $(eval $(call make-target-common,$(element))))
$(foreach element, $(SRC_FILES), $(eval $(call make-target-main,$(element))) )