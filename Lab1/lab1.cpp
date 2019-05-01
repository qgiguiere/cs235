#include <iostream>
#include <fstream>
#include <string>
#include <istream>
#include <cctype>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <limits>

using namespace std;
using std::numeric_limits;

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

double CalculateAvg (double sumScores, int num_students) {
   double averageScore = sumScores / double(num_students);

    return averageScore;
}

double CalculateFinal (double totalGrade, int num_exams) {
    double finalAvg = totalGrade / double(num_exams);

    return finalAvg;
}

int main(int argc, char * argv[]) {
   VS_MEM_CHECK               // enable memory leak check
   // Your program...

    if (argc < 3) {
        cerr << "Please provide name of input and output files";
        return 1;
    }
    cout << "Input file: " << argv[1] << endl;
    ifstream in(argv[1]);
    if (!in) {
        cerr << "Unable to open " << argv[1] << " for input";
        return 2;
    }
    cout << "Output file: " << argv[2] << endl;
    ofstream out(argv[2]);
    if (!out) {
        in.close();
        cerr << "Unable to open " << argv[2] << " for output";
        return 3;
    }
    int num_students;
    int num_exams;
    in >> num_students >> num_exams;
    // Skip the rest of the line
    in.ignore(std::numeric_limits<int>::max(), '\n');

    int **studentScores = new int*[num_students];

    for(int i = 0; i < num_students; ++i) {
        studentScores[i] = new int[num_exams];
    }

    string *studentNames = new string[num_students];
    
    for (int i = 0; i < num_students; ++i) {
        string line;
        getline(in, line);
        size_t p = 0;
        while (!isdigit(line[p])) ++p;	// line[p] is the first digit
        string studentName;
        studentName = line.substr(0, p);
        studentNames[i] = studentName;
        // Put this into an istringstream
        string newLine = line.substr(p);
        istringstream iss(newLine);
        for (int j = 0; j < num_exams; ++j) {
            int scores = 0;
            iss >> scores;
            studentScores[i][j] = scores;
        }
    }
       
    out << "Student Scores:" << endl;

    for (int i = 0; i < num_students; ++i) {
        out << std::setw(20) << studentNames[i] << " ";
        for (int j = 0; j < num_exams; ++j) {
            out << std::fixed << std::setprecision(0) << std::setw(6) << studentScores[i][j];
        }
        out << endl;
    }

    out << "Exam Averages:" << endl;

    double *avgScore = new double[num_exams];

    for (int i = 0; i < num_exams; ++i) {
        double sumScores = 0.0;
        for (int j = 0; j < num_students; ++j) {
            sumScores += studentScores[j][i];
        }
        avgScore[i] = CalculateAvg(sumScores, num_students);
        out << fixed << setprecision(1) << setw(10) << "Exam " << i + 1 << " Average = " <<  std::setw(6) << avgScore[i] << endl;
    }

    out << "Student Exam Grades:" << endl;

    for (int i = 0; i < num_students; ++i) {
        char studentGrade;
        out << std::setw(20) << studentNames[i] << " ";
        for (int j = 0; j < num_exams; ++j) {
            if (studentScores[i][j] >= avgScore[j] + 15) {
                studentGrade = 'A';
            }
            else if (studentScores[i][j] > avgScore[j] + 5) {
                studentGrade = 'B';
            }
            else if (studentScores[i][j] <= avgScore[j] + 5 && studentScores[i][j] >= avgScore[j] - 5) {
                studentGrade = 'C';
            }
            else if (studentScores[i][j] <= avgScore[j] - 15) {
                studentGrade = 'E';
            }
            else {
                studentGrade = 'D';
            }
            out << std::fixed << std::setprecision(0) << std::setw(6) << studentScores[i][j] << "(" << studentGrade << ")";
        }
        out << endl;
    }

    out << "Exam Grades:" << endl;

    int **numGrades = new int*[num_exams];
    for (int i = 0; i < num_exams; ++i) {
        numGrades[i] = new int[6];
    }

    for (int i = 0; i < num_exams; ++i) {
        int numA = 0;
        int numB = 0;
        int numC = 0;
        int numD = 0;
        int numE = 0;
        for (int j = 0; j < num_students; ++j) {
            if (studentScores[j][i] >= avgScore[i] + 15) {
                ++numA;
            }
            else if (studentScores[j][i] > avgScore[i] + 5) {
                ++numB;
            }
            else if (studentScores[j][i] <= avgScore[i] + 5 && studentScores[j][i] >= avgScore[i] - 5) {
                ++numC;
            }
            else if (studentScores[j][i] <= avgScore[i] - 15) {
                ++numE;
            }
            else {
                ++numD;
            }
            numGrades[i][0] = numA;
            numGrades[i][1] = numB;
            numGrades[i][2] = numC;
            numGrades[i][3] = numD;
            numGrades[i][4] = numE;
        }
        out << std::fixed << std::setprecision(0) << std::setw(4) << "Exam " << i + 1 << " " <<  std::setw(4) << numGrades[i][0] << "(A) " <<  std::setw(4) << numGrades[i][1] << "(B) " <<  std::setw(4) << numGrades[i][2] << "(C) " <<  std::setw(4) << numGrades[i][3] << "(D) " <<  std::setw(4) << numGrades[i][4] << "(E) " << endl;
    }

    out << "Student Final Grades:" << endl;

    for (int i = 0; i < num_students; ++i) {
        double totalGrade = 0.0;
        char studentGrade;
        for (int j = 0; j < num_exams; ++j) {
            totalGrade += double(studentScores[i][j]);
        }
        avgScore[i] = CalculateFinal(totalGrade, num_exams);
        //totalGrade = totalGrade / double(num_exams);
         if (totalGrade >= avgScore[i] + 15) {
                studentGrade = 'A';
            }
            else if (totalGrade > avgScore[i] + 5) {
                studentGrade = 'B';
            }
            else if (totalGrade <= avgScore[i] + 5 && totalGrade >= avgScore[i] - 5) {
                studentGrade = 'C';
            }
            else if (totalGrade <= avgScore[i] - 15) {
                studentGrade = 'E';
            }
            else {
                studentGrade = 'D';
            }
        out << studentNames[i] << totalGrade << "(" << studentGrade << ")" << endl;
    }

    for(int i = 0; i < num_students; ++i) {
        delete [] studentScores[i];
    }
    delete [] studentScores;

    for(int i = 0; i < num_exams; ++i) {
        delete [] numGrades[i];
    }
    delete [] numGrades;

    delete [] avgScore;

    delete [] studentNames;


   return 0;
}
