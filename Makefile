IDIR=/usr/share/sdcc/include
CC=sdcc-sdcc 
LIBS=-lstm8
CFLAGS=--out-fmt-ihx -mstm8 -I$(IDIR) -I$(shell pwd)

all:
	$(CC) -c modbus.c $(CFLAGS) $(LIBS)
	$(CC) -c main.c $(CFLAGS) $(LIBS)
	$(CC) *.rel $(CFLAGS) $(LIBS)

test: crc16_test
	./crc16_test

crc16_test: modbus.c crc16_test.c
	gcc -std=c99 -Wall -Wextra -I. crc16_test.c modbus.c -o crc16_test

install:
		#	stm8flash -c stlinkv2 -p stm8s105k4 -w main.ihx
		stm8flash -c stlinkv2 -p stm8s003f3 -w main.ihx

clean:
	rm -f *.asm *.ihx *.lst *.rel *.sym *.lk *.map *.rst *.eeprom crc16_test
