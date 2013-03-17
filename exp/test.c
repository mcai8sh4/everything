/* Filename	:	everything.c
*  Author   :	mcai8sh4
*  Email    :	stehowarth@gmail.com
*  Sumary   :	Create every image possible
*. Version	:	1.0
*/

/*	Set size of output images (row, col) and limit of rgb components (std 255)
*	and filename length. 
*	The program outputs every posible image into PPM files.
*	Theoretically every image, thought.. EVERYTHING possible will be ouputted at some point.
*
*	The file naming function can only handle a max of 26^255 names at present, but this is a POC
*	not realistic to actually run.
*
*	To run a test of the program, comment out the output_img() call (line ~145).
*	This will stop the image creation, and just ouput the data to stdout
*/

#include <stdio.h>
#define ROW 2	// pixels in image
#define COL 2
#define LIMIT 255 // max colour component value
#define N_LENGTH 11 //limited to 255 max => max picture ~60px

// structure to hold eack pixels component RGB value
typedef struct {
	unsigned char r,g,b;
} pix;

void next_name(char* str); // Select the next sequential filename
void output(pix ar[][COL]); // Display the output matrix to STDOUT - mainly testing
void output_img(pix ar[][COL], char* fname); // create image from array data
int inc_colour(pix *p); //inc pixel colour and handle overflow
void update_image(pix ar[][COL]); // update the image 

int main(void)
{
	pix image[ROW][COL];
	int r,c;
	// init image array (all pixels black)
	for (r = 0; r<ROW; r++) 
	{
		for (c = 0; c<COL; c++) 
		{
			image[r][c].r = 0;
			image[r][c].g = 0;
			image[r][c].b = 0;
		}
	}
	update_image(image); // start the show!!
	return 0;
}


void output(pix ar[][COL])
{
	// outputs the contents of 2-dim array in a 
	// readable form, RGB values displayed in hex
	int r,c;

	for (r = 0; r<ROW; r++) 
	{
		for (c = 0; c<COL; c++) 
		{w
			printf("%.2X,%.2X,%.2X ",ar[r][c].r, ar[r][c].g, ar[r][c].b);
		}
		putchar('\n');
    }
	putchar('\n');
}

void output_img(pix ar[][COL], char* fname)
{
	// take the current pixel array and output a ppm image
	// using this data
	FILE *fp = fopen(fname, "wb");
	(void) fprintf(fp, "P6\n%d %d\n%d\n", ROW, COL, LIMIT); // ppm image header details
	(void) fwrite(ar, sizeof(pix), ROW*COL, fp);	// PPM image data
	(void) fclose(fp);
}

int inc_colour(pix *p)
{
	// increment the current pixel colour
	// when one component is 'full' reset and increment the next.
	int full = 0;
	int top = (unsigned char)LIMIT;
	p->b++;
	if(p->b == top)
	{
		p->g++;
		if(p->g ==top)
		{
			p->r++;
			if(p->r == top)
			{
				p->r=0;
				full = 1;
			}
			p->g = 0;
		}
		p->b = 0;
	}
	return full; // if full=1 then current pixel is full! ie. all components are max
}

void next_name(char* str)
{
	// update filename by incrementing letters
	int l = N_LENGTH-1;
	str[l]++;
	while (str[l] > 'Z')
	{
		str[l] = 'A';
		l--;
		str[l]++;
	}
}

void update_image(pix ar[][COL])
{
	// creates each new image array - main part of the program really
	char name[N_LENGTH+1];
	int i;
	int overflow = 0; // for if rgb components are all max
	pix *element_ptr;
	int total =0;
	int r = 0;
	int c = 0;

	// initialise name array
	for (i = 0; i<N_LENGTH; i++) 
		name[i] = 'A';
	name[i]= '\0';  // dont forget to add a null, dickhead!

	while(total < ROW)
	{
		overflow = 0 ;
		r = 0;
		c = 0;
		total = 0;
		element_ptr = &ar[r][c];
		printf("%s\n", name); 	// for debugging
		output(ar);				// for debugging
		output_img(ar, name);
		next_name(name);
		overflow = inc_colour(element_ptr); // inc pixels, return if pixel's full or not
		// handle case where a pixel is max
		while(overflow)
		{
			c++;
			if(c==COL)
			{
				total++;
				c = 0;
				r++;
			}
			element_ptr = &ar[r][c];
			overflow = inc_colour(element_ptr);
		}
	}
}