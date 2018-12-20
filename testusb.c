#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#define USB_NAME "/dev/skel0"

int main(int argc,char **argv) {
	int fd  = -1;
	int ret = -1;
	int i = 0;
	unsigned char read_data[16] = {0};
	unsigned char write_data[16] = {0};

	memset (read_data, '0', 16);
	memset (write_data, 'B', 16);

	fd = open (USB_NAME, O_RDWR);
	if (fd < 0) {
		perror ("open");
		return -1;
	}
	printf ("usb open success. \n");

	ret = write (fd, write_data, 16);
	if (ret < 0) {
		perror ("write");
		return -1;
	}
	printf ("write data: \n");
	for (i = 0; i < 16; ++i) {
		printf ("%.2x ", write_data[i]);
	}
	printf ("\n");

	printf ("before read data: \n");
	for (i = 0; i < 16; ++i) {
		printf ("%.2x ", read_data[i]);
	}
	printf ("\n");

	ret = read (fd, read_data, 16);
	if (ret < 0) {
		perror ("read");
		return -1;
	}
	printf ("after read data: \n");
	for (i = 0; i < 16; ++i) {
		printf ("%.2x ", read_data[i]);
	}
	printf ("\n");

	close (fd);
	printf ("usb close success. \n");
	return 0;
}

