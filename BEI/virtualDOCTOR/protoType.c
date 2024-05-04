
#include<stdio.h>
#include<string.h>
#include<time.h>
#define MAX_SYMPTOMS 10


typedef struct patientDetail {
    char Name[25];
    int Age;
    char Sex[7];
    char contact[13];
} Patient;

// Structure to represent a condition
typedef struct {
    char name[50];
    char symptoms[MAX_SYMPTOMS][50];
    char cure[200];
} Condition;



void getPatient();
void inputSymptoms(char symptoms[MAX_SYMPTOMS][50],int*);
int evaluateSymptoms(char symptoms[MAX_SYMPTOMS][50], Condition conditions[],int num_conditions, int* ,char[][200]);
void generateReport(char symptoms[MAX_SYMPTOMS][50],struct patientDetail p,char name[], Condition conditions[],int num_conditions, int*,char cure[][200]);

void printDetails(struct patientDetail p );
char introMessage[] ="<---------------------------------C-PROJECT --------------------------------------->";
char message2[]=     "|                          VIRTUAL HEALTH DIAGNOSYS PROGRAM                        |";
char message3[]=     "------------------------------------------------------------------------------------";
int prevMatch=0;


//PlanB
typedef struct {
    char name[100];
    char timing[50];
    int isBooked;
} Doctor;

typedef struct {
    char patientName[100];
    char contactDetails[100];
} Appointment;

void listDoctors(Doctor doctors[], int size) {
    printf("Available Doctors:\n");
    for (int i = 0; i < size; i++) {
        if (!doctors[i].isBooked) {
            printf("%d. Dr. %s - Timing: %s\n", i + 1, doctors[i].name, doctors[i].timing);
        }
    }
}

void bookAppointment(Doctor doctors[], int size, Appointment appointments[]) {
    int choice;
    printf("Enter the number of the doctor you want to book: ");
    scanf("%d", &choice);
    getchar(); // Consume the newline character

    if (choice < 1 || choice > size) {
        printf("Invalid choice. Please try again.\n");
        return;
    }

    if (doctors[choice - 1].isBooked) {
        printf("This doctor is already booked. Please choose another doctor.\n");
    } else {
        printf("Enter your name: ");
        fgets(appointments[choice - 1].patientName, 100, stdin);
        appointments[choice - 1].patientName[strcspn(appointments[choice - 1].patientName, "\n")] = 0; // Remove newline

        printf("Enter your contact details: ");
        fgets(appointments[choice - 1].contactDetails, 100, stdin);
        appointments[choice - 1].contactDetails[strcspn(appointments[choice - 1].contactDetails, "\n")] = 0; // Remove newline

        doctors[choice - 1].isBooked = 1;
        printf("Appointment booked for %s with Dr. %s.\n", appointments[choice - 1].patientName, doctors[choice - 1].name);
    }
}

void cancelAppointment(Doctor doctors[], int size, Appointment appointments[]) {
    int choice;
    printf("Enter the number of the doctor whose appointment you want to cancel: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > size) {
        printf("Invalid choice. Please try again.\n");
        return;
    }

    if (!doctors[choice - 1].isBooked) {
        printf("This doctor does not have a booked appointment.\n");
    } else {
        doctors[choice - 1].isBooked = 0;
        printf("Appointment with Dr. %s has been canceled.\n", doctors[choice - 1].name);
    }
}

int main()
{ 
    system("clear");
     // Sample conditions and their symptoms
    printf("\t\t\t\t%s\n\t\t\t\t%s\n\t\t\t\t%s\n",introMessage,message2,message3);






    Condition conditions[] = {
    {"Cold", {"Cough", "Fever", "Runny Nose"}, "Rest, Drink Fluids"},
    {"Flu", {"Fever", "Headache", "Muscle Ache"}, "Rest, Drink Fluids, Take Antiviral Medications"},
    {"Allergy", {"Sneezing", "Itchy Eyes", "Runny Nose"}, "Avoid Allergens, Take Antihistamines"},
    {"Stomach Flu", {"Nausea", "Vomiting", "Diarrhea"}, "Rest, Drink Fluids, Electrolytes"},
    {"Headache", {"Headache", "Nausea", "Light Sensitivity"}, "Pain relievers, Rest in a dark room"},
    {"Stomach Ache", {"Stomach Cramps", "Nausea", "Diarrhea"}, "Hydration, Bland Diet"},
    {"Ear Infection", {"Earache", "Fever", "Drainage from Ear"}, "Antibiotics, Ear Drops"},
    {"Urinary Tract Infection (UTI)", {"Burning Sensation during urination", "Frequent urination", "Lower Abdominal Pain"}, "Antibiotics, Increased Fluids"},
    {"Anxiety", {"Feeling Restless", "Rapid Heartbeat", "Trouble Sleeping"}, "Relaxation Techniques, Meditation"},
    {"Depression", {"Loss of Interest in Activities", "Feeling Sad or Hopeless", "Changes in Sleep or Appetite"}, "Seek Professional Help, Consider Therapy or Medication"}
    };


    int N;
    int* Nptr=&N;
    int num_conditions = sizeof(conditions) / sizeof(conditions[0]);
    char patientName[25];
    char userSymptoms[MAX_SYMPTOMS][50];
    char sugcure[5][200];
    int planB;

    
    Patient p;
    
    printf("\t\t\t\t\t\tEnter Patient Name : ");
    fgets(p.Name,25,stdin);
    p.Name[strcspn(p.Name, "\n")] = '\0'; // Removes newline if one is found
    strcpy(patientName,p.Name);
    printf("\t\t\t\t\t\tEnter Age          : ");
    scanf("%d",&p.Age);
    printf("\t\t\t\t\t\tEnter Gender       : ");
    scanf("%s",p.Sex);
    printf("\t\t\t\t\t\tEnterContact       : ");
    scanf("%s",p.contact);


// Prompt user for symptoms
    
    printf("\t\t\t\t\t\tEnter %s's symptoms (type 'done' to finish):\n", patientName);
    inputSymptoms(userSymptoms,Nptr);
    
    // Evaluate symptoms and output possible conditions
    planB=evaluateSymptoms(userSymptoms, conditions, num_conditions, Nptr,sugcure);
    if (planB==0){
         Doctor doctors[] = {
        {"Arun Rai", "9AM - 11AM", 0},
        {"Puja Limbu", "11AM - 1PM", 0},
      {"Menuka Rai", "11AM - 1PM", 0},
        {"Pujan Khadaka", "2PM - 4PM", 0},
        {"Nisha Chaudhayy", "2PM - 4PM", 0},
        { "Aadarsha Bhusal", "2PM - 4PM", 0},
        { "Stark Tony", "2PM - 4PM", 0},
        { "Dhanjit Mahto", "2PM - 4PM", 0},
        { "Sachi Luitel", "2PM - 4PM", 0},
        { "Samikshya Khadka", "2PM - 4PM", 0},
        { "Jharana Bhattarai", "2PM - 4PM", 0}
    };
    Appointment appointments[sizeof(doctors) / sizeof(doctors[0])]; // Array to store appointments
    int size = sizeof(doctors) / sizeof(doctors[0]);
    int option;

    do {
        printf("\n1. List available doctors\n");
        printf("2. Book an appointment\n");
        printf("3. Cancel an appointment\n");
        printf("4. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                listDoctors(doctors, size);
                break;
            case 2:
                bookAppointment(doctors, size, appointments);
                break;
            case 3:
                cancelAppointment(doctors, size, appointments);
                break;
            case 4:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (option != 4);
    }

    // Generate report file
    generateReport(userSymptoms,p,patientName, conditions,num_conditions, Nptr,sugcure);

    
    
    
    
    
    printf("\n");
    return 0;
  


}



// Function to input symptoms from the user
void inputSymptoms(char symptoms[MAX_SYMPTOMS][50], int *N) {
    char symptom[50];
    *N = 0;
    int i = 0;

    while (1) {
        printf("\t\t\t\t\t\tSymptom %d: ", i + 1);
        getchar(); // Consume the newline character left in the input buffer
        scanf("%[^\n]", symptom);

        if (strcmp(symptom, "done") == 0) {
            break;
        }

        strcpy(symptoms[i], symptom);
        i++;
        *N = *N + 1;

        if (i == MAX_SYMPTOMS) {
            printf("Maximum number of symptoms reached.\n");
            break;
        }
    }
}


// Function to evaluate symptoms and output possible conditions
int evaluateSymptoms(char symptoms[MAX_SYMPTOMS][50], Condition conditions[], int num_conditions, int* N, char sugcure[][200]) {
    int successfulDiagnosis = 0; // Flag to track successful diagnosis

    // Loop through each condition
    for (int i = 0; i < num_conditions; i++) {
        int matchedSymptoms = 0;

        // Loop through each symptom of the condition
        for (int j = 0; j < *N; j++) {
            if (strcmp(symptoms[j], "") != 0) {
                // Check if the symptom matches any symptom of the condition
                for (int k = 0; k < MAX_SYMPTOMS; k++) {
                    if (strcmp(symptoms[j], conditions[i].symptoms[k]) == 0) {
                        matchedSymptoms++;
                        prevMatch++;
                        break;
                    }
                }
            }
        }

        // If at least half of the symptoms match, consider it as a possible condition
        if (matchedSymptoms >= 2) {
            printf("\n\t\t\t\tPossibilities:\n");
            float accuracy = 100 * ((float)(matchedSymptoms) / (*N));
            printf("\t\t\t\t\t\t- %s :  %.2f %%\n", conditions[i].name, accuracy);
            printf("  \t\t\t\t\t\tCure: %s\n", conditions[i].cure);
            strcpy(sugcure[i], conditions[i].cure);
            successfulDiagnosis = 1; // Set flag for successful diagnosis
        }
    }

    // If no condition matches, display the "Couldn't diagnose" message
    if (!successfulDiagnosis) {
        char option;
    printf("Sorry Couldn't Diagnose at The Moment\nTry Adding Proper Symptoms\nWould You Like To Consult with Doctors? [y/n]: ");
    scanf(" %c", &option); // Notice the space before %c to consume the newline character
    getchar(); // Consume the newline character left in the input buffer
    if(option == 'y' || option == 'Y') {
        return 0;
    }
}
}


// Function to generate a report file with patient's name and suggested cures for conditions
void generateReport(char symptoms[MAX_SYMPTOMS][50],struct patientDetail p,char name[], Condition conditions[],int num_conditions, int* N,char sugcure[][200]) {
    char filename[50];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    strcpy(filename, name);
    strcat(filename, ".txt");

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error creating report file.\n");
        return;
    }

    fprintf(fp,"\t\t\t\t\t\t\t\t\t\t\tVIRTUAL DIAGNOSIS\t\t\t\t\n\n\n");
    fprintf(fp, "\t\t\t\tPatient Name : %s",p.Name);
    fprintf(fp,"\t\t\t\t\tSex : %s",p.Sex);
    fprintf(fp, "\n\t\t\t\tAge : %d\t\t\t",p.Age);
    fprintf(fp,"\t\t\t\t\tDate:%d-%02d-%02d %02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,tm.tm_hour, tm.tm_min);
    fprintf(fp,"\t\t------------------------------------------------------------------------------\n\n\t\t\t\t\t\t\t\tSYMPTOMS: \n");

for(int i=0;i<=*N;i++){
    fprintf(fp,"\t\t\t\t\t\t\t\t-\t%s\n ",symptoms[i]);
}
    fprintf(fp,"\t\t\tResult    :\n\t\t");
    fprintf(fp,"\n\t\t\tSuggestion:\n\t\t");
    for(int i=0;i<=5;i++)
    {
        fprintf(fp,"%s",sugcure[i]);
    }
    
    fclose(fp);
    printf("\nReport file '%s' generated successfully.\n", filename);
}