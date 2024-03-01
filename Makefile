CC := gcc
CFLAGS := -Wall -Wextra -Werror

SRCDIR := ./utils/src
BINDIR := ./utils/bin

SRCS := $(wildcard $(SRCDIR)/*.c)
EXES := $(patsubst $(SRCDIR)/%.c,$(BINDIR)/%,$(SRCS))

.PHONY: all clean

all: $(EXES)

$(BINDIR)/%: $(SRCDIR)/%.c | $(BINDIR)
    $(CC) $(CFLAGS) -o $@ $<

$(BINDIR):
    mkdir -p $@

clean:
    rm -rf $(BINDIR)
