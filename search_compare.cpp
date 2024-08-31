/**
 * file: search_compare.cpp
 * type: C++ (source file)
 * date: 30_AUGUST_2023
 * author: karbytes
 * license: PUBLIC_DOMAIN
 */

/* preprocessing directives */
#include <iostream> // library for defining objects which handle command line input (std::cin) and command line output (std::cout)
#include <fstream> // library for defining objects which handle file input (std::ifstream) and file output (std::ostream)
#include <cmath> // library for square root function (std::sqrt) and absolute value function (std::abs)
#include <cstdlib> // library for generating a random number (std::rand)
#include <ctime> // library for function which returns the number of seconds elapsed since the Unix Epoch (std::time(0))
#define MAXIMUM_N 1000 // constant which represents maximum N value
#define MAXIMUM_T 1000 // constant which represents maximum T value

/* function prototypes */
int * generate_randomized_array(int N, int T);
//int linear_search(int A[], int N, int x);

/* program entry point */
int main()
{
    // Declare three int type variables and set each of their initial values to 0.
    int N = 0, T = 0, i = 0;

    // Declare a file output stream object.
    std::ofstream file;

    /**
     * If search_compare_output.txt does not already exist in the same directory as search_compare.cpp, 
     * create a new file named search_compare_output.txt.
     * 
     * Open the plain-text file named search_compare_output.txt 
     * and set that file to be overwritten with program data.
     */
    file.open("search_compare_output.txt");

    // Print an opening message to the command line terminal.
    std::cout << "\n\n--------------------------------";
    std::cout << "\nStart Of Program";
    std::cout << "\n--------------------------------";

    // Print an opening message to the file output stream.
    file << "--------------------------------";
    file << "\nStart Of Program";
    file << "\n--------------------------------";

    // Prompt the program user to input a value to store in the main function variable named N.
    std::cout << "\n\nEnter a natural number, N, which is no larger than ";
    std::cout << MAXIMUM_N;
    std::cout << " (to represent the total number of elements to store in the array named A): ";

    // Print the above command line prompt to the output text file.
    file << "\n\nEnter a natural number, N, which is no larger than ";
    file << MAXIMUM_N;
    file << " (to represent the total number of elements to store in the array named A): ";

    // Scan the command line terminal for the most recent keyboard input value.
    std::cin >> N;

    // Print "The value which was entered for N is {N}." to the command line terminal.
    std::cout << "\nThe value which was entered for N is " << N << ".";

    // Print "The value which was entered for N is {N}." to the output file stream.
    file << "\nThe value which was entered for N is " << N << ".";

    // Prompt the program user to input a value to store in the main function variable named T.
    std::cout << "\n\nEnter a nonnegative integer, T, which is no larger than ";
    std::cout << MAXIMUM_T;
    std::cout << " (to represent the total number of states each element of A can represent exactly one of per instance): ";

    // Print the above command line prompt to the output text file.
    file << "\n\nEnter a nonnegative integer, T, which is no larger than ";
    file << MAXIMUM_T;
    file << " (to represent the total number of states each element of A can represent exactly one of per instance): ";

    // Scan the command line terminal for the most recent keyboard input value.
    std::cin >> T;

    // Print "The value which was entered for T is {T}." to the command line terminal.
    std::cout << "\nThe value which was entered for T is " << T << ".";

    // Print "The value which was entered for T is {T}." to the output file stream.
    file << "\nThe value which was entered for T is " << T << ".";

    // Print a closing message to the command line terminal.
    std::cout << "\n\n--------------------------------";
    std::cout << "\nEnd Of Program";
    std::cout << "\n--------------------------------\n\n";

    // Print a closing message to the file output stream.
    file << "\n\n--------------------------------";
    file << "\nEnd Of Program";
    file << "\n--------------------------------";

    // Close the file output stream.
    file.close();

    // Exit the program.
    return 0;
}

/**
 * This function returns an array consisting of exclusively N int-type elements 
 * which each have a value which is no larger than T and such that those elements 
 * are arranged in a randomized order.
 * 
 * N is assumed to be a natural number no larger than T.
 * 
 * T is assumed to be a nonnegative integer no larger than MAXIMUM_T.
 */
int * generate_randomized_array(int N, int T) 
{
    /**
     * Initialize the (pseudo) random number generator with the number of seconds elapsed since the Unix Epoch.
     * (The Unix Epoch is 12:00AM Coordinated Universal Time on 01_JANUARY_1970).
     */
    std::srand(std::time(0));

    // If the N value which is passed into this function is "out of range", then store the default value ten in the local variable named N.
    N = ((N < 1) || (N > MAXIMUM_N))? 10 : N;

    // If the T value which is passed into this function is "out of range", then store the default value one hundred in the local variable named T.
    T = ((T < 0) || (T > MAXIMUM_T))? 100 : T;

    /**
     * Dynamically allocate memory for the array.
     * (Allocate N contiguous int-sized chunks of random access memory (RAM) to the array and store the address of the first element of that array in the pointer-to-int variable named A).
     * (Note that an int-type variable occupies four contiguous memory cells and that each memory cell has a data capacity of one byte).
     * (Note that the address of a variable is the memory address of the first memory cell of the chunk of contiguous memory cells which is allocated to that variable).
     */
    int * A = new int[N];

    // Populate the array with random values which are no smaller than 0 and no larger than T.
    for (int i = 0; i < N; ++i) A[i] = std::rand() % T;

    // Return the array after setting each element of that array to a randomized nonnegative integer value.
    return A;
}
