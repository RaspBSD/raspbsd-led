#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <err.h>
#include <errno.h>
 
const int sleeptime = 300000;
const char *path = "/dev/led/beaglebone:green:heartbeat";
const char on  = '1';
const char off = '0';
int fd;
 
int main() {
	fd = open(path, O_WRONLY);
	if ( fd > 0 ) {
		while (1) {
			usleep(sleeptime);
			write(fd, &on, sizeof(on));
			usleep(sleeptime);
			write(fd, &off, sizeof(off));
		}
		close(fd);
	} else {
		err(errno, "unable to open: %s; errcode: %d\n", path, fd);
	}
 
	return 0;
}

