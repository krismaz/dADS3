CC = clang++
LINKER = clang++ -o
CFLAGS = -Wall -std=c++11 -g

SRCDIR = src
OBJDIR = obj
BINDIR = bin

TARGET = project1

LFLAGS =
LIBS =

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)


OBJS = $(SRCS:.cpp=.o)

$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(LFLAGS) $(OBJECTS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CC) $(CFLAGS) $(LIBS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONEY: clean
clean:
	@rm -f $(OBJECTS)
	@echo "Cleanup complete!"

.PHONEY: remove
remove: clean
	@rm $(BINDIR)/$(TARGET)
	@echo "Executable removed!"
