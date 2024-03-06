TARGET			= 3DViewer_2.0
TEST_TARGET		= Test_3DViewer_2.0

OS				=	$(shell uname -s)
OPEN_CMD		=
CC				=
LEAK_CHECK		=
GCOV_STR_1		=
GCOV_STR_2		=
IGNORE_FLAG		=

ifeq ($(OS), Linux)
	CC			=	g++
	LEAK_CHECK	=	valgrind --leak-check=full
	OPEN_CMD 	=	xdg-open
	GCOV_STR_1	=	"`pwd`/3DViewer/source/model/model.cc"
	GCOV_STR_2	=	"`pwd`/3DViewer/source/model/model.h"
else ifeq ($(OS), Darwin)
	CC			=	gcc -lstdc++
	LEAK_CHECK	=	leaks --atExit --
	OPEN_CMD	=	open
	GCOV_STR_1	=	"3DViewer/source/model/model.cc"
	GCOV_STR_2	=	"3DViewer/source/model/model.h"
	IGNORE_FLAG	= 	--ignore-errors mismatch,mismatch
endif

LDFLAGS			=	-std=c++17 -Wall -Werror -Wextra
GTEST_FLAGS		=	-lgtest -lgtest_main
GCOV_FLAGS		=	-fprofile-arcs -ftest-coverage
GCOV_DIR		=	gcov/

RM				=	rm -rf

VPATH			= \
	3DViewer/source/controller \
	3DViewer/source/model \
	3DViewer/tests \

TEST_OBJ_DIR	=	3DViewer/obj_test/

TEST_HEADER		= \
	controller.h \
	command.h \
	model.h \
	model_parser.h \

TEST_SRC		= \
	controller.cc \
	command.cc \
	model.cc \
	model_parser.cc \
	tests.cc \

TEST_OBJ		=	$(TEST_SRC:%.cc=$(TEST_OBJ_DIR)%.o)

HTML_DIR		=	html/
DOC_DIR			=	3DViewer/doc/
SRC_DOC			=	$(DOC_DIR)README.md 3DViewer/source/

.PHONY: all install uninstall clean dvi dist tests gcov_report

all: install

install:
	@cd 3DViewer && qmake6 "TARGET=$(TARGET)" 3DViewer.pro
	@$(MAKE) -C ./3DViewer

uninstall:
	if [ -f 3DViewer/Makefile ]; then  $(MAKE) -C ./3DViewer distclean ; fi;
	$(RM) $(TEST_TARGET)
	$(MAKE) clean_2
	$(RM) $(DOC_DIR)$(HTML_DIR)
	$(RM) settings.ini
	$(RM) report

clean:
	@if [ -f 3DViewer/Makefile ]; then $(MAKE) -C ./3DViewer clean ; fi;
	@$(MAKE) clean_2

clean_2:
	$(RM) 3DViewer/obj
	$(RM) 3DViewer/moc
	$(RM) 3DViewer/.qm
	$(RM) 3DViewer/.qmake.stash
	$(RM) 3DViewer/qmake_qmake_qm_files.qrc
	$(RM) $(TEST_OBJ_DIR)
	$(RM) $(GCOV_DIR)
	$(RM) $(DOC_DIR)doxyfile.inc
	$(RM) $(TEST_TARGET)
	$(RM) report

$(DOC_DIR)doxyfile.inc:	../../Makefile
	@echo INPUT = $(SRC_DOC) > $(DOC_DIR)doxyfile.inc
	@echo FILE_PATTERNS = *.md *.h >> $(DOC_DIR)doxyfile.inc
	@echo OUTPUT_DIRECTORY = $(DOC_DIR) >> $(DOC_DIR)doxyfile.inc
	@echo USE_MDFILE_AS_MAINPAGE = $(DOC_DIR)README.md >> $(DOC_DIR)doxyfile.inc
	@echo QUIET = YES >> $(DOC_DIR)doxyfile.inc
	@echo HTML_OUTPUT = $(HTML_DIR) >> $(DOC_DIR)doxyfile.inc
	@echo RECURSIVE = YES >> $(DOC_DIR)doxyfile.inc

dvi:	$(DOC_DIR)doxyfile.inc
	@doxygen $(DOC_DIR)Doxyfile.mk
	@$(OPEN_CMD) $(DOC_DIR)$(HTML_DIR)index.html

dist:
	$(shell mkdir 3DViewer-2.0)
	$(shell cp -r 3DViewer 3DViewer-2.0)
	$(shell cp Makefile 3DViewer-2.0)
	$(MAKE) -C 3DViewer-2.0 uninstall
	$(shell tar -czf 3DViewer-2.0.tar 3DViewer-2.0)
	@$(RM) 3DViewer-2.0

$(TEST_OBJ):	$(TEST_HEADER)

$(TEST_OBJ_DIR)%.o:	%.cc
	@mkdir -p $(TEST_OBJ_DIR)
	@$(CC) $(LDFLAGS) $(GCOV_FLAGS) -c $< -o $@

$(TEST_TARGET):	$(TEST_OBJ)
	@$(CC) $(LDFLAGS) $(GCOV_FLAGS) $(TEST_OBJ) $(GTEST_FLAGS) -o $(TEST_TARGET)
	@echo "Compiled $(TEST_TARGET) successfully!"

tests:	$(TEST_TARGET)
	$(LEAK_CHECK) ./$(TEST_TARGET)

gcov_report:	$(TEST_TARGET)
	@mkdir -p $(GCOV_DIR)
	@./$(TEST_TARGET)
	@lcov -b . -c -d $(TEST_OBJ_DIR) $(IGNORE_FLAG) -o $(GCOV_DIR)s21_test.info
	@lcov -e $(GCOV_DIR)s21_test.info $(GCOV_STR_1) $(GCOV_STR_2) -o $(GCOV_DIR)s21_test_filtered.info
	@genhtml -o report $(GCOV_DIR)s21_test_filtered.info
	@$(OPEN_CMD) report/index.html

docker_alpine: clean
	cd docker_alpine && chmod +x run.sh && ./run.sh

code_style :
	clang-format -n --style=google 3DViewer/source/*.cc 3DViewer/source/*/*.cc 3DViewer/source/*/*.h 3DViewer/tests/*.cc

code_style_refactor :
	clang-format -i --style=google 3DViewer/source/*.cc 3DViewer/source/*/*.cc 3DViewer/source/*/*.h 3DViewer/tests/*.cc
