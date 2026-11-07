#include <stdio.h>
void Input_Readings(int sensors, int readings, int data[sensors][readings]){
	for(int row=0 ; row<sensors; row++){
		for(int col =0 ; col<readings ; col++){
			printf("Enter the reading No %d of sensor No %d: ", col+1,row+1);
			scanf("%d", &data[row][col]);
			
		}//end for (inner loop)
	}//end for (outer loop)
}//end functions Input_Readings

void analyze_readings(int reading[],int n,int *total ,float *avg, int *max_temp, int *min_temp, int *cr, int *wr, int *Lstreak){
	*total = 0 ;
	*avg= 0.0 ;
	*max_temp = reading[0];
	*min_temp = reading[0];
	*cr =0;
	*wr = 0 ;
	*Lstreak = 0 ; 
	
	int streak=0;
	for(int index=0 ; index<n; index++){
		*total += reading[index];
		if(reading[index] > *max_temp) *max_temp = reading[index];//assigning max values
		if(reading[index] < *min_temp) *min_temp = reading[index];//assigning min values
		
		if(reading[index] >= 40)//checks readings of 40 and obove
			(*cr)++;
		else if(reading[index] >=35)//checks readinfs between 35 and 39
			(*wr)++;	
		
		if(reading[index] >=35){
			streak ++;
			if(streak >*Lstreak)
				*Lstreak = streak ;//saves he longest streak if there is new longest 
		}
		else{
			streak = 0 ;//resets the streak to zero when it breaks
		}//end if
	}//end for
	*avg = (float)(*total) /n;
}//end function analyze_readings

int highest_Avg(float avgs[], int sensors){
	float highest = avgs[0];int sensorNO =0;
	for(int i =1 ; i <sensors; i++ ){
		if(avgs[i]>highest){
		
			sensorNO = i;
			highest = avgs[i];
			
		}//end if
	}//end for
	return sensorNO+1;
}//end function highest_Avg

int main(){
	int Max_sensors , Max_readings;
	int Total , Max_temp , Min_temp, CR, WR, longest;
	float Avg;
	
	printf("Enter the total number of sensors: ");
	scanf("%d", &Max_sensors);
	
	printf("Enter the total number of hourly readings: ");
	scanf("%d", &Max_readings);
	
	int sensor_data[Max_sensors][Max_readings];
	float avgs_sensors[Max_sensors];
	
	Input_Readings(Max_sensors,Max_readings,sensor_data);
	
	printf("\n");
	
	for(int i =0 ; i <Max_sensors; i++){
		analyze_readings(sensor_data[i], Max_readings,&Total ,&Avg,&Max_temp,&Min_temp,&CR,&WR,&longest);
		avgs_sensors[i] = Avg;
	    printf("Sensor %d: Total=%d Avg=%.2f Max=%d Min=%d\n",i + 1, Total, Avg, Max_temp, Min_temp);
	    printf("           Critical= %d Warning=%d Longest hot Streak=%d" , CR,WR,longest);
	}
	
	int biggest= highest_Avg(avgs_sensors,Max_sensors);
	printf("\nsensor No %d has the highest Average: %.2f" , biggest, avgs_sensors[biggest -1]);

}
