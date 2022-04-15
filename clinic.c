#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
        "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
            "Number: %05d\n"
            "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
            patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
            "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
            "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
    const struct Appointment* appoint,
    int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
            appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
        patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu (hub) for application
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
            "=========================\n"
            "1) PATIENT     Management\n"
            "2) APPOINTMENT Management\n"
            "-------------------------\n"
            "0) Exit System\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
            "=========================\n"
            "1) VIEW   Patient Data\n"
            "2) SEARCH Patients\n"
            "3) ADD    Patient\n"
            "4) EDIT   Patient\n"
            "5) REMOVE Patient\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
            "=========================\n"
            "1) NAME : %s\n"
            "2) PHONE: ", patient->patientNumber, patient->name);

        displayFormattedPhone(patient->phone.number);

        printf("\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
            "==============================\n"
            "1) VIEW   ALL Appointments\n"
            "2) VIEW   Appointments by DATE\n"
            "3) ADD    Appointment\n"
            "4) REMOVE Appointment\n"
            "------------------------------\n"
            "0) Previous menu\n"
            "------------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    displayPatientTableHeader();
    int i; //iterator
    int found = 0; //a count when patientNumber is found
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber > 0)
        {
            displayPatientData(&patient[i], fmt);
            found++; // add 1 to found
        }
    }
    printf("\n"); // add a new line
    if (found == 0) // if did not found patientNumber
    {
        // Print the no record found message
        printf("*** No records found ***");
    }
}

// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max)
{
    int selection; // select between 0, 1, and 2

    do
    {
        printf("Search Options\n"
            "==========================\n"
            "1) By patient number\n"
            "2) By phone number\n"
            "..........................\n"
            "0) Previous menu\n"
            "..........................\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 1: // when selection = 1
            searchPatientByPatientNumber(patient, max);
            break;
        case 2: // when selection = 2
            searchPatientByPhoneNumber(patient, max);
            break;
        }

    } while (selection);
}

// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max)
{
    int i;
    int index = -1;
    for (i = 0; i < max && index == -1; i++)
    {
        if (patient[i].patientNumber == 0)
        {
            //index = i; //find the index that have no patient number
            index = i;

        }
    }
    if (index == -1)
    {
        // Print error message when there's no empty slot
        printf("ERROR: Patient listing is FULL!\n\n");
    }
    else
    {
        // Get a new patient number when adding a new patient
        patient[index].patientNumber = nextPatientNumber(patient, max);

        // Input patient data in the empty slot
        inputPatient(&patient[index]);

        // Print a message when new patient is successfully added
        printf("*** New patient record added ***\n\n");
    }

}

// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max)
{
    int num; //patient number
    int index = -1; // index/element does not exits
    printf("Enter the patient number: "); // Prompt user to enter patientNumber
    scanf("%d", &num); // User input the patientNumber
    printf("\n");

    // find patient and assign the index/element found in index
    index = findPatientIndexByPatientNum(num, patient, max);

    if (index != -1)
    {
        menuPatientEdit(&patient[index]);
    }
    else
    {
        printf("ERROR: Patient record not found!");
    }
}

// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max)
{
    int num = 0;
    int i = 0;
    int selection; // selection between y or n
    int index = -1;

    printf("Enter the patient number: ");
    scanf("%d", &num);
    printf("\n");
    index = findPatientIndexByPatientNum(num, &patient[i], max);

    if (index != -1)
    {
        displayPatientData(&patient[index], FMT_FORM);
        printf("\nAre you sure you want to remove this patient record? (y/n): ");
        selection = !(inputCharOption("yn") == 'y');

        if (!selection)
        {
            //remove the patient data
            patient[index].patientNumber = 0;
            memset(patient[index].name, '\0', NAME_LEN);
            memset(patient[index].phone.description, '\0', PHONE_DESC_LEN);
            memset(patient[index].phone.number, '\0', PHONE_LEN);

            printf("Patient record has been removed!\n\n");
        }
        else
        {
            printf("Operation aborted.\n\n");
        }
    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }
    clearInputBuffer();
}


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
void viewAllAppointments(struct ClinicData* data)
{
    int i;
    int j;
    int k;

    // Sorting the data by date and time
    for (i = 0; i < data->maxAppointments - 1; i++)
    {
        for (j = 0; j < data->maxAppointments - 1 - i; j++)
        {
            if (compareData(&data->appointments[j],
                &data->appointments[j + 1]) == 1)
            {
                // Swap data if latter data is less than the former data
                swap(&data->appointments[j], &data->appointments[j + 1]);
            }
        }
    }

    displayScheduleTableHeader(&data->appointments->date, 1);

    for (i = 0; i < data->maxAppointments; i++)
    {
        if (data->appointments[i].patientID != 0)
        {
            k = slotByID(data, data->appointments[i].patientID);

            if (k >= 0)
            {
                // Display data if there is an appointment
                displayScheduleData(&data->patients[k],
                    &data->appointments[i], 1);
            }
        }
    }

    putchar('\n');

}

// View appointment schedule for the user input date
void viewAppointmentSchedule(struct ClinicData* data)
{
    int i;
    int j;
    struct Date date = { 0 };

    inputDate(&date);
    putchar('\n');

    displayScheduleTableHeader(&date, 0);

    for (i = 0; i < data->maxAppointments; i++)
    {
        if (data->appointments[i].date.year == date.year &&
            data->appointments[i].date.month == date.month &&
            data->appointments[i].date.day == date.day)
        {
            j = slotByID(data, data->appointments[i].patientID);

            if (j >= 0)
            {
                // Display data depending on valid inputDate
                displayScheduleData(&data->patients[j], &data->appointments[i], 0);
            }
        }
    }

    putchar('\n');
}

// Add an appointment record to the appointment array
void addAppointment(struct Appointment* apptm, int maxAppointment,
    struct Patient* patients, int maxPatient)
{
    int i = 0;
    int counter = 0;
    int availTimeSlot; // 0 = avail time slot and 1 = not available
    struct Appointment tmp = { 0 };

    // Count how many appointment we currently have
    for (i = 0; i < maxAppointment; i++)
    {
        if (apptm[i].patientID != 0)
        {
            counter++;
        }
    }

    // Prompt user to input patient number
    printf("Patient Number: ");
    tmp.patientID = inputInt();

    do
    {
        availTimeSlot = 0;
        inputDate(&tmp.date);
        inputTime(&tmp.time);
        putchar('\n');

        for (i = 0; i < maxAppointment; i++)
        {
            if (apptm[i].date.year == tmp.date.year &&
                apptm[i].date.month == tmp.date.month &&
                apptm[i].date.day == tmp.date.day &&
                apptm[i].time.hour == tmp.time.hour &&
                apptm[i].time.min == tmp.time.min)
            {
                availTimeSlot++;
                printf("ERROR: Appointment timeslot is not available!\n\n");
            }
        }

    } while (availTimeSlot != 0);

    // Assign tmp data to apptm
    apptm[counter].patientID = tmp.patientID;
    apptm[counter].date.year = tmp.date.year;
    apptm[counter].date.month = tmp.date.month;
    apptm[counter].date.day = tmp.date.day;
    apptm[counter].time.hour = tmp.time.hour;
    apptm[counter].time.min = tmp.time.min;

    printf("*** Appointment scheduled! ***\n\n");
}

// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment* apptm, int maxAppointment,
    struct Patient* patients, int maxPatient)
{
    int i;
    int j;
    int index = 0;
    int counter = 0;
    int selection;
    struct Appointment tmp;

    // Prompt user for patient number
    printf("Patient Number: ");
    tmp.patientID = inputInt();

    for (i = 0; i < maxAppointment; i++)
    {
        if (apptm[i].patientID == tmp.patientID) // if found patient with ID
        {
            counter = 1;
            break; // get out of the loop
        }
    }

    if (counter == 0) // if patient was not found
    {
        // Display error message
        printf("ERROR: Patient record not found!\n\n");
        return; // return to the function that called this function
    }

    inputDate(&tmp.date);
    putchar('\n');

    for (i = 0; i < maxAppointment; i++)
    {
        if (apptm[i].patientID == tmp.patientID &&
            apptm[i].date.year == tmp.date.year &&
            apptm[i].date.month == tmp.date.month &&
            apptm[i].date.day == tmp.date.day)
        {
            index = i;
            break;
        }
    }

    for (i = 0; i < maxPatient; i++)
    {
        // Compare patient in struct Patient with patientID in struct Appointment
        if (patients[i].patientNumber == apptm[index].patientID)
        {
            j = i;
            break;
        }
    }

    displayPatientData(&patients[j], FMT_FORM);

    // Prompt user to decide if they want to remove appointment
    printf("Are you sure you want to remove this appointment (y,n): ");
    selection = !(inputCharOption("yn") == 'y');
    putchar('\n');

    if (!selection) // if y (yes)
    {
        apptm[index].patientID = 0;
        apptm[index].date.year = 0;
        apptm[index].date.month = 0;
        apptm[index].date.day = 0;
        apptm[index].time.hour = 0;
        apptm[index].time.min = 0;
        printf("Appointment record has been removed!\n\n");
    }
    else // if n (no)
    {
        printf("Operation aborted.\n\n");
    }
    clearInputBuffer();
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int num;
    int index = -1; // when record is not found
    printf("Search by patient number: ");
    scanf("%d", &num);
    index = findPatientIndexByPatientNum(num, patient, max);
    if (index != -1)
    {
        printf("\n");
        displayPatientData(&patient[index], FMT_FORM);
        printf("\n");
    }
    else
    {
        printf("\n*** No records found ***\n\n");
    }
    clearInputBuffer();
    suspend();
}

// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    char num[PHONE_LEN + 1] = "";
    int i;
    int index = -1;
    printf("Search by phone number: ");
    scanf("%s", num);
    printf("\n");
    displayPatientTableHeader();
    for (i = 0; i < max; i++)
    {
        if (strcmp(num, patient[i].phone.number) == 0)
        {
            displayPatientData(&patient[i], FMT_TABLE);
            index = 1;
        }
    }

    if (index == -1)
    {
        printf("\n*** No records found ***\n");
    }
    printf("\n");
    clearInputBuffer();
    suspend();
}

// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max)
{
    int i = 0;
    int largestNumber; // largest patientNumber
    largestNumber = patient[0].patientNumber;

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber > largestNumber)
        {
            // assign the largest patient number to largestNumber
            largestNumber = patient[i].patientNumber;
        }
    }

    largestNumber = largestNumber + 1;

    return largestNumber;
}

// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber,
    const struct Patient patient[], int max)
{
    int i;
    int index = -1;

    for (i = 0; i < max && index == -1; i++)
    {
        if (patientNumber == patient[i].patientNumber)
        {
            index = i; //position of matched element is returned

        }
    }
    return index;

}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient)
{
    // Display banner and data about the patient
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    //scanf("%15[^\n]", patient->name);
    inputCString(patient->name, 1, NAME_LEN);
    printf("\n");
    clearInputBuffer();
    inputPhoneData(&patient->phone);
}

// Get user input for phone contact information
void inputPhoneData(struct Phone* phone)
{
    int selection;
    //int validPhone;

    printf("Phone Information\n"
        "-----------------\n"
        "How will the patient like to be contacted?\n"
        "1. Cell\n"
        "2. Home\n"
        "3. Work\n"
        "4. TBD\n"
        "Selection: ");
    selection = inputIntRange(1, 4);
    putchar('\n');
    switch (selection)
    {
    case 1:
        strcpy(phone->description, "CELL"); //Copy CELL into phone description
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputCString(phone->number, PHONE_LEN, PHONE_LEN);
        printf("\n");
        clearInputBuffer();
        break;
    case 2:

        strcpy(phone->description, "HOME");
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputCString(phone->number, PHONE_LEN, PHONE_LEN);
        printf("\n");
        clearInputBuffer();
        break;
    case 3:
        strcpy(phone->description, "WORK");
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputCString(phone->number, PHONE_LEN, PHONE_LEN);
        printf("\n");
        clearInputBuffer();
        break;
    case 4:
        strcpy(phone->description, "TBD");
        strcpy(phone->number, "");
        break;
    }
}

// Get user input for the date
void inputDate(struct Date* date)
{
    int leapYear; // 1 for True and 0 for False
    int min = 1;
    int maxMonth = 12;
    int maxDay;

    // Prompt user for the year
    printf("Year        : ");
    date->year = inputInt();

    // See if the year is a leap year (%4)
    if (date->year % 4 == 0)
    {
        leapYear = 1;
    }
    else
    {
        leapYear = 0;
    }

    // Prompt for the month
    printf("Month (%d-%d): ", min, maxMonth);
    date->month = inputIntRange(min, maxMonth);

    if (date->month < min || date->month > maxMonth)
    {
        printf("Please input a valid month (%d-%d)\n", min, maxMonth);
    }

    // max will change depending on the month
    if (date->month == 2 && leapYear == 1)
    {
        maxDay = 29;
    }
    else if (date->month == 2)
    {
        maxDay = 28;
    }
    else if (date->month == 1 || date->month == 3 || date->month == 5 ||
        date->month == 7 || date->month == 8 || date->month == 10 ||
        date->month == 12)
    {
        maxDay = 31;
    }
    else
    {
        maxDay = 30;
    }

    // Prompt user for the day
    printf("Day (%d-%d)  : ", min, maxDay);
    date->day = inputIntRange(min, maxDay);

    if (date->day < min || date->day > maxDay)
    {
        printf("Please input a valid day of the month (%d-%d)\n", min, maxDay);
    }
}

// Get user input for the time
void inputTime(struct Time* time)
{
    int availableTimeSlot; // 0 = not available and 1 available time slot
    int min = 0;
    int maxHour = 23;
    int maxMinute = 59;

    do
    {
        // Prompt for the hour
        printf("Hour (%d-%d)  : ", min, maxHour);
        time->hour = inputIntRange(min, maxHour);

        // Prompt for the minute
        printf("Minute (%d-%d): ", min, maxMinute);
        time->min = inputIntRange(min, maxMinute);

        if ((time->hour >= 10 && time->hour <= 13) && (time->min == 0 || time->min == 30))
        {
            availableTimeSlot = 1;
        }
        else if (time->hour == 14 && time->min == 0)
        {
            availableTimeSlot = 1;
        }
        else
        {
            availableTimeSlot = 0;
            printf("ERROR: Time must be between 10:00 and 14:00 in 30 minute intervals.\n\n");
        }

    } while (!availableTimeSlot);
}


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Convert ID to slot#?
int slotByID(struct ClinicData* addr, int id)
{
    int i;

    for (i = 0; i < addr->maxPatient; i++)
    {
        if (addr->patients[i].patientNumber == id)
        {
            break;
        }

    }
    return i;
}

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    FILE* stream = fopen(datafile, "r"); // open file and read
    char buffer[80];
    int counter;
    char* nextToken;

    if (stream == NULL)
    {
        printf("READING ERROR...\n");
        return -1;
    }
    counter = 0;

    while (fgets(buffer, 80, stream) != NULL && counter < max)
    {
        buffer[strlen(buffer) - 1] = '\0';
        nextToken = strtok(buffer, "|");
        patients[counter].patientNumber = atoi(nextToken);

        // take value of the next field and save in nextToken
        nextToken = strtok(NULL, "|");

        // copy data of nextToken to name
        strcpy(patients[counter].name, nextToken);
        nextToken = strtok(NULL, "|");
        strcpy(patients[counter].phone.description, nextToken);

        if (strcmp(patients[counter].phone.description, "TBD") == 0)
        {
            // No phone number when description is TBD
            patients[counter].phone.number[0] = '\0';
        }
        else
        {
            nextToken = strtok(NULL, "|");
            strcpy(patients[counter].phone.number, nextToken);
        }
        counter++;
    }
    fclose(stream); // close the file
    return counter;
}

// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[],
    int max)
{
    FILE* fp = fopen(datafile, "r");
    int counter;

    if (fp == NULL)
    {
        printf("READING ERROR...\n");
        return -1;
    }
    counter = 0;

    while (fscanf(fp, "%d,%d,%d,%d,%d,%d", &appoints[counter].patientID,
        &appoints[counter].date.year,
        &appoints[counter].date.month,
        &appoints[counter].date.day,
        &appoints[counter].time.hour,
        &appoints[counter].time.min) == 6 && counter < max)
    {
        counter++;
    }
    fclose(fp);
    return counter;
}


//////////////////////////////////////
// Bubble Sort
//////////////////////////////////////

// Compare appointment data
int compareData(struct Appointment* appmt1, struct Appointment* appmt2)
{
    if (appmt1->date.year < appmt2->date.year)
    {
        return -1; // return -1 if value of a is less than b
    }
    else if (appmt1->date.year > appmt2->date.year)
    {
        return 1; // return 1 if value of a is greater than b
    }

    if (appmt1->date.month < appmt2->date.month)
    {
        return -1;
    }
    else if (appmt1->date.month > appmt2->date.month)
    {
        return 1;
    }

    if (appmt1->date.day < appmt2->date.day)
    {
        return -1;
    }
    else if (appmt1->date.day > appmt2->date.day)
    {
        return 1;
    }

    if (appmt1->time.hour < appmt2->time.hour)
    {
        return -1;
    }
    else if (appmt1->time.hour > appmt2->time.hour)
    {
        return 1;
    }

    if (appmt1->time.min < appmt2->time.min)
    {
        return -1;
    }
    else if (appmt1->time.min > appmt2->time.min)
    {
        return 1;
    }

    return 0;
}

// Swap appointment data
void swap(struct Appointment* appmt1, struct Appointment* appmt2)
{
    struct Appointment tmp;

    tmp = *appmt1; // assign data in appmt1 to tmp

    *appmt1 = *appmt2; // swap data
    *appmt2 = tmp;// store tmp data in appmt2
}