#include <graphics.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <chrono>
#include <string>

#define BLACK 0x000000 
#define WHITE 0xFFFFFF

using namespace std;

const int CIRCLE_RADIUS = 20; 
const int DELAY_TIME = 1000; 
const int MAX_COLORS = 15; 

vector<int> arr; 
int size = 0; 
int selectedIndex = 0; // For manual sorting
int manualSwaps = 0, manualComparisons = 0; // Track manual stats

struct Stats {
    int swaps = 0;
    int comparisons = 0;
    double time = 0.0; 
} bubbleStats, selectionStats, insertionStats, quickStats, mergeStats;

void drawFilledCircle(int x, int y, int color) {
    setcolor(color);
    circle(x, y, CIRCLE_RADIUS);
    floodfill(x, y, color); 
}

void drawArray(int offsetY) {
    int width = 400 / (size > 0 ? size : 1);
    for (int i = 0; i < size; i++) {
        int x = (i + 1) * width - width / 2;
        drawFilledCircle(x, offsetY, arr[i]);
        
        char str[4];
        sprintf(str, "%d", arr[i]);
        setcolor(BLACK);
        outtextxy(x - textwidth(str) / 2, offsetY - textheight(str) / 2, str);
    }
}

void drawSelectedCircle(int index, int offsetY) {
    if (index >= 0 && index < size) {
        int width = 400 / (size > 0 ? size : 1);
        int x = (index + 1) * width - width / 2;

        // Draw outer circle first
        setcolor(RED);
        circle(x, offsetY, CIRCLE_RADIUS + 5); // Make sure this is visible

        // Restore color for inner circle
        setcolor(arr[index]);
        drawFilledCircle(x, offsetY, arr[index]);

        // Draw the number on top of the selected circle
        char str[4];
        sprintf(str, "%d", arr[index]);
        setcolor(BLACK);
        outtextxy(x - textwidth(str) / 2, offsetY - textheight(str) / 2, str);
    }
}


void drawHorizontalLine(int offsetY) {
    setcolor(WHITE);
    line(0, offsetY, 400, offsetY);
}

void displayStats(const Stats& stats, int offsetY) {
    char buffer[100];
    sprintf(buffer, "Swaps: %d, Comparisons: %d, Time: %.3f s", stats.swaps, stats.comparisons, stats.time);
    setcolor(WHITE);
    outtextxy(10, offsetY, buffer);
}

void animateSwap(int index1, int index2) {
    int width = 400 / size;
    int y = 50;
    int x1 = (index1 + 1) * width - width / 2;
    int x2 = (index2 + 1) * width - width / 2;
    for (int i = 0; i <= 10; i++) {
        cleardevice();
        drawArray(y);
        drawHorizontalLine(y + CIRCLE_RADIUS + 20);
        int newX1 = x1 + (x2 - x1) * i / 10;
        int newX2 = x2 + (x1 - x2) * i / 10;

        char str1[4], str2[4];
        sprintf(str1, "%d", arr[index1]);
        sprintf(str2, "%d", arr[index2]);
        
        drawFilledCircle(newX1, y, arr[index1]);
        drawFilledCircle(newX2, y, arr[index2]);

        setcolor(BLACK);
        outtextxy(newX1 - textwidth(str1) / 2, y - textheight(str1) / 2, str1);
        outtextxy(newX2 - textwidth(str2) / 2, y - textheight(str2) / 2, str2);
        
        delay(50);
    }
}

void bubbleSort() {
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            bubbleStats.comparisons++;
            if (arr[j] > arr[j + 1]) {
                animateSwap(j, j + 1);
                swap(arr[j], arr[j + 1]);
                bubbleStats.swaps++;
            }
        }
        cleardevice();
        drawArray(50);
        drawHorizontalLine(70);
        displayStats(bubbleStats, 20);
        delay(DELAY_TIME);
    }
    auto end = chrono::high_resolution_clock::now();
    bubbleStats.time = chrono::duration<double>(end - start).count();
}

void selectionSort() {
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            selectionStats.comparisons++;
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            animateSwap(minIndex, i);
            swap(arr[minIndex], arr[i]);
            selectionStats.swaps++;
        }
        cleardevice();
        drawArray(50);
        drawHorizontalLine(70);
        displayStats(selectionStats, 20);
        delay(DELAY_TIME);
    }
    auto end = chrono::high_resolution_clock::now();
    selectionStats.time = chrono::duration<double>(end - start).count();
}

void insertionSort() {
    auto start = chrono::high_resolution_clock::now();
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            insertionStats.comparisons++;
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
        cleardevice();
        drawArray(50);
        drawHorizontalLine(70);
        displayStats(insertionStats, 20);
        delay(DELAY_TIME);
    }
    auto end = chrono::high_resolution_clock::now();
    insertionStats.time = chrono::duration<double>(end - start).count();
}

int partition(int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        quickStats.comparisons++;
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
            animateSwap(i, j);
            quickStats.swaps++;
        }
    }
    swap(arr[i + 1], arr[high]);
    animateSwap(i + 1, high);
    return (i + 1);
}

void quickSort(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

void merge(int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1), R(n2);
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        mergeStats.comparisons++;
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
        mergeStats.swaps++; // Counting moves as swaps for simplicity
    }
    while (i < n1) {
        arr[k++] = L[i++];
        mergeStats.swaps++; // Counting moves as swaps for simplicity
    }
    while (j < n2) {
        arr[k++] = R[j++];
        mergeStats.swaps++; // Counting moves as swaps for simplicity
    }
}

void mergeSort(int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        merge(left, mid, right);
    }
}

void addElement(int color) {
    if (size < MAX_COLORS) {
        arr.push_back(color);
        size++;
        cleardevice();
        drawArray(50);
         drawSelectedCircle(selectedIndex, 50);
    } else {
        cout << "Maximum size reached. Remove an element to add a new one." << endl;
    }
}

void removeElement() {
    if (!arr.empty()) {
        arr.pop_back();
        size--;
        cleardevice();
        drawArray(50);
    } else {
        cout << "No elements to remove." << endl;
    }
}

void displayStatistics() {
    cleardevice();
    setcolor(WHITE);
    outtextxy(10, 10, const_cast<char*>("Sorting Algorithm Performance Statistics:"));

    char buffer[100];
    sprintf(buffer, "Array Size: %d", size);
    outtextxy(10, 30, buffer);

    sprintf(buffer, "Manual Sort: %d swaps, %d comparisons", manualSwaps, manualComparisons);
    outtextxy(10, 50, buffer);

    sprintf(buffer, "Bubble Sort: %d swaps, %d comparisons, %.3f s", bubbleStats.swaps, bubbleStats.comparisons, bubbleStats.time);
    outtextxy(10, 70, buffer);

    sprintf(buffer, "Selection Sort: %d swaps, %d comparisons, %.3f s", selectionStats.swaps, selectionStats.comparisons, selectionStats.time);
    outtextxy(10, 90, buffer);

    sprintf(buffer, "Insertion Sort: %d swaps, %d comparisons, %.3f s", insertionStats.swaps, insertionStats.comparisons, insertionStats.time);
    outtextxy(10, 110, buffer);

    sprintf(buffer, "Quick Sort: %d swaps, %d comparisons, %.3f s", quickStats.swaps, quickStats.comparisons, quickStats.time);
    outtextxy(10, 130, buffer);

    sprintf(buffer, "Merge Sort: %d swaps, %d comparisons, %.3f s", mergeStats.swaps, mergeStats.comparisons, mergeStats.time);
    outtextxy(10, 150, buffer);

    delay(5000);
}

void displayStatistics1() {
    cleardevice();
    setcolor(WHITE);
    outtextxy(10, 10, const_cast<char*>("Sorting Algorithm Performance Statistics:"));

    char buffer[100];
    sprintf(buffer, "Manual Sort: %d swaps, %d comparisons", manualSwaps, manualComparisons);
    outtextxy(10, 30, buffer);

    delay(5000);
}
void manualSort() {
    char command;
    while (true) {
        cleardevice();
        drawArray(50);
       drawSelectedCircle(selectedIndex, 50);
        outtextxy(10, 200, const_cast<char*>("Commands: 'd' to move right, 'a' to move left, 'space' to swap, 'q' to finish sorting."));
        
        char buffer[100];
        sprintf(buffer, "Selected index: %d", selectedIndex);
        outtextxy(10, 220, buffer);
        sprintf(buffer, "Comparisons: %d, Swaps: %d", manualComparisons, manualSwaps);
        outtextxy(10, 240, buffer);

        // Wait for command
        command = getchar();
        if (command == 'a' && selectedIndex > 0) {
            selectedIndex--;
            manualComparisons++;
        } else if (command == 'd' && selectedIndex < size - 1) {
            selectedIndex++;
            manualComparisons++;
        } else if (command == ' ' && selectedIndex < size - 1) {
            swap(arr[selectedIndex], arr[selectedIndex + 1]);
            manualSwaps++;
        } else if (command == 'q') {
            break;
        }
    }
}

void resetStats(Stats& stats) {
    stats.swaps = 0;
    stats.comparisons = 0;
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    int choice;
    cout << "Choose sorting algorithm:\n";
    cout << "1. Bubble Sort\n";
    cout << "2. Selection Sort\n";
    cout << "3. Insertion Sort\n";
    cout << "4. Quick Sort\n";
    cout << "5. Merge Sort\n";
    cin >> choice;
	while (true) {
            cout << "Enter 1 to add an element, 2 to remove an element, 0 to start sorting: ";
            int action;
            cin >> action;

            if (action == 1) {
                int color;
                cout << "Enter color code (1-15): ";
                cin >> color;
                if (color >= 1 && color <= 15) {
                    addElement(color);
                } else {
                    cout << "Invalid color code! Must be between 1 and 15.\n";
                }
            } else if (action == 2) {
                removeElement();
            } else if (action == 0) {
                break;
            } else {
                cout << "Invalid action! Please enter 1, 2, or 0.\n";
            }
        }

    int mode;
    cout << "Select mode:\n1. Manual Sorting\n2. Automated Sorting\n";
    cin >> mode;

    if (mode == 1) {
        manualSort();
        cout << "Your sorted array: ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
        displayStatistics1();
    	delay(10000);
    } else {
        
        switch (choice) {
            case 1: bubbleSort(); break;
            case 2: selectionSort(); break;
            case 3: insertionSort(); break;
            case 4: quickSort(0, size - 1); break;
            case 5: mergeSort(0, size - 1); break;
            default: 
                cout << "Invalid choice.\n"; 
                closegraph(); 
                return 1;
        }
       

        cleardevice();
        drawArray(50);
        delay(3000);
        displayStatistics();
    	delay(10000);
    }
    
    
    closegraph();
    return 0;
}

