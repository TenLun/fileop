#include <iostream>
#include <fstream>
#include <string>
#include <cstring>        // for strcpy(), strcat()
#include <io.h>

using namespace std;

ofstream outfile;

void listFiles(const char* dir) {
	char dirNew[200];
	strcpy(dirNew, dir);
	strcat(dirNew, "\\*.*");    // ��Ŀ¼�������"\\*.*"���е�һ������

	intptr_t handle;
	_finddata_t findData;

	handle = _findfirst(dirNew, &findData);
	if (handle == -1)        // ����Ƿ�ɹ�
		return;

	do {
		if (findData.attrib & _A_SUBDIR) {
			if (strcmp(findData.name, ".") == 0 || strcmp(findData.name, "..") == 0)
				continue;

			//cout << findData.name << "\t<dir>\n";

			// ��Ŀ¼�������"\\"����������Ŀ¼��������һ������
			strcpy(dirNew, dir);
			strcat(dirNew, "\\");
			strcat(dirNew, findData.name);

			listFiles(dirNew);
		}
		else {
			string s = findData.name;
			if (s.find(".exe") != -1) {
				outfile << dir << findData.name << endl; //<< findData.size << " bytes.\n";
			}
		}
	} while (_findnext(handle, &findData) == 0);

	_findclose(handle);    // �ر��������
}

int main(int argc, const char* argv[]) {

	outfile.open("result.txt");
	const char* dir = argv[1];
	listFiles(dir);
	outfile.close();
	return 0;
}