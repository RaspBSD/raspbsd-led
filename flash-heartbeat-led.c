#include <unistd.h>
#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
 
int timetoabort = 0;
const int sleeptime = 300000;
const char *leddevice = "/dev/led/beaglebone:green:heartbeat";
const char *pidfile = "/var/run/flash-heartbeat-led.pid";
const char on  = '1';
const char off = '0';

static void
cleanup(int sig __unused) {
	timetoabort = 1;
}

int
flashloop(FILE *ledfp) {

	if (signal(SIGINT, cleanup) == SIG_ERR) {
		errx(errno, "Unable register signal handler");
	}
	if (signal(SIGTERM, cleanup) == SIG_ERR) {
		errx(errno, "Unable register signal handler");
	}

	while (timetoabort == 0) {
		usleep(sleeptime);
		fprintf(ledfp, "%s", &on);
		fflush(ledfp);
		usleep(sleeptime);
		fprintf(ledfp, "%s", &off);
		fflush(ledfp);
	}

	int retcode = 0;
	retcode = fclose(ledfp);
	if (retcode != 0) {
		err(errno, "Unable to close LED device");
	}
	if (unlink(pidfile) != 0) {
		errx(errno, "Unable to remove pidfile: %s", pidfile);
	}
	return (retcode);
}

int
main(void) {
	FILE *pidfp;
	FILE *ledfp;

	// Open PID file
	pidfp = fopen(pidfile, "w");
	if (pidfp == NULL) {
		errx(errno, "Unable to open: %s", pidfile);
	}

	// Open the LED device
	ledfp = fopen(leddevice, "w");
	if (ledfp == NULL) {
		errx(errno, "Unable to open: %s", leddevice);
	}

	int pid = fork();
	if (pid < 0) {
		errx(errno, "Unable to fork");
	}
	if (pid > 0) {
		printf("PID: %d\n", pid);
		fprintf(pidfp, "%d\n", pid);
		fclose(pidfp);
		return(0);
	}
	return flashloop(ledfp);
}
