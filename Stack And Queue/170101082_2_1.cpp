#include <iostream>
#include <fstream>
using namespace std;

int *stockSpan(int *input, int n){
    // Output array to store the span of each stock on given day
    int *output = new int[n];

    // Using brute force to determine the output by using two for loops
    for(int i = 0; i < n; i++){
        int j = i;
        int span = 0;
        while(j >= 0){
            // If jth stock is lesst than or equal to the ith stock, then increase the span
            // by 1.
            if(input[j] <= input[i]){
                span++;
                j--;
            }
            // If jth stock is greater than ith stock, then output is complete for ith element
            else break;
        }
        // Store the span in the output array
        output[i] = span;
    }

    // Returning output
    return output;
}

int main(){
    // Inputting the file using ifstream for input
    ifstream inputFile;
    inputFile.open("input.txt");

    // Size of the input array
    int n;
    inputFile >> n;

    // Input array to store the stock on each day
    int *input = new int[n];
    for(int i = 0; i < n; i++) inputFile >> input[i];

    // for(int i = 0; i < n; i++) cout << input[i] << " ";
    // cout << endl;

    // Output array to store the span of each stock on given day
    int *output = stockSpan(input, n);

    // Printing the output
    cout << "Day\tPrice\tSpan" << endl;
    for(int i = 0; i < n; i++){
        printf("%2d\t%3d\t%2d\n", i, input[i], output[i]);
    }

    // Deallocating the memory used
    inputFile.close();
    delete[] input;
    delete[] output;
}
