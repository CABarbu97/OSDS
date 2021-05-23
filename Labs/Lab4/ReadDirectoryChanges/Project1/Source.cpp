#include <windows.h>
#include <stdio.h>

char buffer[0x100000];



int ReadChanges()
{
	DWORD bRet = 0;
	HANDLE h = CreateFileW(L"d:\\Tests", FILE_LIST_DIRECTORY, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, 0);

	while (1)
	{

		ReadDirectoryChangesW(h, buffer, 0x100000, TRUE,
			FILE_NOTIFY_CHANGE_FILE_NAME |
			FILE_NOTIFY_CHANGE_DIR_NAME |
			FILE_NOTIFY_CHANGE_ATTRIBUTES |
			FILE_NOTIFY_CHANGE_SIZE |
			FILE_NOTIFY_CHANGE_LAST_WRITE |
			FILE_NOTIFY_CHANGE_LAST_ACCESS |
			FILE_NOTIFY_CHANGE_CREATION |
			FILE_NOTIFY_CHANGE_SECURITY,
			&bRet,
			NULL,
			NULL);


		FILE_NOTIFY_INFORMATION * p = (FILE_NOTIFY_INFORMATION *)buffer;
		wprintf(L"file %s has changed.\n", p->FileName);
	}
	CloseHandle(h);
	return 0;
}

int main()
{
	DWORD id = 0;

	ReadChanges();

	return 0;
}