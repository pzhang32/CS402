#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//---------------------- PROTOTYPE FUCTIONS -----------------------------//

// The below function loads in the data from the data file and creates the DB
float * CreateDB(char* datafile, int* xp, int* yp);

// The below function is used to print out the statistical results of the data        
void PrintDB (float arr[], int size, int total_size);

// Used for sorting
void Swap(float* xp, float* yp);
  
// Function to perform Selection Sort on Employee ID in ascending order
void SelectionSort(float arr[], int n);

// Takes in size of array that is already sorted an returns the median
float median(float arr[], int size);

// Returns mean of an array of floats
double mean(float arr[], int size);

/* Returns population standard deviation by using the following formula: 
   stddev = sqrt((sum((xi - mean)^2))/N)
where the sum() goess from 1 to N, xi is the i-th element, N is 
the number of elements in the data set, and sqrt() is the square root function.  */
double stddev(float arr[], int size);


//------------------------------ Main -----------------------------------//
/* Main function that displays the DB actions menu to the user until they choose to close out of the program. */
int main(int argc, char *argv[])
{
    if ( argc != 2 ) /* argc should be 2 for correct execution */
    {
        /* We print argv[0] assuming it is the program name */
        printf( "usage: %s filename\n", argv[0] );
    }
    else
    {   
        int data_count = 0;
        int array_size = 20;
        float* dataset;

        dataset = CreateDB(argv[1], &data_count, &array_size); // Calls the function above to create the DB from the input data file   
        SelectionSort(dataset, data_count); // Sorts the DB in ascending order
        PrintDB(dataset, data_count, array_size);      
    }
}

// The below function loads in the data from the data file and creates the DB
float * CreateDB(char* datafile, int* data_count, int* array_size)
{
    int n = 20;
    // Dynamically allocate memory using malloc() 
    float* dataset = (float*)malloc(n * sizeof(float)); 
    
    // Check if the memory has been successfully 
    // allocated by malloc or not 
    if (dataset == NULL) { 
        printf("Memory not allocated.\n"); 
        exit(0); 
    } 
    
    // Read in the data from the input file
    int counter = 0;
    float data = 0;
    FILE *file;
    file = fopen(datafile, "r");

    char buffer[100];   
    while (fgets(buffer, sizeof(buffer), file))  
    {
        data = strtof(buffer, NULL);
        dataset[counter] = data;
        counter++; 
        

        if (counter == n)
        {
            
            n = n*2;
            float* dataset_temp = (float*)malloc(n * sizeof(float)); 

            // Check if the memory has been successfully 
            // allocated by malloc or not 
            if (dataset_temp == NULL) { 
                printf("Memory not allocated.\n"); 
                exit(0); 
            }


            memcpy(dataset_temp, dataset, n * sizeof(float));
            free(dataset);
            dataset = (float*)malloc(n * sizeof(float)); 
            memcpy(dataset, dataset_temp, n * sizeof(float));
            free(dataset_temp);
        }
    }
    if (feof(file)) // hit end of file
    {
        fclose(file);
    } 
    *array_size = n;
    *data_count = counter;
    return dataset;
}

// The below function is used to print out the DB        
void PrintDB (float arr[], int n, int total_size)
{
    printf("\nResults:\n");
    printf("-----------\n");
    printf("Num Values:\t\t%d\n", n);
    printf("Mean\t\t\t%lf\n", mean(arr, n));
    printf("Median:\t\t\t%f\n", median(arr, n));
    printf("Stddev:\t\t\t%lf\n", stddev(arr, n));
    printf("Unused Array Capacity:\t%d\n\n", (total_size-n));
}

// Used for sorting
void Swap(float* xp, float* yp) 
{ 
    float temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
// Function to perform Selection Sort on DB
void SelectionSort(float arr[], int n) 
{ 
    int i, j, min_idx; 
   
    // One by one move boundary of unsorted subarray 
    for (i = 0; i < n - 1; i++) { 
  
        // Find the minimum element in unsorted array 
        min_idx = i; 
        for (j = i + 1; j < n; j++) 
            if (arr[j] < arr[min_idx]) 
                min_idx = j; 
  
        // Swap the found minimum element 
        // with the first element 
        Swap(&arr[min_idx], &arr[i]); 
    } 
} 

// Takes in size of array that is already sorted an returns the median
float median(float arr[], int size)
{
    float median = 0;
    // if number of elements are even
    if(size % 2 == 0)
    {
        median = (arr[(size-1)/2] + arr[size/2])/2.0;
    }
    // if number of elements are odd
    else
    {
        median = arr[size/2];
    }
    return median;
}

// Returns mean of an array of floats
double mean(float arr[], int size)
{
    int counter;
    float sum;
    double avg;

    sum = avg = 0;
   
    for(counter = 0; counter < size; counter++) 
    {
      sum = sum + arr[counter];
    }
   
    avg = (double)sum / size;
    return avg;
}

/* Returns population standard deviation by using the following formula: 
   stddev = sqrt((sum((xi - mean)^2))/N)
where the sum() goess from 1 to N, xi is the i-th element, N is 
the number of elements in the data set, and sqrt() is the square root function.  */
double stddev(float arr[], int size)
{
    int counter;
    float sum;
    double avg, stddev;

    avg = mean(arr, size); 
   
    for(counter = 0; counter < size; counter++) 
    {
      sum = sum + ((arr[counter] - avg) * (arr[counter] - avg));
    }
   
    stddev = (double) sqrt(sum / size);
    return stddev;

}