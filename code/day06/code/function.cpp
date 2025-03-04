#include <iostream>
#include <float.h>

struct Matrix
{
    size_t rows;
    size_t cols;
    float * pData;
};

float matrix_max(struct Matrix mat)
{
    float max = FLT_MIN;
    //find max value of mat
    for(size_t r = 0; r < mat.rows; r++)
        for (size_t c = 0; c < mat.cols; c++)
        {
            float val = mat.pData[ r * mat.cols + c];
            max = ( max > val ? max : val);
        }
    return max;
}

Matrix * create_matrix(size_t rows, size_t cols)
{
    Matrix * p = new Matrix{rows, cols};
    p->pData = new float[p->rows * p->cols]{1.f, 2.f, 3.f};
    //you should check if the memory is allocated successfully
    return p;
}

bool matrix_add(const Matrix & matA, const Matrix & matB, Matrix & matC)
{
    if (matA.rows != matB.rows || matA.cols != matB.cols || matA.rows != matC.rows || matA.cols != matC.cols)
        return false;

    for(size_t r = 0; r < matA.rows; r++)
        for (size_t c = 0; c < matA.cols; c++)
        {
            matC.pData[ r * matC.cols + c] = matA.pData[ r * matA.cols + c] + matB.pData[ r * matB.cols + c];
        }
    return true;
}

int main()
{
    using namespace std;

    Matrix matA = {3,4};
    matA.pData = new float[matA.rows * matA.cols]{1.f, 2.f, 3.f};

    Matrix matB = {4,8};
    matB.pData = new float[matB.rows * matB.cols]{10.f, 20.f, 30.f};

    Matrix matC = {4, 2};
    matC.pData = new float[matC.rows * matC.cols]{100.f, 200.f, 300.f};

    // some operations on the matrices

    float maxa = matrix_max(matA);
    float maxb = matrix_max(matB);
    float maxc = matrix_max(matC);

    cout << "max(matA) = " << maxa << endl;
    cout << "max(matB) = " << maxb << endl;
    cout << "max(matC) = " << maxc << endl;


    delete [] matA.pData;
    delete [] matB.pData;
    delete [] matC.pData;

    Matrix mat1 = {4, 4};
    mat1.pData = new float[mat1.rows * mat1.cols]{1.f, 2.f, 3.f, 4.f};

    Matrix mat2 = {4, 4};
    mat2.pData = new float[mat2.rows * mat2.cols]{10.f, 20.f, 30.f, 40.f};

    Matrix mat3 = {4, 4};
    mat3.pData = new float[mat3.rows * mat3.cols]{}; //initialize to 0

    if (matrix_add(mat1, mat2, mat3))
    {
        cout << "mat1 + mat2 = " << endl;
        for(size_t r = 0; r < mat3.rows; r++)
        {
            for (size_t c = 0; c < mat3.cols; c++)
            {
                cout << mat3.pData[ r * mat3.cols + c] << " ";
            }
            cout << endl;
        }
    }
    else
    {
        cout << "mat1 and mat2 have different dimensions" << endl;
    }

    return 0;
}
