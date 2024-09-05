/**
 * file: search_compare.cpp
 * type: C++ (source file)
 * date: 05_SEPTEMBER_2023
 * author: karbytes
 * license: PUBLIC_DOMAIN
 */

/* preprocessing directives */
#include <iostream> // library for defining objects which handle command line input (std::cin) and command line output (std::cout)
#include <fstream> // library for defining objects which handle file input (std::ifstream) and file output (std::ostream)
#include <cmath> // library for square root function (std::sqrt) 
#include <cstdlib> // library for generating a random number (std::rand)
#include <ctime> // library for function which returns the number of seconds elapsed since the Unix Epoch (std::time(0))
#include <chrono> // library for calculating search algorithm runtimes
#include <iomanip>  // library for formatting floating-point numbers ((std::fixed) and (std::setprecision))
#include <algorithm> // library for function which finds the minimum value in a pair of values (std::min)
#define MAXIMUM_N 100000 // constant which represents maximum N value
#define MAXIMUM_T 100000 // constant which represents maximum T value

/* function prototypes */
int * generate_randomized_array(int N, int T);
void print_array(int * A, int N, std::ostream & output);
void bubble_sort(int * A, int S); // copied from: https://karbytesforlifeblog.wordpress.com/sort_compare/
int linear_search(int * A, int N, int x); // choice 0
int binary_search(int * A, int left, int right, int x); // choice 1
int ternary_search(int * A, int left, int right, int x); // choice 2
int fibonacci_search(int * A, int N, int x); // choice 3
int exponential_search(int * A, int N, int x); // choice 4
int jump_search(int * A, int N, int x); // choice 5

/* program entry point */
int main()
{
    // Define seven int type variables such that each of their initial values is set to 0.
    int N = 0, T = 0, x = 0, c = 0, i = 0, l = 0, r = 0;

    // Declare one pointer-to-int variable named A.
    int * A;

    // Define a (static) array of C-strings (character arrays) for storing exactly six search algorithm names.
    const char * search_algorithm_names[] = {"LINEAR_SEARCH", "BINARY_SEARCH", "TERNARY_SEARCH", "FIBONACCI_SEARCH", "EXPONENTIAL_SEARCH", "JUMP_SEARCH"};

    /**
     * // Declare two chrono time point variables to use for calculating the runtime of a search algorithm function.
     * 
     * Note that the high_resolution_clock is typically monotonic, meaning it (almost) always increases and never goes backward 
     * and is typically a measure of time elapsed since the harware system running this code last booted up.
     * 
     * The high_resolution_clock does not (usually) reset over time, but depending on the particular hardware system, 
     * the high_resolution_clock value could overflow if a "very long" time period passes since system boot.
     * ((though, according to ChatGPT-40) such a time period would usually be several years)).
     */
    std::chrono::high_resolution_clock::time_point start_point, end_point;

    // Declare one chrono duration floating-point number type variable for storing the number of seconds between start_point and end_point.
    std::chrono::duration<double> duration;

    // Declare a file output stream object.
    std::ofstream file;

    // Set the command line terminal output to fixed notation (rather than scientific notation) and set the precision of floating-point numerical values to 100 decimal places.
    std::cout << std::fixed << std::setprecision(100);

    // Set the output file stream output to fixed notation (rather than scientific notation) and set the precision of floating-point numerical values to 100 decimal places.
    file << std::fixed << std::setprecision(100);

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

    /**
     * Scan the command line terminal for the most recent keyboard input value.
     * Store that value in the main function variable named N.
     */
    std::cin >> N;

    // Print "The value which was entered for N is {N}." to the command line terminal.
    std::cout << "\n\nThe value which was entered for N is " << N << ".";

    // Print "The value which was entered for N is {N}." to the output file stream.
    file << "\n\nThe value which was entered for N is " << N << ".";

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
    std::cout << "\n\nThe value which was entered for T is " << T << ".";

    // Print "The value which was entered for T is {T}." to the output file stream.
    file << "\n\nThe value which was entered for T is " << T << ".";

    // Print a horizontal divider line to the command line terminal.
    std::cout << "\n\n--------------------------------";

    // Print a horizontal divider line to the output file stream.
    file << "\n\n--------------------------------";

    /**
     * If the N value which was input by the program user is "out of range", 
     * store the default value ten in the main function variable named N
     * and output a message stating this fact to the command line terminal
     * and to the output file stream.
     */
    if ((N < 1) || (N > MAXIMUM_N))
    {
        N = 10;
        std::cout << "\n\nWARNING: N was reset to 10 because the user input value for N was out of range.";
        file << "\n\nWARNING: N was reset to 10 because the user input value for N was out of range.";
    }

    /**
     * If the T value which was input by the program user is "out of range", 
     * store the default value one hundred in the main function variable named T
     * and output a message stating this fact to the command line terminal
     * and to the output file stream.
     */
    if ((T < 0) || (T > MAXIMUM_T))
    {
        T = 100;
        std::cout << "\n\nWARNING: T was reset to 100 because the user input value for T was out of range.";
        file << "\n\nWARNING: T was reset to 100 because the user input value for T was out of range.";
    }

    /** 
     * Dynamically allocate N contiguous int-sized chunks of memory to a one-dimensional array named A.
     * Then populate that array with N random nonnegative integer values which are each no larger than T.
     */
    A = generate_randomized_array(N, T);

    // Print the contents of the array to the command line terminal.
    print_array(A, N, std::cout);

    // Print the contents of the array to the command line terminal.
    print_array(A, N, file);

    // Print a horizontal divider line to the command line terminal.
    std::cout << "\n\n--------------------------------";

    // Print a horizontal divider line to the output file stream.
    file << "\n\n--------------------------------";

    // Prompt the program user to input a value to store in the main function variable named x.
    std::cout << "\n\nEnter a nonnegative integer value, x, which is no larger than ";
    std::cout << MAXIMUM_T;
    std::cout << " to search for in the array named A: ";

    // Print the above command line prompt to the output text file.
    file << "\n\nEnter a nonnegative integer value, x, which is no larger than ";
    file << MAXIMUM_T;
    file << " to search for in the array named A: ";

    /**
     * Scan the command line terminal for the most recent keyboard input value.
     * Store that value in the main function variable named x.
     */
    std::cin >> x;

    // Print "The value which was entered for x is {x}." to the command line terminal.
    std::cout << "\n\nThe value which was entered for x is " << x << ".";

    // Print "The value which was entered for x is {x}." to the output file stream.
    file << "\n\nThe value which was entered for x is " << x << ".";

    /**
     * If the x value which was input by the program user is "out of range", 
     * store the default value one in the main function variable named x
     * and output a message stating this fact to the command line terminal
     * and to the output file stream.
     */
    if ((x < 0) || (x > MAXIMUM_T))
    {
        x = 1;
        std::cout << "\n\nWARNING: x was reset to 1 because the user input value for x was out of range.";
        file << "\n\nWARNING: x was reset to 1 because the user input value for x was out of range.";
    }

    // Print a horizontal divider line to the command line terminal.
    std::cout << "\n\n--------------------------------";

    // Print a horizontal divider line to the output file stream.
    file << "\n\n--------------------------------";

    // Calculate the number of elements in the array of C-strings using sizeof (and store the result in l).
    l = sizeof(search_algorithm_names) / sizeof(search_algorithm_names[0]);

    // Prompt the program user to input a value to store in the main function variable named c.
    std::cout << "\n\nSEARCH ALGORITHMS:\n";
    for (i = 0; i < l; i++) std::cout << "\n" << i << ": " << search_algorithm_names[i];
    std::cout << "\n\nEnter either 0, 1, 2, 3, 4, or 5 to store in the variable named c and which represents one of the above search algorithm choices to implement (to return the first instance of x in A and to determine how long that takes in seconds): ";

    // Print the above command line prompt to the output text file.
    file << "\n\nSEARCH ALGORITHMS:\n";
    for (i = 0; i < l; i++) file << "\n" << i << ": " << search_algorithm_names[i];
    file << "\n\nEnter either 0, 1, 2, 3, 4, or 5 to store in the variable named c and which represents one of the above search algorithm choices to implement (to return the first instance of x in A and to determine how long that takes in seconds): ";

    /**
     * Scan the command line terminal for the most recent keyboard input value.
     * Store that value in the main function variable named c.
     */
    std::cin >> c;

    // Print "The value which was entered for c is {c}." to the command line terminal.
    std::cout << "\n\nThe value which was entered for c is " << c << ".";

    // Print "The value which was entered for c is {c}." to the output file stream.
    file << "\n\nThe value which was entered for c is " << c << ".";

    /**
     * If the c value which was input by the program user is "out of range", 
     * store the default value zero in the main function variable named c
     * and output a message stating this fact to the command line terminal
     * and to the output file stream.
     */
    if ((c < 0) || (c > l))
    {
        c = 0;
        std::cout << "\n\nWARNING: c was reset to 0 because the user input value for c was out of range.";
        file << "\n\nWARNING: c was reset to 0 because the user input value for c was out of range.";
    }

    /**
     * If BINARY_SEARCH, TERNARY_SEARCH, FIBONACCI_SEARCH, EXPONENTIAL_SEARCH, or JUMP_SEARCH was selected, 
     * then arrange the elements of A in ascending order before calculating search algorithm runtime.
     * 
     * Also, re-print the array after it is sorted.
     */
    if ((c == 1) || (c == 2) || (c == 3) || (c == 4) || (c == 5)) 
    {
        bubble_sort(A, N);
        print_array(A, N, std::cout); // Print the contents of the array to the command line terminal.
        print_array(A, N, file); // Print the contents of the array to the output file stream.
    }

    // Print a horizontal divider line to the command line terminal.
    std::cout << "\n\n--------------------------------";

    // Print a horizontal divider line to the output file stream.
    file << "\n\n--------------------------------";

    // Print "Using {search_algorithm_names[c]} to search for the value {x} in the array of {N} randomly-ordered int-type values named A..." to the command line terminal.
    std::cout << "\n\nUsing " << search_algorithm_names[c] << " to search for the value " << x << " in the array of " << N << " randomly-ordered int-type values named A...";

    // Print "Using {search_algorithm_names[c]} to search for the value {x} in the array of {N} randomly-ordered int-type values named A..." to the output file stream.
    file << "\n\nUsing " << search_algorithm_names[c] << " to search for the value " << x << " in the array of " << N << " randomly-ordered int-type values named A...";

    // Get the current time (which is obtained from the system clock of the hardware running this code) to store in the variable named end_point.
    start_point = std::chrono::high_resolution_clock::now();

    // Implement the user-selected search algorithm and store the search result in the variable named r.
    switch (c) 
    {
        case 5:
            r = jump_search(A, N, x);
            break;
        case 4:
            r = exponential_search(A, N, x);
            break;
        case 3:
            r = fibonacci_search(A, N, x);
            break;
        case 2:
            r = ternary_search(A, 0, N - 1, x);
            break;
        case 1:
            r = binary_search(A, 0, N - 1, x);
            break;
        default:
            r = linear_search(A, N, x);
            break;
    }

    // Get the current time (which is obtained from the system clock of the hardware running this code) to store in the variable named end_point.
    end_point = std::chrono::high_resolution_clock::now();

    // Calculate the search function execution time by calculating the (nonnegative number) difference between the value stored in end_point and the value stored in start_point.
    duration = end_point - start_point;

    /**
     * If x was not found to be an element of the array named A, 
     * then print a "Search Finished: The value {x} was not found in the array named A." 
     * to the command line terminal and to the output file stream.
     * 
     * Otherwise (i.e. if x was found to be an element of the array named A),
     * print "Search Finished: The value {x} was fount at array index {r} in the array named A."
     * to the command line terminal and to the output file stream.
     */
    if (r == -1) 
    {
        std::cout << "\n\nSearch Finished: The value " << x << " was not found in the array named A.";
        file << "\n\nSearch Finished: The value " << x << " was not found in the array named A.";
    }
    else
    {
        std::cout << "\n\nSearch Finished: The value " << x << " was found at array index " << r << " in the array named A.";
        file << "\n\nSearch Finished: The value " << x << " was found at array index " << r << " in the array named A.";    
    }

    // Print the function execution runtime (in seconds) to the command line terminal.
    std::cout << "\n\nThe " << search_algorithm_names[c] << " function runtime was " << duration.count() << " seconds.";

    // Print the function execution runtime (in seconds) to the output file stream.
    file << "\n\nThe " << search_algorithm_names[c] << " function runtime was " << duration.count() << " seconds.";

    // De-allocate memory which was used to instantiate the dynamically-allocated array named A.
    delete [] A;

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
 * This function instantiates an array consisting of exclusively N int-type elements 
 * which each have a value which is no larger than T and such that those elements 
 * are arranged in a randomized order. 
 * 
 * This function returns a pointer-to-int value. Specifically, this function returns
 * the memory address of the first element of a dynamic array.
 * 
 * (A dynamic array is an array whose size is not determined until program runtime (which means 
 * that the amount of contiguous memory cells needed to allocate to that array is unknown 
 * to the computer at program compile time (which is not the case for a static array 
 * (i.e. fixed-size array)))).
 * 
 * N is assumed to be a natural number no larger than MAXIMUM_N.
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

    // Populate the array with random values which are no smaller than 0 and no larger than (T - 1).
    for (int i = 0; i < N; i += 1) A[i] = std::rand() % T;

    // Return the array after setting each element of that array to a randomized nonnegative integer value.
    return A;
}

/**
 * Print the contents of the array whose first element (i.e. A[0]) is the memory address stored in A.
 * 
 * First print the following header to the output stream (quotations excluded): "ARRAY A:"
 * Thenn print the data value of each element of A and the memory address of that element on its own separate line.
 * 
 * Assume that A is a pointer-to-int containing the address of A[0].
 * 
 * Assume that N is the total number of elements in A.
 * 
 * Assume that output is an output stream handler.
 */
void print_array(int * A, int N, std::ostream & output)
{
    output << "\n\nARRAY A: ";
    for (int i = 0; i < N; i++) output << "\n\nA[" << i << "] := " << A[i] << ". // The memory address of A[" << i << "] is " << &A[i] << ".";
}

/**
 * Use the Bubble Sort algorithm to arrange the elements of an int type array, 
 * A, in ascending order.
 * 
 * Assume that the value which is passed into this function as A is the memory 
 * address of the first element of a one-dimensional array of int type values.
 * 
 * Assume that the value which is passed into this function as S is the total 
 * number of elements which comprise the array represented by A.
 * 
 * This function returns no value (but it does update the array 
 * referred to as A if the elements of A are not already sorted in 
 * ascending order). 
 */
void bubble_sort(int * A, int S)
{
    int i = 0, placeholder = 0; 
    bool array_is_sorted = false, adjacent_elements_were_swapped = false;
    while (!array_is_sorted)
    {
        adjacent_elements_were_swapped = false;
        for (i = 1; i < S; i += 1)
        {
            if (A[i] < A[i - 1])
            {
                placeholder = A[i];
                A[i] = A[i - 1];
                A[i - 1] = placeholder;
                adjacent_elements_were_swapped = true;
            }
        }
        if (!adjacent_elements_were_swapped) array_is_sorted = true;
    }
}

/**
 * Use the LINEAR_SEARCH algorithm to find the first instance of a given integer value, x, in an array of integers named A.
 * 
 * If x is determined to be the value of an element in A, 
 * then return the index number of the array element which stores that value named x.
 * 
 * Otherwise (i.e. if x is not found in that array), return negative one.
 * 
 * Assume that A is a pointer-to-int variable which stores the memory address of A[0].
 * 
 * Assume that N is the total number of elements in the single-dimensional int-type array named A.
 * 
 * Assume that x is an int-type value.
 * 
 * ------
 * 
 * ChatGPT-4o Summary: 
 * 
 * Linear search is the simplest searching algorithm that checks each element of the data structure sequentially until the desired element is found or the structure is exhausted.
 * 
 * ------
 * 
 * Note that the LINEAR_SEARCH algorithm has a time complexity of O(N) (i.e. linear time in Big-O Notation).
 * 
 * What that means is that, as the total number of elements in the array increases,
 * the worst-case scenario (i.e. least time-efficient) execution time of that algorithm increases at
 * a rate which is directly proportional to the array length increase
 * (which means that the execution time, O, increases at the same rate as does the array length, N).
 */
int linear_search(int * A, int N, int x)
{
    // Iterate over each element in the array named A starting at A[0] and ending at A[N - 1] and traversing the array from left to right.
    for (int i = 0; i < N; i++) 
    {
        // Determine whether the current element, A[i], matches the target value, x.
        if (A[i] == x) 
        {
            // Return the index of A[i] if a match is found.
            return i;  
        }
    }
    // Return -1 if no matches are found.
    return -1;  
}

/**
 * Use the BINARY_SEARCH algorithm to find the first instance of a given integer value, x, in an array of integers named A.
 * 
 * If x is determined to be the value of an element in A, 
 * then return the index number of the array element which stores that value named x.
 * 
 * Otherwise (i.e. if x is not found in that array), return negative one.
 * 
 * NOTE THAT THIS FUNCTION ASSUMES THAT THE ELEMENTS OF A ARE ARRANGED IN ASCENDING ORDER!
 * 
 * Assume that A is a pointer-to-int variable which stores the memory address of A[0] (i.e. the left-most element of A).
 * 
 * Assume that left is the value zero.
 * 
 * Assume that right is a nonnegative integer representing the index of the right-most element of A.
 * 
 * Assume that x is an int-type value.
 * 
 * ------
 * 
 * ChatGPT-4o Summary: 
 * 
 * Binary search is a highly efficient algorithm that works on sorted arrays. It repeatedly divides the search interval in half and compares the middle element with the target value.
 * 
 * ------
 * 
 * Note that the BINARY_SEARCH algorithm has a time complexity of O(log base 2 of N) (i.e. logarithmic time in Big-O Notation).
 * 
 * What that means is that, as the total number of elements in the array increases,
 * the worst-case scenario (i.e. least time-efficient) execution time of that algorithm increases at
 * a rate which is logarithmically proportional to the array length increase
 * (which means that the execution time, O, increases at a slower rate than does the array length, N).
 * 
 * ------
 * 
 * Summary: 
 */
int binary_search(int * A, int left, int right, int x) 
{
    int result = -1;
    while (left <= right) 
    {
        int mid = left + (right - left) / 2;

        if (A[mid] == x) 
        {
            result = mid;  // Store the index, but keep searching the left side.
            right = mid - 1;
        }
        else if (A[mid] < x) 
        {
            left = mid + 1;
        }
        else 
        {
            right = mid - 1;
        }
    }
    return result;  // Return the leftmost occurrence of x or -1 if not found.
}

/**
 * Use the TERNARY_SEARCH algorithm to find the first instance of a given integer value, x, in an array of integers named A.
 * 
 * If x is determined to be the value of an element in A, 
 * then return the index number of the array element which stores that value named x.
 * 
 * Otherwise (i.e. if x is not found in that array), return negative one.
 * 
 * NOTE THAT THIS FUNCTION ASSUMES THAT THE ELEMENTS OF A ARE ARRANGED IN ASCENDING ORDER!
 * 
 * Assume that A is a pointer-to-int variable which stores the memory address of A[0] (i.e. the left-most element of A).
 * 
 * Assume that left is the value zero.
 * 
 * Assume that right is a nonnegative integer representing the index of the right-most element of A.
 * 
 * Assume that x is an int-type value.
 * 
 * ------
 * 
 * ChatGPT-4o Summary: 
 * 
 * Ternary search is similar to binary search but divides the array into three parts and checks two middle points instead of one. It's typically used in unimodal functions (functions that have a single peak or trough).
 * 
 * ------
 * 
 * Note that the TERNARY_SEARCH algorithm has a time complexity of O(log base 3 of N) (i.e. logarithmic time in Big-O Notation).
 * 
 * What that means is that, as the total number of elements in the array increases,
 * the worst-case scenario (i.e. least time-efficient) execution time of that algorithm increases at
 * a rate which is logarithmically proportional to the array length increase
 * (which means that the execution time, O, increases at a slower rate than does the array length, N).
 */
int ternary_search(int * A, int left, int right, int x)
{
    if (right >= left) 
    {
        // Calculate the two mid points in A (or in the current subarray of A).
        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) / 3;

        // Check if x is present at any of those mid points. If so, return the index of the first mid point where x is found.
        if (A[mid1] == x) return mid1;
        if (A[mid2] == x) return mid2;

        // If x is present in the left one-third, return the index of the element of A where x is found.
        if (x < A[mid1]) return ternary_search(A, left, mid1 - 1, x);

        // If x is present in the right one-third, return the index of the element of A where x is found.
        else if (x > A[mid2]) return ternary_search(A, mid2 + 1, right, x);
    
        // If x is present in the middle one-third, return the index of the element of A where x is found.
        else return ternary_search(A, mid1 + 1, mid2 - 1, x); 
    }

    // Return -1 if the target value, x, is not found in A.
    return -1;
}

/**
 * Use the FIBONACCI_SEARCH algorithm to find the first instance of a given integer value, x, in an array of integers named A.
 * 
 * If x is determined to be the value of an element in A, 
 * then return the index number of the array element which stores that value named x.
 * 
 * Otherwise (i.e. if x is not found in that array), return negative one.
 * 
 * NOTE THAT THIS FUNCTION ASSUMES THAT THE ELEMENTS OF A ARE ARRANGED IN ASCENDING ORDER!
 * 
 * Assume that A is a pointer-to-int variable which stores the memory address of A[0].
 * 
 * Assume that N is the total number of elements in the single-dimensional int-type array named A.
 * 
 * Assume that x is an int-type value.
 * 
 * ------
 * 
 * ChatGPT-4o Summary: 
 * 
 * Fibonacci search is similar to binary search but uses Fibonacci numbers to divide the array into sub-arrays. This method minimizes the number of comparisons. 
 *
 * ------
 * 
 * Note that the FIBONACCI_SEARCH algorithm has a time complexity of O(log base φ of n) (i.e. logarithmic time in Big-O Notation).
 * 
 * What that means is that, as the total number of elements in the array increases,
 * the worst-case scenario (i.e. least time-efficient) execution time of that algorithm increases at
 * a rate which is logarithmically proportional to the array length increase
 * (which means that the execution time, O, increases at a slower rate than does the array length, N).
 * 
 * Note that, in this context, phi (i.e. φ) represents the Golden Ratio.
 */
int fibonacci_search(int * A, int N, int x)
{
    // Initialize the first two Fibonacci numbers.
    int fibMMm2 = 0;  // (m-2)'th Fibonacci number
    int fibMMm1 = 1;  // (m-1)'th Fibonacci number
    int fibM = fibMMm2 + fibMMm1;  // m'th Fibonacci number

    // fibM is the smallest Fibonacci number greater than or equal to N.
    while (fibM < N) 
    {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    // The offset denotes the eliminated range from the front of the array.
    int offset = -1;

    // While there are elements to be inspected...
    while (fibM > 1) 
    {
        // Determine whether fibMMm2 is a valid location
        int i = std::min(offset + fibMMm2, N - 1);

        // If x is larger than the value at A[fibMMm2], then eliminate searching through the subarray from A[offset] to A[i].
        if (A[i] < x) 
        {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        }
        // If x is smaller than the value at A[fibMMm2], then eliminate searching through the subarray to the right of A[i+1].
        else if (A[i] > x) 
        {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        }
        // If x is equal to the value at A[fibMMm2], then return the index of the current array element.
        else return i;
    }

    // If the last element in the array (or subarray) is equal to the target value, x, then return the index of that last array element.
    if (fibMMm1 && A[offset + 1] == x) return offset + 1;

    // Return -1 if the target value, x, is not found in A.
    return -1;
}

/**
 * Use the EXPONENTIAL_SEARCH algorithm to find the first instance of a given integer value, x, in an array of integers named A.
 * 
 * If x is determined to be the value of an element in A, 
 * then return the index number of the array element which stores that value named x.
 * 
 * Otherwise (i.e. if x is not found in that array), return negative one.
 * 
 * NOTE THAT THIS FUNCTION ASSUMES THAT THE ELEMENTS OF A ARE ARRANGED IN ASCENDING ORDER!
 * 
 * Note also that this function uses the previously defined function for BINARY_SEARCH as a "helper function".
 * 
 * Assume that A is a pointer-to-int variable which stores the memory address of A[0].
 * 
 * Assume that N is the total number of elements in the single-dimensional int-type array named A.
 * 
 * Assume that x is an int-type value.
 * 
 * ------
 * 
 * ChatGPT-4o Summary: 
 * 
 * Exponential search finds the range in which the element is located and then performs a binary search within that range. It starts with a sub-array size of 1 and doubles it each time.
 *
 * ------
 * 
 * Note that the EXPONENTIAL_SEARCH algorithm has a time complexity of O(log base 2 of N) (i.e. logarithmic time in Big-O Notation).
 * 
 * What that means is that, as the total number of elements in the array increases,
 * the worst-case scenario (i.e. least time-efficient) execution time of that algorithm increases at
 * a rate which is logarithmically proportional to the array length increase
 * (which means that the execution time, O, increases at a slower rate than does the array length, N).
 */
int exponential_search(int * A, int N, int x)
{
    // If the target value is found at the first element of the array, then return the index of that element.
    if (A[0] == x) return 0;

    // Find the range for the binary search by repeated doubling of the array index value.
    int i = 1;
    while (i < N && A[i] <= x) i = i * 2;

    // Perform a binary search on the found range.
    return binary_search(A, i / 2, std::min(i, N - 1), x);
}

/**
 * Use the JUMP_SEARCH algorithm to find the first instance of a given integer value, x, in an array of integers named A.
 * 
 * If x is determined to be the value of an element in A, 
 * then return the index number of the array element which stores that value named x.
 * 
 * Otherwise (i.e. if x is not found in that array), return negative one.
 * 
 * NOTE THAT THIS FUNCTION ASSUMES THAT THE ELEMENTS OF A ARE ARRANGED IN ASCENDING ORDER!
 * 
 * Assume that A is a pointer-to-int variable which stores the memory address of A[0].
 * 
 * Assume that N is the total number of elements in the single-dimensional int-type array named A.
 * 
 * Assume that x is an int-type value.
 * 
 * ------
 * 
 * ChatGPT-4o Summary: 
 * 
 * Jump search works on sorted arrays by jumping ahead by fixed steps and then performing a linear search within the identified block.
 *
 * ------
 * 
 * Note that the JUMP_SEARCH algorithm has a time complexity of O(sqrt(n)) (i.e. square root time in Big-O Notation).
 * 
 * What that means is that, as the total number of elements in the array increases,
 * the worst-case scenario (i.e. least time-efficient) execution time of that algorithm increases at
 * a rate which is proportional to the square root of the array length increase
 * (which means that the execution time, O, increases at a slower rate than does the array length, N).
 */
int jump_search(int * A, int N, int x)
{
    // Find the block size to be jumped.
    int step = std::sqrt(N);

    // Find the block where the target element value is present (if it is present).
    int prev = 0;
    while (A[std::min(step, N) - 1] < x) 
    {
        prev = step;
        step += std::sqrt(N);
        if (prev >= N) 
        {
            return -1; // Element not found.
        }
    }

    // Linear search within the identified block.
    while (A[prev] < x) 
    {
        prev++;
        // If the next block or end of the array is reached, it is determined that the target element is not present.
        if (prev == std::min(step, N)) 
        {
            return -1; // Element not found.
        }
    }

    // Return the index of the array element which has the value x.
    if (A[prev] == x) {
        return prev;
    }

    // Return -1 if the target value, x, is not found in A.
    return -1; 
}
