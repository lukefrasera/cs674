/* 

   The real part is stored in the odd locations of the array
   (data[1], data[3], data[5]. etc) and the imaginary part 
   in the even locations (data[2], data[4], data[6], etc. 

   The elements in the array data must be stored from data[1] 
   to data[2*nn] -  data[0] is not used!  To call fft, use the
   following:  fft(data-1,N,isign);
 
   nn is the length of the input which should be power of 2. 
   Warning: the program does not check this condition.

   isign: -1 Forward FFT, isign: 1  Inverse FFT (based on our definition)
   
   Warning: the FFT routine provided does not multiply by the normalization 
   factor 1/N that appears in the forward DFT equation; you should do this 
   yourself (see page 506 from the fft handout).

*/

#include <math.h>
#ifndef FFT_SOURCE
#define FFT_SOURCE
void fft(float data[], unsigned long nn, int isign);
/* (C) Copr. 1986-92 Numerical Recipes Software 0#Y". */
#endif
