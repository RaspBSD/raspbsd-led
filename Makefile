all: flash-heartbeat-led

flash-heartbeat-led: flash-heartbeat-led.c
	cc -o flash-heartbeat-led flash-heartbeat-led.c

clean:
	rm flash-heartbeat-led
