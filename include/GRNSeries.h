//
// Created by patrick on 07/12/23.
//

#ifndef ES_GRNSERIES_H
#define ES_GRNSERIES_H
#include <string>

using namespace std;

class GRNSeries {
private:
    double **vectors;
    int numTimeSteps;
    int numColumns;
    bool matrixInitialized;
    double *maxValues;
    double *minValues;
    double *initialValues;
public:
    GRNSeries();
    GRNSeries(int numTimeSteps, int numVariables, double *vector, double* times, int granularity);
    GRNSeries(string filepath);
    GRNSeries(GRNSeries &grnSeries, int start, int end, bool copyMaxValues = false);
    ~GRNSeries();
    void loadFromFile(string filename);
    void initializeMatrix(string filepath);
    void loadMaxValuesFrom(GRNSeries &grnSeries);

    double **getVectors() const;

    void setVectors(double **vectors);

    int getNumTimeSteps() const;

    int getNumColumns() const;

    int getNumVariables() const;

    double getStartTime() const;

    double getEndTime() const;

    double* getInitialValues() const;

    bool isMatrixInitialized() const;

    void setMatrixInitialized(bool matrixInitialized);

    void initializeInitialValues();

    double *getMaxValues() const;
    double *getMinValues() const;

    void loadMinMaxValues();

    string toString();

};


#endif //ES_GRNSERIES_H
