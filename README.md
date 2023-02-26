# cpplib

記錄我練習寫 c++ library

以下是目錄：

- list - 使用 std::shared_ptr 做為 list node 的 doubly linked list
- vector - 能自動增長 capacity 的 vector，記憶體分配均攤 O(1)
- string - 模仿 std::string，支援 iostream 的 stream operator (`>>` 和 `<<`)
