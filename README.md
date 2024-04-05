# Course Management System

This is a simple course management system implemented in C, designed to manage course data using hash tables with linear probing and double probing collision resolution techniques.

## Project Overview

The Course Management System is designed to facilitate the management of course data within an educational institution. Its primary goal is to provide a robust and efficient platform for storing, retrieving, and manipulating information related to courses offered by the institution.

## Features

- **Hash Table Implementation:** Utilizes hash tables for efficient storage and retrieval of course data.
- **Collision Resolution:** Implements collision resolution techniques including linear probing and double hashing.
- **File I/O:** Reads course data from a text file and writes data back to another text file.
- **User Interaction:** Provides a command-line interface for user interaction, allowing users to perform operations such as insertion, deletion, search, and comparison between hash table implementations.
  
## How to Use

1. **Compilation:** Compile the source code using a C compiler. For example, using `gcc`:
    ```
    gcc main.c -o course_management
    ```

2. **Execution:** Run the compiled executable:
    ```
    ./course_management
    ```

3. **Menu Options:** Once the program is running, follow the menu options to interact with the system.

## Menu Options

The program provides the following menu options:
1. Print hashed tables (including empty spots).
2. Print out table size and the load factor.
3. Print out the used hash functions.
4. Insert a new record to the hash table (insertion will be done on both hash tables).
5. Search for a specific word (specify which table to search in).
6. Delete a specific record (from both tables).
7. Compare between the two methods in terms of the number of collisions occurred.
8. Save hash table back to a file named saved_courses.txt (of the double hashing).

## File Structure

- **main.c:** Contains the main code implementation.
- **offered_courses.txt:** Input file containing course data.
- **saved_courses.txt:** Output file where the double hashing hash table is saved.
