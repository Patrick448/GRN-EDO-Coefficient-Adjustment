//
// Created by patrick on 04/01/24.
//

#ifndef ES_GRN5MODEL_H
#define ES_GRN5MODEL_H
#include "dependencies.h"

class GRN5Model {

public:
    static const int TAU_SIZE = 5;
    static const int N_SIZE = 7;
    static const int K_SIZE = 7;
    static const int MODEL_DIMENSION = TAU_SIZE + N_SIZE + K_SIZE;
    static constexpr double MIN_K = 0.1;
    static constexpr double MAX_K = 1;
    static constexpr double MIN_N = 1;
    static constexpr double MAX_N = 25;
    static constexpr double MIN_TAU = 0.1;
    static constexpr double MAX_TAU = 5;
    static int modelFunction(double t, double *y, double *ydot, void *context) {
        appContext *ctx = (appContext *)context;
        double* individual = ctx->individual;
        double* maxValues = ((GRNSeries*)ctx->series)->getMaxValues();
        double *tau = &individual[0];
        double *k = &individual[TAU_SIZE];
        double *n = &individual[TAU_SIZE + K_SIZE];


        ydot[0] = ((1 - (pow((y[4] / maxValues[4]), (int)n[0])) /
                        (pow((y[4] / maxValues[4]), (int)n[0]) + pow(k[0], (int)n[0]))) -
                   (y[0] / maxValues[0])) /
                  tau[0];

        ydot[1] = (((pow((y[0] / maxValues[0]), (int)n[1])) /
                    (pow((y[0] / maxValues[0]), (int)n[1]) + pow(k[1], (int)n[1]))) -
                   (y[1] / maxValues[1])) /
                  tau[1];

        ydot[2] = (((pow((y[1] / maxValues[1]), (int)n[2])) /
                    (pow((y[1] / maxValues[1]), (int)n[2]) + pow(k[2], (int)n[2]))) -
                   (y[2] / maxValues[2])) /
                  tau[2];

        ydot[3] = (((pow((y[2] / maxValues[2]), (int)n[3])) /
                    (pow((y[2] / maxValues[2]), (int)n[3]) + pow(k[3], (int)n[3]))) -
                   (y[3] / maxValues[3])) /
                  tau[3];

        ydot[4] = ((((pow(y[1] / maxValues[1], (int)n[4]) / (pow(y[1] / maxValues[1], (int)n[4]) + pow(k[4], (int)n[4]))) * (
                pow(y[3] / maxValues[3], (int)n[5]) / (pow(y[3] / maxValues[3], (int)n[5]) + pow(k[5], (int)n[5])))) + (
                            (pow(y[3] / maxValues[3], (int)n[5]) / (pow(y[3] / maxValues[3], (int)n[5]) + pow(k[5], (int)n[5]))) * (
                                    pow(y[4] / maxValues[4], (int)n[6]) / (pow(y[4] / maxValues[4], (int)n[6]) + pow(k[6], (int)n[6]))))) - (
                           y[4] / maxValues[4])) / tau[4];

        return 0;
    }

};

#endif //ES_GRN5MODEL_H
