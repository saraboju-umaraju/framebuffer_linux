#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

int main()
{
    int fbfd = 0;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    int screensize = 0;
    char *fbp = 0;
    int x = 0, y = 0;
    long int location = 0;

    // Open the file for reading and writing
    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }
    printf("The framebuffer device was opened successfully.\n");

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("Error reading fixed information");
        exit(2);
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
        exit(3);
    }

    printf("\nxres = %d\n",vinfo.xres);
    printf("\nyres = %d\n",vinfo.yres);
    printf("\nbits per pixel = %d\n",vinfo.bits_per_pixel);
    printf("\n%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

    // Figure out the size of the screen in bytes
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
    printf("\nframebuffer size in bytes = %d\n",screensize);
    printf("framebuffer size in kilo bytes  = %d\n",screensize/1024);
    printf("framebuffer size in mega bytes = %d\n",screensize/(1024*1024));

    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
   // if ((int)fbp == -1) {
    if (fbp ==-1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }
    printf("The framebuffer device was mapped to memory successfully.\n");

    x = 100; y = 100;       // Where we are going to put the pixel

    // Figure out where in memory to put the pixel

    int xx = 1360;
    int yy = 760;


    while ( xx && yy ) {

        for (y = yy; y > (yy-100); y--)
            for (x = xx; x > (xx-100); x--) {

                location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                    (y+vinfo.yoffset) * finfo.line_length;

                //printf("location %lu ", location);
                if (vinfo.bits_per_pixel == 32) {
                    *(fbp + location + 0) = 0;       // Some blue
                    *(fbp + location + 1) = 255;     // A little green
                    *(fbp + location + 2) = 0;    // A lot of red
                    *(fbp + location + 3) = 0;      // No transparency
                }   
            }

        sleep(1);

        for (y = yy; y > (yy-100); y--)
            for (x = xx; x > (xx-100); x--) {

                location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                    (y+vinfo.yoffset) * finfo.line_length;

                //printf("location %lu ", location);
                if (vinfo.bits_per_pixel == 32) {
                    *(fbp + location + 0) = 0;       // Some blue
                    *(fbp + location + 1) = 0;     // A little green
                    *(fbp + location + 2) = 255;    // A lot of red
                    *(fbp + location + 3) = 0;      // No transparency
                }   
            }

        sleep(1);
        
        for (y = yy; y > (yy-100); y--)
            for (x = xx; x > (xx-100); x--) {

                location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                    (y+vinfo.yoffset) * finfo.line_length;

                //printf("location %lu ", location);
                if (vinfo.bits_per_pixel == 32) {
                    *(fbp + location + 0) = 255;       // Some blue
                    *(fbp + location + 1) = 0;     // A little green
                    *(fbp + location + 2) = 0;    // A lot of red
                    *(fbp + location + 3) = 0;      // No transparency
                }   
            }

       sleep(1);
        
       for (y = yy; y > (yy-100); y--)
            for (x = xx; x > (xx-100); x--) {

                location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                    (y+vinfo.yoffset) * finfo.line_length;

                //printf("location %lu ", location);
                if (vinfo.bits_per_pixel == 32) {
                    *(fbp + location + 0) = 0;       // Some blue
                    *(fbp + location + 1) = 0;     // A little green
                    *(fbp + location + 2) = 0;    // A lot of red
                    *(fbp + location + 3) = 0;      // No transparency
                }   
            }

        xx-=100;
        yy-=100;
    }

    munmap(fbp, screensize);
    close(fbfd);
    return 0;
}
