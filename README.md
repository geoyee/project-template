# project-template

CMake 管理的 C/C++ 项目模板，包含代码风格化、测试、Java 导出、文档导出等示例

## 获取

```
git clone --recursive https://github.com/geoyee/project-template.git
```

## 结构

```
    ├─ 3rdparty                        # 三方库
    ├─ cmake                           # CMake 文件
    ├─ libraryT                        # 模块模板
    │    ├─ include/libraryT           # 头文件
    │    └─ src                        # 源文件
    ├─ sample                          # 示例代码
    ├─ swig                            # SWIG 多语言接口导出
    ├─ test                            # 测试代码
    ├─ .clang-format                   # C/C++ 代码风格文件
    ├─ .cmake-format.py                # CMake 代码风格文件
    ├─ .gitignore                      # git 忽略文件
    ├─ .gitmoudles                     # git 子模块文件
    ├─ CMakeLists.txt                  # 顶层 CMake 文件
    ├─ Doxygen.in                      # 文档生成配置文件
    └─ README.md                       # 说明
```

# 依赖

- 单元测试：[googletest: GoogleTest - Google Testing and Mocking Framework](https://github.com/google/googletest)
- 变量调试：[dbg-macro: A dbg(…) macro for C++](https://github.com/sharkdp/dbg-macro)
- 日志记录：[spdlog: Fast C++ logging library](https://github.com/gabime/spdlog)

# 工具集

- C/C++ 代码格式化：[llvm-project: The LLVM Project is a collection of modular and reusable compiler and toolchain technologies](https://github.com/llvm/llvm-project)
- CMake 代码格式化：[cmake_format: Source code formatter for cmake listfiles](https://github.com/cheshirekow/cmake_format)
- 多语言接口导出：[swig: SWIG is a software development tool that connects programs written in C and C++ with a variety of high-level programming languages](https://github.com/swig/swig)
- 文档导出：[doxygen: Official doxygen git repository](https://github.com/doxygen/doxygen)
