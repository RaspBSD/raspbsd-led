PREFIX=/usr/local

all: flash-heartbeat-led

flash-heartbeat-led: flash-heartbeat-led.c
	cc -o flash-heartbeat-led flash-heartbeat-led.c

install: flash-heartbeat-led
	install ${.ALLSRC} ${PREFIX}/sbin

clean:
	rm flash-heartbeat-led
