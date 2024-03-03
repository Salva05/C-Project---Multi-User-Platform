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

Usage: The program is meant to be ran from CLI. Download all the files and run database.c within an IDE.

![Screenshot from 2024-03-03 11-37-36](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/ebcc4f24-6778-4fc8-91a6-35ef3f933710)
![Screenshot from 2024-03-03 11-37-04](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/89dd0271-7c35-4dbe-9a1c-677e6607bba5)
![Screenshot from 2024-03-03 11-36-08](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/66fd68e4-ac9a-4a4f-aec5-deaecf93e925)
![Screenshot from 2024-03-03 11-35-58](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/1fb0f01b-303d-4d91-a978-f90a722d01c1)
![Screenshot from 2024-03-03 11-34-53](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/d0a1d3ed-1b55-4e7f-a446-94fe0c4ce10b)
![Screenshot from 2024-03-03 11-23-41](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/e2204f1b-6aa8-4685-bcc6-72ec16d99ae4)
![Screenshot from 2024-03-03 11-23-29](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/adb74f42-01f1-49dc-aee4-1f62911a58fb)
![Screenshot from 2024-03-03 11-23-08](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/7a0dcc71-833c-4f42-88d6-ef7de089a903)
![Screenshot from 2024-03-03 11-22-59](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/4a375876-afb5-472e-be81-5b8efe93d7d2)
![Screenshot from 2024-03-03 11-20-01](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/9972e988-777b-4876-b2d5-0ee7cd15db90)
![Screenshot from 2024-03-03 11-19-49](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/2ede9cf9-55f0-41b3-87cb-845cb4ad574e)
![Screenshot from 2024-03-03 11-19-36](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/99cb31d3-1254-4f77-9cad-111321ec9abb)
![Screenshot from 2024-03-03 11-19-05](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/ce3e7fa5-1455-4509-b553-094faa4fbfa2)
![Screenshot from 2024-03-03 11-18-30](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/a5aa5672-8fe1-4bd7-9190-34f9ecc6b0b4)
![Screenshot from 2024-03-03 11-18-20](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/915bed46-4d26-46fc-8c3f-0cb3f7ef2f98)
![Screenshot from 2024-03-03 11-16-30](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/f7366318-e957-43e0-bce7-a45325867da0)
![Screenshot from 2024-03-03 11-15-57](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/2b35aab2-b6a0-49d1-95ed-5ffae15f4adb)
![Screenshot from 2024-03-03 11-14-54](https://github.com/Salva05/C-Project---Multi-User-Platform/assets/141848378/d3747ea2-ec02-4bd6-a66b-b035a45eb878)
