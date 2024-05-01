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

To clone and build the airline ticketing system code, follow these steps:

1. **Clone the Repository:**

   ```bash
   git clone https://github.com/tangwep/CProgrammingCompetition2081.git
   cd CProgrammingCompetition2081/BCT/airplane\ seat\ reservation\ system

2. **Build the Code:**
   Use the following command to compile the source files using gcc:
   ```bash
   gcc airline_ticketing_system.c -o airline_ticketing_system

### Things to consider before running the code 
1. flights.txt file are must before ruunig code as it needs data to display the flights in console. And then you can run airline_ticketing_system.c
