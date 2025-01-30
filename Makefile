# Компилятор и флаги
CC = cc
CFLAGS = -O2
LDFLAGS = -L/usr/lib -lraylib -lm

# Папка с исходными файлами
SRC_DIR = source

# Папка для объектных файлов
OBJ_DIR = build

# Итоговый исполняемый файл
TARGET = build/nights

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
	$(CC) $(LDFLAGS) $^ -o $@

# Очистка
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Указываем, что clean и all не являются реальными файлами
.PHONY: all clean
