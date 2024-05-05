# **Eastern-CinePlex** #
![Eastern Cineplex](Pic-Eastern-Cineplex.jpeg)
<sup>AI generated image.</sup>

## **Our Team** ##
1) [Abhishek Niraula](https://github.com/AbhishekNiraula)

2) [Sneha Karna](https://github.com/snehaa1278)

3) [Prashan Chenta Rai](https://github.com/PrashanRaii)

4) [Dhiraj Bikram Rai](https://github.com/hdhirajbrai17)


## **Project Description** ##

**Eastern-CinePlex** is a group Project developed for the submission of the final project for C-Programming as I/I (first-year first part) students of electronics engineering at IOE Purwanchal Campus, Dharan. The project reflects a movie ticket management system that allows admin and user login functionality.

**Eastern-CinePlex** is a non-gui project that runs on a terminal and reflects just the internal logic behind how a ticket management system might function in the real world. The primary highlight of the project is a well-thought interface for the terminal.

The project allows users to register with their username, password, and phone number while an admin is hard-coded into the application. The user can view the current movies in the listing, select the film to view available shows and seats and book the ticket. The admin can change the ticket price, add a film to the listing, create shows, and view already booked shows and earned balance.

## How to run the project??
- Download all the files in one folder it must include `extra.h`, `main.c`, `users.txt`, `user.c`, `login.c`, and `admin.c` files.
- Run `gcc main.c -o main` or Build `main.c` file.
- Run `./main` or execute the `main.c` file.
- `admin-interface` access is hardcoded and the credentials are:
    - Username: `Abhishek`
    - Password: `pass`

## Additional Info:
- Previously, when the project was presented in front of our respected teacher there was a big loophole with the project i.e on exiting the program with `CTRL + C` all of the changed data would be flushed except for user data which was saved with file handling.

- But, now with updated code all of the data that are changed will be intact in three files `reserve.txt`, `movies.txt`, and `users.txt`
and loaded as the user interacts with the program.
- If in any case there is an issue with executing `main.exe` you can delete it and rerun the program. If there is an issue with files, the files can just be deleted and they will be created again by the program itself.
