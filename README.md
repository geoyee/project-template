# project-template

自用的C/C++项目的CMake模板

## 结构

```
    ├─ .github/workflows               # *github CI/CD
    ├─ 3rdparty                        # 三方库
    ├─ cmake                           # CMake文件
    ├─ doc                             # 文档
    ├─ libraryT                        # 模块模板
    │    ├─ include/libraryT           # 头文件
    │    └─ src                        # 源文件
    ├─ sample                          # 示例代码
    ├─ swig                            # swig多语言接口导出
    ├─ test                            # 测试代码
    ├─ .clang-format                   # 代码风格文件
    ├─ .gitignore                      # git忽略文件
    ├─ .gitmoudles                     # git子模块文件
    ├─ CMakeLists.txt                  # 顶层CMake文件
    ├─ Doxygen                         # 文档生成配置文件
    └─ README.md                       # 说明
```

## 依赖

- 代码测试：[GoogleTest](https://github.com/google/googletest)
- \*代码格式化：[LLVM](https://github.com/llvm/llvm-project)
- \*多语言导出：[SWIG](https://github.com/doxygen/doxygen)
- \*文档导出：[Doxygen](https://github.com/swig/swig)
