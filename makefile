# 設定編譯器和編譯參數
CXX := g++
CXXFLAGS := -Wall -Wextra -MMD -MP -std=c++17

# 設定目標檔案和目標執行檔
TARGETS := main
OBJDIR := obj
OBJS := $(addprefix $(OBJDIR)/, $(addsuffix .o, $(TARGETS)))

# 自動尋找所有的 .cpp 檔案
SRCDIRS := $(shell find . -type d)
SRCS := $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.cpp))

# 將每個 .cpp 檔案的路徑替換成對應的 .o 檔案路徑
OBJS += $(addprefix $(OBJDIR)/, $(patsubst %.cpp, %.o, $(SRCS)))

# 設定 VPATH 變數
VPATH := $(SRCDIRS)

# 從目標文件列表中生成對應的依賴文件列表
DEPS := $(patsubst %.o,%.d,$(OBJS))

# 規則: 編譯所有目標檔案
all: $(TARGETS)

debug: CXXFLAGS += -g -DDEBUG -fsanitize=leak -fsanitize=undefined
debug: LDFLAGS += -fsanitize=address -lubsan -lasan
debug: $(TARGETS)

$(TARGETS): %: $(OBJDIR)/%.o
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $@

# 包含每個 .d 檔案，這樣才會自動找到依賴關係
-include $(DEPS)

# 規則: 刪除所有目標檔案和目標執行檔
clean:
	$(RM) -r $(OBJDIR) $(TARGETS)

.PHONY: all debug clean
