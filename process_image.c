/**
	@file process_image_edge.c

	@brief This program uses Prewitt templates and 2d convolution to detect vertical and horizontal
	edges as determined by the value of a flag.

	@author Jarrod Nix
*/

#include <stdio.h>
#include <math.h>
#include <X11/Xlib.h>

#define DIM 512
#define K 3
#define MAX_PIXEL 255

/******************************************************************/
/* This structure contains the coordinates of a box drawn with    */
/* the left mouse button on the image window.                     */
/* roi.x , roi.y  - left upper corner's coordinates               */
/* roi.width , roi.height - width and height of the box           */
/******************************************************************/
extern XRectangle roi;

/******************************************************************/
/* Main processing routine. This is called upon pressing the      */
/* Process button of the interface.                               */
/* image  - the original greyscale image                          */
/* size   - the actual size of the image                          */
/* proc_image - the image representation resulting from the       */
/*              processing. This will be displayed upon return    */
/*              from this function.                               */
/******************************************************************/
void process_image(image, size, proc_img)
unsigned char image[DIM][DIM];
int size[2];

unsigned char proc_img[DIM][DIM];
{
	
	/** 
		Use this flag to specify which filter to apply 
	*/

	/** @var flag */
	int vertical = 0;

	/** @var Counter */
	int i;

	/** @var Counter */
	int j;

	/** @var Counter */
	int ii;

	/** @var Counter */
	int jj; 

	/** @var Counter */
	int sum; 

	/** @var flag */
	float data, coeff;

	/**
		Must use transpose of templates to alight with image storage organization 
	*/
	
	/** @var Vertical Pewitt template */
	int vert[K][K] = {			
									{1, 1, 1},
									{0, 0, 0},
									{-1, -1, -1} };
	
	/** @var Horizontal Pewitt template */
	int horiz[K][K] = {			
									{1, 0, -1},
									{1, 0, -1},
									{1, 0, -1} };

	if (vertical) {
		printf("Using vertical orientation template\n");
	}
	else {
		printf("Using horizontal orientation template\n");
	}

	/** Process vertical edges */	
	for (i = (K / 2); i < (size[0] - (K / 2) ); ++i) {
		for (j = K / 2; j < (size[1] - (K / 2) ); ++j) {
			sum = 0;
		
			/** Convolve image with kernel */	
			for (ii = (-K / 2); ii <= (K / 2); ++ii) {
				for (jj = (-K / 2); jj <= (K / 2); ++jj) {
					data = image[i + ii][j + jj];
					
					/** Use flags to determine what edges are desired */
					if (vertical) {
						coeff = vert[ii + (K / 2)][jj + (K / 2)];
					}
					else {
						coeff = horiz[ii + (K / 2)][jj + (K / 2)];
					}

					sum = sum + (data * coeff);
					sum = abs(sum);
				}
			}

			/** Normalize sum of each pixel */
			proc_img[i][j] = (sum * MAX_PIXEL) / DIM;
		}
	}
}

