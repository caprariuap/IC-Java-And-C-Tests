#include "layer.h"
#include <string.h>

/* The sigmoid function and derivative. */
double sigmoid(double x) {
    /**** PART 1 - QUESTION 1 ****/
    return 1.0 / (1.0 + exp(-x));
    /* 1 MARK */
}

double sigmoidprime(double x) {
    return x * (1 - x);
}

/* Creates a single layer. */
layer_t *layer_create() {
    /**** PART 1 - QUESTION 2 ****/
    struct layer *layert = malloc(sizeof(struct layer));
    memset(layert, 0, sizeof(struct layer));
    return layert;
    /* 2 MARKS */
}

/* Initialises the given layer. */
bool layer_init(layer_t *layer, int num_outputs, layer_t *prev) {
    /**** PART 1 - QUESTION 3 ****/
    layer->prev = prev;
    layer->num_outputs = num_outputs;
    layer->outputs = calloc(num_outputs, sizeof(double));
    if (layer->outputs == NULL) {
        return true;
    }
    memset(layer->outputs, 0, sizeof(double) * num_outputs);
    if (prev == NULL) {
        return false;
    }
    prev->next = layer;
    layer->num_inputs = prev->num_outputs;
    layer->biases = calloc(num_outputs, sizeof(double));
    layer->deltas = calloc(num_outputs, sizeof(double));
    if (!layer->deltas || !layer->biases) {
        return true;
    }
    layer->weights = malloc(sizeof(double *) * layer->num_inputs);
    if (!layer->weights) {
        return true;
    }
    layer->weights[0] = malloc(sizeof(double) * num_outputs * layer->num_inputs);
    if (!layer->weights[0]) {
        return true;
    }
    int i, j;
    for (i = 1; i < layer->num_inputs; i++) {
        layer->weights[i] = layer->weights[i - 1] + num_outputs;
    }
    for (i = 0; i < layer->num_inputs; i++) {
        for (j = 0; j < layer->num_outputs; j++) {
            layer->weights[i][j] = ANN_RANDOM();
        }
    }
    return false;
    /* 4 MARKS */
}

/* Frees a given layer. */
void layer_free(layer_t *layer) {
    /**** PART 1 - QUESTION 4 ****/
    if (layer->outputs) {
        free(layer->outputs);
    }
    if (layer->weights) {
        if (layer->weights[0]) {
            free(layer->weights[0]);
        }
        free(layer->weights);
    }
    if (layer->biases) {
        free(layer->biases);
    }
    if (layer->deltas) {
        free(layer->deltas);
    }
    /* 2 MARKS */
}

/* Computes the outputs of the current layer. */
void layer_compute_outputs(layer_t const *layer) {
    /**** PART 1 - QUESTION 5 ****/
    /* objective: compute layer->outputs */
    int i, j;
    for (j = 0; j < layer->num_outputs; j++) {
        double sum = 0;
        for (i = 0; i < layer->num_inputs; i++) {
            sum += (layer->weights[i][j] * layer->prev->outputs[i]);
        }
        layer->outputs[j] = sigmoid(layer->biases[j] + sum);
    }
    /* 3 MARKS */
}

/* Computes the delta errors for this layer. */
void layer_compute_deltas(layer_t const *layer) {
    /**** PART 1 - QUESTION 6 ****/
    /* objective: compute layer->deltas */
    int i, j;
    for (i = 0; i < layer->num_outputs; i++) {
        double sum = 0;
        for (j = 0; j < layer->next->num_outputs; j++) {
            sum += (layer->next->weights[i][j] * layer->next->deltas[j]);
        }
        layer->deltas[i] = sigmoidprime(layer->outputs[i]) * sum;
    }
    /* 2 MARKS */
}

/* Updates weights and biases according to the delta errors given learning rate. */
void layer_update(layer_t const *layer, double l_rate) {
    /**** PART 1 - QUESTION 7 ****/
    /* objective: update layer->weights and layer->biases */
    int i, j;
    for (i = 0; i < layer->num_inputs; i++) {
        for (j = 0; j < layer->num_outputs; j++) {
            layer->biases[j] += (l_rate * layer->deltas[j]);
            layer->weights[i][j] += (l_rate * layer->prev->outputs[i] * layer->deltas[j]);
        }
    }
    /* 1 MARK */
}
