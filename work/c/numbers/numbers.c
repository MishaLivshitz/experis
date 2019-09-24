#include <stdio.h>
#include <math.h>

int CheckAscending(int num){

int currNum;

for(currNum = num%10,num/=10 ; num>0; num/=10){
	if(currNum<num%10){
		
		return 0;
		}

}
return 1;

}

int isPalindrom(int num){

int newNum=0,tempNum=num,reminder;

while(tempNum>0){
	reminder=tempNum%10;
	newNum=newNum*10+reminder;	
	tempNum/=10;
}
return newNum==num;

}

int isPrime(int num){

	int i;
	double root = sqrt(num);
	for(i=num-1;i>=root;i--){
		if (num%i==0)
		return 0;
		}
return 1;
}


int findGreatePrime(int num){

	int i;
	for(i=num;!isPrime(i);i++);
	return i;
}

int isPerfectNumber(int num){
	
	int tempNum=num,counter=1,sum=0,reminder;
	while(counter<num){
		reminder=tempNum%counter;
		if(reminder==0)
		{
			sum+=counter;
		}
		counter++;
	}
	return sum==num;
}

int main(){
int num;
printf("insert a number: ");
scanf("%d",&num);
printf("CheckAscending: %d\n",CheckAscending(num));
printf("isPalindrom: %d\n",isPalindrom(num));
printf("isPrime: %d\n",isPrime(num));
printf("findGreatePrime: %d\n",findGreatePrime(num));
}
