CC              = gcc
CCLINK          = g++
LIBS            =
CCOPTIONS       = -Wall -pedantic -std=gnu17 -g
LDOPTIONS       =

BUILD_DIR       = build

TEST    = test_minesweeper
PROGRAM = minesweeper

COMMON_HDRS      = config.h
LIBRARY_FILES    = ms_visualizer shortcut
ASSIGNMENT_HDRS  = general.h 
ASSIGNMENT_FILES = ms_board ms_cell ms_game ms_ui_utils
MAIN_DRIVER      = ms_main_driver
TEST_DRIVER      = ms_test_driver

LIBRARY_H        = $(addsuffix .h, $(LIBRARY_FILES))
ASSIGNMENT_H     = $(addsuffix .h, $(ASSIGNMENT_FILES)) $(ASSIGNMENT_HDRS)
ASSIGNMENT_C     = $(addsuffix .c, $(ASSIGNMENT_FILES)) $(MAIN_DRIVER).c

HDRS			 = $(ASSIGNEMT_H) $(SHARED_HDRS) $(COMMON_HDRS) $(LIBRARY_H)
TESTOBJECT       = $(addprefix $(BUILD_DIR)/, $(TEST_DRIVER).o)
MAINOBJECT       = $(addprefix $(BUILD_DIR)/, $(MAIN_DRIVER).o)
LIBRARY_OBJS     = $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(LIBRARY_FILES)))
TEST_OBJS        = $(addprefix $(BUILD_DIR)/, $(addprefix test_, $(addsuffix .o, $(ASSIGNMENT_FILES))))
MAIN_OBJ         = $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(ASSIGNMENT_FILES)))
OBJS             = $(LIBRARY_OBJS) $(MAIN_OBJ) $(TEST_OBJS)

DOXY             = doxygen

all: $(PROGRAM)
	./$(PROGRAM)

$(TEST): $(BUILD_DIR) $(OBJS) $(TESTOBJECT)
	$(CCLINK) -o $@ $(LDOPTIONS) $(OBJS) $(TESTOBJECT)

$(PROGRAM): $(BUILD_DIR) $(OBJS) $(MAINOBJECT)
	$(CCLINK) -o $@ $(LDOPTIONS) $(OBJS) $(MAINOBJECT)

.PHONY: clean cleanall doxy test setsample setassignment definesample defineassignment assignmentfolder

clean:
	rm -f $(PROGRAM) $(TEST) $(TESTOBJECT) $(MAINOBJECT) $(OBJS)
	rm -rf $(BUILD_DIR)
	rm -f *.o

cleanall: clean
	rm -f index.html
	rm -rf html


doxy:
	$(DOXY)
	rm -f index.html
	ln -s html/index.html index.html

test: $(TEST)
	./$(TEST)

cleantest: clean
	clear
	make test

$(BUILD_DIR): 
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CCOPTIONS) -c -o $@ $<

#sets project as sample solution
setsample:
	$(foreach name, $(ASSIGNMENT_H) $(ASSIGNMENT_C), cp $(name).sample $(name);)

#sets project as assignment
setassignment:
	$(foreach name, $(ASSIGNMENT_H) $(ASSIGNMENT_C), cp $(name).assignment $(name);)

# defines current state of project as sample solution
definesample:
	$(foreach name, $(ASSIGNMENT_H) $(ASSIGNMENT_C), cp $(name) $(name).sample;)

# defines current sate of project as assignment
defineassignment :
	$(foreach name, $(ASSIGNMENT_H) $(ASSIGNMENT_C), cp $(name) $(name).assignment;)

# creates a folder which can serve as a publishable assignment
assignmentfolder:
	make setassignment
	make doxy
	rm -rf ../assignment
	mkdir ../assignment
	cp -R * ../assignment
	cp .gitignore ../assignment
	rm ../assignment/*.sample
	rm ../assignment/*.assignment
	make cleanall
