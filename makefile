
ARCH=x86

ifeq ($(ARCH),arm)

CCPREFIX=arm-none-eabi-
CC=$(CCPREFIX)gcc
AR=$(CCPREFIX)ar

endif

SRC_DIR=./src

# targets with no dependencies
NODEPS := clean

# http://stackoverflow.com/a/313787
# add .d to Make's recognised suffixes
SUFFIXES += .d

all: sneaky.a

SOURCES := $(shell find src -name "*.c")
DEPFILES := $(patsubst %.c,%.d,$(SOURCES))
OBJS := $(patsubst %.c,%.o,$(SOURCES))


# don't create deps when cleaning
ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
	-include $(DEPFILES)
endif


src/%.d: src/%.c
	$(CC) $(CFLAGS) -MM -MT '$(patsubst src/%.c,src/%.o,$<)' $< -MF $@

src/%.o: src/%.c src/%.d src/%.h
	$(CC) $(CFLAGS) -o $@ -c $<	

sneaky.a: $(OBJS)
	$(AR) r $@ $<

clean:
	rm -f $(OBJS) $(DEPFILES)

.PHONY: clean

