// Catherine Roschmann
// Project Assignment 3
// April 13, 2022
// COSC 1436.22002
/* Objective: This program will read in a list of names for students along with the students’ grades from a provided file.
Then based on the user’s selection from a menu, you will output a table of student names with either their average, maximum, or minimum numerical 
grade along with the corresponding letter grade.  */

#include <iostream>     // cout, cin
#include <cstdlib>      // exit()
#include <string>       // strings
#include <fstream>      // file processing
#include <iomanip>      // stream manipulation

using namespace std;

// GLOBAL VARIABLES /////////////////////////////////////////////////////////////////////////////////////////////
const int MAX_STUDENTS = 25;                 // we will not process more than 25 students even if the file contains more
const int MAX_GRADES = 5;                    // each student has exactly 5 grades
const string FILENAME = "NamesGrades.txt";   // the name of the file we are reading

// FUNCTION DECLARATIONS ////////////////////////////////////////////////////////////////////////////////////////
int loadStudentNamesGrades(string students[], int grades[][MAX_GRADES], string filename, int maxStudents);
void displayAverages(string students[], int grades[][MAX_GRADES], int studentCount);
void displayMax(string students[], int grades[][MAX_GRADES], int studentCount);
void displayMin(string students[], int grades[][MAX_GRADES], int studentCount);
char getLetterGrade(double grade);


int main()
{
    // VARIABLES //////////////////////////////////

    int studentCount;                        //variable to keep up with actual number of student
    string students[MAX_STUDENTS];           //array of strings for student names after they have been concenated from two strings
    int grades[MAX_STUDENTS][MAX_GRADES];    //two dimensinal array of ints for the grades of the students, tied back to students
    int menuSelection;                       //variable to hold the choice of the use for the menu

    // GET THE STUDENTS NAMES AND GRADES /////////////////////////////////////////////////////////////////////////
    studentCount = loadStudentNamesGrades(students, grades, FILENAME, MAX_STUDENTS);

    // PROGRAM MENU ////////////////////////////////////////////////////////////////
    //Loop until the use says to quit     
    //Prompt the user with menu options: 
    cout << "Grade Report Program" << endl;
    cout << "1. Display Average Grade" << endl;
    cout << "2. Display Maximum Grade" << endl;
    cout << "3. Display Minimun Grade" << endl;
    cout << "4. Quit Program" << endl;

    //Allow user to enter menu selection
    cout << endl << "Enter your choice (1-4): ";
    
    //expression and call functions for menu 
    while (1)
    {
        cin >> menuSelection;

        if (menuSelection == 1)
        {
            displayAverages(students, grades, studentCount);
        }
        else if (menuSelection == 2)
        {
            displayMax(students, grades,studentCount);
        }
        else if (menuSelection == 3)
        {
            displayMin(students, grades, studentCount);
        }
        else if (menuSelection == 4)
        {
            cout << "\n Press enter to quit Grade Report Program\n";
            break;
        }
        else
        {
            cout << "\n Invalid Entry, pleae enter a number 1-4\n";
        }   

    }
  
    return 0;
}

    // FUNCTION: loadStudentNamesGrades /////////////////////////////////////////////////////////////////////
    int loadStudentNamesGrades(string students[], int grades[][MAX_GRADES], string fileName, int maxStudents)
    {
     //local vairbles 
        ifstream studentFile;                              //to input from a file
        string firstName;                                  // to hold first name
        string lastName;                                   // to hold last name
        string inputLine;
        int score1, score2, score3, score4, score5;       // to hold input of names from file
        int nameCount = 0 ;                               // name counter 
            

     //open file and test for opening errors 
         studentFile.open(fileName);
         if (!studentFile)
          {
             cout << "Error: File " << fileName << " could not be opened :(" << endl << endl;
          }
              
     //while loop to put into from txt file into variables and arrays
                 
           while(studentFile >> firstName >> lastName >> score1 >> score2 >> score3 >> score4 >> score5)    
           {   
             students[nameCount] = firstName + " " + lastName;        //concatenate the firstName and lastName string with space in the middle to separate 

             grades[nameCount][0] = score1;                            //putting each score into the an array
             grades[nameCount][1] = score2;
             grades[nameCount][2] = score3;
             grades[nameCount][3] = score4;
             grades[nameCount][4] = score5;
                            
             
             nameCount++;                                            //counting how many students we have
                      
           }

       studentFile.close();

       return nameCount;
    }
    
   // FUNCTION: AVERAGE FOR MENU 1 ///////////////////////////////////////////////////////////////////////
   void displayAverages(string students[], int grades[][MAX_GRADES], int studentCount)
   {
       cout << setprecision(1) << fixed;
       cout << showpoint;
       cout << endl << "Average Grades" << endl;
       cout << setw(17) << left << "Name" << setw(10) << right << "Average" << setw(10) << right << "Grade" << endl;

        //local varibles: 
        double sum;         // to hold the summed score of all the grades
        double average;     // to hold the average grade
        int x;              //array index for student
        int y;              //array index for grades

        // for loop to collected the students
       for (x = 0; x < studentCount; x++)
       {
        
        sum = 0.0;
            
           //for loop to collect grades and sum them together
          for (y = 0; y < MAX_GRADES; y++)
          {
            sum += grades[x][y];
          }
        average = sum / MAX_GRADES;
         
        //display students, average, and letter grade    
        cout << setw(17) << left << students[x] << setw(10) << right << average << setw(10) << right << getLetterGrade(average) << endl;
       }
       
    }
  
    // FUNCTION: MAX GRADE FOR MENU 2 /////////////////////////////////////////////////////////////////////
    void displayMax(string students[], int grades[][MAX_GRADES], int studentCount)
   {
        cout << endl << "Max Grades" << endl;
        cout << setw(17) << left << "Name" << setw(15) << right << "Max" << setw(15) << right << "Grade" << endl;

        for (int x = 0; x < studentCount; x++)
        {
            double highest = 0.0;

            for (int y = 0; y < MAX_GRADES; y++)
            {
                if (grades[x][y] > highest)
                    highest = grades[x][y];

            }

            //display students, highest grade, and letter grade    
            cout << setprecision(3);
            cout << setw(17) << left << students[x] << setw(15) << right << highest << setw(15) << right << getLetterGrade(highest) << endl;
            
        }

    }
  

    // FUNCTION: MIN GRADE FOR MENU 3 //////////////////////////////////////////////////////////////////////
    // 7.6 in powerpoint
    void displayMin(string students[], int grades[][MAX_GRADES], int studentCount)
    {
        cout << endl << "Min Grades" << endl;
        cout << setw(17) << left << "Name" << setw(15) << right << "Min" << setw(15) << right << "Grade" << endl;

        for (int x = 0; x < studentCount; x++)
        {
            double lowest = 0.0;

            for (int y = 0; y < MAX_GRADES; y++)
            {
                if (grades[x][y] > lowest)
                    lowest = grades[x][y];

            }

            //display students, lowest grade, and letter grade    
            cout << setprecision(3);
            cout << setw(17) << left << students[x] << setw(15) << right << lowest << setw(15) << right << getLetterGrade(lowest) << endl;

        }

    }

    // FUNCTION: GET LETTER GRADE /////////////////////////////////////////////////////////////////////////
    char getLetterGrade(double grade)
     {
        if (grade <= 100 && grade >= 90)
            return 'A';
        else if (grade < 90 && grade >= 80)
            return 'B';
        else if (grade < 80 && grade >= 70)
            return 'C';
        else if (grade < 70 && grade >= 60)
            return 'D';
        else (grade < 60 && grade >= 0);
            return 'F';

    }

  
    