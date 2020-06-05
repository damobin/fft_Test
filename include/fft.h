#ifndef FFT_H
#define FFT_H
#define _COMPLEX_DEFINED
typedef struct Matrix{
	float real;
	float image;
}Mat;

typedef struct FFT_INPUTS{
	Mat *Input;
	int Lens;
	int Class;
}FFT_Data;


void FFT_CaculateFuns(FFT_Data *INPUT);

#endif