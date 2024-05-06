# Hotel Management System

## Team Members
- Aashish Mahat
- Angel Khanal
- Bipin Bista
- Gehendra Rai

## Description
This project is a basic implementation of a hotel management system in C. It allows users to perform various tasks such as booking rooms, ordering food, selecting programs, providing feedback, and more. The system also provides functionalities for staff members to view details and handle complaints/suggestions.

## Files
1. `hotel_management.c`: This file contains the main C code for the hotel management system.
2. `file.txt`: This text file is used to store customer details such as name, nationality, email, address, room number, room type, selected program, and bill price.
3. `complain.txt`: This file is used to store customer complaints and suggestions.

## Functions
- `main()`: Initializes the program and prompts users to enter their details.
- `begin()`: Displays the main menu and handles user choices.
- `book_room()`: Allows users to book a room of their choice.
- `program()`: Allows users to select programs such as jungle walk, jeep drive, canoe ride, or cultural show.
- `show_details()`: Displays customer details, accessible only for staff members after login.
- `login()`: Authenticates staff login credentials.
- `storedata()`: Stores customer details in the `file.txt` file.
- `foodmenu()`: Displays the food menu and allows users to order food.
- `complaints_suggestions()`: Allows users to provide complaints or suggestions, which are stored in the `complain.txt` file.

## Usage
1. Compile the `hotel_management.c` file.
2. Run the executable.
3. Follow the on-screen prompts to interact with the hotel management system.

**Note:**
- Ensure that all input data is valid and properly handled to prevent runtime errors.
- Regularly maintain and update the system to add new features and improve user experience.
