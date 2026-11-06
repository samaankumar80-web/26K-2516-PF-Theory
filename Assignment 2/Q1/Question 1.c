#include <stdio.h>
int main(){
	int rows , cols;
	
	//seating input
	printf("Enter the Number of rows: ");
	scanf("%d",&rows); 
	
	printf("Enter the Number of seats in a row: ");
	scanf("%d",&cols);
	
	//2d array of seating arangment
	int seats[rows][cols];
	
	
	//taking input of seating availbiity
	printf("Enter seat availbility:\n");
	for(int i =0 ; i <rows ; i++){
		for(int j = 0 ; j <cols; j++){
			printf("Enter status of row no %d and seat no %d:",i,j);
			scanf("%d" ,&seats[i][j]);
		}
	}
	
	
	//displaying seating arrangement
	printf("   "); //skiping spaces for correct labeling 
	for(int i =0; i <cols; i ++){
		printf("%2d ", i);// labels of seats in a row
	}
	printf("\n");
	for(int j  =0 ; j<rows ; j ++){
		printf("R%-2d", j);// label of row 
		for(int x = 0 ; x <cols ; x++){
			if(seats[j][x]==0 ){
				printf(" _ ");// available seats
			}
			else{
				printf(" x ");//available seats
			}
		}
		printf("\n");//new line for new row 
	}
	int available =0 , total_available = 0 ;
	for(int x = 0 ; x <rows ; x++){//loop for rows
		for(int y=0; y<cols ; y++){//loop for cols
			if(seats[x][y] == 0){
				available ++;//incrementing the available seats if not reserved
			}
		}
		printf("The available seats in row %d are %d" , x, available);
		printf("\n");
		total_available += available;//incrementing the total seats available
		available = 0;//reseting available to zero for every row
	}
	printf("The total seats available in the hall are: %d\n", total_available);

	//taking input of the number of persons in a group and validating it 
	int flag = -1 , k ;
	while(flag == -1){
		printf("Enter the number of persons in the group(1-%d): " , cols);
		scanf("%d", &k);
		if(k <1 || k > cols)
			flag = -1;
		else 
			flag = 0;
	}
	
	int mid = rows/2;//calculating the first row to search 
	int found_row , found = 0 , foundstart ;
	for(int distance_from_mid = 0 ; distance_from_mid <rows && !found ; distance_from_mid++){
		for(int row_turn = 0 ; row_turn < 2 && !found; row_turn++ ){
			int CheckRow ;
			if (row_turn == 0 )
				CheckRow = mid - distance_from_mid;  //search lower number row
			else
				CheckRow = mid - distance_from_mid;  //search higher number row
			
			if(row_turn == 1 && distance_from_mid == 0)
				continue;
			
			if(CheckRow<1 || CheckRow>= rows)
				continue ;
				
			int count_free_seats =0 , index = 0;
			while(count_free_seats !=k && index <cols){
				if(seats[CheckRow][index] ==0 )
					count_free_seats++;
				else 
					count_free_seats = 0;
					
				index ++;
			}
			if(count_free_seats ==k){
				found = 1;
				found_row = CheckRow;
				foundstart = index - k +1 ;
				break; 
			}
		}
	}
	if(found){
		for(int seatNO = foundstart ;seatNO <foundstart+k; seatNO++){
			seats[found_row][seatNO] =1 ;
			total_available --;
		}
		printf("\nThe group of %d has been allocated seats in row %d seating from seat no %d to %d" , k,found_row,foundstart,foundstart+k-1);
		
		printf("\nUpdated seating plan:\n");
			printf("   "); //skiping spaces for correct labeling 
		for(int i =0; i <cols; i ++){
		printf("%2d ", i);// labels of seats in a row
		}
		
		printf("\n");
		for(int j  =0 ; j<rows ; j ++){
			printf("R%-2d", j);// label of row 
		for(int x = 0 ; x <cols ; x++){
			if(seats[j][x]==0 ){
				printf(" _ ");// available seats
			}
			else{
				printf(" x ");//available seats
			}
		}
		printf("\n");//new line for new row 
		
	}
		printf("\nTotal remaining seats in hall are %d" , total_available);
	
	}
	else{
		printf("\nSorry no row has the number of consecutive seats you asked for");
	}
	

}