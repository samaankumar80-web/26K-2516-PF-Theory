#include <stdio.h>
#include <string.h>
void displayMenu(){
	printf("====== UNIVERSITY LIBRARY MENU ======\n");
	printf("1. Register Member\n");
	printf("2. Display Available Books\n");
	printf("3. Borrow a Book\n");
	printf("4. Return a Book\n");
	printf("5. Display Member Record\n");
	printf("6. Exit\n");
	printf("Enter your Choice: ");
}//end function display Menu

void registerMember(char name[], int *studentID, int *memberType){
	printf("Enter name: ");//promting the user
	scanf(" %49[^\n]" , name);//storing the input
	printf("Enter student ID: ");//promting the user
	scanf("%d" , studentID);//storing the input
	
	 *memberType = -1 ; 
	while(*memberType != 1 && *memberType != 2){
		printf("Enter membership type (1 = Student, 2 = faculty): ");//promting the user
		scanf("%d", memberType);//storing the input
		
		if(*memberType !=1 && *memberType != 2){
			printf("Invalid Input\n");
		}//end if 
	}//end while
		
}//end funtion registerMember



void displayBooks(int bookIDs[] , char bookTitles[][50], int availableCopies[] , int totalBooks){
	printf("\n---------------------------------------------------------------");//printing the table header line
	printf("| %-4s | %-20s | %-6s |\n", "ID", "Title", "Copies");//printing titles
	printf("\n--------------------------------------------------");//tabe line
	for(int i =0 ; i <totalBooks ; i++){
		printf("| %-4d | %-20s | %-6d |\n", bookIDs[i], bookTitles[i], availableCopies[i]);
	}//end for 
	printf("----------------------------------------\n");
}// end function displayBooks



void borrowBook(int bookIDs[], char bookTitles[][50], int availableCopies[] , int totalBooks , int borrowedBookIDs[], int *borrowedCount ,int memberType){
	int ID ;
	if(*borrowedCount >= 3){
		printf("borrowing limit reached\n");
		return ; 
	}//end if
	
	printf("Enter the ID of the book you want to borrow: \n");//promting the user
	scanf("%d" , &ID);//storing the input
	int index = -1;
	for(int i = 0 ; i <totalBooks ; i ++){
		if(bookIDs[i] == ID){
			index = ID;
		}// end if 
	}//end for 
	
	if(index == -1){
		printf("invalid book ID.\n");
		return ; 
	}//end if
	
	if(availableCopies[index] <= 0){
		printf("sorry mo more copies available.\n");
		return ;
	}// end if
	
	for(int i = 0 ; i <*borrowedCount ; i ++){
		if(borrowedBookIDs[i] == ID){
			printf("you have already borrowed this book.\n");
			return;
		}//end if
	}//end for loop
	int days;
	printf("Enter th number of dasy u  want to keep the book: ");
	scanf("%d", &days);
	
	if(days <=0){
		printf("Number of days must be positive.\n");
		return;
	}//end  if
	int max_days;
	if(memberType == 1)
		max_days = 14;
	else 
		max_days = 30;
	
	if(days > max_days)
		printf("your premitted prios id %d days. fine applies if kept beyond that.\n" , max_days);
	
	borrowedBookIDs[*borrowedCount] = ID;
	(*borrowedCount)++;//incrementing the count 
	availableCopies[index] --;//derecmenting count of available copies 
	
	printf("You borrowed %s", bookTitles[index]);//printing title of the book borrowed 
}//end function borrow book



float returnBook(int bookIDs[], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType, float *totalFine){
	int return_id ;
	printf("Enter the id of the book u want to return: \n");
	scanf("%d" ,&return_id);
	int id ;
	for(int i = 0 ; i <totalBooks; i++){
		if(bookIDs[i] == return_id)
			 id = i;
	}
	int pos;
	for(int j = 0; j<*borrowedCount; j++){
		if(borrowedBookIDs[j] == return_id)
			pos = j;
	}
	
	if(id == -1 || pos == -1){
		printf("you have not borrowed a book with this ID.\n");
		return 0 ;
	}
	int actual_days;
	printf("Enter the actual number of days the book was kept: ");
	scanf("%d" , &actual_days);
	if(actual_days <=0){
		printf("Number of days must be positive.\n");
		return 0;
	}
	
	int max_days;
	if(memberType == 1)
		max_days = 14;
	else 
		max_days = 30;
	int extra_days;
	float  fine;
	char fine_code[30];
	if(actual_days >max_days){
		extra_days = actual_days - max_days;
		if(memberType == 1)
			fine = extra_days * 20.0f;
		else 
			fine = extra_days * 10.0f;
		
		printf("the book is returned late the fine is %.2f" , fine);
		
		*totalFine += fine ;
		
		printf("Enter the membership code for waiver or enter A to skip: ");
		scanf("%29s" , fine_code);
		
		if(strcmp(fine_code , "LIB2026") == 0 ){
			fine = fine * 0.5f;
			printf("Code accepted 50% waiver applied final amount to pay is %.2f\n" , fine);
		}//end  inner if
		else {
			printf("Incorrect code no waiver applied\n");
		}//end else
	}// end outer if
	else {
		printf("Book Retruned without fine\n");
	}//end outer elsex
	
	availableCopies[id]++;
	for(int i =pos ; i <*borrowedCount -1 ; i++)
		borrowedBookIDs[i] = borrowedBookIDs[i+1] ;
	
	(*borrowedCount)--;
	
	return fine ;

}// end function return book

void displayMemberRecord(char name[], int studentID, int memberType, int borrowedBookIDs[],int borrowedCount, float totalFine, float fineAfterWaiver){
	printf("\n===== MEMBER RECORD =====\n");
	printf("Name: %s\n" , name);
	printf("Student ID: %d\n" , studentID); 
	printf("Membership Type: %s\n" , memberType == 1? "Student" : "Faculty");
	printf("Currently borrowed books: ");
	if(borrowedCount == 0)
		printf("None");
	for(int i = 0; i <borrowedCount; i ++){
		printf("%d " , borrowedBookIDs[i]);
	}//end for 
	
	printf("\nTotal fine charged (before waiver): Rs. %.2f\n", totalFine);
    printf("Final fine payable (after waiver): Rs. %.2f\n", fineAfterWaiver);
}//end function displayMemberRecord 


int main(){
	int BookIDs[4] = {101,102,103,104};
	char BookTitles[4][50] = {"Programming fundamentals" , "Calculus and analytical geometry", "ICP" ,"Data Science"};
	int AvailableCopies[4] = {5,3,0,4};
	int TBooks = 4 ;
	char name[50] = "";
	int StudentID = 0 , MemberType = 0 ;
	int choice ;
	
	

	float Tfine = 0.0 , FineAfterWaiver= 0.0;
	int BorrowCount =0 , Registered =0;
	int BorrowedBookIDs[3];
	do{
		displayMenu();
		scanf("%d" ,&choice);
		
		switch(choice){
		case 1:
			registerMember(	name, &StudentID, &MemberType);
			BorrowCount = 0 ;
			Tfine = 0.0;
			FineAfterWaiver = 0;
			Registered =1 ;
			
			break;
		case 2:
			displayBooks(BookIDs , BookTitles , AvailableCopies ,TBooks );
			
			break;
		case 3:
			if(!Registered) printf("PLease register first (option 1).\n");//checking if the member is registered or not
			else borrowBook(BookIDs,BookTitles, AvailableCopies , TBooks ,BorrowedBookIDs, &BorrowCount ,MemberType);
			
			break;
		case 4:
			if(!Registered) printf("PLease register first (option 1).\n");//checking if the member is registered or not
			else FineAfterWaiver +=returnBook(BookIDs, AvailableCopies,TBooks ,BorrowedBookIDs, &BorrowCount , MemberType, &Tfine);
		
			break;
		case 5:
			if(!Registered) printf("PLease register first (option 1).\n");//checking if the member is registered or not
			else displayMemberRecord(name, StudentID, MemberType, BorrowedBookIDs, BorrowCount, Tfine, FineAfterWaiver);
			
			break;
		case 6 :
			printf("Goodbye\n");
			
			break;
		default:
			printf("Invalid Choice! please enter 1-6.\n");//invalid choice handling
	}// end swtich 

	}while(choice !=6); // end do while loop
}//end main function


