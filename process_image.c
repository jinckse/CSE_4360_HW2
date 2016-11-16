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
	
	int i, j, ii, jj, k, ell, sum_image, sum_template;
	float data, coeff, f_bar, t_bar;
	int diff_w = size[0] - (roi.width - 1);
	int diff_h = size[1] - (roi.height - 1);
	int cnt = 0;

	/* Build image template */
	unsigned char image_template[roi.width][roi.height];

	/* 
		Build image template 
	*/

	/* Access each vector x in original image to template width + offset */
	for (i = roi.x; i < (roi.width + roi.x); i++) {
		/* Access each element y in original image to template height + offset */
		for (j = roi.y; j < (roi.height + roi.y); j++) {
			image_template[i - roi.x][j - roi.y] = image[i][j];	
			sum_template += image[i][j];
		}
	}

	/* Compute template mean */
	t_bar = sum_template / (roi.width * roi.height);
	
	/* Do for each pixel in image */
	for (i = 0; i < diff_w; i++) {
		for (j = 0; j < diff_h; j++) {

			/* Iterate over image slice */
			for (ii = i; ii < roi.width + i; ii++) {
				for (jj = j; jj < roi.height + j; jj++) {
					sum_image += image[ii][jj];
					proc_img[ii][jj] = image_template[ii - i][jj - j];
				}
			}
			/* Computer current image slice mean */
			f_bar = sum_image / (size[0] * size[1]);
	
			/* Computer normalized correction */
			
		}
	}
}

