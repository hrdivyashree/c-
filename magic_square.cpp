/* MAGIC SQUARE - An NxN matrix containing values from 1 to N*N that are  */
/* ordered so that the sum of the rows, columns, and the major diagonals  */
/* are all equal.  There is a particular algorithm for odd integers, and  */
/* this program constructs that matrix, up to 13 rows and columns.  This   */
/* program also adds the sums of the row, columns, and major diagonals.   */

#include <iostream>
#include <iomanip>            /* Sets the field width to be used on output operations */
using namespace std;

/**********************************************

*Author - Divyashree Hassan Ravindrakumar
*OS - macOS Sierra - version 10.12.5
*Compiler g++
*	Configured with: --prefix=/Library/Developer/CommandLineTools/usr --with-gxx-include-dir=/usr/include/c++/4.2.1
*	Apple LLVM version 8.1.0 (clang-802.0.42)
*	Target: x86_64-apple-darwin16.7.0
*	Thread model: posix
*	InstalledDir: /Library/Developer/CommandLineTools/usr/bin
*
**********************************************/

                              /* Class Matrix */
class Matrix                   
{
	public:            
	    Matrix(int rowcol);     /* Constructor takes in the row = coulmn from input */
	    ~Matrix();              /* destructor to deallocate Matrix memory */
	    void Init(void);
	    void PrintMatrix(void);

	private:                     /* private variable */
	    int rows; 
       int cols;
	    int **myMatrix;
       int otherdiag;
};

Matrix::Matrix(int rowcol): rows(rowcol), cols(rowcol)
{
      myMatrix = new int*[rows];                /* Dynamically allocate the space on heap for */   
      for (int row = 0; row <= rows; row++)     /* 2 dimensional Matrix using rows and columns value */
      {                                         
          myMatrix[row] = new int[cols];        /* Initialize Matrix to zero */
          for (int col = 0; col <= cols; col++)
              myMatrix[row][col] = 0;
      }
}

Matrix::~Matrix() {
	for (int row = 0; row <= rows; row++)        /* deallocate the 2D matrix space on heap */
	   delete [] myMatrix[row];
	delete [] myMatrix;
}

void Matrix::Init(){

      int row = 1;                         /* First value gets to sit on */
      int col = cols/2 + 1;                /*  1st row, middle of matrix.*/
      otherdiag = 0; 
      int value = 0; 
/*                                                                        */
/*    Loop for every value up to input*input, and position value in matrix*/
/*                                                                        */
      for (value = 1; value <= rows*cols; value++)
      {                                    /* Loop for all values.       */
         if (myMatrix[row][col] > 0)       /* If some value already      */
         {                                 /*  present, then             */
            row += 2;                      /*  move down 1 row of prev.  */
            if (row > rows)                /*  If exceeds side, then     */
               row -= rows;                /*   go to other side.        */

            col--;                         /*  move left 1 column.       */
            if (col < 1)                   /*  If exceeds side, then     */
               col = cols;                 /*   go to other side.        */
         }

         myMatrix[row][col] = value;       /* Assign value to location.  */

/*                                                                        */
/*       Add to totals                                                    */
/*                                                                        */
         myMatrix[0][col] += value;         /* Add to its column total.   */
         myMatrix[row][0] += value;         /* Add to its row total.      */
         if (row == col)                    /* Add to diagonal total if   */
            myMatrix[0][0] += value;        /*  it falls on the diagonal. */

         if (row+col == row+1)              /* Add to other diagonal if   */
            otherdiag += value;             /*  it falls on the line.     */

/*                                                                        */
/*       Determine where new row and col are                              */
/*                                                                        */
         row--;
         if (row < 1)                       /* If row exceeds side then   */
            row = rows;                     /*  goto other side.          */
         col++;
         if (col > rows)                    /* If col exceeds side then   */
            col = 1;                        /*  goto other side.          */
      }                                     /* End of getting all values. */
}

void Matrix::PrintMatrix(){

/*                                                                        */
/*    Print out the matrix with its totals                                */
/*                                                                        */
      cout << "\nThe number you selected was "<<rows ;
      cout << ", and the matrix is:\n\n";
      for (int row = 1; row <=rows; row++)                        /* Loop: print a row at a time*/
      {
         cout << "     ";                                         /* Create column for diag.total*/
         for (int col = 1; col <=cols; col++)
            cout << setw( 5 ) << myMatrix[row][col] ;             /* Print values found in a row*/
         cout<< " = " << setw( 5 ) << myMatrix[row][0] << "\n";   /* Print total of row.*/
      }
/*                                                                        */
/*    Print out the totals for each column, starting with diagonal total. */
/*                                                                        */
      for (int col = 0; col <=cols; col++)            /* Print line separating the  */
         cout << "-----";                             /* value matrix and col totals*/
      cout << "\n"<<setw( 5 )<<otherdiag;             /* Print out the diagonal total*/
      for (int col = 1; col <=cols; col++)
	      cout << setw( 5 ) << myMatrix[0][col];       /* Print out the column totals*/
      cout<< "   "<<setw( 5 ) <<myMatrix[0][0];       /* Print out the other diagonal*/
                                                      /* total*/
}

int main()
{
   int input;                               /* User defined integer       */
   int loc[14][14];                         /* Array holding all          */
                                            /*  input*input values.       */
   int row;                                 /* Determines row of matrix   */
   int col;                                 /* Determines col of matrix   */
   int value;                               /* Integer between 1 and      */
                                            /*  input*input               */
   int otherdiag;                           /* Total of one matrix diagonal*/

/*                                                                        */
/* Print introduction of what this program is all about.                  */
/*                                                                        */
   cout << "\nMagic Squares: This program produces an NxN matrix where\n";
   cout << "N is some positive odd integer.  The matrix contains the \n";
   cout << "values 1 to N*N.  The sum of each row, each column, and \n";
   cout << "the two main diagonals are all equal.  Not only does this \n";
   cout << "program produces the matrix, it also computes the totals for\n";
   cout << "each row, column, and two main diagonals.\n";

   cout << "\nBecause of display constraints, this program can work with\n";
   cout << "values up to 13 only.\n\n";

   cout << "Enter a positive, odd integer (-1 to exit program):\n";
   while (cin >> input)
   {

/*                                                                        */
/*    If input = -1, then exit program.                                   */
/*                                                                        */
      if (input == -1)
	     break;
/*                                                                        */
/*    Validity check for input: Must be a positive odd integer < 13.      */
/*                                                                        */
      if (input <= 0)
      {
         cout << "Sorry, but the integer has to be positive.\n";
	      cout << "\nEnter a positive, odd integer (-1 to exit program):\n";
  	      continue;
      }
      if (input > 13)
      {
	      cout << "Sorry, but the integer has to be less than 15.\n";
	      cout << "\nEnter a positive, odd integer (-1 to exit program):\n";
	      continue;
      }
      if (input%2 == 0)
      {
	      cout <<"Sorry, but the integer has to be odd.\n";
	      cout <<"\nEnter a positive, odd integer (-1 to exit program):\n";
	      continue;
      }

      Matrix *newMatrix = new Matrix(input);
      newMatrix->Init();
      newMatrix->PrintMatrix();

      delete newMatrix;
      cout << "\nEnter a positive, odd integer (-1 to exit program):\n";
   }                                        /* End of while input>-1 loop */
   cout << "\nBye bye!\n";
}
