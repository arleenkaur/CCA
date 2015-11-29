#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
//#include <koolplot.h>

void lshift(int s1[], int limit) {
	int i;
	for (i = 0; i < limit - 1; i++) {
		s1[i] = s1[i + 1];
	}

}

void add(int A[], int B[], int limit) {
	int c = 0;
	int i;
	int temp;
	for (i = limit - 1; i >= 0; i--) {
		temp = A[i];
		A[i] = ((A[i] + B[i] + c) % 2);
		c = (temp + B[i] + c) / 2;
	}
}

void increment(int A[], int limit) {
	int c = 1;
	int i;
	int temp;
	for (i = limit - 1; i >= 0; i--) {
		temp = A[i];
		A[i] = ((A[i] + c) % 2);
		c = (temp + c) / 2;
	}

}

void display(int a[], int limit) {
	int i;

	for (i = 0; i < limit; i++)
		printf("%d", a[i]);

}

void printSpace(int count) {
	int i;
	for (i = 0; i < count; i++) {
		printf(" ");
	}
}

int main()

{

	//Limit
	int N;
	//Dividend
	int Z[64];
	//Temp Dividend
	int tempZ[64];
	//Divisor
	int D[32];
	//Divisors 2's compliment for subtraction
	int D_[32];
	//Sign
	int sign;
	//variable for iteration
	int i, j, k;

	//variables for counting quotient bits and addition/subtraction operation
	double countQ;
	double countAddSub;
	time_t t;

	/* Intializes random number generator */
	srand((unsigned) time(&t));

	k = 16;
	while (k <= 32) {

		//initializing to 0
		countQ = 0;
		countAddSub = 0;

		N = k;
		j = 0;
		//This loop executes for 10000 times
		//for each iteration it creates and new dividend and divisor to process
		while (j < 10000) {

			//Creating a random Dividend
			for (i = 0; i < 2 * N; i++) {
				Z[i] = (rand() % 2);
				tempZ[i] = Z[i];
			}

			//The dividend created is printed
			//printf("\nTempZ %d:\n", j);
			//display(tempZ, 2 * N);

			//Creating a random Divisor
			//Setting first two values of divisor to 01
			D[0] = 0;
			D_[0] = 1;
			D[1] = 1;
			D_[1] = 0;
			for (i = 2; i < N; i++) {
				D[i] = (rand() % 2);
				D_[i] = D[i] ? 0 : 1;
			}

			//The divisor created is printed
			//printf("\nD %d:\n", j);
			//display(D, N);

			//Changing from 1's compliment to 2's compliment
			increment(D_, N);

			//printf("\nD_:\n");
			//display(D_, N);

			//Start the processing

			i = 0;
			while (i < N) {
				//printf("\nTempZ%d:\n", i);
				//display(tempZ, 2 * N );

				//increment the quotient bit count
				countQ++;

				if (tempZ[0] == 0 && tempZ[1] == 0) {
					lshift(tempZ, 2 * N);

					tempZ[2 * N - 1] = 0;

				} else if (tempZ[0] == 1 && tempZ[1] == 1) {
					lshift(tempZ, 2 * N);

					tempZ[2 * N - 1] = 0;

				} else {

					//increment add/sub operation counter
					countAddSub++;

					//Takes the sign bit of current reminder
					sign = tempZ[0];

					//depending on the sign bit of reminder the addition or subtraction is done
					if (sign == 0) {
						//Add 2's compliment od divisor
						//printf("\nD_%d:\n", i);
						//display(D_, N);

						add(tempZ, D_, N);
					} else {
						//add Divisor
						//printf("\nD%d:\n", i);
						//display(D, N);

						add(tempZ, D, N);
					}

					//printf("\nAfter Add TempZ%d:\n", i);
					//display(tempZ, 2 * N);

					//left shift tempZ
					//left shift the current reminder by one
					lshift(tempZ, 2 * N);

					//printf("\nAfter left shift TempZ%d:\n", i);
					//display(tempZ, 2 * N );

					//Calculating Quotient and appends to the reminder variable for later use
					tempZ[2 * N - 1] = tempZ[0] ? 0 : 1;

					//printf("\nAfter Appending Quotient TempZ%d:\n", i);
					//display(tempZ, 2 * N);
				}
				//increments i for next iteration in the process
				i++;
			}

			//printf("\nQuotient %d:\n", j);
			//display(tempZ + (N), N);

			//printf("\nReminder %d:\n", j);
			//display(tempZ, N);

			//increments j for next iteration with new dividend and divisor
			j++;
		}

		k = k + 2;

		printf("\n\nProcess Result of %d bit divisor", N);
		printf("\nTotal number of Quotient bit counts is : %f", countQ);
		printf("\nTotal number of Addition/Subtraction operation is : %f",
				countAddSub);
		printf(
				"\nAverage number of quotient bits processed per Addition/Subtraction operation is : %f",
				countQ / countAddSub);

	}

	printf("\n\nTHE FINAL TEST WITH THE GIVEN VALUE\n");
	//Testing with the given data
	//Dividend 00001001101000001010101010101010

	//Divisor bit number is set to 16
	N = 16;
	//Dividend

	tempZ[0] = 0;
	tempZ[1] = 0;
	tempZ[2] = 0;
	tempZ[3] = 0;
	tempZ[4] = 1;
	tempZ[5] = 0;
	tempZ[6] = 0;
	tempZ[7] = 1;
	tempZ[8] = 1;
	tempZ[9] = 0;
	tempZ[10] = 1;
	tempZ[11] = 0;
	tempZ[12] = 0;
	tempZ[13] = 0;
	tempZ[14] = 0;
	tempZ[15] = 0;
	tempZ[16] = 1;
	tempZ[17] = 0;
	tempZ[18] = 1;
	tempZ[19] = 0;
	tempZ[20] = 1;
	tempZ[21] = 0;
	tempZ[22] = 1;
	tempZ[23] = 0;
	tempZ[24] = 1;
	tempZ[25] = 0;
	tempZ[26] = 1;
	tempZ[27] = 0;
	tempZ[28] = 1;
	tempZ[29] = 0;
	tempZ[30] = 1;
	tempZ[31] = 0;

	//Divisor
	//Divisor  0111101100101010

	D[0] = 0;
	D[1] = 1;
	D[2] = 1;
	D[3] = 1;
	D[4] = 1;
	D[5] = 0;
	D[6] = 1;
	D[7] = 1;
	D[8] = 0;
	D[9] = 0;
	D[10] = 1;
	D[11] = 0;
	D[12] = 1;
	D[13] = 0;
	D[14] = 1;
	D[15] = 0;

	//The dividend is printed
	//printf("\nDivident :");
	printf("\n");
	display(tempZ, 2 * N);

	//The divisor is printed
	//printf("\nDivisor :");
	printf("\n");
	display(D, N);
	printf("\n================================\n");

	//Creating the D'(D's 2 Compliment)
	for (i = 0; i < N; i++) {
		D_[i] = D[i] ? 0 : 1;
	}
	//Changing from 1's compliment to 2's compliment
	increment(D_, N);

	//This loop runs for total number of divisor bits (here 16)
	i = 0;
	while (i < N) {
		//Prints value of reminder before each iteration starts
		//printf("\n\nDividend  %d th Step:", i);

		printSpace(i);
		display(tempZ, N);
		printf("\n");

		if (tempZ[0] == 0 && tempZ[1] == 0) {
			lshift(tempZ, 2 * N);

			tempZ[2 * N - 1] = 0;

		} else if (tempZ[0] == 1 && tempZ[1] == 1) {
			lshift(tempZ, 2 * N);

			tempZ[2 * N - 1] = 0;

		} else {

			//Takes the sign value
			sign = tempZ[0];

			//if sign is '0' then divisor compliment is added to the current reminder
			//else the divisor itself is added to the current reminder
			if (sign == 0) {
				//Add 2's compliment od divisor
				//printf("\nD- %d:", i);
				printSpace(i);
				display(D_, N);
				printf("\n");

				add(tempZ, D_, N);
			} else {
				//add Divisor
				//printf("\nD+ %d:", i);
				printSpace(i);
				display(D, N);
				printf("\n");

				add(tempZ, D, N);
			}

			//Prints the Reminder after the add or subtract operation
			//printf("\nAfter Add TempZ%d:", i);
			printf("--------------------------------\n");
			printSpace(i);
			display(tempZ, N);
			printf("\n");
			printf("--------------------------------\n");

			//left shift tempZ
			// Current Reminder is left shifted
			lshift(tempZ, 2 * N);

			//Prints the reminder after the shift operation
			//printf("\nAfter left shift TempZ%d:", i);
			//display(tempZ, 2 * N);

			//Depending on the sign of current reminder the quotient bit is collected
			//Calculating Quotient
			tempZ[2 * N - 1] = tempZ[0] ? 0 : 1;

			//Prints the value of reminder after appending the quotient to it for later use
			//printf("\nAfter Appending Quotient TempZ%d:", i);
			//display(tempZ, 2 * N);

		}

		i++;
	}

	//Prints the Quotient
	printf("\n\nQuotient:");
	display(tempZ + N, N + 1);

	//Prints the Reminder
	printf("\nReminder:");
	display(tempZ, N);

	//Plotdata x(-3.0, 3.0), y = sin(x) - 0.5*x;
	//plot(x, y);

	return 0;
}
