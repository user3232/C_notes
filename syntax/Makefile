
# yoyo Make

COMP := gcc

# STD := std=c90
STD := -std=c11
WARNINGS := -pedantic-errors -Werror
FLAGS :=
FLAGS += $(STD)
FLAGS += $(WARNINGS)

# command to create dir if not exists
MKDIR_P := mkdir -p
# directories to create
BIN_DIR := ./bin
# following runs function every time
# this makefile is parsed.
# It makes neccessary directories if they not exists.
# output of command is not pased to makefile because
# of info function.
$(info $(shell mkdir -p $(BIN_DIR)))

# alternatively use targets:
# .PHONY : directories
# directories : $(BIN_DIR)
# $(BIN_DIR):
#    ${MKDIR_P} $(BIN_DIR)


to_compile_list = c_synt.c polymorphisms.c array_sum.c alignment.c
executables_names = $(basename $(to_compile_list))
# executables = $(addprefix $(BIN_DIR)/, $(executable_names))


all : $(executables_names)

# executable names are make targets
# one can use:
# > make array_sum
$(executables_names) : % : $(BIN_DIR)/%
	echo "target: $@ , sources: $^"

$(BIN_DIR)/% : %.c
	echo "target: $@ , sources: $^"
	$(COMP) $(FLAGS) -o $@ $<

# this actually builds separate programs
# (and generates multiple rules)
# see:
# https://makefiletutorial.com/#static-pattern-rules
#$(BIN_DIR)/% : %.c
#	$(COMP) $(FLAGS) -o $(BIN_DIR)/$@ $<


test : $(BIN_DIR)/main
	$(BIN_DIR)/main yoyo








# $@ is (effective) target name
# $< is (effective, may come from implicit rule) 
#    first dependance name
# $? are (effective) all dependencies names newer than target
# $^ are (effective) all dependencies names (unique)
# $+ are (effective) all dependencies names (possible duplicates)
# 
# main : c_synt.c
# 	$(COMP) $(FLAGS) -o $(OUT_DIR)/main $^
# 
# array_sum_example : array_sum.c
# 	$(COMP) $(FLAGS) -o $(OUT_DIR)/array_sum_example $^
# 
# alignment : alignment.c
# 	$(COMP) $(FLAGS) -o $(OUT_DIR)/alignment $^






