PREFIX?=/usr/local
CC?=	cc

all: flash-heartbeat-led

flash-heartbeat-led: flash-heartbeat-led.c
	${CC} -Wall -Werror -o flash-heartbeat-led flash-heartbeat-led.c

install: flash-heartbeat-led
	install ${.ALLSRC} ${DESTDIR}${PREFIX}/sbin

clean:
	rm flash-heartbeat-led
