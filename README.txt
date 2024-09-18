******************************************************
General information
******************************************************
// Program: assingment2 movie.c
// Author: chung-yu, yang
// Date: 2/6/2023
// Description: 
1. Create a directory named "your_onid.movies.random" with permissions 
set to rwxr-x--- where "your_onid" is the user's ONID and "random" 
is a random number between 0 and 99999.
2.Parse the chosen file and find out the movies released in each year.
3.In the new directory, create one file for each year in which at least 
one movie was released. The file should be named "YYYY.txt" where YYYY is 
the 4 digit year, and have permissions set to rw-r-----.
4.Write the titles of all the movies released in a year within its respective file, one title per line.

OUTPUT:
to compile this program Do
gcc -std=c99 movie.c -o movie
and ./movie to run the program
1. Select file to process
2. Exit the program

Enter a choice from 1 to 2: 1

Which file you want to process?
Enter 1 to pick the largest file
Enter 2 to pick the smallest file
Enter 3 to specify the name of a file

Enter a choice from 1 to 3: 1
Now processing the chosen file named movies_large.csv
Created directory with name yang.movies.XXXXX

Enter a choice from 1 to 3: 2
Now processing the chosen file named movies_small.csv
Created directory with name yang.movies.XXXXX

Enter a choice from 1 to 3: 3
Enter the complete file name: movies_small.csv
Now processing the chosen file named movies_small.csv
Created directory with name yang.movies.XXXX

1. Select file to process
2. Exit the program
 
information
struct movie;

******************************************************
Data and file overview
******************************************************
The code is a C program that reads data about movies from a CSV file 
and stores it in a linked list of movie structures. The structure 
contains fields for the movie title, year, language(s), rating, and 
a pointer to the next movie in the list. The code includes functions 
to display movies based on different criteria, such as year and 
language, as well as functions to sort the movie list and display 
the highest-rated movie of each year. Additionally, it provides a 
function that changes a string to lowercase and another function to 
read the movie data from a CSV file and build the linked list.

******************************************************
Sharing and access information
******************************************************
This code reads a CSV file containing information about movies such a
s title, year, language, rating, etc. and performs various operations 
on it such as printing the movies released in a particular year, 
printing the movies released in a particular language, and printing 
the highest rated movie of every year. The code uses functions such 
as strtok_r, strcmp, qsort, atof, and atoi to parse and manipulate the 
data in the file. The movies are stored as objects of the "movie" 
structure, which contains fields for the title, year, language, rating, 
and a pointer to the next movie. The code uses dynamic memory allocation 
for the movie objects and for some of the string fields in the structure.

******************************************************
Methodological information
******************************************************
The code is a program written in the C language. It parses a CSV 
file that contains information about movies and processes this data. 
The information stored in the CSV file includes the title of the movie, 
its year of release, language(s), rating, and other details.

The code defines a movie structure to hold movie information, 
and contains functions that are used to manipulate the movie data 
stored in the CSV file. Some of these functions are:

movie_list(): reads data from the CSV file and stores it in a linked list
lowercase(): converts a string to lowercase
c_List(): creates a linked list from a given line in the CSV file
show_movie_year(): displays the title of movies released in a specified year
show_movies_language(): displays the title of movies released in a specified language
sort(): used to sort movie data based on year and rating
show_movie_rated(): displays the highest rated movie of every year
The program also uses standard C libraries such as stdio.h, stdlib.h, string.h, 
ctype.h, dirent.h, stdbool.h, sys/types.h, sys/stat.h, time.h, fcntl.h, and unistd.h.
 
******************************************************
Data-specific information
******************************************************
This code is an implementation in C of a movie database program. 
The program reads movie data from a CSV file and stores it in a 
linked list of movie structures. The code implements functions to 
display movies released in a specific year, movies released in a 
specific language, and the highest rated movie of every year. 
The code uses various library functions such as strtok_r, malloc, 
atof, strcmp, and qsort.