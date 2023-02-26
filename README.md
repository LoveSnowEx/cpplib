# cpplib

這個 repository 記錄了我練習寫 C++ 函式庫（library）的過程。每個項目是在不同時間撰寫的，而我在過程中持續改進自己的程式，因此不同項目的程式碼風格會有些微的不同。

目錄：

- list - 使用 std::shared_ptr 做為 list node 的 doubly linked list
- vector - 能自動增長 capacity 的 vector，記憶體分配均攤 O(1)
- string - 模仿 std::string，支援 iostream 的 stream operator (`>>` 和 `<<`)
- algorithm
  - sort
    - mergesort

## Requirements

- GCC v7.x or higher
- Make

## Build

The code can be compiled with the provided makefile using the standard `make`
command.

```shell
make
```

## Run

To run the code.

```shell
./main
```

## Project Structure

```text
.
├── README.md
├── main.cpp
├── makefile
├── src
│   ├── algorithm
│   │   └── sort.hpp
│   ├── list
│   │   └── list.hpp
│   ├── string
│   │   ├── string.cpp
│   │   └── string.hpp
│   └── vector
│       └── vector.hpp
└── test
    ├── list.hpp
    ├── string.hpp
    └── vector.hpp
```
