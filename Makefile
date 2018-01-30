PROGRAM = PasswordCreator
OBJS = PasswordCreator.o
SRCDIR = src/
OBJDIR = obj/
BINDIR = bin/
CC = gcc
CFLAGS = -Wall -O2

$(PROGRAM): $(OBJDIR)$(OBJS)
	$(CC) -o $(BINDIR)$(PROGRAM) $^

$(OBJDIR)PasswordCreator.o: $(SRCDIR)PasswordCreator.c
	@[ -d $(OBJDIR) ]
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	$(RM) $(OBJDIR)$(PROGRAM) $(OBJDIR)$(OBJS)
