# chilib

## 介绍

自己实现一些 C++ 库，比如`string`、`vector`、`linked_list`啥的。

在写了在写了（新建`*.hpp`文件）。

## 文件结构

1. `chilib/*.hpp`：库文件
2. `CMakeList.txt`：`CMake`使用的工程配置文件，当做模板
3. `document`：文档

## 使用说明

1. 代码都在`chilib`命名空间中
2. `include`对应头文件之后即可使用
3. 文件命名会尽量参照`STL`
4. 文档：
   1. `linked_list`：[文档](./Document/linked_list.md)

## 参与贡献

1. Fork 本仓库
2. 新建 Feat_xxx 分支
3. 提交代码
4. 新建 Pull Request
