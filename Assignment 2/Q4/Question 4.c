#include <stdio.h>

int getValidDays(){
	int festival_days =-1;
	do{
		printf("Enter the number of days(1-7): ");
		scanf("%d",&festival_days);
		
	}while(festival_days <=1 || festival_days >=7);
	
	return festival_days;
}//end function getValidDays

float calculateDailySales(int daynumber){
	int orders ;
	
	printf("\nEnter the number of customers orders recieved on day %d: " , daynumber);
	scanf("%d", &orders);
	
	float orders_amount[orders];
	float amount;
	for(int i = 0 ; i <orders ; i++){
		printf("Enter the amonut of order number %d: ", i+1);
		scanf("%f" , &amount);
		while(amount <0){
			printf("Invalid amount renter amount: ");
			scanf("%f" ,&amount);
		}//end while
		
		orders_amount[i] = amount;
	}//end for
	float highest_order_amount = orders_amount[0] , total_sales = 0.0;
	for(int index = 0 ; index <orders; index++){
		total_sales += orders_amount[index];
		if(orders_amount[index] >highest_order_amount)
			highest_order_amount = orders_amount[index] ; 
	}//end for 
	float Avg = total_sales /orders;
	
	printf("Total Sales: Rs. %.2f\n" , total_sales);
	printf("Average order: Rs. %.2f\n" , Avg);
	printf("Highest order: Rs. %.2f\n", highest_order_amount);
	
	return total_sales;
	
}//end function calculateDailySales


int findHighestSalesDay(float dailySales[], int numberOfDays){
	int earliest = 0;
	float highest_sales = dailySales[0];
	
	for(int i = 1 ; i <numberOfDays; i++){
		if(dailySales [i] >highest_sales){
			highest_sales = dailySales[i];
			earliest = i +1;
		}//end if 
	}//end for 
	
	return earliest;
	
}//end function findHighestSalesDay

void displayBarChart(float dailySales[], int numberOfDays){
	int asterisk;
	printf("=====Daily Total Sales Bar Chart======\n");
	for(int i = 0 ; i <numberOfDays ; i ++){
		printf("Day %d: " , i +1);
		asterisk = dailySales[i] /100; // calculating how many stars
		for(int j = 0 ; j <asterisk ; j ++){
			printf("*");
		}//end for 
		printf("\n");
	}//end outer for 
}


int main(){
	int valid_days = getValidDays();
	float DailyTotalSales[valid_days], Festival_Total = 0.0;
	
	for(int i = 0 ; i <valid_days; i ++){
		DailyTotalSales[i] = calculateDailySales(i +1);
		Festival_Total += DailyTotalSales[i];
		
	}
	
	int highestSalesDay = findHighestSalesDay(DailyTotalSales, valid_days);
	
	printf("\n====== FESTIVAL SUMMARY ======\n");
	printf("Total festival sales: Rs. %.2f\n" , Festival_Total);
	printf("Day with highest sales: Day %d\n", highestSalesDay);
	printf("Highest daily sales: Rs. %.2f\n", DailyTotalSales[highestSalesDay - 1]);



	displayBarChart(DailyTotalSales, valid_days);
	
}
