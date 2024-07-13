/****************************************************************************** 
This is to certify that this project is my own & partners work, based on 
my/our personal efforts in studying and applying the concepts learned. I/we 
have constructed the functions and their respective algorithms and 
corresponding code by me. The program was run, tested, and 
debugged by my own efforts. I further certify that I have not copied in 
part or whole or otherwise plagiarized the work of other students and/or 
persons. 
<VINCE ALEJSON V. ALEJANDRINO> - <12206342>
******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MONTHURFRI_TIMESLOTS 6
#define WEDSAT_TIMESLOTS 3
#define USERS 30
#define MAX_RESERVATION 3

typedef char str5 [6];
typedef char str15[16];
typedef char str100[101];

typedef struct dateTag
{
    int month;
    int day;
    int year;
}DateTag;
typedef struct dateTag dateType;

typedef struct userTag
{
    long idNumber;//
    str15 lastName;
    str15 firstName;
    str15 program;
    dateType date;
    str15 mondayThursdayFridayTimeslots;
    str15 wednesdaySaturdayTimeslots;
    int participants;
    str100 description;
    str5 room;
    int numRecord;
} UserTag;
typedef struct userTag userType;

/* GetDayOfWeek gets the day of the week for a given date 
@param year - indicates the year
@param month- represents month
@param day- represents what day
*/
int getDayOfWeek(int year, int month, int day) 
{
    int h;
    int daysInMonth;

    // Input validation: Check if year, month, and day are within valid ranges
    if (year < 1 || month < 1 || month > 12 || day < 1) 
    {
        printf("Invalid date: Please provide a valid year (>= 1), month (1-12), and day (>= 1).\n");
        // Return an error code. For simplicity, return -1 to indicate an error.
        return -1;
    }

    // Check if the day is within a valid range for the given month
   
    if (month == 2) 
    {
        // February
        daysInMonth = 28;
    } 
    else if (month == 4 || month == 6 || month == 9 || month == 11) 
    {
        // April, June, September, November
        daysInMonth = 30;
    } 
    else 
    {
        // All other months 
        daysInMonth = 31;
    }

    if (day > daysInMonth) 
    {
        printf("Invalid date: The day exceeds the number of days in the given month.\n");
        // Return an error code. For simplicity,  return -1 to indicate an error.
        return -1;
    }

    if (month < 3) 
    {
        month += 12;
        year--;
    }

    h = (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400 + 1) % 7;
    return h;
}

/* printCalendar is used to print the calendar for a specific month and year
@param year - indicates the year
@param month- represents month
*/
void printCalendar(int year, int month)
 {
    const char* months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
    const char* daysOfWeek[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int dayOfWeek, day, i;

    if (month < 1 || month > 12) 
    {
        printf("Invalid month. Please enter a month between 1 and 12.\n");
        return;
    }

    dayOfWeek = getDayOfWeek(year, month, 1);

    printf("%s %d\n", months[month - 1], year);
    for (i = 0; i < 7; i++) 
    {
        printf("%s ", daysOfWeek[i]);
    }
    printf("\n");

    for (i = 0; i < dayOfWeek; i++)
        printf("    ");

    for (day = 1; day <= daysInMonth[month - 1]; day++) 
    {
        printf("%3d ", day);
        if (++dayOfWeek > 6) 
        {
            dayOfWeek = 0;
            printf("\n");
        }
    }
    printf("\n");
}

/* displayAvailableTimeslot prints the available timeslots for the specific day 
@param dayofWeek - used to know the day (Monday-Saturday)
@param mondayThursdayFridayTimeslots- shows the timeslots given for that day
@param wednesdaySaturdayTimeslots- shows the (different) timeslots given for that day
*/
void displayAvailableTimeslot(int dayofWeek,   const char** mondayThursdayFridayTimeslots,  const char** wednesdaySaturdayTimeslots)
{
    int i;
    printf("AVAILABLE TIMESLOTS: \n\n");
    if (dayofWeek == 1 || dayofWeek == 2 || dayofWeek == 4 || dayofWeek == 5) 
    {
        for (i = 0; i < MONTHURFRI_TIMESLOTS; i++)
        {
                printf("%d. %s\n", i + 1, mondayThursdayFridayTimeslots[i]);  
        }
    } 
    else if (dayofWeek == 3 || dayofWeek == 6) 
    {
        for (i = 0; i < WEDSAT_TIMESLOTS; i++)
        {
                printf("%d. %s\n", i + 1, wednesdaySaturdayTimeslots[i]);
            
        }
    } 
    else 
    {
        printf("No available timeslots for the selected day.\n");
        return;
    }
}

/* count gets the number of records to keep track the maximum reservation 
@param userType S - is a struct used for the user
@param numRecords - number of records
@param ID- used to compare the IDs of the user 
*/
int count(userType S[], int numRecords, long ID)
{
    int count = 0;
    int i;
    for(i = 0; i < numRecords; i++)
    {
        if(S[i].idNumber == ID)
            count++;
    }

    return count;
}

/* convertRoom converts integer to string 
@param nChoice - used to know what room did the user pick 
*/
char* convertRoom(int nChoice)
{
    char* room[16] = {"Y0611","Y0612","Y0613","Y0614","A0611","A0612","A0613","A0614","G0001","G0002","G0003","G0004","M0211","M0212","M0213","M0214"};
    
   
        return room[nChoice-1];

}


/* convert used to convert integer to string to compare
@param day- represents what day
@param chosenTimeslot- integer to know what timeslot did the user choose
*/

char* convert(int day, int chosenTimeslot)
{
    char* mondayThursdayFridayTimeslots[6] = {"09:15 - 10:45", "11:00 - 12:30", "12:45 - 14:15","14:30 - 16:00", "16:15 - 17:45", "18:00 - 19:00"};
    char* wednesdaySaturdayTimeslots[3] = {"09:00 - 12:00", "13:00 - 16:00", "16:15 - 19:15"};
    if(day == 1 || day ==2 || day == 4 || day == 5)
    {
        return  mondayThursdayFridayTimeslots[chosenTimeslot-1];
    }
    else if( day == 3 || day == 6)
    {
        return  wednesdaySaturdayTimeslots[chosenTimeslot-1];
    }


}

/* checker is used to check if the room is available
@param userType S - is a struct used for the user
@param numRecords - number of records
@param month- represents month
@param day- represents what day
@param chosenTimeslot- integer to know what timeslot did the user choose
@param nChoice- used to know what room did the user pick 
*/

int checker(userType S[], int numRecords, int day, int month, int chosenTimeslot, int nChoice)
{
    int i;
    int valid = 1;
    for(i = 0; i < numRecords; i++)
    {
            if(month == S[i].date.month && day == S[i].date.day && strcmp(S[i].room, convertRoom(nChoice))==0 && strcmp(S[i].mondayThursdayFridayTimeslots, convert(day, chosenTimeslot)) == 0)
            {
                    printf("ROOM TAKEN!");
                    valid = 0;
            }    
    }
        return valid;
}



/* roomReservation is used to reserve room for the user
@param userType S - is a struct used for the user
@param userType tempEntry- used to store information temporarily
@param numRecords - number of records
@param month- represents month
@param day- represents what day
@param chosenTimeslot- integer to know what timeslot did the user choose
@param ID- used to compare the IDs of the user  
*/
void roomReservation(userType S[], userType* tempEntry,int numRecords, int day, int month, int chosenTimeslot, long ID)
{
    //str5 room[16] = {"Y0611","Y0612","Y0613","Y0614","AO611","AO612","AO613","AO614","G0001","G0002","G0003","G0004","M0211","M0212","MO213","MO214"};
 
    int nChoice;

     
if(count(S, numRecords, ID) < 3)
{

    system("cls");
    printf("\n=================================================================\n");
    printf("|                           Choose Room                         |\n");
    printf("=================================================================\n");
    printf("| 1. Auditorium (Yuchengco Building)       MAX 60 PARTICIPANTS  |\n");
    printf("| 2. Classroom (Andrew Building)           MAX 40 PARTICIPANTS  |\n");
    printf("| 3. Seminar Room (Gokongwei Building)     MAX 20 PARTICIPANTS  |\n");
    printf("| 4. Training Room (St. Miguel Building)   MAX 10 PARTICIPANTS  |\n");
    printf("===============================================================\n\n");
    printf("Enter number of Participants: ");
    scanf("%d", &tempEntry->participants);
    fflush(stdin);
    if(tempEntry->participants <=10)
    {

        do
        {
        printf("\n=========================================================\n");
        printf("| AUDITORIUM | CLASSROOM | SEMINAR ROOM | TRAINING ROOM |\n");
        printf("=========================================================\n");
        printf("| [1] Y0611  | [5] A0611 |  [9] G0001   |   [13] M0211  |\n");
        printf("| [2] Y0612  | [6] A0612 |  [10] G0002  |   [14] M0212  |\n");
        printf("| [3] Y0613  | [7] A0613 |  [11] G0003  |   [15] M0213  |\n");
        printf("| [4] Y0614  | [8] A0614 |  [12] G0004  |   [16] M0214  |\n");
        printf("=========================================================\n\n");
         printf("Choose Room: ");
         scanf("%d", &nChoice);
         fflush(stdin);
         }while(nChoice >= 16);
        if(checker(S,numRecords,day, month, chosenTimeslot, nChoice) != 0)
        {
            strcpy(tempEntry->room,convertRoom(nChoice));
            printf("Enter Description: ");
            scanf("%[^\n]s", tempEntry->description);
        }
  }
  else if(tempEntry->participants >= 11 && tempEntry->participants <=20)
  {
    do{
        printf("\n========================================\n");
        printf("| AUDITORIUM | CLASSROOM | SEMINAR ROOM |\n");
        printf("=========================================\n");
        printf("| [1] Y0611  | [5] A0611 |  [9] G0001   |\n");
        printf("| [2] Y0612  | [6] A0612 |  [10] G0002  |\n");
        printf("| [3] Y0613  | [7] A0613 |  [11] G0003  |\n");
        printf("| [4] Y0614  | [8] A0614 |  [12] G0004  |\n");
        printf("=========================================\n\n");
         printf("Choose Room: ");
         scanf("%d", &nChoice);
         fflush(stdin);
    }while(nChoice >= 12);
         if(checker(S,numRecords,day, month, chosenTimeslot, nChoice) != 0)
        {
            strcpy(tempEntry->room,convertRoom(nChoice));
            printf("Enter Description: ");
            scanf("%[^\n]s", tempEntry->description);
        }
    
  }
  else if(tempEntry->participants >= 21 && tempEntry->participants <=40)
  {
    do{
        printf("\n==========================\n");
        printf("| AUDITORIUM | CLASSROOM |\n");
        printf("==========================\n");
        printf("| [1] Y0611  | [5] A0611 |\n");
        printf("| [2] Y0612  | [6] A0612 |\n");
        printf("| [3] Y0613  | [7] A0613 |\n");
        printf("| [4] Y0614  | [8] A0614 |\n");
        printf("==========================\n\n");
         printf("Choose Room: ");
         scanf("%d", &nChoice);
         fflush(stdin);
        }while(nChoice >= 8);
        if(checker(S,numRecords,day, month, chosenTimeslot, nChoice) != 0)
        {
            strcpy(tempEntry->room,convertRoom(nChoice));
            printf("Enter Description: ");
            scanf("%[^\n]s", tempEntry->description);
        }
    
  }
  else if(tempEntry->participants >=41 && tempEntry->participants <=60)
  {
    do{ 
        printf("\n==============\n");
        printf("| AUDITORIUM |\n");
        printf("==============\n");
        printf("| [1] Y0611  |\n");
        printf("| [2] Y0612  |\n");
        printf("| [3] Y0613  |\n");
        printf("| [4] Y0614  |\n");
        printf("==============\n\n");
         printf("Choose Room: ");
         scanf("%d", &nChoice);
         fflush(stdin);
        }while(nChoice >=4 );
        
        if(checker(S,numRecords,day, month, chosenTimeslot, nChoice) != 0)
        {
            strcpy(tempEntry->room,convertRoom(nChoice));
            printf("Enter Description: ");
            scanf("%[^\n]s", tempEntry->description);
        }
    
    }
else
    {
        printf("YOU HAVE REACHED THE MAXIMUM RESERVATION!");
    }
    }
}

/* reservation lets the user input the information needed
@param userType S - is a struct used for the user
@param numRecords - number of records
@param mondayThursdayFridayTimeslots- shows the timeslots given for that day
@param wednesdaySaturdayTimeslots- shows the (different) timeslots given for that day
*/
void reservation(userType S[], int numRecords, const char** mondayThursdayFridayTimeslots,  const char** wednesdaySaturdayTimeslots)
{
    userType tempEntry;
    int year = 2023;
    int dayofWeek;
    const char* daysOfWeek[] = {"Saturday","Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    int chosenTimeslot;
    int month;
    int day;
   
    printf("Enter Last Name: ");
    scanf("%[^\n]s", tempEntry.lastName);
    printf("Enter First Name: ");
    scanf(" %[^\n]s", tempEntry.firstName);
    printf("Enter ID Number: ");
    scanf("%ld", &tempEntry.idNumber);
    printf("Enter Program (Ex. BSCS-ST): ");
    scanf(" %[^\n]s", tempEntry.program);
    do
    {
    printf("Enter the month (1-12): ");
    scanf("%d", &month);
     }while(month < 8);
    
    do{
    printf("Enter the day (1-31): ");
    scanf("%d", &day);
    }while(day > 31);

    dayofWeek = getDayOfWeek(year, month, day);
    tempEntry.date.year = year;
    tempEntry.date.month = month;
    tempEntry.date.day = day;
    printCalendar(year, month);
    if(dayofWeek != 6)
        printf("The selected day (%d-%d-%d) is: %s\n", day, month, year, daysOfWeek[dayofWeek+1]);
    else
        printf("The selected day (%d-%d-%d) is: %s\n", day, month, year, daysOfWeek[0]);
    displayAvailableTimeslot(dayofWeek, mondayThursdayFridayTimeslots,  wednesdaySaturdayTimeslots);
    
    printf("Choose your timeslot [1-3] for Wednesday/Saturday and [1-6] for Monday/Thursday/Friday): ");
    scanf("%d", &chosenTimeslot);
    if ((dayofWeek == 1 || dayofWeek == 2 || dayofWeek == 4 || dayofWeek == 5) && chosenTimeslot >= 1 && chosenTimeslot <= 6)
     {
        strcpy(tempEntry.mondayThursdayFridayTimeslots,mondayThursdayFridayTimeslots[chosenTimeslot]);
        printf("You reserved timeslot: %s\n", tempEntry.mondayThursdayFridayTimeslots);
     } 
    else if ((dayofWeek == 3 || dayofWeek == 6) && chosenTimeslot >= 1 && chosenTimeslot <= 3) 
    {
        strcpy(tempEntry.wednesdaySaturdayTimeslots,wednesdaySaturdayTimeslots[chosenTimeslot-1]);  
        printf("You reserved timeslot: %s\n",  wednesdaySaturdayTimeslots[chosenTimeslot-1]); 
    } 
    else 
    {
        printf("Invalid choice. Please choose a valid and available timeslot.\n");
        return;
    }

    roomReservation(S, &tempEntry , numRecords,day, month, chosenTimeslot, tempEntry.idNumber);

    S[numRecords]=tempEntry;
    printf("ADDED SUCCESSFULLY!\n");
}

/* editReservation gives a user a chance to edit his/her reservation
@param userType S - is a struct used for the user
@param numRecords - number of records
@param month- represents month
@param day- represents what day
@param chosenTimeslot- integer to know what timeslot did the user choose
*/
void editReservation(int numRecords, userType S[],int day, int month, int chosenTimeslot)
{
    long ID;
    int i;
    int index = -1;
    str5 room;
    int nChoice;
    if(numRecords == 0)
    {
        printf("EMPTY!\n");
         return;
    }

    printf("Enter ID number: ");
    scanf("%ld", &ID);
    fflush(stdin);
    printf("Enter room name to change: ");
    scanf("%[^\n]s", room);
    fflush(stdin);

    for(i = 0; i < numRecords; i++)
    {
        if(ID == S[i].idNumber && strcmp(room, S[i].room)==0)
        {
            index = i;
        }
    }

    if(index == -1)
    {
        printf("\nNo Entry Found!\n");
         return;
    }

    system("cls");
    printf("\n=================================================================\n");
    printf("|                           Choose Room                         |\n");
    printf("=================================================================\n");
    printf("| 1. Auditorium (Yuchengco Building)       MAX 60 PARTICIPANTS  |\n");
    printf("| 2. Classroom (Andrew Building)           MAX 40 PARTICIPANTS  |\n");
    printf("| 3. Seminar Room (Gokongwei Building)     MAX 20 PARTICIPANTS  |\n");
    printf("| 4. Training Room (St. Miguel Building)   MAX 10 PARTICIPANTS  |\n");
    printf("===============================================================\n\n");
    printf("Enter number of Participants: ");
    scanf("%d", &S[index].participants);
    fflush(stdin);
    if(S[index].participants <=10)
    {

        do
        {
        printf("\n=========================================================\n");
        printf("| AUDITORIUM | CLASSROOM | SEMINAR ROOM | TRAINING ROOM |\n");
        printf("=========================================================\n");
        printf("| [1] Y0611  | [5] A0611 |  [9] G0001   |   [13] M0211  |\n");
        printf("| [2] Y0612  | [6] A0612 |  [10] G0002  |   [14] M0212  |\n");
        printf("| [3] Y0613  | [7] A0613 |  [11] G0003  |   [15] M0213  |\n");
        printf("| [4] Y0614  | [8] A0614 |  [12] G0004  |   [16] M0214  |\n");
        printf("=========================================================\n\n");
         printf("Choose Room: ");
         scanf("%d", &nChoice);
         fflush(stdin);
         }while(nChoice >= 16);
        
        if(checker(S,numRecords,day, month, chosenTimeslot, nChoice) != 0)
        {
            strcpy(S[index].room,convertRoom(nChoice));
            printf("Enter Description: ");
            scanf("%[^\n]s", S[index].description);
        }
  }
  else if(S[index].participants >= 11 && S[index].participants <=20)
  {
    do{
        printf("\n========================================\n");
        printf("| AUDITORIUM | CLASSROOM | SEMINAR ROOM |\n");
        printf("=========================================\n");
        printf("| [1] Y0611  | [5] A0611 |  [9] G0001   |\n");
        printf("| [2] Y0612  | [6] A0612 |  [10] G0002  |\n");
        printf("| [3] Y0613  | [7] A0613 |  [11] G0003  |\n");
        printf("| [4] Y0614  | [8] A0614 |  [12] G0004  |\n");
        printf("=========================================\n\n");
         printf("Choose Room: ");
         scanf("%d", &nChoice);
         fflush(stdin);
    }while(nChoice >= 12);
         if(checker(S,numRecords,day, month, chosenTimeslot, nChoice) != 0)
        {
            strcpy(S[index].room,convertRoom(nChoice));
            printf("Enter Description: ");
            scanf("%[^\n]s", S[index].description);
        }
    
  }
  else if(S[index].participants >= 21 && S[index].participants <=40)
  {
    do{
        printf("\n==========================\n");
        printf("| AUDITORIUM | CLASSROOM |\n");
        printf("==========================\n");
        printf("| [1] Y0611  | [5] A0611 |\n");
        printf("| [2] Y0612  | [6] A0612 |\n");
        printf("| [3] Y0613  | [7] A0613 |\n");
        printf("| [4] Y0614  | [8] A0614 |\n");
        printf("==========================\n\n");
         printf("Choose Room: ");
         scanf("%d", &nChoice);
         fflush(stdin);
        }while(nChoice >= 8);
        if(checker(S,numRecords,day, month, chosenTimeslot, nChoice) != 0)
        {
            strcpy(S[index].room,convertRoom(nChoice));
            printf("Enter Description: ");
            scanf("%[^\n]s", S[index].description);
        }
    
  }
  else if(S[index].participants >=41 && S[index].participants <=60)
  {
    do{ 
        printf("\n==============\n");
        printf("| AUDITORIUM |\n");
        printf("==============\n");
        printf("| [1] Y0611  |\n");
        printf("| [2] Y0612  |\n");
        printf("| [3] Y0613  |\n");
        printf("| [4] Y0614  |\n");
        printf("==============\n\n");
         printf("Choose Room: ");
         scanf("%d", &nChoice);
         fflush(stdin);
        }while(nChoice >=4 );
        
        if(checker(S,numRecords,day, month, chosenTimeslot, nChoice) != 0)
        {
            strcpy(S[index].room,convertRoom(nChoice));
            printf("Enter Description: ");
            scanf("%[^\n]s", S[index].description);
        }
    
    }


}

/* cancelReservation gives a user a chance to cancel unwanted reservation
@param userType S - is a struct used for the user
@param numRecords - number of records
*/
void cancelReservation(int *numRecords, userType S[])
{
    long ID;
    int i;
    int index = -1;
    //char room[5];
   
    if(*numRecords == 0)
    {
        printf("EMPTY!\n");
        return;
    }

    printf("Enter ID number: ");
    scanf("%ld", &ID);

    for(i = 0; i < *numRecords; i++)
    {
        if(ID == S[i].idNumber)
        {
            index = i; 
        }
    }

    if(index == -1)
    {
        printf("\nNo Entry Found!\n");
        return;
    }

    for(i = index; i < *numRecords - 1; i++)
    {
        S[i] = S[i+1];
    }
    
    (*numRecords)--;
    printf("\nDELETED!\n");
}


/* viewAllReservation lets the user double check his/her reservation
@param userType S - is a struct used for the user
@param numRecords - number of records
*/
void viewAllReservation(userType S[], int numRecords)
{
    int i;

    if(numRecords == 0)
    {
        printf("EMPTY!\n");
        return;
    }

    printf("\nView All Reservation:\n");
    printf("---------------------------------------------------------------------------------------------\n");
  
    for(i = 0; i < numRecords; i++)
    {
        printf(" \n\nLast Name: %s \n First Name: %s \n ID: %ld \n Program: %s \n Date: %d-%d-%d \n MTF: %s \n WS: %s \n Description: %s \n Room: %s\n"
                , S[i].lastName, S[i].firstName, S[i].idNumber, S[i].program, S[i].date.month, S[i].date.day, S[i].date.year, S[i].mondayThursdayFridayTimeslots, S[i].wednesdaySaturdayTimeslots, S[i].description, S[i].room);
    }
}

/*txtImport is responsible for importing data to a file.
@param userType S[] - is a struct used for the user
@param numRecords - number of records*/
void txtImport(userType S[], int numRecords)
{
    FILE *fp;
    int i;

    fp = fopen("Records.txt","r");
    if(fp == NULL)
    {
        printf("ERROR: file does not exist.");
    }
    else
        printf("File opened successfully.\n");
    
    for(i = 0; i < numRecords; i++)
    {
        fscanf(fp,"%[^\n]s",S[i].lastName);
        fscanf(fp," %[^\n]s",S[i].firstName);
        fscanf(fp,"%ld",&S[i].idNumber);
        fscanf(fp," %[^\n]s",S[i].program);
        fscanf(fp,"%d",&S[i].date.month);
        fscanf(fp,"%d",&S[i].date.day);
        fscanf(fp,"%d",&S[i].date.year);
        fscanf(fp," %[^\n]s",S[i].mondayThursdayFridayTimeslots);
        fscanf(fp," %[^\n]s",S[i].wednesdaySaturdayTimeslots);
        fscanf(fp," %[^\n]s", S[i].description);
        fscanf(fp," %[^\n]s", S[i].room);
        
        
    }

    fclose(fp);
}


/*txtExport is responsible for exporting data to a file.
@param userType S[] - is a struct used for the user
@param numRecords - number of records*/
void txtExport(userType S[], int numRecords)
{

    FILE *fp;
    int i;

    fp = fopen("Records.txt","w");
    if(fp == NULL)
    {
        printf("ERROR: file does not exist.");
    }
    else
        printf("File opened successfully.\n");
    
    for(i = 0; i < numRecords; i++)
    {
        fprintf(fp, "\n\nLast Name: %s \nFirst Name: %s \nID: %ld \nProgram: %s \nDate: %d-%d-%d \nMTF: %s \nWS: %s \nDescription: %s \nRoom: %s\n" , S[i].lastName, S[i].firstName, S[i].idNumber, S[i].program, S[i].date.month, S[i].date.day, S[i].date.year, S[i].mondayThursdayFridayTimeslots, S[i].wednesdaySaturdayTimeslots, S[i].description, S[i].room);
    }

    fclose(fp);
}

int main()
{
    userType S[USERS*MAX_RESERVATION];
    int numRecords = 0; //tracks the number of user
    int nInput; 
    const char* mondayThursdayFridayTimeslots[6] = {"09:15 - 10:45", "11:00 - 12:30", "12:45 - 14:15","14:30 - 16:00", "16:15 - 17:45", "18:00 - 19:00"};
    const char* wednesdaySaturdayTimeslots[3] = {"09:00 - 12:00", "13:00 - 16:00", "16:15 - 19:15"};
    int day = 0;
    int month = 0;
    int chosenTimeslot = 0;

    txtImport(S,numRecords);
     
    

    system("cls");
    do
    {
        
        printf("[1] Make new reservation\n");
        printf("[2] Edit reservation\n");
        printf("[3] Cancel reservation\n");
        printf("[4] View all reservation\n");
        printf("[5] Exit Program\n");
        printf("Your Input: ");
        scanf("%d",&nInput);
        fflush(stdin);

        switch(nInput)
        {
            case 1: 
                    reservation(S, numRecords,mondayThursdayFridayTimeslots,wednesdaySaturdayTimeslots);
                    numRecords++;
                    break;
            case 2:
                    editReservation(numRecords, S, day, month, chosenTimeslot);
                    break;
            case 3:
                    cancelReservation(&numRecords, S);
                    break;
            case 4:
                    viewAllReservation(S, numRecords);
                    break;
            case 5:
                    printf("Thank you!");
                    break;
            default: 
                    printf("INVALID INPUT!");
                    break;
        }
    }while(nInput != 5);
    txtExport(S,  numRecords);
    return 0;
}