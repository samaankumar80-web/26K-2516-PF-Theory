#include <stdio.h>

//function to sum the diviosr of number
int sumdivisor(int x){
	int i ,sum ;
		
	if(x<=1)
		return 0;//eturn zero if the number is 1 as 1 has no divisor
	sum = 1 ;
	for(i = 2 ; i <=x/2 ; i ++){
		if(x % i ==0)
			sum +=i;
	}//end for
	return sum ;
}//end user define function

//start of main function
int main(){
	int n=-1 ;
	while(n <0){//validating the n
		printf("Enter the number n untill which u want amicable pairs: ");
		scanf("%d", &n);
	}//endwhile
	
	printf("Amicable pairs up to %d:\n" , n);
	int count_pairs = 0, b;//int vaiable to count pairs
	for(int a = 2; a <= n; a++){
		b = sumdivisor(a);
		if(b <=n && b > a && sumdivisor(b) == a ){//validating that a and b are amicable pair with a being the smallest
			printf("\n(%d,%d)" , a,b);
			count_pairs ++;
		}//end if
	}//end for
		
		//printing the number of amicable pairs if any 
		printf("\n");
		if(count_pairs == 0 )
			printf("There are on amicable pairs till n");
		else 
			printf("Total pairs: %d", count_pairs );

}//end main
	
