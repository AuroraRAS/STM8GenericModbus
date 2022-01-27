IDIR=/usr/share/sdcc/include
CC=sdcc-sdcc 
LIBS=-lstm8
CFLAGS=--out-fmt-ihx -mstm8 -I$(IDIR) -I$(shell pwd)

all:
	$(CC) -c modbus.c $(CFLAGS) $(LIBS)
	$(CC) -c main.c $(CFLAGS) $(LIBS)
	$(CC) *.rel $(CFLAGS) $(LIBS)

install:
#	stm8flash -c stlinkv2 -p stm8s105k4 -w main.ihx
	stm8flash -c stlinkv2 -p stm8s003f3 -w main.ihx

clean:
	rm -f *.asm *.ihx *.lst *.rel *.sym *.lk *.map *.rst *.eeprom
