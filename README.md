
#Sorting Algorithm Visualization Program - README
Overview
This program simulates and visualizes various sorting algorithms using graphics. It allows the user to select an algorithm, interactively sort an array of integers using manual or automated methods, and view performance statistics. The algorithms supported include Bubble Sort, Selection Sort, Insertion Sort, Quick Sort, and Merge Sort.

Features
Manual Sorting Mode: Allows users to sort the array interactively by moving elements and swapping them.
Automated Sorting Mode: Sorts the array automatically using the selected sorting algorithm and visualizes the sorting process.
Array Manipulation: Users can add or remove elements (with color codes ranging from 1 to 15) to/from the array.
Performance Statistics: Displays statistics such as the number of swaps, comparisons, and the time taken for each sorting algorithm.
Real-time Visualization: Displays each element as a colored circle, and the sorting process is visually represented by moving the circles.
Prerequisites
Graphics.h library: This program uses the graphics.h library to handle the graphical rendering of arrays. It is compatible with Turbo C++ or other compilers that support graphics.h (often found in older or legacy C++ compilers).
Installation
Install a C++ IDE that supports graphics.h (e.g., Turbo C++).
Ensure that the graphics.h library is available in your development environment.
How to Use
1. Selecting Sorting Algorithm
At the start of the program, you will be prompted to select a sorting algorithm:

Bubble Sort
Selection Sort
Insertion Sort
Quick Sort
Merge Sort
Choose the algorithm by entering the corresponding number.

2. Adding/Removing Elements
Once an algorithm is selected, the program will ask if you want to modify the array. You can:

Enter 1 to add an element with a color code (between 1 and 15).
Enter 2 to remove the last element.
Enter 0 to proceed to sorting.
3. Sorting Modes
Manual Sorting Mode: Allows you to move elements left or right and swap them interactively using keyboard commands:
Press 'a' to move left.
Press 'd' to move right.
Press Spacebar to swap the selected element with the next one.
Press 'q' to finish sorting.
Automated Sorting Mode: The selected algorithm will automatically sort the array, and the program will visualize the sorting process.
4. Performance Statistics
After sorting is completed, the program will display performance statistics for each sorting algorithm:

Number of swaps
Number of comparisons
Time taken to perform the sort.
The statistics are updated for both the manual sorting and automated sorting processes.

5. Graphical Visualization
The sorting process is visually represented:

Each element is shown as a colored circle with the element's value displayed at the center.
Swaps and movements are animated, showing the transition of elements as they are sorted.
6. End of Sorting
Once the sorting is completed, the program will display the sorted array and wait for 5 seconds before closing. The program also offers an option to display a summary of the sorting algorithm's performance.

Key Functions
Drawing Functions
drawFilledCircle(x, y, color): Draws a filled circle at position (x, y) with a specified color.
drawArray(offsetY): Draws the array with the elements displayed as circles.
drawSelectedCircle(index, offsetY): Highlights the selected circle (element) during manual sorting.
animateSwap(index1, index2): Animates the swap of two elements at index1 and index2.
Sorting Functions
bubbleSort(): Implements the bubble sort algorithm with visualization.
selectionSort(): Implements the selection sort algorithm with visualization.
insertionSort(): Implements the insertion sort algorithm with visualization.
quickSort(low, high): Implements the quicksort algorithm with visualization.
mergeSort(left, right): Implements the merge sort algorithm with visualization.
Utility Functions
addElement(color): Adds a new element with a given color code (from 1 to 15) to the array.
removeElement(): Removes the last element from the array.
manualSort(): Allows the user to interactively sort the array by moving and swapping elements manually.
displayStatistics(): Displays statistics about the sorting algorithms' performance.
displayStatistics1(): Displays only manual sorting statistics.
resetStats(stats): Resets the statistics for a sorting algorithm.
