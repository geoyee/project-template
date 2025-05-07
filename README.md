# project-template

![Static Badge](https://img.shields.io/badge/Windows_build-pass-green) ![Static Badge](https://img.shields.io/badge/Linux_build-pass-green)

CMake 管理的 C/C++ 项目模板，包含代码风格化、测试、Java 导出、文档导出等示例

## 获取

```
git clone --recursive https://github.com/geoyee/project-template.git
```

> [!IMPORTANT]
> 如仅拉取了本仓库，可以通过 `git submodule update --init` 更新各个子模块

## 结构

```
    ├─ 3rdparty                        # 三方库
    ├─ cmake                           # CMake 文件
    ├─ libraryT                        # 模块模板
    │    ├─ include/libraryT           # 头文件
    │    └─ src                        # 源文件
    ├─ sample                          # 示例代码
    ├─ swig                            # SWIG 多语言接口导出
    ├─ test                            # 测试代码（包含多语言测试）
    ├─ .clang-format                   # C/C++ 代码风格文件
    ├─ .cmake-format.py                # CMake 代码风格文件
    ├─ .gitignore                      # git 忽略文件
    ├─ .gitmoudles                     # git 子模块文件
    ├─ CMakeLists.txt                  # 顶层 CMake 文件
    ├─ Doxygen.in                      # 文档生成配置文件
    └─ README.md                       # 说明
```

# 依赖

- 单元测试：[googletest](https://github.com/google/googletest)
- 变量调试：[dbg-macro](https://github.com/sharkdp/dbg-macro)
- 日志记录：[spdlog](https://github.com/gabime/spdlog)

> [!NOTE]
> 如不需要这些第三方依赖，可自行删除

# 工具集

- C/C++ 代码格式化：[llvm-project](https://github.com/llvm/llvm-project)
- CMake 代码格式化：[cmake_format](https://github.com/cheshirekow/cmake_format)
- 多语言接口导出：[swig](https://github.com/swig/swig)
- 文档导出：[doxygen](https://github.com/doxygen/doxygen)
- 多语言测试：[Gauge](https://github.com/getgauge/gauge)

> [!TIP]
> 工具集不安装也可以使用该模版，但使用这些工具能够使得该模版更加好用
