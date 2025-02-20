#include <stdio.h>
#include "input.h"
#include "recognition.h"

#define INPUT_SIZE 64
#define RETRAIN 0 /* Set to 1 to force retraining on every run */

int main(void)
{
  double userInput[INPUT_SIZE];
  double result;

  printf("Initializing perceptron...\n");
  trainPerceptron(RETRAIN); /* Train or load weights */

  printf("Draw your letter on the 8x8 grid. Press Enter when done.\n");
  getUserGridInput(userInput);

  result = classifyGrid(userInput);
  printf("Classification Result: %f\n", result);

  if (result > 0.95)
  {
    printf("Letter 'A' detected!\n");
  }
  else
  {
    printf("No match found.\n");
  }

  printf("Press Enter to exit...");
  getchar();

  return 0;
}