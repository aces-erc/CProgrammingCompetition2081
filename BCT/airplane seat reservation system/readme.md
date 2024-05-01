# Airline Ticketing System

This project is a simple airplane seat reservation system written in C. It was developed as part of the ACES C-Project Demonstration by the team members listed below.

## Team Members

- Rabin Kattel
- Prabin Sah
- Pramod Dhami
- Susan Sapkota

## Features

- **Register New User**: Allow users to add new passwords, including name, username, and password.
- **Login**: Enable users to log in with their credentials.
- **Update Password**: Users can update their username or password.
- **Book Tickets**: Reserve flights and make bookings.
- **View Old Tickets**: View previously booked tickets.

## File Structure

- `main.c`: Contains the main function and orchestrates the overall flow of the program.
- `passwordmanager.c`: Implements book management functionalities.
- `passwords.txt`: Stores the passwords in plain text format.

## Cloning and Building the Code

To clone and build the password manager code, follow these steps:

1. **Clone the Repository:**

   ```bash
   git clone https://github.com/yourusername/airline-ticketing-system.git
   cd airline-ticketing-system

####Build the Code:Use the following command to compile the source files using gcc:
    `gcc airline_ticketing_system.c -o airline_ticketing_system`


**Usage**
Login or Register: Choose either option to log in with existing credentials or register as a new user.
Book a New Flight: Reserve flights, select seats, and make payments.
View Old Tickets: Check previously booked tickets.
Update Information: Update profile details such as username or password.
Delete Data Records: Clear user data records.
Logout: Exit the program.
