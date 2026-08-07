Personal Finance Manager (CLI)
Overview

This project is a Command Line Interface (CLI) Personal Finance Manager built in C++ using Object-Oriented Programming (OOP) principles.

Class Responsibilities

1. User

   Purpose
   Represents one registered user.

   A User object only stores information about a user.

   It does not perform login, file handling, or finance calculations.

   Stores
   User ID
   Username
   Password
   Example
   User
   {
   id = 1
   username = "prasanna"
   passwordHash = "89ad72..."
   }
   Common Functions
   getID()

   getUsername()

   getPassword()

   setUsername()

   setPassword()

2. UserManager
   Purpose

   Manages all users in the application.

   (All file handling Operations)

   Responsibilities
   Load users from file
   Save users to file
   Add new users
   Find users
   Check whether a username already exists

   Functions
   loadUsers()

   saveUsers()

   addUser()

   findUser()

   usernameExists()

3. AuthSystem
   Purpose

   Responsible for authentication.

   It determines whether a user can access the application.
   Uses UserManager to authenticate users.
   Maintains the currently logged-in user.
   Delegates all user storage operations to UserManager.
   Responsibilities
   Login
   Sign Up
   Logout
   Track the currently logged-in user

   Functions
   login()

   signup()

   logout()

   getCurrentUser()
