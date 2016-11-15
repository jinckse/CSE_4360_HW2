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
	
	int i, j, ii, jj, sum;
	float data, coeff;
	int diff_w = size[1] - (roi.width - 1);
	int diff_h = size[0] - (roi.height - 1);
	int cnt = 0;
	
	/* Iterate over each pixel in image */
	for (i = 0; i < diff_h; i++) {
		for (j = 0; j < diff_w; j++) {
			/* Compute a pixel-wise metric between image and template */
			for (ii = 0; ii < roi.height; ii++) {
				for(jj = 0; jj < roi.width; jj++) {
				/* sum */			 
				proc_img[ii][jj] = cnt += 5;	
				}
				cnt = 0;
	 		}
		/* Record the similarity */
		}
	}
}

