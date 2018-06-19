SHELL:=/bin/bash -O extglob

FLAGS = \
	-DNULL=0 \
	-o0 \
	-D__AVR32_UC3B0256__ \
	-fPIC \
	-g \
	-Werror=implicit-function-declaration \
	-Imock_hardware \
	-Imock_hardware/stubs \
	-Iansible/libavr32/src \
	-Iansible/libavr32/conf \
	-Iansible/libavr32/conf/trilogy \
	-Iansible/libavr32/src/euclidean \
	-Iansible/libavr32/src/usb/midi                                    
	
SOURCES = \
	ansible/src/main.c \
	ansible/src/ansible_grid.c \
	ansible/src/ansible_arc.c \
	ansible/src/ansible_midi.c \
	ansible/src/ansible_tt.c \
	ansible/libavr32/src/events.c \
	ansible/libavr32/src/timers.c \
	ansible/libavr32/src/monome.c \
	ansible/libavr32/src/util.c \
	ansible/libavr32/src/music.c \
	ansible/libavr32/src/arp.c \
	ansible/libavr32/src/notes.c \
	ansible/libavr32/src/random.c \
	ansible/libavr32/src/midi_common.c \
	ansible/libavr32/src/euclidean/euclidean.c \
	ansible/libavr32/src/euclidean/data.c \
	mock_hardware/adapter.c \
	mock_hardware/mock_hardware.c\
	mock_hardware/stubs/dac.c\
	mock_hardware/stubs/init_ansible.c\
	mock_hardware/stubs/i2c.c\

TARGETNAME = ../res/firmware/ansible

include ../../../arch.mk

ifeq ($(ARCH), lin)
	LDFLAGS += -shared
	TARGET = $(TARGETNAME).so
endif

ifeq ($(ARCH), mac)
	LDFLAGS += -shared -undefined dynamic_lookup
	TARGET = $(TARGETNAME).dylib
endif

ifeq ($(ARCH), win)
	LDFLAGS += -shared 
	TARGET = $(TARGETNAME).dll
endif

OBJECTS += $(patsubst %, ../build/firmware/%.o, $(SOURCES))

../build/firmware/%.c.o: %.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

all: $(TARGET)

clean:
	rm -rfv ../build/firmware 