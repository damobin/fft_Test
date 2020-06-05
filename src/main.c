#include <main_head.h>

int main(int argc, char *argv[])
{
	float Frequency,Range;
	FFT_Data First;
	if(argc>=2){
		First.Lens = atoi(argv[1]);
	}else{
		First.Lens = 64;
	}
	First.Input 	= (Mat  *) malloc (sizeof( Mat  ) * First.Lens);
	Frequency = 3;
	Range = 2;
	for(int i=0;i<First.Lens;i++){
		//Fn = (2pi * fw) / 2pi = fw = Frequency = 3Hz
		//Fs = 1 / 0.125 =8Hz
		First.Input[i].real = Range * cos(2*PI*0.3+2*PI*Frequency*(float)(i*0.125) );		// i * 采样频率
		First.Input[i].image = 0;
	}
	printf("JUST Test \n");
	FFT_CaculateFuns(&First);
	fflush(stdout);	
	free(First.Input);
	printf("Range Test = %2.5f",atan2(37.928,-20.419));
    return 0;
}

//如何获取每一个采样点的频率
//Fn=(n-1)*Fs/N。
/*
某点n所表示的频率为：Fn=(n-1)*Fs/N。
由上面的公式可以看出，Fn所能分辨到频率为Fs/N，
如果采样频率Fs为1024Hz，采样点数为1024点，则可以分辨到1Hz。
1024Hz的采样率采样1024点，刚好是1秒，
也就是说，采样1秒时间的信号并做FFT，则结果可以分析到1Hz，
如果采样2秒时间的信号并做FFT，则结果可以分析到0.5Hz。
如果要提高频率分辨力，则必须增加采样点数，也即采样时间。
频率分辨率和采样时间是倒数关系。 
*/
//如何获取每一个采样点的幅值
//A = ( module / (N/2) )
/*
假设原始信号的峰值为A，那么FFT的结果的每个点（除了第一个点直流分量之外）的模值
就是A的N/2倍。而第一个点就是直流分量，它的模值就是直流分量的N倍
*/
//如何获取每一个采样点的相位
// 	cos(2*PI*0.3+ XXX)			atan2(37.928,-20.419)) = 2.06466
//position = (atan2(b,a))  是弧度    position  / pi   =  0.3 * 2 =0.6 核对
/*
该点的相位即是对应该频率下的信号的相位。相位的计算可用函数atan2(b,a)计算。
 atan2(b,a)是求坐标为(a,b)点的角度值，范围从-pi到pi。
*/