// �������� ������� �������,
// ������� ��� � ���� �������� ���� �����, 
// �� �������� �� ���� ����������.
#include <stdio.h>
#include <windows.h>

int main() {
    // ������� CreateDirectoryA ��� ��������� ��������
	LPCSTR pathToDir = "C:\\Users\\Sager\\source\\repos\\SPZ-LAB4\\newDir";
    if (CreateDirectoryA(pathToDir, NULL)) {
        printf("Directory has been created.\n\n");
    } 
    else {
        printf("Error!\n\n");
    }

    // ������� GetFileAttributesExA ��� ��������� ���� � ���� �������� ���� �����
    LPCSTR filePath1 = "C:\\Users\\Sager\\source\\repos\\SPZ-LAB4\\some.txt";
    WIN32_FILE_ATTRIBUTE_DATA fileAttr; // �������� �����
    if (GetFileAttributesExA(filePath1, GetFileExInfoStandard, &fileAttr)) {
        FILETIME lastWriteTime = fileAttr.ftLastWriteTime; // ��� � ���� �������� ���� �����

        SYSTEMTIME stUTC, stLocal; // ����������� ���� � UTC � ��������� ���
        FileTimeToSystemTime(&lastWriteTime, &stUTC);
        SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

        printf("Time the file some.txt was last modified: %02d.%02d.%d %02d:%02d\n\n",
            stLocal.wDay, stLocal.wMonth, stLocal.wYear,
            stLocal.wHour, stLocal.wMinute);
    }
    else {
        printf("Error!\n\n");
    }

    // ������� GetFileAttributesA ��� �������� ����� �� �����������
    LPCSTR filePath2 = "C:\\Users\\Sager\\source\\repos\\SPZ-LAB4\\some.txt";
    DWORD fileAttributes = GetFileAttributesA(filePath2);
    if (fileAttributes != INVALID_FILE_ATTRIBUTES) {
        if (fileAttributes & FILE_ATTRIBUTE_HIDDEN) { // �������� �� ������� �����������
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