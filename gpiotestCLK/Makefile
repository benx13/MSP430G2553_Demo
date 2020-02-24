# Makefile

MCU = msp430g2553
INCLUDE_DIR = $$MSP_HOME/msp430_gcc/include/

IFLAGS = -I $(INCLUDE_DIR)
LFLAGS = -L $(INCLUDE_DIR)

CC = msp430-gcc

CFLAGS = -Os -Wall -g -mmcu=$(MCU)

OBJS = main.o


all: $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) -o main.elf $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $<

clean:
	rm -fr main.elf $(OBJS)
