#ifndef PUBLIC_H
#define PUBLIC_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define  	ON  		1
#define  	OFF 		0
#define 	DISPLAY 	1
#define  	Debug 		0	//鏄?惁鎵撳嵃
typedef unsigned char uint8_t;
typedef unsigned char byte;
typedef unsigned int uint;



#define   PI				3.141592658
#define   STOP 	while(1);
#define   GETLOWBYTE0(x)  	((x>>0)&0x000000ff)
#define   GETLOWBYTE1(x)  	((x>>0)&0x0000ff00)
#define   GETLOWBYTE2(x)  	((x>>0)&0x00ff0000)
#define   GETLOWBYTE3(x)  	((x>>0)&0xff000000)
#define   GET_BIT(x,bit)  	((x&(1<<bit)>>bit)						//获取位
#define   CLEAR_BIT(x,bit) 	(x&=~(1<<bit))							//清零位
#define   SET_BIT(x,bit) 	(x|= (1<<bit))							//设置位
#define   BIT_M_TO_N(x,m,n) ((unsigned int)(x<<(31-(n)))>>((31-(n))+(m)))	//获取位段n~m位 n>m
//鏁扮粍杈撳嚭
//瀛楃?涓叉寚閽堣緭鍑?
/*    printf("\nTime=%s P_Line=%d\n",__TIME__,__LINE__);   */
#ifdef DISPLAY
#define DISPLAYPOINTSTING(SRCS,LEN,LEVEL)	do{	    \
    if(LEVEL){                                      \
        if((LEN)>16){                               \
            for(int a=0;a<(LEN);a++)                \
            {										\
                printf("%02x ",*(SRCS+a));			\
                if(a!=0 && (a+1)%0x10==0){          \
					if(LEVEL>=1){					\
						printf("\n");               \
						}							\
                }                                   \
            }										\
			if(LEVEL>2){							\
				printf("\n");						\
			}										\
        }                                           \
        else{                                       \
            for(int a=0;a<(LEN);a++)                \
            {										\
                printf("%02x ",*(SRCS+a));			\
            }										\
			if(LEVEL>2){							\
				printf("\n");						\
			}										\
        }                                           \
    }                                               \
}while(0);
#else
#define DISPLAYPOINTSTING(SRCS,(LEN),LEVEL)  do{    \
}while;                    
#endif

#ifdef DISPLAY
#define DISPLAYSS(STR,LEVEL)          do{             \
    if(LEVEL){                                        \
        printf("%s\n",STR);                           \
    }                                                 \
}while(0);
#else
#define DISPLAYSS(STR,LEVEL)          do{             \
}while(0);           
#endif

//瀛楃?涓瞔opy
#define CHARCPYS(DESTS,SRCS,LEN)	do{		\
	for(a=0;a<LEN;a++)						\
	{										\
		*(DESTS+a) = *(SRCS+a);				\
	}										\
}while(0);

//瀛楃?涓瞂or
#define CHARXORS(DESTS,SRCS,LEN)	do{		\
	for(a=0;a<LEN;a++)						\
	{										\
		*((DESTS)+a) ^= *((SRCS)+a);		\
	}										\
}while(0);

#define FSWAP(DESTS,SRCS)	do{					\
	float a = (DESTS);							\
	(DESTS)=(SRCS);									\
	(SRCS)=a;										\
}while(0);

//MATRIX COPY
#define MATRIXCPYS(DESTS,SRCS,ORDER)	do{			\
	for(a=0;a<ORDER;a++){							\
		for(b=0;b<ORDER;b++){						\
			*(DESTS[a]+b) = *(SRCS[a]+b);			\
		}											\
	}												\
}while(0);

//MATRIX EXCHANGE TO INEX
#define MATRIXEXCHANGEINDEX(INDEX,MATRIX,ORDER)	do{			\
	for(a=0;a<ORDER;a++){									\
		for(b=0;b<ORDER;b++){								\
		*(INDEX+a*ORDER + b) = *(MATRIX[a]+b);				\
		}													\
	}														\
}while(0);

#define MATRIX_PRINT(SRCS,NAME)	do{		                                                                                                            \
    if(strlen(SRCS)>=16) {                                                                                                                          \
	    printf("%s is:               %02X %02X %02X %02X   ",NAME,SRCS[0],SRCS[4],SRCS[8],SRCS[12]); printf("\n");                                  \
	    printf("                         %02X %02X %02X %02X   ",SRCS[1],SRCS[5],SRCS[9],SRCS[13]); printf("\n");                                   \
	    printf("                         %02X %02X %02X %02X   ",SRCS[2],SRCS[6],SRCS[10],SRCS[14]); printf("\n");                                  \
	    printf("                         %02X %02X %02X %02X   ",SRCS[3],SRCS[7],SRCS[11],SRCS[15]); printf("\n");                                  \
	    printf("\n");                                                                                                                               \
    }                                                                                                                                               \
}while(0);

#define MATRIX_LINEPRINT(SRCS,NAME)	do{		                                                                                                        \
    if(strlen(SRCS)>=16) {                                                                                                                          \
	    printf("%s is:               %02X %02X %02X %02X   ",NAME,SRCS[0],SRCS[1],SRCS[2],SRCS[3]); printf("\n");                                   \
	    printf("                         %02X %02X %02X %02X   ",SRCS[4],SRCS[5],SRCS[6],SRCS[7]); printf("\n");                                    \
	    printf("                         %02X %02X %02X %02X   ",SRCS[8],SRCS[9],SRCS[10],SRCS[11]); printf("\n");                                  \
	    printf("                         %02X %02X %02X %02X   ",SRCS[12],SRCS[13],SRCS[14],SRCS[15]); printf("\n");                                \
	    printf("\n");                                                                                                                               \
    }                                                                                                                                               \
}while(0);

#define MATRIX_PRINT_DINDEX(SRCS,NAME,LEVEL)	do{	\
	printf("%s\n",NAME);							\
	DISPLAYPOINTSTING(SRCS[0],4,LEVEL);				\
	DISPLAYPOINTSTING(SRCS[1],4,LEVEL);				\
	DISPLAYPOINTSTING(SRCS[2],4,LEVEL);				\
	DISPLAYPOINTSTING(SRCS[3],4,LEVEL);				\
	printf("\n");									\
}while(0);




#endif