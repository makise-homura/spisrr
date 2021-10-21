#include <linux/spi/spidev.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    const char *dev = "/dev/spidev0.0";
    if(argc > 1)
    {
        if (!strcmp(argv[1], "--help"))
        {
            printf("Show SPI status register of spidev device.\n"
                   "Usage: %s [device]\n"
                   "If no device is specified, /dev/spidev0.0 is examined.\n", argv[0]);
            return 0;
        }
        dev = argv[1];
    }

    char rx_buffer;
    struct spi_ioc_transfer tr[2];
    memset(&tr, 0, sizeof(tr));
    tr[0].tx_buf = (__u64)"\x05";
    tr[1].rx_buf = (__u64)&rx_buffer;
    tr[0].len = tr[1].len = 1;
    int fd = open(dev, O_RDONLY);
    if (fd < 0) { perror("Error opening device"); return 2; }
    if (ioctl(fd, SPI_IOC_MESSAGE(2), &tr[0]) < 0) { perror("Error performing ioctl"); return 1; }
    printf("Status register (%s): 0x%02x\n", dev, rx_buffer);
    return 0;
}
