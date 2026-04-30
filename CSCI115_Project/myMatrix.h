#ifndef MY_MATRIX
#define MY_MATRIX
#include<iostream>
#include<stdexcept>
#include<iomanip>
class myMatrix {
public:
    myMatrix(int r = 0, int c = 0) {
        rows = r;
        cols = c;

        if (rows > 0 && cols > 0) {
            data = new double[rows * cols];
            for (int i = 0; i < rows * cols; i++) {
                data[i] = 0;
            }
        } else {
            data = nullptr;
        }
    }
    myMatrix(const myMatrix& other) {
        rows = other.rows;
        cols = other.cols;

        if (rows > 0 && cols > 0) {
            data = new double[rows * cols];
            for (int i = 0; i < rows * cols; i++) {
                data[i] = other.data[i];
            }
        } else {
            data = nullptr;
        }
    }
    myMatrix& operator=(const myMatrix& other) {
        if (this != &other) {
            delete [] data;
            rows = other.rows;
            cols = other.cols;
            if(rows > 0 && cols > 0) {
                data = new double[rows * cols];
                for (int i = 0; i < rows * cols; i++) {
                    data[i] = other.data[i];
                }
            } else {
                data = nullptr;
            }
        }
        return *this;
    }
    ~myMatrix(){delete[] data;}
    int getRows()const {return rows;}
    int getCols() const {return cols;}
    int getIndex(int i, int j) const {
        if(i < 0 || i >= rows || j < 0 || j >= cols) {
            throw std::out_of_range("Matrix Index Out of Range");
        }
        return i * cols + j;
    }
    double get(int i, int j) const {
        return data[getIndex(i, j)];
    }
    void set(int i, int j, double value) {
        data[getIndex(i,j)] = value;
    }
    myMatrix multiply(const myMatrix& other) const{
        if (cols != other.getRows()) {
            throw std::invalid_argument("Matrix dimensions don't match for multipliation");
        }
        
        myMatrix result(rows, other.getCols());
        for (int r = 0; r < rows; r++) {
            for (int Oc = 0; Oc < other.getCols(); Oc++) {
                double sum = 0.0;
                for (int c = 0; c < cols; c++) {
                    sum += get(r,c) * other.get(c,Oc);
                }
                result.set(r, Oc, sum);
            }
        }
        return result;
    }
    void display() const{
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
               double val = get(i, j);

                if (val == __DBL_MAX__) {
                    std::cout << std::setw(6) << "INF";
                } else {
                    std::cout << std::setw(6) << val;
                }
            }
            std::cout << std::endl;
        }
    }
private:
    int rows;
    int cols;
    double* data;
};

#endif