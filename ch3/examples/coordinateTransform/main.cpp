/**
 * @brief 坐标变换举例
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <Eigen/Core>
#include <Eigen/Geometry>

// 命名空间
using namespace std;
using namespace Eigen;

int main(int argc, char **argv) {
    // 定义两个四元数
    Quaterniond q1(0.35, 0.2, 0.3, 0.1);
    Quaterniond q2(-0.5, 0.4, -0.1, 0.2);
    // 四元数使用前进行归一化
    q1.normalize();
    q2.normalize();
    // 定义平移变量
    Vector3d t1(0.3, 0.1, 0.1);
    Vector3d t2(-0.1, 0.5, 0.3);
    // 定义待转换坐标
    Vector3d p1(0.5, 0, 0.2);
    // 进行欧式变换
    Isometry3d T1w(q1);
    Isometry3d T2w(q2);
    T1w.pretranslate(t1);
    T2w.pretranslate(t2);

    // 坐标p1在坐标系2中的坐标为
    Vector3d p2 = T2w * T1w.inverse() * p1;
    cout << endl << p2.transpose() << endl;

    return 0;
}
