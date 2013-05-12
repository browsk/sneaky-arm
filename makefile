
#ARCH=x86

ifeq ($(ARCH),arm)

CCPREFIX=arm-none-eabi-
CC=$(CCPREFIX)gcc
AR=$(CCPREFIX)ar
AS=$(CCPREFIX)as

endif

SRC_DIR=./src

# targets with no dependencies
NODEPS := clean

CFLAGS := $(CFLAGS) -Wall -Werror -Isrc

# http://stackoverflow.com/a/313787
# add .d to Make's recognised suffixes
SUFFIXES += .d

all: sneaky.a check_sneaky

SOURCES := $(shell find src -name "*.c")
DEPFILES := $(patsubst %.c,%.d,$(SOURCES))
OBJS := $(patsubst %.c,%.o,$(SOURCES))
LSTFILES := $(patsubst %c,%lst,$(SOURCES))
ASMFILES := $(patsubst %c,%s,$(SOURCES))

TESTSOURCES := $(shell find tests -name "*.c")
TESTDEPFILES := $(patsubst %.c,%.d,$(TESTSOURCES))
TESTOBJS := $(patsubst %.c,%.o,$(TESTSOURCES))



# don't create deps when cleaning
ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
	-include $(DEPFILES)
endif

%.s: %.c
	$(CC) $(CFLAGS) -fverbose-asm -Wa,-a,-ad -o $@ -S $<	

%.lst: %.s
	$(AS) -alhnd $< > $@

%.d: %.c
	$(CC) $(CFLAGS) -MM -MT '$(patsubst src/%.c,src/%.o,$<)' $< -MF $@

%.o: %.c %.d %.h
	$(CC) $(CFLAGS) -o $@ -c $<	

sneaky.a: $(OBJS) makefile
	$(AR) r $@ $<

check_sneaky: $(TESTOBJS) sneaky.a
	$(CC) $(LDFLAGS) -o $@ $^ -lcheck

clean:
	rm -f $(OBJS) $(DEPFILES) $(ASMFILES) $(LSTFILES) $(TESTOBJS) $(TESTDEPFILES)

.PHONY: clean

