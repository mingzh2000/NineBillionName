#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char c[9];
char i[9];
long count=0;

int repeatcheck(int M)
{
	int p,q;
	char temp,next, repeat;
		
		if(M>3)
		{
			for(p=0;p<M-3;p++)//后三位不需要检测，因为前面可以检测到 
			{
				temp = c[p];
				next=0;
				for(q=0;q<p;q++)
				{
					if(temp==c[q])
					{
						next=1;
						break;
					}
				}
				if(next)
					continue; 
					
				repeat=0;
				for(q=p+1;q<M;q++)
				{
					if(temp==c[q])
					{
						repeat++;
						if(repeat>2)
							return 0;
					}
				}
			}
		}

	return 1;		
}

godname(int M, FILE* fp)
{
	int j,p;
	int n;
	n=M-1; 
	for(j=0;j<M;j++)//初始化M位字符的数组和进制
	{
		c[j]='a';

		i[j]=0;
	}

	while(1)
	{
		if(repeatcheck(M))
		{
			fprintf(fp,"%s\n",c);
			count++;	
		}
		i[n]++;//最后一位+1

		for(j=0;j<M;j++)
		{
			if(i[0]>25)//最高位溢出则退出
				return;

			if(i[n-j]>25)//依次进位
			{
				i[n-1-j]++;
				i[n-j]=0;
			}
		}

		for(j=0;j<M;j++)
		{
			c[j]='a'+i[j];
		}
	 } 
}



int main(int argc, char *argv[]) {	
	int x;	
	int number;
	FILE * fp;
	time_t starttime,finishedtime;
    struct tm * lt;
    
	remove("log.logs");
	fp=fopen("log.logs","a+");
	if(fp==NULL) return;

	printf("请输入位数1-9：");
	scanf("%d",&number);
	
	time (&starttime);//获取Unix时间戳。

	for(x=1;x<=number;x++)//从1-6个字符依次
	{
		godname(x,fp);
	}
	
	lt = localtime (&starttime);//转为时间结构。
    fprintf(fp,"Start time：%d/%d/%d %d:%d:%d\n",lt->tm_year+1900, lt->tm_mon, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);//输出结果
    
	time (&finishedtime);//获取Unix时间戳。
	lt = localtime (&finishedtime);//转为时间结构。
    fprintf(fp,"Finished time：%d/%d/%d %d:%d:%d\n",lt->tm_year+1900, lt->tm_mon, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
    
    fprintf(fp,"count: %d",count); 
	fclose(fp);	
	return 0;
}
