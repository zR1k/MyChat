# 设置构建目录
$buildDir = "D:/VS_Code/C++/project/MyChat/Server/GateServer/build"

#清理构建目录
if (Test-Path $buildDir) {
    Remove-Item -Recurse -Force $buildDir
}

# 创建构建目录
New-Item -ItemType Directory -Path $buildDir


# 进入构建目录
Set-Location $buildDir

# 运行 CMake 配置
cmake .. -DCMAKE_TOOLCHAIN_FILE=D:/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release

# 编译项目
cmake --build . --config Debug

Copy-Item -Path "../config.ini" -Destination "./Debug/config.ini" -Force

# 保持窗口打开
Pause
# 进入Debug
Set-Location "./Debug"
# 运行程序
./GateServer.exe