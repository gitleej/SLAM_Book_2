#include <iostream>
using namespace std;

#include <ctime>
// Eigen核心
#include <Eigen/Core>
// 稠密矩陣的代數運算（逆、特徵值）
#include <Eigen/Dense>
using namespace Eigen;

#define MATRIX_SIZE 50

/**
 * @brief 本程序演示Eigen基本類型的使用
 */

int main(int argc, char **argv) {
    // Eigen中所有向量和矩陣都是Eigen::Matrix，是一個模板類，前三個參數爲數據類型、行、列
    // 聲明一個2*3的float矩陣
    Matrix<float, 2, 3> matrix_23;

    // Eigen通過typedef提供了許多內置類型，但底層仍然爲Eigen::Matrix。
    // 如Vector3D實質上是Eigen::Matrix<double, 3, 1>，即三維向量
    Vector3d v_3d;
    // 和上面等價
    Matrix<float, 3, 1> vd_3d;

    // Matrix3D實質上是Eigen::Matrix<double, 3, 3>
    Matrix3d matrix_33 = Matrix3d::Zero();  // 初始化爲0
    // 如果不確定矩陣大小，可使用動態大小的矩陣
    Matrix<double, Dynamic, Dynamic> matrix_dynamic;
    // 動態大小矩陣
    MatrixXd matrix_x;

    // 下面是對Eigen進行操作
    // 輸入數據初始化
    matrix_23 << 1, 2, 3, 4, 5, 6;
    // 輸出
    cout << "matrix 2x3 from 1 to 6:\n" << matrix_23 << endl;

    // 使用()訪問矩陣中的元素
    cout << "print matrix 2x3:" << endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << matrix_23(i, j) << "\t" ;
        }
        cout << endl;
    }

    // 矩陣和向量相乘
    v_3d << 3, 2, 1;
    vd_3d << 4, 5, 6;
    // 在Eigen中不能混合兩種不同數據類型進行相關操作
    // 在進行操作時，應進行顯示轉換
    Matrix<double, 2, 1> result = matrix_23.cast<double>() * v_3d;
    cout << "[1, 2, 3; 4, 5, 6]*[3, 2, 1] = " << result.transpose() << endl;

    Matrix<float, Dynamic, Dynamic> result2 = matrix_23 * vd_3d;
    cout << "[1, 2, 3; 4, 5, 6]*[4, 5, 6] = " << result2.transpose() << endl;
    // Matrix<float, 2, 3> result3 = matrix_23 * vd_3d;

    // 一些矩陣運算
    // 四則運算：+-*/
    matrix_33  = Matrix3d::Random();        // 隨機矩陣
    cout << "Random Matrix: \n" << matrix_33 << endl;
    cout << "Transpose: \n" << matrix_33.transpose() << endl;   // 轉置
    cout << "sum: \n" << matrix_33.sum() << endl;               // 各元素和
    cout << "trace: \n" << matrix_33.trace() << endl;           // 跡
    cout << "times 10: \n" << matrix_33 * 10 << endl;           // 數乘
    cout << "inverse: \n" << matrix_33.inverse() << endl;       // 逆
    cout << "det: \n" << matrix_33.determinant() << endl;       // 行列式

    // 特徵值
    // 實對稱矩陣可以保證對角化成功
    SelfAdjointEigenSolver<Matrix3d> eigen_solver(matrix_33.transpose() * matrix_33);
    cout << "Eigen values = \n" << eigen_solver.eigenvalues() << endl;
    cout << "Eigen vectors = \n" << eigen_solver.eigenvectors() << endl;

    // 解方程
    // 求解 matrix_NN * x = v_Nd 方程
    // N的大小在前面宏定義中，隨機生成
    // 直接求逆是最直接的解法，但運算量大
    Matrix<double, MATRIX_SIZE, MATRIX_SIZE> matrix_NN = MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE);
    matrix_NN = matrix_NN * matrix_NN.transpose();      // 保證半正定
    Matrix<double, MATRIX_SIZE, 1> v_Nd = MatrixXd::Random(MATRIX_SIZE, 1);

    clock_t time_start = clock();
    // 直接求逆
    Matrix<double, MATRIX_SIZE, 1> x = matrix_NN.inverse() * v_Nd;
    cout << "time of normal inverse is " << (clock() - time_start) * 1000 / (double) CLOCKS_PER_SEC << " ms." << endl;
    cout << "x = " << x.transpose() << endl;

    // 採用矩陣分解來求解，例如QR分解
    time_start = clock();
    x = matrix_NN.colPivHouseholderQr().solve(v_Nd);
    cout << "time of normal inverse is " << (clock() - time_start) * 1000 / (double) CLOCKS_PER_SEC << " ms." << endl;
    cout << "x = " << x.transpose() << endl;

    // 對於正定矩陣， 還可以用cholesky分解來解方程
    time_start = clock();
    x = matrix_NN.ldlt().solve(v_Nd);
    cout << "time of normal inverse is " << (clock() - time_start) * 1000 / (double) CLOCKS_PER_SEC << " ms." << endl;
    cout << "x = " << x.transpose() << endl;
    
    return 0;
}
