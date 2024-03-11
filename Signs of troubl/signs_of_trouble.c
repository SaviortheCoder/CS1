#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define APLHABET_SIZE 26    // 3. Replace magic numbers like 26 with a constant or a macro to make the code more understandable.
#define MAX_CHARS 100000 


//to improve code...

// 1. Optimize Input Reading: Instead of using fgets, you can use scanf to read input. Since you're reading a single line of characters, scanf can simplify the input reading process.

// 2. Use Array Indexing: Instead of using ASCII math to convert characters to array indices, you can directly use array indexing. This can improve code readability.

// 3. Remove Magic Numbers: Replace magic numbers like 26 with a constant or a macro to make the code more understandable.

// 4. Avoid Redundant Loop: You can combine the loops for counting letters in both the original and desired messages into a single loop.

// 5. base case for if memory allocation failed for example ....  if (original == NULL || desired == NULL) { perror ("memory allaction failed");  return 1; }


int main(void){

    char* initial_Str;  //The pointer arrays for the first and second string
    char* final_Str;
    char f = ' ';   //A char variable for the getchar user input for the frist and second string
    char s = ' ';
    int index = 0;  //Index for arr for the first and second strings for the get char method
    int index2 = 0;
    int letterCount[APLHABET_SIZE]= {0};   // arr for the fist and second aplhabet plus setting it equal to zero.. a counter array
    int letterCount2[APLHABET_SIZE] = {0}; 
    int NewLetterTotal = 0;     // a int variable for the output of new chars needed to make a new sign

    initial_Str = (char*)malloc(sizeof(char) * MAX_CHARS); //ASKING FOR MEMORY AND SPECIFYING THE TYPE AND SIZE NEEDED FOR THE FIRST AND FINAL STRING
    final_Str = (char*)malloc(sizeof(char) * MAX_CHARS);


    if(initial_Str == NULL || final_Str == NULL){    // 5. base case if memory allocation fails
        perror("Memory allocation failed");  //perror is a method to print an error message to the user
        return 1;
    }


    while( f != '\n'){ //loop for the arr of user input

        f = getchar(); //SIMILAR TO SCANF FOR CHAR BY CHAR to get the user input per letter for the first sign by taking ever character until the uer presses return or \n key
        initial_Str[index] = f; //Setting the arr[] equal to the getchar user input then adding on to the index
        index++; 

    } 
    initial_Str[index] = '\0'; 

    while (s != '\n'){  // a loop to get the user input per letter for the second sign

        s = getchar();
        final_Str[index2] = s;
        index2++;

    }
    final_Str[index2] = '\0'; //To inpret the last character of the arr


    for(int i = 0; initial_Str[i] != '\0'; i++){ //BOTH FOR LOOPS ONLY TAKE CAPITAL VALUES
        if(initial_Str[i] >= 65 && initial_Str[i] <= 90){   //referencing the ASii values of A-Z all capital letters ... could have used 'A' & 'Z'
            letterCount[(int)initial_Str[i] - 65]++;     //turns intitalStr to its ASII value, adds to the count of the letter Arr and  saves each letter of the aplhabet to save it into the ARR 
        }
    }
   for(int i = 0; final_Str[i] != '\0'; i++){
        if(final_Str[i] >= 65 && final_Str[i] <= 90){
            letterCount2[(int)final_Str[i] - 65]++; //turns Final_Str to its ASII value, adds to the count of the letter Arr and  saves each letter of the aplhabet to save it into the ARR
        }
    } 

    for(int i=0; i < 26; i++){     //a for loop for the alphabet
        if(letterCount2[i]-letterCount[i] > 0){     //if the difference is greater than add that difference to the total letters needed to get
            NewLetterTotal = NewLetterTotal + (letterCount2[i]-letterCount[i]);
            
        }

    }

printf("%d\n", NewLetterTotal);      //print function for total characters needed for the new sign
free(initial_Str);      //since I used the method malloc I made sure to free the space for the initail and final string
free(final_Str);
return 0;
}