//
// Created by patrick on 07/12/23.
//
#include "GRNSeries.h"
#include <fstream>
#include <vector>
#include <iostream>


GRNSeries::GRNSeries() {

}


GRNSeries::GRNSeries(string filepath) {
    loadFromFile(filepath);
    loadMaxValues();
    initializeInitialValues();
}

GRNSeries::GRNSeries(int numTimeSteps, int numColumns, double *vector, double *times, int granularity) {
    this->numTimeSteps = numTimeSteps;
    this->numColumns = numColumns;

    this->vectors = new double*[numColumns];
    for(int i=0; i<numColumns; i++){
        this->vectors[i] = new double[numTimeSteps];
    }
    matrixInitialized = true;

    for (int i = 0; i < numColumns; i++)
    {
        for (int j = 0; j <= numTimeSteps; j++)
        {
            int index = granularity*j* numColumns + i;
            std::cout << vector[index] << " ";
            this->vectors[i][j] = vector[index];
        }
        cout << endl;
    }

    loadMaxValues();
    initializeInitialValues();
}


GRNSeries::GRNSeries(GRNSeries &grnSeries, int start, int end, bool copyMaxValues) {
    int timeSteps = end - start + 1;
    this->numTimeSteps = timeSteps;
    this->numColumns = grnSeries.getNumColumns();

    this->vectors = new double*[grnSeries.getNumColumns()];
    for(int i=0; i<grnSeries.getNumColumns(); i++){
        this->vectors[i] = new double[timeSteps];
    }
    matrixInitialized = true;

    for(int i=0; i<grnSeries.getNumColumns(); i++){
        for(int j=0; j<timeSteps; j++){
            this->vectors[i][j] = grnSeries.getVectors()[i][j+start];
        }
    }

    if(copyMaxValues){
        this->maxValues = new double[grnSeries.getNumVariables()];
        for(int i=0; i<grnSeries.getNumVariables(); i++){
            this->maxValues[i] = grnSeries.getMaxValues()[i];
        }
    }
    else{
        loadMaxValues();
    }
    initializeInitialValues();
}

vector<double> extractDoubleRow(string text)
{
    vector<double> result;
    string part;

    for (int i = 0; i < text.size(); i++)
    {
        if (text[i] == ' ' || text[i] == '\n' || text[i] == '\r' || text[i] == '\t')
        {
            if(part != "") {

                result.push_back(stod(part));
                part = "";
            }

        }
        else
        {
            part += (text[i]);
        }
    }

    if(part != ""){
        result.push_back(stod(part));
    }
    return result;
}

void GRNSeries::initializeMatrix(string filepath){
    int rowCount = 0;
    int columnCount = 0;
    ifstream input(filepath);
    string textAux;

    if(!input.eof()) {
        getline(input, textAux);
        vector<double> lineElements = extractDoubleRow(textAux);
        columnCount = (int) lineElements.size();
        rowCount++;
    }

    for(int i=1; !input.eof(); i++){
        getline(input, textAux);
        if(textAux != ""){
            rowCount++;
        }

    }

    input.close();
    this->numTimeSteps = rowCount;
    this->numColumns = columnCount;

    this->vectors = new double*[this->numColumns];
    for(int i=0; i<this->numColumns; i++){
        this->vectors[i] = new double[this->numTimeSteps];
    }
    matrixInitialized = true;

}

void GRNSeries::loadFromFile(string filepath)//(string path, int numVectors, double *vectors[])
{
    initializeMatrix(filepath);
    ifstream input(filepath);
    string textAux;
    vector<double> lineElements;

    //todo: ver se preciso tratar caso de linha vazia
    for(int i=0; !input.eof(); i++){
        getline(input, textAux);
        if(textAux != ""){
            lineElements = extractDoubleRow(textAux);
            for(int j=0; j<this->numColumns; j++){
                this->vectors[j][i] = lineElements[j];
            }
        }
    }

    input.close();

}

double getMaxValue(double *values, int start, int end)
{
    double maxValue = 0;
    for (int i = start; i <= end; i++)
    {
        if (values[i] > maxValue)
        {
            maxValue = values[i];
        }
    }

    return maxValue;
}

void GRNSeries::loadMaxValues()
{
    int start = 0;
    int end = this->numTimeSteps - 1;
    this->maxValues = new double[this->numColumns];

    for (int i = 1; i < this->numColumns; i++)
    {
        this->maxValues[i - 1] = getMaxValue(this->vectors[i], start, end);
    }
}

double **GRNSeries::getVectors() const {
    return vectors;
}

void GRNSeries::setVectors(double **vectors) {
    GRNSeries::vectors = vectors;
}

int GRNSeries::getNumTimeSteps() const {
    return numTimeSteps;
}


int GRNSeries::getNumColumns() const {
    return numColumns;
}


bool GRNSeries::isMatrixInitialized() const {
    return matrixInitialized;
}

void GRNSeries::setMatrixInitialized(bool matrixInitialized) {
    GRNSeries::matrixInitialized = matrixInitialized;
}



GRNSeries::~GRNSeries() {
    if(this->matrixInitialized){
        for(int i=0; i<this->numColumns; i++){
            delete[] this->vectors[i];
        }
        delete[] this->vectors;
        delete[] this->maxValues;
        delete[] this->initialValues;
    }

}


double *GRNSeries::getMaxValues() const {
    return maxValues;
}

int GRNSeries::getNumVariables() const {
    return this->numColumns - 1;
}

double GRNSeries::getStartTime() const {
    return vectors[0][0];
}

double GRNSeries::getEndTime() const {
    return vectors[0][this->numTimeSteps - 1];
}

void GRNSeries::initializeInitialValues() {
    this->initialValues = new double[this->getNumVariables()];

    for (int i = 0; i < this->getNumVariables(); i++)
    {
        this->initialValues[i] = this->vectors[i + 1][0];
    }
}

double *GRNSeries::getInitialValues() const {
    return this->initialValues;
}

void GRNSeries::loadMaxValuesFrom(GRNSeries &grnSeries) {
    for(int i=0; i<grnSeries.getNumVariables(); i++){
        this->maxValues[i] = grnSeries.getMaxValues()[i];
    }
}




