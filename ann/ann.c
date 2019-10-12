#include "ann.h"

/* Creates and returns a new ann. */
ann_t *ann_create(int num_layers, int *layer_outputs) {
    /**** PART 2 - QUESTION 1 ****/
    if (num_layers < 1) {
        return NULL;
    }
    ann_t *ann = malloc(sizeof(ann_t));
    if (!ann) {
        return NULL;
    }
    ann->input_layer = layer_create();
    layer_init(ann->input_layer, layer_outputs[0], NULL);
    int i;
    layer_t *iter = ann->input_layer;
    for (i = 1; i < num_layers; i++) {
        layer_t *layer = layer_create();
        layer->prev = iter;
        iter->next = layer;
        layer_init(layer, layer_outputs[i], iter);
        iter = layer;
    }
    ann->output_layer = iter;
    return ann;
    /* 4 MARKS */
}

/* Frees the space allocated to ann. */
void ann_free(ann_t *ann) {
    /**** PART 2 - QUESTION 2 ****/
    layer_t *iter = ann->input_layer;
    while (iter != ann->output_layer) {
        layer_free(iter);
        iter = iter->next;
    }
    layer_free(iter);
    free(ann);
    /* 2 MARKS */
}

/* Forward run of given ann with inputs. */
void ann_predict(ann_t const *ann, double const *inputs) {
    /**** PART 2 - QUESTION 3 ****/
    layer_t *iter = ann->input_layer;
    int i;
    for (i = 0; i < iter->num_outputs; i++) {
        iter->outputs[i] = inputs[i];
    }
    iter = iter->next;
    while (iter != ann->output_layer) {
        layer_compute_outputs(iter);
        iter = iter->next;
    }
    layer_compute_outputs(iter);
    /* 2 MARKS */
}

/* Trains the ann with single backprop update. */
void ann_train(ann_t const *ann, double const *inputs, double const *targets, double l_rate) {
    /* Sanity checks. */
    assert(ann != NULL);
    assert(inputs != NULL);
    assert(targets != NULL);
    assert(l_rate > 0);

    /* Run forward pass. */
    ann_predict(ann, inputs);

    /**** PART 2 - QUESTION 4 ****/
    int j;
    layer_t *iter = ann->output_layer;
    for (j = 0; j < iter->num_outputs; j++) {
        iter->deltas[j] = sigmoidprime(iter->outputs[j]) * (targets[j] - iter->outputs[j]);
    }
    layer_update(iter, l_rate);
    iter = iter->prev;
    while (iter != ann->input_layer) {
        layer_compute_deltas(iter);
        layer_update(iter, l_rate);
        iter = iter->prev;
    }
    /*iter = iter->next;
    while (iter != ann->output_layer) {
        layer_update(iter, l_rate);
        iter = iter->next;
    }
    layer_update(ann->output_layer, l_rate);*/
    /* 3 MARKS */
}
