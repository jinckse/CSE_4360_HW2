/** 
	@file process_image_template.c

	@brief This program processes an image to compute template maches based on
	a user selected region of the image to match using normalized correlation.

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

	/** @var counter */
	int i;

	/** @var counter */
	int j; 

	/** @var counter */
	int ii;

	/** @var counter */
	int jj; 

	/** @var Original image element summation */
	int sum_image ;

	/** @var Current image template summation */
	int sum_template;

	/** @var Flag used to denote initial iteration over image template */
	int first_run = 1;

	/** @var Out-of-bounds checker used when iterating template over image */
	int diff_w = size[0] - (roi.width - 1);

	/** @var Out-of-bounds checker used when iterating template over emage */
	int diff_h = size[1] - (roi.height - 1);

	/** @var counter */
	int cnt = 0;
	
	/** @var counter */
	float f_bar;

	/** @var counter */
	float t_bar;

	/** @var counter */
	float f_std;

	/** @var counter */
	float t_std;

	/** @var counter */
	float c;

	/** @var counter */
	float c_num;

	/** @var counter */
	float c_denom;

	/** @var counter */
	float pixel_value;

	/** @var counter */
	float max;

	/** @var counter */
	float min;

	/** @var Used to store image template */
	unsigned char image_template[roi.width][roi.height];

	printf("Processing image...\n");

	/**
		Compute normalized correlation
	*/

	/** Access each vector x in original image to template width + offset */
	for (i = roi.x; i < (roi.width + roi.x); i++) {
		/** Access each element y in original image to template height + offset */
		for (j = roi.y; j < (roi.height + roi.y); j++) {
			/** Compute summation of template pixels */
			sum_template += image[i][j];
		}
	}

	/** Compute template mean */
	t_bar = sum_template / (roi.width * roi.height);
	
	/** Do for each pixel in image */
	for (i = 0; i < diff_w; i++) {
		for (j = 0; j < diff_h; j++) {

			/** Iterate over image window to find f_bar */
			for (ii = i; ii < roi.width + i; ii++) {
				for (jj = j; jj < roi.height + j; jj++) {
					sum_image += image[ii][jj];
				}
			}

			/** Compute current image window mean */
			f_bar = sum_image / (roi.width * roi.height);
			sum_image = 0;
			
			/** Compute summations for standard deviations and numerator */
			for (ii = i; ii < roi.width + i; ii++) {
				for (jj = j; jj < roi.height + j; jj++) {

					/** Sum standard deviations */
					f_std += powf( (image[ii][jj] - f_bar), 2);
					t_std += powf( (image_template[ii][jj] - t_bar), 2);
					
					/** Sum numerator */
					c_num += fabs(((image[ii][jj] - f_bar) * (image_template[ii][jj] - t_bar)));
				}
			}
			c_denom = sqrt(f_std * t_std);

			/** Account for divide by zero */
			if (f_std == 0 || t_std == 0) {
				c = -1;	
			}
			else {
				c = c_num / c_denom;

				/** intialize max and min to first c value in this window */
				if (first_run) {
					max = c;
					min = c;
					first_run = 0;
				}

				if (c > max) {
					max = c;
				}
	
				if (c < min) {
					min = c;
				}
			}
		
			/**
				Populate a new image with normalized correlation values at the center
				of each template-sized image window.
			*/
			
			/** Do for each element in current window */
			for (ii = i; ii < roi.width + i; ii++) {
				for (jj = j; jj < roi.height + j; jj++) {
					
					/** Place the normalized correlation result in the center of the image window */
					if (ii - i == (roi.width / 2) && jj - j == (roi.height / 2)) {
						proc_img[ii][jj] = ( (c - min) / (max - min) ) * 255;
					}
				}
			}

			/** Reset values */	
			f_std = 0;
			t_std = 0;
			c_num = 0;
			c_denom = 0;
			c = 0;
		}
		first_run = 1;
	}
}

