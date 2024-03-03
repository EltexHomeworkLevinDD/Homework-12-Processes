CC := gcc
CFLAGS := -g

MAIN_DIR := interpretator
MAIN_SRC_DIR := $(MAIN_DIR)/src
MAIN_OBJ_DIR := $(MAIN_DIR)/obj
MAIN_BIN_DIR := $(MAIN_DIR)/bin
MAIN := interpretator

UTIL_DIR := utils
UTIL_SRC_DIR := $(UTIL_DIR)/src
UTIL_OBJ_DIR := $(UTIL_DIR)/obj
UTIL_BIN_DIR := $(UTIL_DIR)/bin

UTILS := showdir tog

UTIL := showdir
SRC_DIR := $(UTIL_SRC_DIR)/$(UTIL)
OBJ_DIR := $(UTIL_OBJ_DIR)/$(UTIL)
BIN_DIR := $(UTIL_BIN_DIR)
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
BIN_FILE := $(BIN_DIR)/$(UTIL)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@
$(BIN_FILE): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

UTIL := tog
SRC_DIR := $(UTIL_SRC_DIR)/$(UTIL)
OBJ_DIR := $(UTIL_OBJ_DIR)/$(UTIL)
BIN_DIR := $(UTIL_BIN_DIR)
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
BIN_FILE := $(BIN_DIR)/$(UTIL)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@
$(BIN_FILE): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: utils_all interpretator_all

utils_all: $(foreach util,$(UTILS),$(UTIL_BIN_DIR)/$(util))

SRC_DIR := $(MAIN_SRC_DIR)
OBJ_DIR := $(MAIN_OBJ_DIR)
BIN_DIR := $(MAIN_BIN_DIR)
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
BIN_FILE := $(BIN_DIR)/$(MAIN)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@
$(BIN_FILE): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

interpretator_all: $(BIN_FILE)

clean_all:
	rm -rf $(UTIL_OBJ_DIR)/*.o
	rm -rf $(UTIL_BIN_DIR)/*
	rm -rf $(MAIN_OBJ_DIR)/*.o
	rm -rf $(MAIN_BIN_DIR)/*

all: interpretator_all utils_all
#---------------------------------------------------------------------------------

# $(MAKE) - рекурсивный вызов make с переданными параметрами

# wildcard - поиск файлов по шаблону
# patsubst - замена шаблонов в списках строк $(шаблон поиска, шаблон замены, список строк), 
# работает только на всю строку с импользованием %
# subst - замена вхождений (шаблон поиска, шаблон замены, список строк)
# notdir - убирает путь перед файлом

# eval - это функция, которая говорит программе GNU Make оценить и выполнить строку в Makefile. 
# Это позволяет вам создавать или изменять правила или переменные в Makefile во время его выполнения
# здесь мы используем его для динамического создания правил Makefile на основе переменных 
# или других значений, которые мы хотим включить в наш сборочный процесс

# call - вызвать определенный макрос (или функцию) с указанными параметрами call define,$(param1)

# % - 0 и более символов в строке
# используется в конструкции подстановки шаблонов (например будет сопоставлять файлы .c с файлами .o)

# $< - первая зависимость в правиле
# $^ - все зависимости в правиле
# $$ - экранированный символ $ в шаблонных правилах 
# $@ - имя цели
# @ перед командой подавляет вызов команды
# ** - рекурсивно
# $(foreach var,list,text)
# $(addsuffix что, куда) - добавить в конец строки

# print_util_objs:
# 	@echo "kekw: $(variable)"