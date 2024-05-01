#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Appointment_Schedule
{
    char pat_name[50];
    int pat_age;
    // int pat_id;
    char pat_address[50];
    char app_date[20];
    char app_time[20];
} appnmt;
//FUNCTION DECLARATION
void app_display();
void app_choice();
void new_app();
void cng_app();
void view_app();
void cancel_app();
int appointment();