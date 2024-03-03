# C-Project---Multi-User-Platform
Welcome to the "Multi-User Platform" project. This is a basic project written in C, designed as a practice exercise focusing on implementing read-write files features in the C programming language.

- C User Authentication and Management System
  
This C application serves as a practice project aimed at implementing a basic user authentication and management system. While the project primarily focuses on utilizing text files for data storage, it provides functionalities for user registration, login, and access to personalized user area.

- Features
  
User Registration: Users can register on the platform by providing necessary details which are stored in text files.

User Login: Registered users can log in to their accounts securely to access their personalized areas.

Root User Access: The root user has special privileges to manage the platform, including database resets and user removal.

Subscription Display: Users can view a list of subscriptions, displaying their account names and level.

Personalized User Area: Upon login, users are directed to their personalized areas where they can view their level, score, and permissions.

Level Progression: Users can increase their level by playing a basic game (wordle) and winning, earning a fixed amount of scores that accumulate over time.

The project is structured in a modular manner, with different functionalities encapsulated within separate C files.

database.c: This file contains the main execution logic of the program, encompassing the user interface and interaction. The program connects to its header files, housing additional program logic such as core functionalities and auxiliary operations.
The program manages data by creating .txt files for each registered user, named using a specific convention based on the user's name and surname initials, along with the total number of registered users at the time of registration. These .txt files store user information, facilitating access, reading, and writing operations related to the user's personal area, including permissions, level, and total experience.
Additionally, the program utilizes data.txt to store user information provided during registration, and an index.txt file to track the total number of registered users, enabling various user operations such as ID number management, accessing, and removal from the root menu. The index.txt file also serves as a reference for correct ID generation.

- Usage

The program is designed to be run from the command line interface (CLI). To use it, download all files, create an empty directory and name it "usr", place it where "database.c" is located, and run "database.c" within an integrated development environment (IDE).

Important Note: This program has been developed exclusively for Linux using C. As a result, it is fully compatible only with Linux operating systems. Attempting to run it on other operating systems may trigger a different string management system, leading to disruptions in internal logic and potential bugs.


The main menù with the available options, to access the enter the corresponding number
![1](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/f343a068-c91e-4a5d-a493-4669055b576d)

The program handles invalid input porperly
![2](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/b5de439d-bb2a-4a3e-98dd-8eeda4c71e73)

Limited-attempts system while doing log-in
![3](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/2cefbdf2-045f-4bdd-9fd3-ff1ad44d7c6a)

There's a root user (the first lines inside the data.txt) with special privileges
![4](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/a31aa3d4-e4a3-49cf-a06f-e7b9af648d4d)

This is the menu, with the available options.
![5](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/d364a716-6487-47a2-a4da-3ea93cb1ab60)

To delete an account from the platform, enter the corresponding ID
![7](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/ae327c64-f4dc-49a1-aafc-b6f1ca9a0475)
![6](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/8c6dfc63-9a93-4643-851f-29b2b9704970)

If you don't remember the ID of the associated account, enter the option 3 to show all the account's ID and their email.
![18](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/9900839d-460e-4228-b345-2f854893998e)

It handles non-existing ID
![9](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/ec6e590e-94a6-4633-9ef0-52a78b243ee3)

The option to reset the whole database will clean the data.txt and delete all the existing .txt files within the usr folder.
![8](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/1f9f78fd-3fa9-49cd-87d3-bc04570a847f)

Back to the main menu, registering will create a txt file inside the usr folder, and will generate some lines of text in the data.txt with the user's data. These lines will be read back from the program during the log-in.
![10](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/7f18952a-b397-42be-84e6-4820c9ace65f)

After registering, a defualt statistics belonging to the user will be created, and personal informations will be displayed.
There is also the possibility to access a game, to earn scores and increase the level.
![11](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/a744d89b-1ea9-48a6-8e55-ed0188b929ee)

The game support various modalities and each of them has a progressive increased difficulty.
![12](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/ffa92c0e-5abb-4a50-8835-26f4852643fd)
![13](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/fa57fc81-98f4-4bb2-bea4-20646dd95ed0)

The user has to guess a randomly choosen word among it's corresponding length words stored in txt file.
![15](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/2547fb9e-4927-48ec-9b38-9b8318dd2dd3)

After the game the score are updated.
![16](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/14204a1b-e6ee-4ce5-a042-5056c3723493)

Again back to the main menu, there is the option to display how many subcribers, with their name and level.
![17](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/9a35182b-83ab-4bad-9454-4484c3742e84)
