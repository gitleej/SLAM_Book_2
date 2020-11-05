#include <cmath>
#include <iostream>

using namespace std;

#include <Eigen/Core>
#include <Eigen/Geometry>

using namespace Eigen;

int main(int argc, char **argv) {
    // Eigen/Geometry模塊提供了各種旋轉和平移的表示
    // 3D旋轉矩陣直接用Matrix3d或Matrix3f
    Matrix3d rotation_matrix = Matrix3d::Identity();
    // 旋轉向量用AngleAxis，底層不直接是Matrix，但是運算時可以直接當成矩陣（因爲有進行運算符重載）
    AngleAxisd rotation_vector(M_PI / 4, Vector3d(0, 0, 1)); // 沿Z軸旋轉45°
    cout.precision(3);
    // 可以直接用matrix()轉換成矩陣，也可以直接賦值
    cout << "rotation matrix = \n" << rotation_vector.matrix() << endl;
    rotation_matrix = rotation_vector.toRotationMatrix();

    // 用AngleAxis可以進行坐標變換
    Vector3d v(1, 0, 0);
    Vector3d v_rotated = rotation_vector * v;
    cout << "(1, 0, 0) after rotation (by angle axis) = "
         << v_rotated.transpose()
         << endl;

    // 或者用旋轉矩陣
    v_rotated = rotation_matrix * v;
    cout << "(1, 0, 0) after rotation (by matrix) = " << v_rotated.transpose()
         << endl;

    // 歐拉角：可以將旋轉矩陣直接轉換成歐拉角
    // ZYX順序，即roll-pitch-yaw順序
    Vector3d euler_angles = rotation_matrix.eulerAngles(2, 1, 0);
    cout << "yaw pitch rool = " << euler_angles.transpose() << endl;

    // 歐式變換矩陣使用Eigen::Isometry
    Isometry3d T = Isometry3d::Identity();  // 雖然稱爲3D，實質上是4*4矩陣
    T.rotate(rotation_vector);              // 按照rotation_vector進行旋轉
    T.pretranslate(Vector3d(1, 3, 4));  // 把向量平移設置成(1, 3, 4)
    cout << "Transform matrix = \n" << T.matrix() << endl;

    // 釆用變換矩陣進行坐標變換
    Vector3d v_transformed = T * v;     // 相當於R×v+t
    cout << "v transformed = " << v_transformed.transpose() << endl;

    // 仿射變換和射影變換，使用Eigen::Affine3d和Eigen::Projective3d即可

    // 四元數
    // 可以直接把AngleAxis賦值給四元數，反之亦然
    Quaterniond q = Quaterniond(rotation_vector);
    cout << "quaternion from ratation vector = " << q.coeffs().transpose()
         << endl;   // coeffs()的順序爲(x, y, z, w), w爲實部
    // 也可以把旋轉矩陣賦值給它
    q = Quaterniond(rotation_matrix);
    cout << "quaternion from rotation matrix = " << q.coeffs().transpose()
         << endl;
    // 使用四元數旋轉一個向量
    v_rotated = q * v;      // 數學上爲qpq^(-1)
    cout << "(1, 0, 0) after rotation by quaternion = " << v_rotated.transpose()
         << endl;
    // 用常規向量乘法表示，計算過程如下
    cout << "should be equal to "
         << (q * Quaterniond(0, 1, 0, 0) * q.inverse()).coeffs().transpose()
         << endl;

    return 0;
}
