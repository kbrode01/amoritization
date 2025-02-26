/* 
* Loan Amortization Calculator
*
* Description: This program calculates a loan amoritization table based on three inputs: 
* YR = length of loan, LN = amount of loan, INT = loan interest
* 
*
* Author: Brodersen, Kevin 
*
* Date: 16 NOV 2020  
*/

//libraries
#include <stdio.h>
#include <math.h>
//defined constants YR = length of loan, LN = amount of loan, INT = loan interest
const double MIN_YR = 4.0;
const double MAX_YR = 30.0;
const double MIN_LN = 10000.0;
const double MAX_LN = 2000000.0;
const double MIN_INT = 1.0;
const double MAX_INT = 20.0;
//function calls
void GetInterest(double*); 
void GetLoanAmount(double*); 
void GetLoanTerm(double*); 
void CalcAmort(double*, double*, double*, double*, double*);

//main calling function
int main(int argc, char *argv[]){
	//initialize all as double to be filled 
	double numYears = 1.0;
	double intRate = 1.0;
	double loanAmt = 1.0;
	double totalInt = 0.0;
	double totalPri = 0.0;
	
	//populate loan length, amount and interest from three functions and test if the values are zero.
	GetLoanTerm(&numYears);
	GetInterest(&intRate);
	GetLoanAmount(&loanAmt);
	while ((numYears != 0) && (intRate != 0) && (loanAmt != 0)){
		//calculates amortization and prints chart
		CalcAmort(&numYears, &intRate, &loanAmt, &totalInt, &totalPri);
		//prints required stats
		printf("The total cost of this loan is: %.2lf\n", totalPri + totalInt);
		printf("The total interest for this loan is: %.2lf\n", totalInt);
		printf("The total principal for this loan is: %.2lf\n", totalPri);
			//Getting new values for fresh run
			GetLoanTerm(&numYears);
			GetInterest(&intRate);
			GetLoanAmount(&loanAmt);
	}
 printf("You have chosen to quit.\n");
 return 0;	
}//end of main

//additional functions
 void GetLoanTerm(double* numYears){
	/* 
	* Function Name: GetLoanTerm() 
	*
	* Input Parameters: Takes in the address of numYears
	*
	* Description: Gets a value for the number of years for the loan and compares it to the defined
	* constants above. It will continue to ask for different input if the value enter is out of the accepted 
	* range unless 0 or an acceptable answer are entered. 
	*
	* Return Value: void. Writes to address of numYears. 
	*/ 
	
	//local declaration 
	double holder; 
	
	printf("Enter in the number of years (4 to 30) for this loan or zero to quit: \n");
	scanf("%lf", &holder);
	*numYears = holder;
	while ((*numYears > MAX_YR) || (*numYears < MIN_YR)){
		if (*numYears == 0){
			return;
		}
    else{
		printf("The value entered is out of range. Please enter a new value: \n");
		scanf("%lf", &holder);
		*numYears = holder;
    }
	}
 return;
 }
 
 void GetInterest(double* intRate){ //gets interest return to main verifies in accepted limits
	/* 
	* Function Name: GetInterest() 
	*
	* Input Parameters: Takes in the address of intRate
	*
	* Description: Gets a value for the interest rate for the loan and compares it to the defined
	* constants above. It will continue to ask for different input if the value enter is out of the accepted 
	* range unless 0 or an acceptable answer are entered. I left this as a whole number because returning a
	* decimal caused an improper program exit.
	*
	* Return Value: void. Writes to address of intRate. 
	*/ 
	
	//local declaration 
	double holder;
	
	printf("Enter in the interest rate (1 to 20) for this loan or zero to quit: \n");
	scanf("%lf", &holder);
	*intRate = holder;
	while ((*intRate > MAX_INT) || (*intRate < MIN_INT)){
		if (intRate == 0){
			return;
		}
    else{
		printf("The value entered is out of range. Please enter a new value: \n");
		scanf("%lf", &holder);
		*intRate = holder;
    }
	}
 return;
}
 
 void GetLoanAmount(double* loanAmt){//gets loanamount return to main verifies in accepted limits
	/* 
	* Function Name: GetLoanAmount() 
	*
	* Input Parameters: Takes in the address of loanAmt
	*
	* Description: Gets a value for the amount of the loan and compares it to the defined
	* constants above. It will continue to ask for different input if the value enter is out of the accepted 
	* range unless 0 or an acceptable answer are entered. 
	*
	* Return Value: void. Writes to address of loanAmt. 
	*/ 
	
	//local declaration 
	double holder;
	
	printf("Enter in the total amount of the loan (10 thousand to 2 million) or zero to quit: \n");
	scanf("%lf", &holder);
	*loanAmt = holder;
	while ((*loanAmt > MAX_LN) || (*loanAmt < MIN_LN)){
		if (loanAmt == 0){
			return;
		}
    else{
		printf("The value entered is out of range. Please enter a new value: \n");
		scanf("%lf", &holder);
		*loanAmt = holder;
    }
	}
 return;
}
 
void CalcAmort(double* numYears, double* intRate, double* loanAmt, double* totalInt, double* totalPri){
	/* 
	* Function Name: CalcAmort() 
	*
	* Input Parameters: Takes in the addresses of numYears, intRate, loanAmt, totalInt and totalPri
	*
	* Description: CalcAmort() calculates the monthly payment for the entered inputs. It then prints the month,
	* interest, principal and remaining balance into a chart. On each run it adds the principal and interest to the total.
	*
	* Return Value: void. Writes to address of totalInt and totalPri. 
	*/ 
	
	//local declarations
	*intRate = *intRate / 100;//convert interest rate to a decimal
	//for montly payment formula below
	double r = *intRate / 12.0;
	double rPlus = r + 1;
	double n = *numYears * 12.0;
	double p = 0.0;//monthly payment
	//variables for the chart
	double interestI = 0.0;
	double balanceI = *loanAmt;
	double princI = 0.0;
	int i;
	//monthly payment formula
	p = balanceI / ((pow((rPlus), n) -1) / (r * pow((rPlus), n)));
	//printing first line of output
	printf("|_Mnt___Int_______Princ_______Balance__|\n");
	//printing chart
	for(i=0; i < (int)n; ++i){
		interestI = r * balanceI;
		princI = p - interestI;
		balanceI = balanceI - princI;
		*totalPri = *totalPri + princI;
		*totalInt = *totalInt + interestI;
		printf("| %3.0d | %7.2lf | %.2lf | %8.2lf\n", i+1, interestI, princI, balanceI);
	}
 return;
}
