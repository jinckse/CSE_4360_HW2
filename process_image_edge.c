/** 
TODO: Only works without normalizing sums at the moment 
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
	
	int vertical = 0;
	int blur = 0;
	int i, j, ii, jj, sum, proc_pixel;
	float data, coeff;

	int vert[K][K] = {			
									{-1, 0, 1},
									{-1, 0, 1},
									{-1, 0, 1} };
	int horiz[K][K] = {			
									{-1, -1, -1},
									{0, 0, 0},
									{1, 1, 1} };

	float box_filt[K][K] = {			
									{0.111, 0.111, 0.111},
									{0.111, 0.111, 0.111},
									{0.111, 0.111, 0.111} };
	if (blur) {
		printf("Using box filter\n");
		/* Apply a Gaussian Blur to the image to reduce noise */
		for (i = (K / 2); i < (size[0] - (K / 2) ); ++i) {
		 for (j = K / 2; j < (size[1] - (K / 2) ); ++j) {
			 sum = 0;
		 
			 /* Iterate over kernel */	
			 for (ii = (-K / 2); ii <= (K / 2); ++ii) {
				 for (jj = (-K / 2); jj <= (K / 2); ++jj) {
					 data = image[i + ii][j + jj];
					 coeff = box_filt[ii + (K / 2)][jj + (K / 2)];

					 sum = sum + (data * coeff);
					 sum = abs(sum);
				 }
			 }
			 /* Normalize sum of each pixel */
			 proc_img[i][j] = (sum * MAX_PIXEL) / DIM;
		 }
		}
	}

	else if (vertical) {
		printf("Using vertical orentation template\n");
		/* Process vertical edges */	
		for (i = (K / 2); i < (size[0] - (K / 2) ); ++i) {
			for (j = K / 2; j < (size[1] - (K / 2) ); ++j) {
				sum = 0;
			
				/* Iterate over kernel */	
				for (ii = (-K / 2); ii <= (K / 2); ++ii) {
					for (jj = (-K / 2); jj <= (K / 2); ++jj) {
						data = image[i + ii][j + jj];
						coeff = vert[ii + (K / 2)][jj + (K / 2)];

						sum = sum + (data * coeff);
						sum = abs(sum);
					}
				}

				/* Normalize sum of each pixel */
				proc_img[i][j] = (sum * MAX_PIXEL) / DIM;
			}
		}
	}
	else if (!vertical){
		printf("Using horizontal orentation template\n");
		/* Process horizontal edges */	
		for (i = (K / 2); i < (size[0] - (K / 2) ); ++i) {
			for (j = K / 2; j < (size[1] - (K / 2) ); ++j) {
				sum = 0;
			
				/* Iterate over kernel */	
				for (ii = (-K / 2); ii <= (K / 2); ++ii) {
					for (jj = (-K / 2); jj <= (K / 2); ++jj) {
						data = image[i + ii][j + jj];
						coeff = horiz[ii + (K / 2)][jj + (K / 2)];

						sum = sum + (data * coeff);
						sum = abs(sum);
					}
				}
				/* Normalize sum of each pixel */
				proc_img[i][j] = (sum * MAX_PIXEL) / DIM;
			}
		}
	}
	else
		printf("No selection made\n");
}


