# 设置构建目录
$buildDir = "D:/VS_Code/C++/project/MyChat/Server/GateServer/build"

<<<<<<< HEAD
# 清理构建目录
if (Test-Path $buildDir) {
    try {
        Remove-Item -Recurse -Force $buildDir -ErrorAction Stop
    } catch {
        Write-Host "Error: Failed to remove build directory. Make sure no files are in use." -ForegroundColor Red
        exit 1
    }
}

# 创建构建目录
New-Item -ItemType Directory -Path $buildDir | Out-Null
=======
#清理构建目录
if (Test-Path $buildDir) {
    Remove-Item -Recurse -Force $buildDir
}

# 创建构建目录
New-Item -ItemType Directory -Path $buildDir

>>>>>>> e1c4624a03be4442f9c0d3c6ae4b7e48971b6ee4

# 进入构建目录
Set-Location $buildDir

# 运行 CMake 配置
<<<<<<< HEAD
cmake .. -DCMAKE_TOOLCHAIN_FILE=D:/vcpkg/scripts/buildsystems/vcpkg.cmake `
         -DCMAKE_BUILD_TYPE=Debug `
         -DBUILD_SHARED_LIBS=OFF `
         -DVCPKG_TARGET_TRIPLET=x64-windows-static

if ($LASTEXITCODE -ne 0) {
    Write-Host "Error: CMake configuration failed!" -ForegroundColor Red
    exit 1
}

# 编译项目
cmake --build . --config Debug
if ($LASTEXITCODE -ne 0) {
    Write-Host "Error: Build failed!" -ForegroundColor Red
    exit 1
}

# 确保 Debug 目录存在
if (-Not (Test-Path "./Debug")) {
    New-Item -ItemType Directory -Path "./Debug" | Out-Null
}

# 复制配置文件
Copy-Item -Path "../config.ini" -Destination "./Debug/config.ini" -Force

# 进入 Debug 目录
Set-Location "./Debug"

# 运行程序
if (Test-Path "./GateServer.exe") {
    Write-Host "Running GateServer.exe..."
    ./GateServer.exe
} else {
    Write-Host "Error: GateServer.exe not found!" -ForegroundColor Red
    exit 1
}
=======
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
>>>>>>> e1c4624a03be4442f9c0d3c6ae4b7e48971b6ee4
