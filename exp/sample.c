#include <stdlib.h>
#include <stdio.h>
// just a test 
int main(void)
{
  const int dimx = 256, dimy = 256;
  int i, j;
  FILE *fp = fopen("first.ppm", "wb"); /* b - binary mode */
  (void) fprintf(fp, "P6\n%d %d\n255\n", dimx, dimy);
  for (j = 0; j < dimy; ++j)
  {
    for (i = 0; i < dimx; ++i)
    {
      static unsigned char color[3];
      color[0] = i % 255;  /* red */
      color[1] = j % 255;  /* green */
      color[2] = (i * j) % 255;  /* blue */
      (void) fwrite(color, 1, 3, fp);
    }
  }
  (void) fclose(fp);
  return EXIT_SUCCESS;
}
