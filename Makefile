# AVR Makefile
# #####################################
#
# Part of the uCtools project
# uctools.github.com
#
#######################################
# user configuration:
#######################################
# TARGET: name of the output file
TARGET = $(FILE)
# MCU: part number to build for
MCU = atmega16m1
# SOURCES: list of input source sources
SOURCES = $(FILE).c uart.c api.c
# INC: list of build dependencies
INC = -Isrc/
# OUTDIR: directory to use for output
OUTDIR = build
# PROGRAMMER: name of programmer
PROGRAMMER = avrispmkII
#PROGRAMMER = dragon_isp
# PORT: location of programmer
PORT = usb
# define flags
CFLAGS = -mmcu=$(MCU) -g -Os -Wall -Wunused $(INC)
ASFLAGS = -mmcu=$(MCU) -x assembler-with-cpp -Wa,-gstabs
LDFLAGS = -mmcu=$(MCU) -Wl,-Map=$(OUTDIR)/$(TARGET).map
AVRDUDE_FLAGS = -p $(MCU) -v -c $(PROGRAMMER) -P $(PORT)

#######################################
# end of user configuration
#######################################
#
#######################################
# binaries
#######################################
CC      = avr-gcc
LD      = avr-ld
AR      = avr-ar
AS      = avr-gcc
GASP    = avr-gasp
NM      = avr-nm
OBJCOPY = avr-objcopy
RM      = rm -f
MKDIR	= mkdir -p
AVRDUDE = avrdude
#######################################

# file that includes all dependancies
DEPEND = $(SOURCES:.c=.d)

# list all object files
OBJECTS = $(addprefix $(OUTDIR)/,$(SOURCES:.c=.o))

# default: build all
all: $(OUTDIR)/$(TARGET).elf $(OUTDIR)/$(TARGET).hex $(OUTDIR)/$(TARGET).srec

$(OUTDIR)/%.srec: $(OUTDIR)/%.elf
	$(OBJCOPY) -j .text -j .data -O srec $< $@

$(OUTDIR)/%.elf: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) $(LIBS) -o $@

$(OUTDIR)/%.hex: $(OUTDIR)/%.elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

$(OUTDIR)/%.o: src/%.c | $(OUTDIR)
	$(CC) -c $(CFLAGS) -o $@ $<

%.lst: %.c
	$(CC) -c $(ASFLAGS) -Wa,-anlhd $< > $@

# create the output directory
$(OUTDIR):
	$(MKDIR) $(OUTDIR)

# download to mcu flash
flash: $(OUTDIR)/$(TARGET).hex
	$(AVRDUDE) $(AVRDUDE_FLAGS) -Uflash:w:$<

# verify mcu flash
verify: $(OUTDIR)/$(TARGET).hex
	$(AVRDUDE) $(AVRDUDE_FLAGS) -U flash:v:$<

clean:
	-$(RM) -r $(OUTDIR)/*

#these are default fuses (H:FF, E:DF, L:62)
#changed fuses to (H:FF, E:DF, L:22) to output clk on pin32
#command is:  sudo avrdude -p atmega16m1 -v -c avrispmkII -P usb -U lfuse:w:0x22:m -U hfuse:w:0xff:m -U efuse:w:0xdf:m


#ArduIMU default fuses are:
#avrdude: safemode: Fuses OK (H:05, E:DA, L:FF)

sudo avrdude -p atmega328p -v -c avrispmkII -P usb -U lfuse:w:0xff:m -U hfuse:w:0x05:m -U efuse:w:0xda:m

#We changed fuses to: sudo avrdude -p atmega328p -v -c avrispmkII -P usb -U lfuse:w:0xa0:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m
