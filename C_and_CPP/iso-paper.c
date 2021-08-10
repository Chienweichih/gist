/*
 * Calculate ISO 216/ISO 269 paper formats -- Markus Kuhn -- 2000-02-24
 */
#include <stdio.h>
#include <math.h>

int main()
{
  int height, width;
  int format;
  int tmp;

  /* A series */
  width  = 1000.0 / sqrt(sqrt(2.0)) + 0.5;
  height = sqrt(sqrt(2.0))*1000.0 + 0.5;
  printf("4A0 = %4d mm x %4d mm\n", width*2, height*2);
  printf("2A0 = %4d mm x %4d mm\n", height, width*2);
  for (format = 0; format <= 10; format++) {
    if (format < 10) putchar(' ');
    printf("A%d = %4d mm x %4d mm\n", format, width, height);
    tmp = height;
    height = width;
    width = tmp / 2;
  }
  putchar('\n');
  /* B series */
  width  = 1000.0;
  height = sqrt(2.0)*1000.0 + 0.5;
  for (format = 0; format <= 10; format++) {
    if (format < 10) putchar(' ');
    printf("B%d = %4d mm x %4d mm\n", format, width, height);
    tmp = height;
    height = width;
    width = tmp / 2;
  }
  putchar('\n');
  /* C series */
  width  = 1000.0 / sqrt(sqrt(sqrt(2.0))) + 0.5;
  height = sqrt(sqrt(sqrt(8.0)))*1000.0 + 0.5;
  for (format = 0; format <= 10; format++) {
    if (format < 10) putchar(' ');
    printf("C%d = %4d mm x %4d mm\n", format, width, height);
    tmp = height;
    height = width;
    width = tmp / 2;
  }

  return 0;
}
