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
	long int screensize = 0;
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

	printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

	// Figure out the size of the screen in bytes
	screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

	// Map the device to memory
	fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
	if ((int)fbp == -1) {
		perror("Error: failed to map framebuffer device to memory");
		exit(4);
	}
	printf("The framebuffer device was mapped to memory successfully.\n");

	x = 100; y = 100;       // Where we are going to put the pixel

	// Figure out where in memory to put the pixel
#if 0
	for (y = 100; y < 300; y++)
		for (x = 100; x < 300; x++) {
#endif
#define WIDTH 1366
#define HEIGHT (768-6)
#define BOARDER 20
#define GAP (HEIGHT/8)
#define GAPV (WIDTH/16)
			int _ = 0;
			int l = 0;
			int k = 0 ;
			int m = 0 ;
			int color = 255 ;
while (1) {
		usleep(100000);
		color ^=255;
			for (y = 00, l=0,k=0; y < (HEIGHT); y++,l++,k=0)
				for (x = 00,m=0; x < WIDTH; m++,x++) {
					location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
						(y+vinfo.yoffset) * finfo.line_length;

					if (m<(GAPV+1) ) {

						if (l<(GAP+1) ) {
							_ = 255 ;
						} else {
							_ = 0 ;
							if (!(l%GAP))
								l = 0 ;
						} 
					}else {
#if 1
						if (m<(GAPV+1) ) {
#endif
							_ = 0 ;
						} else {
							_ = 255 ;
							if (!(m%GAPV))
								m = 0 ;
						}
					}

					if (vinfo.bits_per_pixel == 32) {
						*(fbp + location)     = _^255^color;        
						*(fbp + location + 1) = _^255^color;
						*(fbp + location + 2) = _^255^color; 
						*(fbp + location + 3) = 255;   
						//location += 4;
					} else  { //assume 16bpp
						int b = 10;
						int g = (x-100)/6;     // A little green
						int r = 31-(y-100)/16;    // A lot of red
						unsigned short int t = r<<11 | g << 5 | b;
						*((unsigned short int*)(fbp + location)) = t;
					}

				}
#if 0
			for (y = 00; y < (HEIGHT); y++,l++,k=0)
				for (x = 00,m=0; x < WIDTH; m++,x++) {
					location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
						(y+vinfo.yoffset) * finfo.line_length;

					if ( y < BOARDER || x < BOARDER || y>(HEIGHT-BOARDER) || x>(WIDTH-BOARDER))
						if (vinfo.bits_per_pixel == 32) {
							*(fbp + location)     = 0;        
							*(fbp + location + 1) = 0;
							*(fbp + location + 2) = 255; 
							*(fbp + location + 3) = 255;   
							//location += 4;
						}  //assume 16bpp
		}
#endif
}
			munmap(fbp, screensize);
			close(fbfd);
			return 0;
		}
