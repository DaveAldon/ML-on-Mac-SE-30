#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "recognition.h"

#define INPUT_SIZE 64
#define TRAINING_SAMPLES 2
#define WEIGHTS_FILE "weights.dat"

static double weights[INPUT_SIZE];
static double bias;

static double sigmoid(double x);
static void saveWeights(void);
static int loadWeights(void);
static void initTrainingData(void);

static double training_data[TRAINING_SAMPLES][INPUT_SIZE];
static double labels[TRAINING_SAMPLES];

static double sigmoid(double x)
{
  return 1.0 / (1.0 + exp(-x));
}

/* Save Weights to a .dat file */
static void saveWeights(void)
{
  FILE *file;
  int i;

  file = fopen(WEIGHTS_FILE, "wb");
  if (file == NULL)
  {
    printf("Error saving weights.\n");
    return;
  }

  fwrite(weights, sizeof(double), INPUT_SIZE, file);
  fwrite(&bias, sizeof(double), 1, file);
  fclose(file);
}

/* Load Weights from .dat file */
static int loadWeights(void)
{
  FILE *file;
  int i;

  file = fopen(WEIGHTS_FILE, "rb");
  if (file == NULL)
  {
    return 0; /* File does not exist */
  }

  fread(weights, sizeof(double), INPUT_SIZE, file);
  fread(&bias, sizeof(double), 1, file);
  fclose(file);

  return 1; /* Successfully loaded */
}

/* Initializes our simple training data */
static void initTrainingData(void)
{
  int i;
  double sample1[INPUT_SIZE] = {
      0, 1, 1, 1, 1, 1, 1, 0,
      1, 0, 0, 0, 0, 0, 0, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      1, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 0, 0, 1,
      0, 0, 0, 0, 0, 0, 0, 0};

  double sample2[INPUT_SIZE] = {
      0, 1, 1, 1, 1, 1, 1, 0,
      1, 0, 0, 0, 0, 0, 0, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      1, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 0, 0, 1,
      0, 0, 0, 0, 0, 0, 0, 0};

  for (i = 0; i < INPUT_SIZE; i++)
  {
    training_data[0][i] = sample1[i];
    training_data[1][i] = sample2[i];
  }

  labels[0] = 1.0;
  labels[1] = 1.0;
}

/* Training loop for our perceptron */
void trainPerceptron(int retrain)
{
  double learning_rate = 0.1;
  int epochs = 100;
  int epoch, i, j;
  double sum, output, error;

  if (!retrain && loadWeights())
  {
    printf("Loaded trained weights from file.\n");
    return;
  }

  printf("Training perceptron...\n");

  initTrainingData();

  for (i = 0; i < INPUT_SIZE; i++)
  {
    weights[i] = ((double)rand() / (double)RAND_MAX) * 0.2 - 0.1;
  }

  bias = 0.1;

  for (epoch = 0; epoch < epochs; epoch++)
  {
    for (i = 0; i < TRAINING_SAMPLES; i++)
    {
      sum = bias;
      for (j = 0; j < INPUT_SIZE; j++)
      {
        sum += training_data[i][j] * weights[j];
      }
      output = sigmoid(sum);
      error = labels[i] - output;

      for (j = 0; j < INPUT_SIZE; j++)
      {
        weights[j] += learning_rate * error * training_data[i][j];
      }
      bias += learning_rate * error;
    }
  }

  printf("Training complete. Saving weights...\n");
  saveWeights();
}

double classifyGrid(double input[INPUT_SIZE])
{
  double sum = bias;
  int i;

  for (i = 0; i < INPUT_SIZE; i++)
  {
    sum += input[i] * weights[i];
  }

  return sigmoid(sum);
}