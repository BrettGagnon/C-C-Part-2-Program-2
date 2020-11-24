/*------------------------------------------------------------------------------

Program file: bgagnonp2.c
Author:       Brett Gagnon
Date:         2/17/2019
Assignment:   Program #2
Objective:    Write a C program that prompts the user for a date (mm/dd/yyyy). The program should then
take that date and use the formula on page 190 (see problem 2 in the textbook) to convert the
date entered into a very large number representing a particular date. This very large number
can be stored in a variable of type long integer, and is referred to in the formula below (and on
page 190) as N. Your assignment is to take the value stored in variable N and, using the
formula below, determine the number representing the day of the week that the date falls on.
That is, if the number calculated by the algorithm is zero, then the day is Sunday. If the number
calculated is a 1, then the day is Monday, etc.
              
------------------------------------------------------------------------------*/

#include <stdio.h>

/* Declare structure to hold date */
/*----------------------------------------------------------------------------*/
struct date
{
 int month;
 int day;
 int year;
};

/*function calc_date_number: which takes a date as an argument and returns a
number representing the date entered. */
/*----------------------------------------------------------------------------*/
int calc_date_number(struct date);

/* function calc_day_number: which takes as a parameter the number calculated
in calc_date_number, and returns the number (0 - 6) representing the day of
the week (Sunday - Saturday). */
/*----------------------------------------------------------------------------*/
int calc_day_number(int number);

/*function display_day_of_week: which takes as a parameter the N from the prior function.
You must then take this numeric representation of the day of the week, and use it as an
index into a character string array, to get the English representation of the day of the
week. */
/*----------------------------------------------------------------------------*/
void display_day_of_week(int number,struct date dt);

int main()
{
	/* Declare variables */
	/*------------------------------------------------------------------------*/
	struct date sdate; 	
	int day_num,n;
	int flag=1; 
	
	printf ("Welcome to the Date to Day-of-the-Week program\n\n");
	printf ("This program will give you the day of the week for any date from 1/1/1900\n");
	/* Repeat loop until valid date is entered */
	/*------------------------------------------------------------------------*/
	while(1) 
	{
		printf ("\nEnter date (mm/dd/yyyy): ");
		scanf("%d/%d/%d", &sdate.month, &sdate.day, &sdate.year); /*%d to account for 01 etc */
		flag=1; /*reset flag to true */
		
		/*Check if year is valid */
		/*--------------------------------------------------------------------*/
		if(sdate.year>=1900)
    	{
        /*Check month */
        if(sdate.month>=1 && sdate.month<=12)
        {
            /*Check days, accounting for dates that don't exist and leapyear */
            /*---------------------------------------------------------------*/
            if ((sdate.day >=1 && sdate.day<=31) && (sdate.month==1 || sdate.month==3 || sdate.month==5 || sdate.month==7 || sdate.month==8|| sdate.month==10 || sdate.month==12))
                printf("Date is valid.\n");
            else if((sdate.day>=1 && sdate.day<=30) && (sdate.month==4 || sdate.month==6 || sdate.month==9 || sdate.month==11))
                printf("Date is valid.\n");
            else if((sdate.day>=1 && sdate.day<=28) && (sdate.month==2))
                printf("Date is valid.\n");
            else if(sdate.day==29 && sdate.month==2 && (sdate.year%400==0 ||(sdate.year%4==0 && sdate.year%100!=0)))
                printf("Date is valid.\n");
            else
            /* Else Day entered is invalid, set flag to false, prompt error message and re-loop */
            /*---------------------------------------------------------------*/
            {
                flag=0; 
				printf("Invalid day. Please re-enter date.");
				continue;
            }
        }
        else
        /* Else invalid Month entered, set flag to false, prompt and re-loop */
        /*-------------------------------------------------------------------*/
        {
            flag=0; 
			printf("Invalid month. Please re-enter date.");
			continue;
        }
    }
    else
    /* Else invalid Year entered, set flag to false, prompt and re-loop */
    /*------------------------------------------------------------------*/
    {
        flag=0; 
			printf("\nInvalid year. Please re-enter date. Year must be greater than 1900.");
			continue; 
    }
		
		/* Stop the loop if the date entered is valid */
		/*-------------------------------------------------------------------*/
		if(flag) break; 
	}
	
	/* Call functions while assigning values to variables n and day_num */
	/*-----------------------------------------------------------------------*/
	n=calc_date_number(sdate);
	day_num=calc_day_number(n); 
	display_day_of_week(day_num,sdate); 
	
	return 0; /* end main */
}

/* Calc_date_number function */
/*----------------------------------------------------------------------------*/
int calc_date_number(struct date dt)
{
	/*If month is jan or feb, decrement the year and increment the month */
	/*------------------------------------------------------------------------*/
	int a,b,n;
	if (dt.month <= 2) 
		{
			a = dt.year - 1; 
			b = dt.month + 13; 
		}
		else
		/*Year remains same, increment month by 1 */
		/*--------------------------------------------------------------------*/
		{
			a = dt.year; 
			b = dt.month + 1; 
		}
	/*Calculate the Julian day number with following equation */
	/*------------------------------------------------------------------------*/	
	n = (( 1461 * a ) / 4) + (( 153 * b ) / 5) + dt.day; 
	return n;
}

/*Feed number from calc_date_number function into calc_day_number function
and apply formula from assignment sheet  */
/*-------------------------------------------------------------------------*/
int calc_day_number(int number)
{
	return (( number - 621049) % 7);
}

/*Take the number from the calc_day_number function and assign it to a weekday
from the days char string array */
/*--------------------------------------------------------------------------*/
void display_day_of_week(int number,struct date dt)
{

	char *days[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
	printf("%d/%d/%d falls on a %s.\n\n",dt.month,dt.day,dt.year,days[number]);
	printf("Thank you for using the Date to Day-of-Week program.\n");
}
