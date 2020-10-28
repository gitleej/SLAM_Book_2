# 聲明要求的cMake的最低版本
cmake_minimum_required( VERSION 2.8 )

# 聲明一個cmake工程
project( HelloSLAM )

# 添加一個可執行程序
# 語法：add_executable( 程序名 源代碼文件)
add_executable( helloSLAM helloSLAM.cpp)
