#!/bin/sh

MODBUS_ADDR=1
fMASTER=2000000
baud=9600

function ftoi()
{
	local p5=$(echo "scale=0;$1/1" | bc -l).5
	if [ $(expr "$1" "<" "$p5") = 1 ]; then
		echo "scale=0;$1/1" | bc -l
	else
		echo "scale=0;1+$1/1" | bc -l
	fi
}

UART_DIV=$(echo "$fMASTER/$baud" | bc -l)
UART_DIV=$(ftoi "$UART_DIV")
UART_BRR1=$(($UART_DIV>>4 &0xff))
UART_BRR2=$((($UART_DIV>>8 &0xf0) + ($UART_DIV &0x0f)))

if [ $(expr "$baud" "<=" "19200") = 1 ];then
	frame_INV=$(echo "(11*1000000/$baud)*3.5" | bc -l)
else
	frame_INV=1750
fi

#TIM_PSCR <= 7
#TIM_ARR < 256
#TIM_ARR * (1MHz/fMASTER) * 2^TIM_PSCR = frame_INV = 4010us (in 9600 baud)
TIM_PSCR=$(echo "l($frame_INV*($fMASTER/1000000)/255)/l(2)" | bc -l)
TIM_PSCR=$(echo "scale=0;1+$TIM_PSCR/1" | bc -l)

TIM_ARR=$(echo "$frame_INV*($fMASTER/1000000)/e($TIM_PSCR*l(2))" | bc -l)
TIM_ARR=$(ftoi "$TIM_ARR")

printf "UART_DIV is:  0x%04x\n" "$(($UART_DIV &0xffff))"

printf "UART_BRR1 is: 0x%02x\n" "$UART_BRR1"
printf "UART_BRR2 is: 0x%02x\n" "$UART_BRR2"
echo "ideal frame_INV is: "$frame_INV"us"
echo "our frame_INV is:   $(echo "$TIM_ARR * (1000000/$fMASTER) * 2^$TIM_PSCR" | bc -l)us"

echo "TIM_PSCR is: $TIM_PSCR"
echo "TIM_ARR is:  $TIM_ARR"

printf "%b" "$(printf "\\\x%02x\\\x%02x\\\x%02x\\\x%02x\\\x%02x" "$MODBUS_ADDR" "$UART_BRR1" "$UART_BRR2" "$TIM_PSCR" "$TIM_ARR")" > env.eeprom

#stm8flash -c stlinkv2 -p stm8s105k4 -s eeprom -w "env.eeprom"
stm8flash -c stlinkv2 -p stm8s003f3 -s eeprom -w "env.eeprom"
echo "OK"