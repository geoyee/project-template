# cmake-project-template

自用的 C/C++项目模板

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
    ├─ test                            # 测试代码
    ├─ .clang-format                   # 代码风格文件
    ├─ .gitignore                      # git忽略文件
    ├─ .gitmoudles                     # git子模块文件
    ├─ CMakeLists.txt                  # 顶层CMake文件
    └─ README.md                       # 说明
```

## 默认依赖

- 基础库：[POCO](https://github.com/pocoproject/poco.git)
- 测试库：[GoogleTest](https://github.com/google/googletest.git)