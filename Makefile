VPATH			:= 	./src , ./src/tests
CFLAGS		:= 	-lm -std=c99
OBJDIR			:= 	./obj
BINDIR			:= 	./bin
ALL_OBJ		:=		$(OBJDIR)/input.o $(OBJDIR)/grid.o $(OBJDIR)/actions.o $(OBJDIR)/saving.o $(OBJDIR)/scores.o $(OBJDIR)/gameloop.o

# Main Program:
minesweeper: main.c $(ALL_OBJ)
	gcc $(CFLAGS) $^ -o $(BINDIR)/minesweeper

# All Tests:
tests: gridtest actionstest savingtest scorestest gamelooptest

# Grid Test
gridtest: $(OBJDIR)/gridtest.o $(OBJDIR)/grid.o
	gcc $(CFLAGS) $^ -o $(BINDIR)/gridtest
$(OBJDIR)/gridtest.o: gridtest.c
	gcc -c $< -o $@

# Actions Test
actionstest: $(OBJDIR)/actionstest.o $(OBJDIR)/grid.o $(OBJDIR)/actions.o
	gcc $(CFLAGS) $^ -o $(BINDIR)/actionstest
$(OBJDIR)/actionstest.o: actionstest.c
	gcc -c $< -o $@

# Game Loop Test
gamelooptest: $(OBJDIR)/gamelooptest.o $(ALL_OBJ)
	gcc $(CFLAGS) $^ -o $(BINDIR)/gamelooptest
$(OBJDIR)/gamelooptest.o: gamelooptest.c
	gcc -c $< -o $@

# Saving Test
savingtest: $(OBJDIR)/savingtest.o $(OBJDIR)/grid.o $(OBJDIR)/saving.o
	gcc $(CFLAGS) $^ -o $(BINDIR)/savingtest
$(OBJDIR)/savingtest.o: savingtest.c
	gcc -c $< -o $@

# Scores Test
scorestest: $(OBJDIR)/scorestest.o $(OBJDIR)/grid.o $(OBJDIR)/scores.o
	gcc $(CFLAGS) $^ -o $(BINDIR)/scorestest
$(OBJDIR)/scorestest.o: scorestest.c
	gcc -c $< -o $@
	
# Module Objects
$(OBJDIR)/%.o: %.c %.h
	gcc $(CFLAGS) -c $< -o $@

