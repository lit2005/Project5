#include <iostream>  
using namespace std;

template <typename T>
class Matrix {
private:
    T** data;
    size_t rows;
    size_t cols;

public:
    
    Matrix(size_t r, size_t c) : rows(r), cols(c) {
        data = new T * [rows];
        for (size_t i = 0; i < rows; ++i) {
            data[i] = new T[cols];
        }
    }

    
    ~Matrix() {
        for (size_t i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    
    void fill() {
        cout << "Введите элементы матрицы " << rows << "x" << cols << ":\n";
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                cin >> data[i][j];
            }
        }
    }

   
    void fillFixed() {
        T value = 1; 
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                data[i][j] = value++;
            }
        }
    }

   
    void display() const {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                cout << data[i][j] << ' ';
            }
            cout << '\n';
        }
    }

   
    Matrix operator+(const Matrix& other) {
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("Размеры матриц должны совпадать для сложения");
        }
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

 
    Matrix operator-(const Matrix& other) {
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("Размеры матриц должны совпадать для вычитания");
        }
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    
    Matrix operator*(const Matrix& other) {
        if (cols != other.rows) {
            throw invalid_argument("Количество столбцов первой матрицы должно совпадать с количеством строк второй");
        }
        Matrix result(rows, other.cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < other.cols; ++j) {
                result.data[i][j] = 0;
                for (size_t k = 0; k < cols; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    
    Matrix operator/(T scalar) {
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] / scalar;
            }
        }
        return result;
    }

   
    T maxElement() const {
        T max = data[0][0];
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                if (data[i][j] > max) {
                    max = data[i][j];
                }
            }
        }
        return max;
    }

    
    T minElement() const {
        T min = data[0][0];
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                if (data[i][j] < min) {
                    min = data[i][j];
                }
            }
        }
        return min;
    }
};


class A {
public:
    int value;

    A() : value(0) {}
    A(int v) : value(v) {}
 
    A operator+(const A& other) const {
        return A(this->value + other.value);
    }

    A operator-(const A& other) const {
        return A(this->value - other.value);
    }

    A operator*(const A& other) const {
        return A(this->value * other.value);
    }

    A operator/(const A& other) const {
        return A(this->value / other.value);
    }

    friend ostream& operator<<(ostream& os, const A& obj) {
        os << obj.value;
        return os;
    }
};

int main() {
     
    Matrix<A> mat1(2, 2);
    mat1.fillFixed(); 
    cout << "Matrix 1:\n";
    mat1.display();

    Matrix<A> mat2(2, 2);
    mat2.fillFixed();
    cout << "Matrix 2:\n";
    mat2.display();

    Matrix<A> matSum = mat1 + mat2;
    cout << "Sum of Matrices:\n";
    matSum.display();

    Matrix<A> matDiff = mat1 - mat2;
    cout << "Difference of Matrices:\n";
    matDiff.display();

    Matrix<A> matProd = mat1 * mat2;
    cout << "Product of Matrices:\n";
    matProd.display();

    cout << "Max element in Matrix 1: " << mat1.maxElement() << '\n';
    cout << "Min element in Matrix 1: " << mat1.minElement() << '\n';

    return 0;
}