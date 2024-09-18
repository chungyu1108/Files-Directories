/**************************************************************************************************
// Program: movie.c
// Author: chung-yu, yang
// Date: 2/6/2023
// Description: Reads directory entries
Finds a file in the current directory based on user specified criteria
Reads and processes the data in the chosen file
Creates a directory
Creates new files in the newly created directory and writes processed data to these files
// ** Output: 
// 1. Show movies released in the specified year
// 2. Show highest rated movie for each year
// 3. Show the title and year of release of all movies in a specific language
// 4. Exit from the program
****************************************************************************************************/
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h> 
#include <fcntl.h>
#include <unistd.h>


void movie_list(char f_name[], char f_csv[]);
char* lowercase(char* s);

//structure defined for movie
struct movie
{
    char   title[500];
    int    year;
    int    mult;
    char   language[5][21];
    float  rating;
    struct movie *next;
};

struct movie *c_List(char *Line) 
{
  struct movie *curr = malloc(sizeof(struct movie));
  char *ptr;

  char *temp = strtok_r(Line, ",", &ptr); //title of the movie save data into saveptr 
  // currmovie->title = calloc(strlen(temp) + 1, sizeof(char));
  strcpy(curr->title, temp);

  temp = strtok_r(NULL, ",", &ptr); // year
  curr->year = atoi(temp); //character to int

  temp = strtok_r(NULL, ",", &ptr); //lang
  //curr->languages = calloc(strlen(temp) + 1, sizeof(char));
  temp += 1;
  temp [strlen(temp)-1] = 0;
  char* saveptr;
  char* token = strtok_r(temp, ";", &saveptr);
  strcpy(curr->language[0], token);
  int k = 1;
  while(token != NULL)
  {
    token = strtok_r(NULL, ";", &saveptr);
    if (token == NULL) 
    {
      break;
    }
    strcpy(curr->language[k], token);
    k++;
  }

  temp = strtok_r(NULL, ",\n", &ptr); // rating
  curr->rating = atof(temp);

  curr->next = NULL;
  return curr;
}

//function to show the movie year from assignment1
void show_movie_year(struct movie m[], int n, int year)
{
    int a = 0;
    for(int i = 0; i < n; i++)
    {
        if(m[i].year == year)
        {
            printf("%s\n", m[i].title);
            a = 1;
        }
    }
    //if no movie is found for that year
    if(a == 0) printf("\nNo data about movies released in year %d\n\n", year);
    printf("\n");
}

//function to show movies released in specific language from assignment1
void show_movies_language(struct movie m[], int n, char x[])
{
    int a = 0;
    for(int i = 0; i < n ;i++)
    {
        for (int j = 0; j < m[i].mult; j++) 
        { 
            //printf("TEST1: %s", m[i].language[j]);
            if(strcmp(lowercase(m[i].language[j]), lowercase(x)) == 0)
            {
                printf("%d %s\n",m[i].year, m[i].title);
                a = 1;
            }
        }
    }
    //if no movie is found for that language 
    if(a == 0)printf("No data about movies released in language %s\n\n", x);
    printf("\n");
}

//compara for sorting function
//sorting firstly on the basis of year and if year matches, sort in descending order of rating
//from assignment1
int sort(const void * a, const void* b)
{
    if(((struct movie*)a)->year == ((struct movie*)b)->year)
        return ((struct movie*)a)->rating < ((struct movie*)b)->rating;
    else
        return ((struct movie*)a)->year < ((struct movie*)b)->year;
}

//function to show highest rated movie of every year from assignment1
void show_movie_rated(struct movie m[], int n)
{
    //sort the object array first on the basis of year and if years are same
    //then sort in descending order of rating
    qsort(m, n + 1, sizeof(m[0]), sort);

    int curr_year = -1;
    for(int i = 0; i < n - 1; i++)
    {
        if(m[i].year != curr_year)
        {
            printf("%d %.2f %s\n", m[i].year, m[i].rating, m[i].title);
        }
        curr_year = m[i].year;
    }
    printf("\n");
}

//function to make the letter to lower from assignment1
char* lowercase(char s[])
{
    for(int i=0;i<strlen(s);i++)
    {
        s[i]= tolower(s[i]);
    }
    return s;
}

//link file
struct movie *process_file(char *file) 
{ 
  char * temp;
  temp = malloc(100 * sizeof(char));
  strcpy(temp, file);
  FILE * data = fopen(temp, "r"); //data
  if (data == NULL) printf("OPEN FILE Failed\n");
  char line[100];

  struct movie *h = NULL; //create head for the link
  struct movie *t = NULL; //tail
  //check the data is real
  if(data != NULL) 
  {
    fgets(line, sizeof line, data); //skip the first line
    //loop until the file hits the blank
    while(fgets(line, sizeof line, data) != NULL) 
    { 
      struct movie *node = c_List(line);
      if(h == NULL) 
      { 
        h = node;
        t = node;
      } else {
        t->next = node;
        t = node;
      }
    }
  }
  fclose(data); //cloase the file
  free(temp);
  return h;
}


void largest() { //find the largest file 
  DIR* curr_Dir = opendir("."); //give the start direct to scan
  struct dirent *dir1;
  struct stat fileL;

  unsigned int size = 0;
  char *name;

  char file_name[20];
  char myname[20] = "yangchun.movies.";
  srand(time(0));
  int num = rand() % 99999;
  sprintf(file_name, "%s%d", myname, num); //make the name of the folder first

  // Go through all the entries
  while((dir1 = readdir(curr_Dir)) != NULL)
  {
    if(dir1) 
    {
      char tmp[strlen(dir1->d_name)];
      for(int i = 0; i < 7; i++) {
        tmp[i] = dir1->d_name[i];
      }
      if (strcmp("movies_", tmp) == 0) 
      { //if the first 6 letters are "movie_"
        for(int i = 0; i < 7; i++) { tmp[i] = '\0';
      } //reset tmp
        //if the first 4 letter is movie then check out the last 4 letter of this file is ending with .csv
        int k = 0;
        for(int i = strlen(dir1->d_name) - 1; i > strlen(dir1->d_name) - 5; i--) 
        { 
          tmp[k] = dir1->d_name[i];
          k++;
        }
        //check it it is the .csv file backword
        if (strcmp("vsc.", tmp) == 0) 
        {  
          if (!stat(dir1->d_name, &fileL)) 
          {
            if((unsigned int)fileL.st_size > size) 
            { //if the size is bigger then keep the name of the file
              //set the size is equal to the largest for the next compare.
              size = (unsigned int)fileL.st_size; 
              name = dir1->d_name;
            }
          }
        }
      } 
    }
  }
  // Close the directory
  closedir(curr_Dir); //closed after saved data
  printf("Now processing the chosen file named %s\n", name);
  int make = mkdir(file_name, 0750); //create a directory
  printf("Created directory with name %s\n", file_name);
  movie_list(file_name, name); //after make the folder start working on making the movie list
  printf("\n");
}

//have the similar function
void smallest() 
{ 
  DIR* curr_Dir = opendir(".");
  struct dirent *dir2;
  struct stat fileS;

  unsigned int size = 100000; //set to max number to find out the smallest file size
  char *name;

  char file_name[20];
  char myname[20] = "yangchun.movies.";
  srand(time(0));
  int num = rand() % 99999;
  sprintf(file_name, "%s%d", myname, num);

  // Go through all the entries
  while((dir2 = readdir(curr_Dir)) != NULL)
  {
    if(dir2) 
    {
      char tmp[strlen(dir2->d_name)];
      for(int i = 0; i < 7; i++) 
      {
        tmp[i] = dir2->d_name[i];
      }
      if (strcmp("movies_", tmp) == 0) { //if the first 6 letters are "movie_"
        for(int i = 0; i < 7; i++) { tmp[i] = '\0';} //reset tmp

        int k = 0;
        for(int i = strlen(dir2->d_name) - 1; i > strlen(dir2->d_name) - 5; i--) {
          tmp[k] = dir2->d_name[i];
          k++;
        }
        //check it it is the .csv file
        if (strcmp("vsc.", tmp) == 0) 
        {  
          if (!stat(dir2->d_name, &fileS)) 
          {
            if((unsigned int)fileS.st_size < size) 
            { //if small then keep the data file
              size = (unsigned int)fileS.st_size; //set the size is equal to the smallest for the next compare.
              name = dir2->d_name;
            }
          }
        }
      } 
    }
  }
  // Close the directory
  closedir(curr_Dir); //same as the largest function
  printf("Now processing the chosen file named %s\n", name);
  int make = mkdir(file_name, 0750); //create a directory
  printf("Created directory with name %s\n", file_name);
  movie_list(file_name, name);
  printf("\n");
}
//search the file
void find_name() 
{ 
  DIR* curr_Dir = opendir(".");
  struct dirent *dir3;
  struct stat fileS;
  char input[1000];
  bool bol = false;

  char file_name[20];
  char myname[20] = "yangchun.movies.";
  srand(time(0));
  int num = rand() % 9999;
  sprintf(file_name, "%s%d", myname, num); //make the name of the file first

  printf("Enter the complete file name: ");
  scanf("%s", input); //get the user input

  while((dir3 = readdir(curr_Dir)) != NULL)
  {
    if(dir3) 
    {//if there is no diffrerence then
      if (strcmp(dir3->d_name, input) == 0) 
      { 
        bol = true; //make the bol to true
      }
    }
  }
  closedir(curr_Dir); //close the file
  // if the program find the file
  if(bol) 
  { 
    printf("Now processing the chosen file named %s\n", input);
    int make = mkdir(file_name, 0777); //create a directory
    printf("Created directory with name %s\n", file_name);
    movie_list(file_name, input); //process to create the movie list
    printf("\n");
  } else {
    printf("The file %s was not found. Try again\n", input);
    printf("\n");

    int put; //run the inner menu again
      printf("\nWhich file you want to process?");
      printf("\nEnter 1 to pick the largest file");
      printf("\nEnter 2 to pick the smallest file");
      printf("\nEnter 3 to specify the name of a file");
      printf("\n\nEnter a choice from 1 to 3: ");
      
      int input;
      scanf("%d", &input);
      if(put == 1) {
        largest();
      } else if(put == 2) {
        smallest();
      } else if(put == 3) {
        find_name();
      }
  }
}

void check(char dirc[], struct movie *mv) { //to make the text file to list movie in same year
  struct movie *temp = mv;
  int check = 0;
  int file;


  if(mv->next != NULL && temp->year != 0) { //check the struct is the last one
    char dir_n[100];

    sprintf(dir_n, "%s/%d.txt", dirc, temp->year);
    file = open(dir_n, O_RDWR | O_CREAT | O_APPEND, 0640);

    while(temp != NULL) { //compare until the struct is over
      if(temp->year == mv->year) { //if year is same
        char msg[100];
        sprintf(msg, "%s\n", temp->title);
        check = 1;
        //printf("year: %d, title: %s", temp->year, msg);
        write(file, msg, strlen(temp->title) + 1); //put the movie title into the text file
      }
      temp = temp->next;
    } 
  }
  //close(file);
}

void movie_list(char f_name[], char f_csv[]) 
{ 
  struct movie *mv = process_file(f_csv);
  
  int year[100], i = 0, k = 0;
  check(f_name, mv);
  year[i] = mv->year; //save the first year into the array
  i++;

  while(mv != NULL) {
    for(int j = 0; j < i; j++) {
      if(mv->year == year[j]) { //check if there is any same year
        k = 1;
      }
    }

    if(k == 1) { //if the computer find the same year then move to the next
      mv = mv->next;
    } else { //if not then save year to the value
      check(f_name, mv); // run to find the high rate
      year[i] = mv->year;
      i++;
      mv = mv->next;
    }
    k = 0; //reset the status
  }
  printf("\n");
}

int main(void)
{
  int input = 0;
  while(input != 2) 
  {
    printf("\n1. Select file to process");
    printf("\n2. Exit the program");
    printf("\n\nEnter a choice from 1 to 2: ");
    int input;
    scanf("%d", &input);

    //Inner menu when the user hits 1 from the main menu
    if(input == 1) 
    {
      int choose = 0;
      printf("\nWhich file you want to process?");
      printf("\nEnter 1 to pick the largest file");
      printf("\nEnter 2 to pick the smallest file");
      printf("\nEnter 3 to specify the name of a file");
      printf("\n\nEnter a choice from 1 to 3: ");
      scanf("%d", &choose);
      if(choose == 1) {
        largest();
      } else if(choose == 2) {
        smallest();
      } else if(choose == 3) {
        find_name();
      }
    }
    else if (input == 2)
    {
      break;
    }
  }
  return 0;
}

