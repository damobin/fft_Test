#include <fft.h>
#include <public.h>
#include "math.h"
static unsigned char GetClass(int Lens);
static void DisFFTDATA(FFT_Data *FFTData);
static void DisMatrixIndex(Mat *Matrixs,int lens);
static void GetIndexExc(FFT_Data *INPUT);	//蝶形变换
static void FFT_Caculas(FFT_Data *INPUT);
static Mat MultMats(Mat src,Mat anotherMat);	//复数乘法
static Mat MulAdds(Mat src,Mat anotherMat);		//复数加法
static Mat MulSubs(Mat src,Mat anotherMat);	//复数减法
//FFT运算流程
static void FFT_Caculas(FFT_Data *INPUT)
{
	Mat StepFactorInit,StepFactor;			//旋转因子

	for(int i=2,mid=1;i<= INPUT->Lens;i<<=1,mid<<=1){
		StepFactor.real		=	cos(2*PI/i);
		StepFactor.image	=	sin(2*PI/i);
		for(int j=0;j<INPUT->Lens;j+=i){
			StepFactorInit.real =1;
			StepFactorInit.image=0;
			for(int k=j;k<j+mid;k++,StepFactorInit=MultMats(StepFactorInit,StepFactor)){
				Mat TempPre,TempAfter;
				TempPre 	= INPUT->Input[k] ;
				TempAfter	= MultMats(StepFactorInit,INPUT->Input[k+mid]);
				INPUT->Input[k]  	= MulAdds( TempPre , TempAfter);
				INPUT->Input[k+mid]	= MulSubs( TempPre , TempAfter);
				
			}
		}
	}
}
static Mat MultMats(Mat src,Mat anotherMat)	//复数乘法
{
	Mat MulSum;
	MulSum.real		= ( src.real * anotherMat.real ) - ( src.image * anotherMat.image );
	MulSum.image 	= ( src.real * anotherMat.image) + ( src.image * anotherMat.real  );
	return MulSum;
}
static Mat MulAdds(Mat src,Mat anotherMat)	//复数加法
{
	Mat MulSum;
	MulSum.real		= ( src.real + anotherMat.real );
	MulSum.image 	= ( src.real + anotherMat.image);
	return MulSum;	
}
static Mat MulSubs(Mat src,Mat anotherMat)	//复数减法
{
	Mat MulSum;
	MulSum.real		= ( src.real - anotherMat.real );
	MulSum.image 	= ( src.real - anotherMat.image);
	return MulSum;	
}
static unsigned char GetClass(int Lens)
{
	unsigned char Class;
	for(int i=0;i<32;i++){  //2^8
		if( Lens & 0x01 ){
			Class = i;
		}
		Lens = Lens >> 1;
	}
	return Class;
}
//蝶形变换
static void GetIndexExc(FFT_Data *INPUT)	
{
	int Temp,i,j;
	for(i=0;i<INPUT->Lens;i++){
		Temp=0;
		for( j=0;j<INPUT->Class;j++){
			if( i & ( 1<<j ) ){
				Temp += 1<<(INPUT->Class-j-1);
			}
		}
		if(Temp>i){
			FSWAP(INPUT->Input[i].real,INPUT->Input[Temp].real);
			FSWAP(INPUT->Input[i].image,INPUT->Input[Temp].image);
		}
	}
}
//显示FFT结构数据
static void DisFFTDATA(FFT_Data *FFTData)
{
	printf("\nLens = %d\n",FFTData->Lens);
	printf("Class = %d\n",FFTData->Class);
	DisMatrixIndex(FFTData->Input,FFTData->Lens);
}
//显示向量数据
static void DisMatrixIndex(Mat *Matrixs,int lens)
{
	for(int i=0;i<lens;i++){
		printf("\'%d\'(%.3f,%.3f) ",i,Matrixs[i].real,Matrixs[i].image);
		if(i!=0 && (i+1)%0x10==0){
			printf("\n");
		}
	}
}
//总运算函数
void FFT_CaculateFuns(FFT_Data *INPUT)
{
	DisFFTDATA(INPUT);	
	INPUT->Class=GetClass(INPUT->Lens);	//获取级数
	GetIndexExc(INPUT);					//蝶形转置
	DisFFTDATA(INPUT);
	FFT_Caculas(INPUT);
	DisFFTDATA(INPUT);
}
