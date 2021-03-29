#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int** create_matrix(int size){
    int** matrix = new int* [size];
    for (int i = 0; i < size; i++)
    {
        matrix[i] = new int[size];
    }
    return matrix;
}

int** create_matrix_input(int &raw, int &col){
    do
    {
        cin >> raw >> col;
    } while (raw <= 0 && col <= 0);
    int** M1 = new int* [raw];
    for (int i = 0; i < raw; i++)
        M1[i] = new int[col];
    return M1;
}

void fill_matrix(int** matrix, int raw, int col){
    for (int i = 0; i < raw; i++)
        for (int j = 0; j < col; j++)
            cin >> matrix[i][j];
}

void fill_matrix_random(int** matrix, int raw, int col){
    for (int i = 0; i < raw; i++)
        for (int j = 0; j < col; j++)
            matrix[i][j] = rand() % 10;
}

void output_matrix(int** matrix, int raw, int col){
    for (int i = 0; i < raw; i++)
    {
        for (int j = 0; j < col; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
}

int** reducing_matrix(int** matrix, int raw, int col, int size){

    int** new_matrix = new int* [size];
    for (int i = 0; i < size; i++)
    {
        new_matrix[i] = new int[size];
        for (int j = 0; j < size; j++)
            new_matrix[i][j] = 0;
    }
    for (int i = 0; i < raw; i++) {
        for (int j = 0; j < col; j++)
            new_matrix[i][j] = matrix[i][j];

    }
    return new_matrix;
}

int** dividing_matrix_submatrix(int** matrix, int size, int koef_i, int koef_j){
    int** submatrix = new int* [size / 2];
    for (int i = 0; i < size / 2; i++)
    {
        submatrix[i] = new int[size / 2];
        for (int j = 0; j < size / 2; j++)
            submatrix[i][j] = matrix[i + koef_i][j + koef_j];
    }

    return submatrix;
}

void delete_matrix(int** matrix,int raw){
    for (int i = 0; i < raw; i++)
        delete[] matrix[i];
}

int main()
{
    setlocale(LC_ALL, "RUSSION");
    srand(time(NULL));
    int raw_matrix1, col_matrix1, raw_matrix2, col_matrix2, choice, size = 2;
    system("chcp 1251");
    cout << "Вас приветствует программа" << endl <<
         "быстрого перемножения матриц методом Штрассена\n\n";

    ///////////////////////////////////////////////////////////////////////////////
    ////////////////////Ввод размеров матрицы пользователем////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    cout << "Введите размеры первой матрицы\n";
    int** matrix1 = create_matrix_input(raw_matrix1, col_matrix1);

    cout << "Введите размеры второй матрицы\n";
    int** matrix2 = create_matrix_input(raw_matrix2, col_matrix2);

    ///////////////////////////////////////////////////////////////////////////////
    ////////////////Выбор способа заполнения и заполнение матриц///////////////////
    ///////////////////////////////////////////////////////////////////////////////

    do
    {
        cout << "Выберите способ заполнения матриц\n" <<
             "1 - Вручную \n2 - Случайным образом\n";
        cin >> choice;
    } while (choice < 1 || choice > 2);
    switch (choice)
    {
        case 1:
            fill_matrix(matrix1, raw_matrix1, col_matrix1);
            cout << "\nМатрица 1\n\n";
            output_matrix(matrix1, raw_matrix1, col_matrix1);

            fill_matrix(matrix2, raw_matrix2, col_matrix2);
            cout << "\nМатрица 2\n\n";
            output_matrix(matrix2, raw_matrix2, col_matrix2);

            break;
        case 2:
            fill_matrix_random(matrix1, raw_matrix1, col_matrix1);
            cout << "\nМатрица 1\n\n";
            output_matrix(matrix1, raw_matrix1, col_matrix2);

            fill_matrix_random(matrix2, raw_matrix2, col_matrix2);
            cout << "\nМатрица 2\n\n";
            output_matrix(matrix2, raw_matrix2, col_matrix2);
            break;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /////////////////Приведение матриц к требуемому размеру////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    while (size < raw_matrix1 || size < raw_matrix2 || size < col_matrix1 || size < col_matrix2)
        size *= 2;

    int** reduc_matrix1 = reducing_matrix(matrix1, raw_matrix1, col_matrix1, size);
    int** reduc_matrix2 = reducing_matrix(matrix2, raw_matrix2, col_matrix2, size);

    cout << "Приведенные матрицы\n";

    cout << "\nМатрица 1\n\n";
    output_matrix(reduc_matrix1, size, size);

    cout << "\nМатрица 2\n\n";
    output_matrix(reduc_matrix2, size, size);

    ///////////////////////////////////////////////////////////////////////////////
    ///////////////Разбиение матриц на подматрицы и их заполнение//////////////////
    ///////////////////////////////////////////////////////////////////////////////

    int** submatrix1 = dividing_matrix_submatrix(matrix1, size, 0, 0);
    int** submatrix2 = dividing_matrix_submatrix(matrix1, size, 0, size / 2);
    int** submatrix3 = dividing_matrix_submatrix(matrix1, size, size / 2, 0);
    int** submatrix4 = dividing_matrix_submatrix(matrix1, size, size / 2, size / 2);
    int** submatrix5 = dividing_matrix_submatrix(matrix2, size, 0, 0);
    int** submatrix6 = dividing_matrix_submatrix(matrix2, size, 0, size / 2);
    int** submatrix7 = dividing_matrix_submatrix(matrix2, size, size / 2, 0);
    int** submatrix8 = dividing_matrix_submatrix(matrix2, size, size / 2, size / 2);

    ///////////////////////////////////////////////////////////////////////////////
    ////////////////////////Создание промежуточных матриц//////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    int** midmatrix1 = create_matrix(size / 2);
    int** midmatrix2 = create_matrix(size / 2);
    int** midmatrix3 = create_matrix(size / 2);
    int** midmatrix4 = create_matrix(size / 2);
    int** midmatrix5 = create_matrix(size / 2);
    int** midmatrix6 = create_matrix(size / 2);
    int** midmatrix7 = create_matrix(size / 2);


    ///////////////////////////////////////////////////////////////////////////////
    ////////////////////Вычисление значений промежуточных матриц///////////////////
    ///////////////////////////////////////////////////////////////////////////////

    for (int i = 0; i < size / 2; i++)
    {
        for (int j = 0; j < size / 2; j++)
        {
            midmatrix1[i][j] = 0;
            midmatrix2[i][j] = 0;
            midmatrix3[i][j] = 0;
            midmatrix4[i][j] = 0;
            midmatrix5[i][j] = 0;
            midmatrix6[i][j] = 0;
            midmatrix7[i][j] = 0;
            for (int z = 0; z < size / 2; z++)
            {
                midmatrix1[i][j] += (submatrix1[i][z] + submatrix4[i][z]) * (submatrix5[z][j] + submatrix8[z][j]);
                midmatrix2[i][j] += (submatrix3[i][z] + submatrix4[i][z]) * submatrix5[z][j];
                midmatrix3[i][j] += submatrix1[i][z] * (submatrix6[z][j] - submatrix8[z][j]);
                midmatrix4[i][j] += submatrix4[i][z] * (submatrix7[z][j] - submatrix5[z][j]);
                midmatrix5[i][j] += (submatrix1[i][z] + submatrix2[i][z]) * submatrix8[z][j];
                midmatrix6[i][j] += (submatrix3[i][z] - submatrix1[i][z]) * (submatrix5[z][j] + submatrix6[z][j]);
                midmatrix7[i][j] += (submatrix2[i][z] - submatrix4[i][z]) * (submatrix7[z][j] + submatrix8[z][j]);
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////Создание вспомогательных матриц/////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    int** supmatrix1 = create_matrix(size / 2);
    int** supmatrix2 = create_matrix(size / 2);
    int** supmatrix3 = create_matrix(size / 2);
    int** supmatrix4 = create_matrix(size / 2);

    ///////////////////////////////////////////////////////////////////////////////
    ////////////Подсчет значений вспомогательных матриц из промежуточных///////////
    ///////////////////////////////////////////////////////////////////////////////

    for (int i = 0; i < size / 2; i++)
    {
        for (int j = 0; j < size / 2; j++)
        {
            supmatrix1[i][j] = midmatrix1[i][j] + midmatrix4[i][j] - midmatrix5[i][j] + midmatrix7[i][j];
            supmatrix2[i][j] = midmatrix3[i][j] + midmatrix5[i][j];
            supmatrix3[i][j] = midmatrix2[i][j] + midmatrix4[i][j];
            supmatrix4[i][j] = midmatrix1[i][j] - midmatrix2[i][j] + midmatrix3[i][j] + midmatrix6[i][j];
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////Создание результирующей матрицы/////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    int** result_matrix1 = create_matrix(size);


    ///////////////////////////////////////////////////////////////////////////////
    ///////Занесение информации из вспомогательных матриц в результирующую/////////
    ///////////////////////////////////////////////////////////////////////////////

    for (int i = 0; i < size / 2; i++)
    {
        for (int j = 0; j < size / 2; j++)
        {
            result_matrix1[i][j] = supmatrix1[i][j];
            result_matrix1[i][j + size / 2] = supmatrix2[i][j];
            result_matrix1[i + size / 2][j] = supmatrix3[i][j];
            result_matrix1[i + size / 2][j + size / 2] = supmatrix4[i][j];
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    ////////////////Выравнивание границ результирующей матрицы/////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    int x = 0, f = 100, s = 100;
    for (int i = 0; i < size; i++)
    {
        x = 0;
        for (int j = 0; j < size; j++)
        {
            if (result_matrix1[i][j] != 0)
            {
                x++;
                f = 100;
                s = 100;
            }
        }
        if (x == 0 && i < f)
        {
            f = i;
        }
        if (x == 0 && i < s)
        {
            s = i;
        }
    }




    int** result_matrix2 = new int* [f];
    for (int i = 0; i < f; i++)
    {
        result_matrix2[i] = new int[s];
        for (int j = 0; j < s; j++)
            result_matrix2[i][j] = result_matrix1[i][j];
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////Вывод результирующей матрицы////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    cout << "\nРезультирующая матрица\n\n";
    output_matrix(result_matrix2, f, s);


    system("pause");

    ///////////////////////////////////////////////////////////////////////////////
    /////////////////////Очистка динамической памяти///////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    delete_matrix(matrix1, raw_matrix1);
    delete_matrix(matrix2, raw_matrix2);
    delete_matrix(reduc_matrix1, size);
    delete_matrix(reduc_matrix2, size);
    delete_matrix(result_matrix1, size);
    delete_matrix(result_matrix2, f);
    delete_matrix(submatrix1, size / 2);
    delete_matrix(submatrix2, size / 2);
    delete_matrix(submatrix3, size / 2);
    delete_matrix(submatrix4, size / 2);
    delete_matrix(submatrix5, size / 2);
    delete_matrix(submatrix6, size / 2);
    delete_matrix(submatrix7, size / 2);
    delete_matrix(submatrix8, size / 2);
    delete_matrix(supmatrix1, size / 2);
    delete_matrix(supmatrix2, size / 2);
    delete_matrix(supmatrix3, size / 2);
    delete_matrix(supmatrix4, size / 2);
    delete_matrix(midmatrix1, size / 2);
    delete_matrix(midmatrix2, size / 2);
    delete_matrix(midmatrix3, size / 2);
    delete_matrix(midmatrix4, size / 2);
    delete_matrix(midmatrix5, size / 2);
    delete_matrix(midmatrix6, size / 2);
    delete_matrix(midmatrix7, size / 2);


    delete[] matrix1, matrix2, reduc_matrix1, reduc_matrix2, result_matrix1, result_matrix2;
    delete[] submatrix1, submatrix2, submatrix3, submatrix4, submatrix5, submatrix6, submatrix7, submatrix8, supmatrix1, supmatrix2, supmatrix3, supmatrix4;
    delete[] midmatrix1, midmatrix2, midmatrix3, midmatrix4, midmatrix5, midmatrix6, midmatrix7;


    return 0;
}