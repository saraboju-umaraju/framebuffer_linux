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
#define BOARDER 50
#define do_less_stuff(z) do { \
	_r = arr[((z)*3)] ; \
	_g = arr[((z)*3)+1]; \
	_b = arr[((z)*3)+2];  \
}while(0);
			srand(getpid());
			unsigned char arr[30] = {};
			volatile unsigned char index = 0;
			volatile sleep = 100000;

			int _ = 0;
			for(_=0; _< 256; _++)
				arr[_] = rand()%256 ;
			int add = 0;
			int l = 0;
			int k = 0 ;
			int m = 0 ;
			int _r = 0 ;
			int _g = 0 ;
			int _b = 0 ;
			while(1) {
			usleep(sleep);
			index-=3;
			for (y = 00; y < (HEIGHT); y++,l++,k=0)
				for (x = 00,m=0; x < WIDTH; m++,x++) {
					location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
						(y+vinfo.yoffset) * finfo.line_length;

					if ( y < BOARDER || x < BOARDER || y>(HEIGHT-BOARDER) || x>(WIDTH-BOARDER)) {
					do_less_stuff(index+83); 
					} else if ( y < (BOARDER*2) || x < (BOARDER*2) || y>(HEIGHT-(BOARDER*2)) || x>(WIDTH-(BOARDER*2))) {
					do_less_stuff(index+80); 
					} else if ( y < (BOARDER*3) || x < (BOARDER*3) || y>(HEIGHT-(BOARDER*3)) || x>(WIDTH-(BOARDER*3))) {
					do_less_stuff(index+77); 
					} else if ( y < (BOARDER*4) || x < (BOARDER*4) || y>(HEIGHT-(BOARDER*4)) || x>(WIDTH-(BOARDER*4))) {
					do_less_stuff(index+74); 
					} else if ( y < (BOARDER*5) || x < (BOARDER*5) || y>(HEIGHT-(BOARDER*5)) || x>(WIDTH-(BOARDER*5))) {
					do_less_stuff(index+71); 
					} else if ( y < (BOARDER*6) || x < (BOARDER*6) || y>(HEIGHT-(BOARDER*6)) || x>(WIDTH-(BOARDER*6))) {
					do_less_stuff(index+68); 
					} else if ( y < (BOARDER*7) || x < (BOARDER*7) || y>(HEIGHT-(BOARDER*7)) || x>(WIDTH-(BOARDER*7))) {
					do_less_stuff(index+65); 
					} else if ( y < (BOARDER*8) || x < (BOARDER*8) || y>(HEIGHT-(BOARDER*8)) || x>(WIDTH-(BOARDER*8))) {
					do_less_stuff(index+62); 
					} else { 
						_r = 0 ;
						_b = 0;
						_g = 0;
					}
#if 0
					if ( y < BOARDER || x < BOARDER || y>(HEIGHT-BOARDER) || x>(WIDTH-BOARDER)) {
					do_less_stuff(index); 
					} else if ( y < (BOARDER*2) || x < (BOARDER*2) || y>(HEIGHT-(BOARDER*2)) || x>(WIDTH-(BOARDER*2))) {
					do_less_stuff(index+3); 
					} else if ( y < (BOARDER*3) || x < (BOARDER*3) || y>(HEIGHT-(BOARDER*3)) || x>(WIDTH-(BOARDER*3))) {
					do_less_stuff(index+6); 
					} else if ( y < (BOARDER*4) || x < (BOARDER*4) || y>(HEIGHT-(BOARDER*4)) || x>(WIDTH-(BOARDER*4))) {
					do_less_stuff(index+9); 
					} else if ( y < (BOARDER*5) || x < (BOARDER*5) || y>(HEIGHT-(BOARDER*5)) || x>(WIDTH-(BOARDER*5))) {
					do_less_stuff(index+12); 
					} else if ( y < (BOARDER*6) || x < (BOARDER*6) || y>(HEIGHT-(BOARDER*6)) || x>(WIDTH-(BOARDER*6))) {
					do_less_stuff(index+15); 
					} else if ( y < (BOARDER*7) || x < (BOARDER*7) || y>(HEIGHT-(BOARDER*7)) || x>(WIDTH-(BOARDER*7))) {
					do_less_stuff(index+18); 
					} else if ( y < (BOARDER*8) || x < (BOARDER*8) || y>(HEIGHT-(BOARDER*8)) || x>(WIDTH-(BOARDER*8))) {
					do_less_stuff(index+21); 
					} else { 
						_r = 0 ;
						_b = 0;
						_g = 0;
					}
#endif
						if (vinfo.bits_per_pixel == 32) {
							*(fbp + location)     = _b;        
							*(fbp + location + 1) = _g;
							*(fbp + location + 2) = _r; 
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
}
			munmap(fbp, screensize);
			close(fbfd);
			return 0;
}
