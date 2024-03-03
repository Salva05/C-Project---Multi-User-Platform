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

database.c: Contains the main execution logic of the program, including user interface and interaction.
From there, the program connects to it's header files, where the other logics of the porgram lives, such as the root functionalities and the asides. The porgram manages the data by creating .txt files for each registered user, named with the first letter of the name, the last letter of the surname, and the number of total registered users at the moment of registration. That txt file contains user's informations from where the program stores and access/reads/write the informations related to the user's personal area, such as their permissions in the platform, the level, anfd the total experience. The porgram also uses the data.txt to store user's information received at the moment of registration, and an index.txt file wich allos the program to read the amount of total user registered and base the user's operations such as ID number changes, accessing and removing users from the root menu, and it also serves as index for a correct ID generation.
