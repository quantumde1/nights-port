#!/bin/bash

# Папка с файлами
SOURCE_DIR="source"

# Проходим по всем файлам в папке
for file in "$SOURCE_DIR"/*; do
    # Проверяем, что это файл
    if [ -f "$file" ]; then
        # Заменяем слово 'short' на 'int' с помощью sed
        sed -i 's/\<short\>/int/g' "$file"
    fi
done

