// Програма створює каталог,
// визначає час і дату останньої зміни файлу, 
// та перевіряє чи файл прихований.
#include <stdio.h>
#include <windows.h>

int main() {
    // Функція CreateDirectoryA для створення каталогу
	LPCSTR pathToDir = "C:\\Users\\Sager\\source\\repos\\SPZ-LAB4\\newDir";
    if (CreateDirectoryA(pathToDir, NULL)) {
        printf("Directory has been created.\n\n");
    } 
    else {
        printf("Error!\n\n");
    }

    // Функція GetFileAttributesExA для отриамння дати і часу останньої зміни файлу
    LPCSTR filePath1 = "C:\\Users\\Sager\\source\\repos\\SPZ-LAB4\\some.txt";
    WIN32_FILE_ATTRIBUTE_DATA fileAttr; // атрибути файлу
    if (GetFileAttributesExA(filePath1, GetFileExInfoStandard, &fileAttr)) {
        FILETIME lastWriteTime = fileAttr.ftLastWriteTime; // час і дата останньої зміни файлу

        SYSTEMTIME stUTC, stLocal; // конвертація часу з UTC в локальний час
        FileTimeToSystemTime(&lastWriteTime, &stUTC);
        SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

        printf("Time the file some.txt was last modified: %02d.%02d.%d %02d:%02d\n\n",
            stLocal.wDay, stLocal.wMonth, stLocal.wYear,
            stLocal.wHour, stLocal.wMinute);
    }
    else {
        printf("Error!\n\n");
    }

    // Функція GetFileAttributesA для перевірки файлу на прихованість
    LPCSTR filePath2 = "C:\\Users\\Sager\\source\\repos\\SPZ-LAB4\\some.txt";
    DWORD fileAttributes = GetFileAttributesA(filePath2);
    if (fileAttributes != INVALID_FILE_ATTRIBUTES) {
        if (fileAttributes & FILE_ATTRIBUTE_HIDDEN) { // перевірка на атрибут прихованості
            printf("File is hidden.\n");
        }
        else {
            printf("File is not hidden.\n");
        }
    }
    else {
        printf("Error!\n");
    }

	return 0;
}