/** 
	@file image_process_edge.c

	@brief This program performs edge detection on an image using horizontal and vertical Prewitt
	edge templates. The process of convolving each part of the image and its surrounding neighbors
	with the template produces an output that represents the edges found in the image. 

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
	
	/** Flag to specify which type of edge detection to use */
	int vertical = 1;

	/** Counters */
	int i, j, ii, jj;
	
	/** Convolution sum */
	int sum;
	
	/** Image element data */
	float data;

	/** Prewitt template element data */
	float coeff;

	/** 
		Note: Must use transpose of Prewitt templates 
	*/

	/** Vertical Prewitt template */
	int vert[K][K] = {			
									{1, 1, 1},
									{0, 0, 0},
									{-1, -1, -1} };

	/** Horizontal Prewitt template */
	int horiz[K][K] = {			
									{1, 0, -1},
									{1, 0, -1},
									{1, 0, -1} };

	if (vertical) {
		printf("Using vertical orentation template\n");
	}
	else {
		printf("Using horizontal orentation template\n");
	}
		
	/* Process vertical edges */	
	for (i = (K / 2); i < (size[0] - (K / 2) ); ++i) {
		for (j = K / 2; j < (size[1] - (K / 2) ); ++j) {
			sum = 0;
		
			/* Convolve image kernel with template */	
			for (ii = (-K / 2); ii <= (K / 2); ++ii) {
				for (jj = (-K / 2); jj <= (K / 2); ++jj) {
					data = image[i + ii][j + jj];

					/** Use desired detection type */
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

			/* Normalize sum of each pixel */
			proc_img[i][j] = (sum * MAX_PIXEL) / DIM;
		}
	}
}

