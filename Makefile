# Определение платформы
ifeq ($(OS), Windows_NT)
    PLATFORM = WINDOWS
    CC = x86_64-w64-mingw32-gcc
    CFLAGS = -O2 -I./source/headers
    LDFLAGS = -lwinmm -lgdi32 -luser32 -lopengl32 -L./ -lraylib -lm
    TARGET = nights.exe
else
    UNAME := $(shell uname)
    ifeq ($(UNAME), Linux)
        PLATFORM = LINUX
        CC = gcc
        CFLAGS = -O2 -I./source/headers
        LDFLAGS = -L./ -lraylib -lm
        TARGET = build/nights
    else ifeq ($(UNAME), Darwin)
        PLATFORM = MACOS
        CC = gcc
        CFLAGS = -O2 -L./ -lraylib -lm -framework OpenGL -framework Cocoa -framework IOKit -I./source/headers
        LDFLAGS =
        TARGET = build/nights
    else ifeq ($(BUILD_WINDOWS), true)
        PLATFORM = WINDOWS
        CC = x86_64-w64-mingw32-gcc
        CFLAGS = -O2 -I./source/headers
        LDFLAGS = -lwinmm -lgdi32 -luser32 -lopengl32 -L./ -lraylib -lm
        TARGET = nights.exe
    else
        $(error Unsupported platform: $(UNAME))
    endif
endif

# Папка с исходными файлами
SRC_DIR = source

# Папка для объектных файлов
OBJ_DIR = build

# Находим все исходные файлы в папке source/
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Генерируем список объектных файлов, заменяя .c на .o и добавляя папку obj/
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Правило по умолчанию
all: $(OBJ_DIR) $(TARGET)

# Создаем папку для объектных файлов, если её нет
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Правило для сборки объектных файлов
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Правило для линковки объектных файлов в исполняемый файл
$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

# Очистка
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Указываем, что clean и all не являются реальными файлами
.PHONY: all clean
