/* Filename	:	ste
*  Author   :	mcai8sh4
*  Email    :	stehowarth@gmail.com
*  Sumary   :	POC and playground for testing
*  				my super amazing image generation software.
*  				Should only be used with caution!!!
*/

#include <stdio.h>
#define ROW 2
#define COL 2
#define LIMIT 2 // max colour component value

typedef struct {
	int r,g,b;
} pix;

void output(pix ar[][COL]); // Display the output
int inc_colour(pix *p); //TEST inc pixel colour
void update_image(pix ar[][COL]); // update the image

int main(void)
{
	pix image[ROW][COL];
	int r,c;
	// init array
	for (r = 0; r<ROW; r++) 
	{
		for (c = 0; c<COL; c++) 
		{
			image[r][c].r = 0;
			image[r][c].g = 0;
			image[r][c].b = 0;
		}
	}
	update_image(image);
	return 0;
}


void output(pix ar[][COL])
{
	// outputs the contents of 2-dim array in a 
	// readable form
	int r,c;

	for (r = 0; r<ROW; r++) 
	{
		for (c = 0; c<COL; c++) 
		{
			printf("[%d,%d,%d] ",ar[r][c].r, ar[r][c].g, ar[r][c].b);
		}
		putchar('\n');
	}
}

int inc_colour(pix *p)
{
	int full = 0;
	p->b++;
	if(p->b == LIMIT)
	{
		p->b = 0;
		p->g++;
		if(p->g == LIMIT)
		{
			p->g = 0;
			p->r++;
			if(p->r == LIMIT)
			{
				p->r=0;
				full = 1;
			}
		}
	}
	return full;
}

void update_image(pix ar[][COL])
{
	int overflow = 0;
	pix *element_ptr;
	int i;
	int r = 0;
	int c = 0;
	for(i=0; i<4097; i++)
	{
		overflow = 0 ;
		r = 0;
		c = 0;
		element_ptr = &ar[r][c];

		output(ar);
		overflow = inc_colour(element_ptr);
		printf("OVERFLOW = %d\n", overflow);
		while(overflow)
		{
			c++;
			if(c==COL)
			{
				c = 0;
				r++;
			}
			element_ptr = &ar[r][c];
			overflow = inc_colour(element_ptr);
			printf("OVERFLOW = %d\n", overflow);
		}
	}
}
