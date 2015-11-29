// ByRCA.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <fstream>
 
// The one and only application object

int ShiftOver(int n,int operatorA,int operatorB);
int Max(int x, int y, int z) ;

double CCAShiftDelay[33];
int A[32],B[32],Carry0[64],Carry1[64],Sum[64];

void main()
{
	
	int operator1,operator2 ;

	int temp = 0;
	for(int n=2;n<=32;n++)
	{
		CCAShiftDelay[n] = 0;
		srand ( time(NULL)*pow(2.0f,n/10.0f));
		for(int i=0;i<10000;i++)
		{
			operator1 = (rand());
			operator2 = (rand());
			temp = CCAShiftDelay[n];
			temp = temp + ShiftOver(n,operator1,operator2);
			CCAShiftDelay[n]  = temp;
		}

		temp = CCAShiftDelay[n];
		CCAShiftDelay[n] = temp/10000.0f;

		printf("Delay of multiplier with shift over 0's/1's for n = %d is %f D \n",n,CCAShiftDelay[n]);
	}  
	 
	scanf("Press any key to end");
}

int ShiftOver(int n, int operatorA, int operatorB)
{
	const int MAX = 70;
	int  flag1,flag2,flag3,j,k,z,m, temp1, temp2,temp3, bNum,a = 0, b = 0;
	unsigned int y ;
	int sum[MAX], carry0[MAX], carry1[MAX],tempBuf1[MAX],tempBuf2[MAX];
	int delay;//delay variables.
	delay = 0;
	m = 0;
	z=0;
	bNum = 0;
	temp1 = 1;
	j = 0; k = 0;
	for(j=0;j<MAX;j++)
	{
		A[j] = 0;
		B[j]=0;
		sum[j]=0;
		carry0[j]=0;
		carry1[j]=0;
		tempBuf1[j]=0;
		tempBuf2[j]=0;
	}
	for(j=0;  j<n ;j++)
	{
		A[j] = operatorA % 2;// random bits generation
		operatorA = operatorA/2;
		B[j] = operatorB % 2;
		operatorB = operatorB/2;
	}
	--j;
	y = n - 1;
	z = n - 1;
	flag1 = 1;
 
	while(bNum < n)
	{
		int action = 0;
		if(flag1 == 1)
		{

			if(B[0] == 1) // checking first bit of B
			{
				for(j= z; j>=0; j--)
				{
					temp2 =   (!A[j]);	// operBuffer
					tempBuf1[j] = temp2;
				}
				j = 0;
				if(tempBuf1[j] == 0)
					tempBuf1[j] = 1;
				else
				{
					while( tempBuf1[++j] != 0 )
						tempBuf1[j] = 1;

					if(tempBuf1[j] == 0)
					{
						tempBuf1[j] = 1;
					}
				}
				j = y;
				action = 2;
				delay += 1;
				//if(tempBuf1[z] == 1)// Sign Extension of Negative number
				//	tempBuf1[++z] == 1;
				//else
				//	tempBuf1[++z] = 0;
			}
			else // first bit of B is '0':-zero shift
			{
				z++;
				m++;
				action = 0;
				flag1 = 0;
				delay += 1; //'1' => 2d for shift delay and 2d for trigger next cycle delay

			}
		}
		else if(flag1!=1)
		{
			for(int i=0;i<=z;i++)
				tempBuf1[i]=0;
			bNum++;
			action = B[bNum] * 2 + B[bNum - 1] ;
			if(action == 0 || action == 3)//Check for 0-0 or 1-1
			{
				if(tempBuf2[z] == 1)
				{
					z++;
					tempBuf2[z] = 1; // Sign extension of '1'
				}
				else
				{
					z++;
					tempBuf2[z] = 0; // Sign extension of '0'
				}
				m++;
				delay += 1; //'1' => 2d for shift delay and 2d for trigger next cycle delay
				//To skip Addition process
			}
			else 
			{
				if(action == 2) //Check for 1-0
				{
					for(j=y; j>=0; j--)
					{
						temp2 = !(A[j]);
						tempBuf1[j] = temp2;
					}
					if(tempBuf1[j] == 0)
						tempBuf1[j] = 1;
					else
					{
						while(tempBuf1[++j] != 0)
							tempBuf1[j] = 0;

						if(tempBuf1[j] == 0)
						{
							tempBuf1[j] = 1;
						}
					}
					j = y;
				}
				else if(action == 1)//Check for 0-1
				{
					for(j=y; j>=0; j--)
					{
						temp2 = A[j];
						tempBuf1[j] = temp2;
					}
					j = y;
				}

				flag2 = m;
				while(flag2 > 0  )
				{
					for(j=z; j>=0; j--)
					{
						temp3 = tempBuf1[j];
						tempBuf1[j+1] = temp3;
					}
					tempBuf1[m-flag2] = 0;
					j = y+1;
					flag2--;
				}
				delay += 1;
			}
		}
		flag1 = 0;
		carry0[0] = carry1[0] = 0 ; flag3 = 0 ;k = 0;
		int addDelay = 0;
		while(flag3 != 1 && k<=z)
		{
			flag3 = 1;
			if(k ==0)
			{
				sum[k] = (tempBuf2[k] + tempBuf1[k] + 0) % 2;
				carry1[k] = ((tempBuf2[k] & tempBuf1[k]) | ((tempBuf2[k] ^ tempBuf1[k])) & 0);
				carry0[k] = (((!tempBuf2[k]) & (!tempBuf1[k])) | ((tempBuf2[k] ^ tempBuf1[k]))& !0);
			}
			else
			{
				temp1 = (tempBuf2[k] + tempBuf1[k] + carry1[k-1]) % 2;
				sum[k] = temp1;
				temp1 = ((tempBuf2[k] & tempBuf1[k]) | ((tempBuf2[k] ^ tempBuf1[k])) & carry1[k-1]);
				carry1[k] = temp1;
				temp1 = (((!tempBuf2[k]) & (!tempBuf1[k])) | ((tempBuf2[k] ^ tempBuf1[k]))& !carry0[k-1]);
				carry0[k] = temp1;
			}
			for(j = 0; j<=z; j++)
			{
				flag3 &= (carry0[j] | carry1[j]);
			}
			k++;
		}

		a = b = 0;
		for(k=z; k>=0; k--)
		{
			tempBuf2[k] = sum[k];
		}
		if(action!=0 && action!=3)
		{
			m++;
			if(tempBuf2[z] == 1)
			{
				z++;
				tempBuf2[z] = 1; // Sign xtension for '0'
			}
			else
			{
				z++;
				tempBuf2[z] = 0; // Sign extension for '0'
			}

			for(j = 0; j<=z-1 ; j++)
			{
				if(carry0[j] == 1)
				{
					if(a == 0)
						a++;
					else if ((tempBuf2[j] != 0) || (B[j] != 0))
						a++;
					else
					{
						if(a > addDelay)
							addDelay = a;
						a = 0;
					}
				}
				else
				{
					if(a > addDelay)
						addDelay = a;
					a = 0;
				}
				if((carry1[j] == 1) && ((tempBuf2[j] + tempBuf1[j] + carry1[j]) < 3))
					b++;
				else
				{
					if(b > addDelay){
						addDelay = b;
						b = 0;
					}
					if((tempBuf2[j] + tempBuf1[j] + carry1[j]) == 3) // next 1-1
						b = 1;
				}
			}
			
			addDelay = Max(a, b, addDelay);
		}
		else
			addDelay = 0;
		delay += addDelay;
	}
	delay = (delay + 1)* 2 ;
	return  delay;
}

int Max(int x, int y, int z)  // to determine the max of 3 numbers
{
	int max = x;

	if(max < y)
		max = y;

	if(max < z)
		max = z;

	return max;
}
