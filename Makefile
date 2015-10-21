PREFIX?=/usr/local
CC?=	cc

all: flash-heartbeat-led

flash-heartbeat-led: flash-heartbeat-led.c
	${CC} -o flash-heartbeat-led flash-heartbeat-led.c

install: flash-heartbeat-led
	install ${.ALLSRC} ${PREFIX}/sbin

clean:
	rm flash-heartbeat-led
