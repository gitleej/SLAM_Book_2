# 聲明要求的cMake的最低版本
cmake_minimum_required( VERSION 2.8 )

# 聲明一個cmake工程
project( HelloSLAM )

# 添加一個可執行程序
# 語法：add_executable( 程序名 源代碼文件)
add_executable( helloSLAM helloSLAM.cpp )

# 添加靜態庫 .a
add_library( hello libHelloSLAM.cpp )

# 添加共享庫 .so
add_library( hello_shared SHARED libHelloSLAM.cpp)

# 添加可執行程序，調用hello庫中的函數
add_executable( useHello useHello.cpp )
# 將庫文件鏈接到可執行程序
target_link_libraries( useHello hello )

