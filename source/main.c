/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ardayalman <ardayalman@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 01:37:50 by ardayalman        #+#    #+#             */
/*   Updated: 2022/09/01 03:04:06 by ardayalman       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/neural_network.h"

double init_weights()
{
	return (((double)rand()) / ((double)RAND_MAX));
}

double sigmoid(double val)
{
	return (1 / (1 + (exp(-val))));
}

/* Derivative of the sigmoid function
*/
double dsigmoid(double val)
{
	return (val * (1 - val));
}

//Basic swap function.
void swap(int *a, int *b)
{
	int	i;

	i = *a;
	*a = *b;
	*b = i;
}

/*Dataset that we want to shuffle.
*/
void shuffle(int *array, size_t n)
{
		size_t	i;
		size_t	j;

	if (n > 1)
	{
		i = 0;
		while (i < n - 1)
		{
			j = i + rand() / (RAND_MAX / (n - i) + 1);
			swap(&array[j], &array[i]);
			i++;
		}
	}
}

int main()
{
	const double lr = 0.1f;

	double hidden_layer[numHiddenNodes];
	double output_layer[numOutputs];

	double hidden_layer_bias[numHiddenNodes];
	double output_layer_bias[numOutputs];

	double hidden_weights[numInputs][numHiddenNodes];
	double output_weights[numHiddenNodes][numOutputs];

	double training_inputs[numTrainingSets][numInputs] =	{{0.0f, 0.0f},
															{1.0f, 0.0f},
															{0.0f, 1.0f},
															{1.0f, 1.0f}};

	double training_outputs[numTrainingSets][numOutputs] = 	{{0.0f},
															{1.0f},
															{1.0f},
															{0.0f}};

	for (int i = 0; i < numInputs; i++)
		for (int j = 0; j < numHiddenNodes; j++)
			hidden_weights[i][j] = init_weights();

	for (int i = 0; i < numHiddenNodes; i++)
		for (int j = 0; j < numOutputs; j++)
			output_weights[i][j] = init_weights();

	for (int j = 0; j < numOutputs; j++)
		output_layer_bias[j] = init_weights();

	int training_set_order[] = {0,1,2,3};

	int number_of_epochs = 10000;

	// train the neural network for a number of epochs

	for (int epoch = 0; epoch < number_of_epochs; epoch++)
	{
		shuffle(training_set_order, numTrainingSets);
		for (int i = 0; i < numTrainingSets; i++)
		{
			int a = training_set_order[i];
			// Forward pass

			// compute hidden layer activation
			for (int j = 0; j < numHiddenNodes ; j++)
			{
				double activation = hidden_layer_bias[j];
				for (int k = 0; k < numInputs; k++)
					activation += training_inputs[a][k] * hidden_weights[k][j];
				hidden_layer[j] = sigmoid(activation);
			}

			// compute output layer activation
			for (int j = 0; j < numOutputs ; j++)
			{
				double activation = output_layer_bias[j];
				for (int k = 0; k < numHiddenNodes; k++)
					activation += hidden_layer[k] * output_weights[k][j];
				output_layer[j] = sigmoid(activation);
			}
			printf("Input = %g Output = %g predicted output = %g\n", training_inputs[i][0], training_outputs[i][0], training_outputs[i][0])
		}
	}

}