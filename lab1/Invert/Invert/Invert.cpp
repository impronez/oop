#include <iostream>
#include <fstream>
#include <array>
#include <string>

const int SIZE_OF_MATRIX = 3;
const int LENGTH_OF_STRING = 255;

typedef std::array<std::array<double, SIZE_OF_MATRIX>, SIZE_OF_MATRIX> Matrix;

double GetDouble(const char* string, bool& isCorrectData)
{
    char* ptrEnd;
    double num = std::strtod(string, &ptrEnd);
    if (*ptrEnd != '\0' || ptrEnd == string)
    {
        isCorrectData = false;
    }
    return num;
}

Matrix ReadMatrix(std::istream& input, bool& isCorrectData)
{
    Matrix matrix;
    for (int i = 0; i < SIZE_OF_MATRIX; i++)
    {
        for (int j = 0; j < SIZE_OF_MATRIX; j++)
        {
            char elem[LENGTH_OF_STRING];
            input >> elem;
            matrix[i][j] = GetDouble(elem, isCorrectData);
        }
    }
    return matrix;
}

double GetDeterminant(Matrix& matrix)
{
    double det = 0;
    for (int i = 0; i < SIZE_OF_MATRIX; i++)
    {
        det = det + (matrix[0][i] *
            (matrix[1][(i + 1) % SIZE_OF_MATRIX] * matrix[2][(i + 2) % SIZE_OF_MATRIX] -
            matrix[1][(i + 2) % SIZE_OF_MATRIX] * matrix[2][(i + 1) % SIZE_OF_MATRIX]));
    }
    return det;
}

Matrix GetAdjointMatrix(Matrix& matrix)
{
    Matrix adjointMatrix;
    for (int i = 0; i < SIZE_OF_MATRIX; i++)
    {
        for (int j = 0; j < SIZE_OF_MATRIX; j++)
        {
            // Получение минора и занесение в сопряженную матрицу
            adjointMatrix[i][j] = 
                ((matrix[(i + 1) % 3][(j + 1) % 3] * matrix[(i + 2) % 3][(j + 2) % 3]) -
                (matrix[(i + 1) % 3][(j + 2) % 3] * matrix[(i + 2) % 3][(j + 1) % 3]));
        }
    }
    return adjointMatrix;
}

void GetInverseMatrix(Matrix& matrix)
{
    double det = GetDeterminant(matrix);
    if (det == 0)
    {
        std::cout << "The determinant is 0. There is no inverse matrix.\n";
        return;
    }

    Matrix adjointMatrix = GetAdjointMatrix(matrix);
    for (int i = 0; i < SIZE_OF_MATRIX; i++)
    {
        for (int j = 0; j < SIZE_OF_MATRIX; j++)
        {
            std::cout << (std::floor((adjointMatrix[i][j] / det) * 1000) / 1000) << '\t';
        }
        std::cout << std::endl;
    }
    return;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {

        std::cout << "Invalid argument count.\nUsage: invert.exe <matrixFile>.\n";
        return 1;
    }

    std::ifstream inputFile;
    inputFile.open(argv[1]);
    if (!inputFile.is_open())
    {
        std::cout << "Failed to open '" << argv[1] << "' for reading.\n";
        return 1;
    }

    bool isCorrectData = true;
    Matrix matrix = ReadMatrix(inputFile, isCorrectData);
    if (!isCorrectData)
    {
        std::cout << "Incorrect data in '" << argv[1] << "'. Matrix must be the size of 3 * 3.\n";
        return 1;
    }

    GetInverseMatrix(matrix);
}