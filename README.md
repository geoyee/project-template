# project-template

自用的 C/C++项目的 CMake 模板，包含代码风格化、测试、Java 导出、文档导出等示例

## 结构

```
    ├─ 3rdparty                        # 三方库
    ├─ cmake                           # CMake文件
    ├─ libraryT                        # 模块模板
    │    ├─ include/libraryT           # 头文件
    │    └─ src                        # 源文件
    ├─ sample                          # 示例代码
    ├─ swig                            # SWIG多语言接口导出
    ├─ test                            # 测试代码（包含多语言测试）
    ├─ .clang-format                   # C/C++代码风格文件
    ├─ .cmake-format.py                # CMake代码风格文件
    ├─ .gitignore                      # git忽略文件
    ├─ .gitmoudles                     # git子模块文件
    ├─ CMakeLists.txt                  # 顶层CMake文件
    ├─ Doxygen.in                      # 文档生成配置文件
    └─ README.md                       # 说明
```

## 第三方依赖

- 代码测试：[GoogleTest](https://github.com/google/googletest)
- 变量调试：[dbg](https://github.com/sharkdp/dbg-macro)

## 可选工具

- C/C++ 代码格式化：[LLVM](https://github.com/llvm/llvm-project)
- CMake 代码格式化：[CMakeLang](https://github.com/cheshirekow/cmake_format)
- 多语言导出：[SWIG](https://github.com/doxygen/doxygen)
- 文档导出：[Doxygen](https://github.com/swig/swig)
- 多语言测试：[Gauge](https://github.com/getgauge/gauge)
