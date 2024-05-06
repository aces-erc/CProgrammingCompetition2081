# Veloce: A Version Control System

Veloce is a version control system (VCS) built using C, designed to provide users with a fast and efficient way to manage their projects and codebase. The name "Veloce" is derived from the Indonesian word "velo" meaning version and Italian word "veloce" meaning swift or fast, reflecting its core philosophy of speed and efficiency.

This project was developed as part of the ACES C-Project Demonstration.

## Team Members

- [Kaushal Rijal](https://github.com/kaushalrijal)
- [Hariom Raj Chauhan](https://github.com/HariomRajChauhan)
- [Kaushal Kumar Roy](https://github.com/Prashantt6)
- [Guru Prakash Gupta](https://github.com/satguru117)

## Features

- **User Authentication:** Veloce allows users to sign up for an account and log in securely.
- **Repository Management:** Users can create repositories to organize their projects and code.
- **Commit Creation:** Veloce enables users to create commits to track changes in their codebase.
- **Commit Viewing:** Users can view commit history to understand the evolution of their projects.
- **Commit Reversion:** Veloce supports reverting to previous commits to roll back changes if needed.
- **Security Measures:** Veloce incorporates security features such as security questions and encrypted passwords to ensure user data remains protected.

## File Structure

- `main.c`: Contains the main function and orchestrates the overall flow of the program.
- `auth.c`: Handles user authentication and account management functionalities.
- `loading.c`: Manages loading and saving of user data using binary files with a `.dat` extension.
- `commits.c`: Implements commit creation, viewing, and reversion functionalities.
- `repos.c`: Handles repository management operations.

## Usage

### Cloning and Building the Code

To clone and build the Veloce code, follow these steps:

1. **Clone the Repository:**

   ```bash
   git clone https://github.com/kaushalrijal/Veloce
   cd Veloce
   ```

2. **Build the Code:**
   Use the following command to compile the source files using `gcc`:

   ```bash
   gcc -o vcs main.c commits.c auth.c repos.c loading.c
   ```

3. **Run Veloce:**
   After successfully building the code, you can run the compiled executable:
   ```bash
   ./vcs
   ```
   or if you're on Windows:
   ```bash
   vcs.exe
   ```

### Basic Workflow

1. **Sign Up/Login:** Create a new account or log in with existing credentials.
2. **Create Repositories:** Organize your projects by creating repositories.
3. **Make Commits:** Track changes to your codebase by creating commits.
4. **View Commit History:** Understand the evolution of your projects by viewing commit history.
5. **Revert to Commits:** Roll back changes if needed by reverting to previous commits.
