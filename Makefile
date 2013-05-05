
CCPREFIX=arm-none-eabi-
CC=$(CCPREFIX)gcc
AR=$(CCPREFIX)ar

SRC_DIR=./src

# targets with no dependencies
NODEPS := clean

# http://stackoverflow.com/a/313787
# add .d to Make's recognised suffixes
SUFFIXES += .d

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
	#@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<	

sneaky.a: $(OBJS)
	$(AR) r $< $@

all: sneaky.a

clean:
	rm -f $(OBJS) $(DEPFILES)

.PHONY: clean

