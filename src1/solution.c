#include <stdio.h>
#include <string.h>
#include <dirent.h>

long long add(char *rootPath);

long long mul(char *rootPath);

long long add(char *rootPath) {
	FILE* file;
	DIR* dirList = opendir(rootPath);
	long long res = 0;
	long long n;
	char c;
	if (dirList) {
		struct dirent* dir = readdir(dirList);
		while (dir) {
			if (dir->d_name[0] == '.') {
				dir = readdir(dirList);
				continue;
			}
			if (strcmp(dir->d_name, "add") == 0) {
				strcat(rootPath, "/add");
				res = res + add(rootPath);
				rootPath[strlen(rootPath) - 4] = '\0';
			}
			else if (strcmp(dir->d_name, "mul") == 0) {
				strcat(rootPath, "/mul");
				res = res + mul(rootPath);
				rootPath[strlen(rootPath) - 4] = '\0';
			}
			else {
				strcat(rootPath, "/");
				strcat(rootPath, dir->d_name);
				file = fopen(rootPath, "r");
				fscanf(file, "%lld", &n);
				c = fgetc(file);
				res = res + n;
				while ((c != EOF) && (c != '\n') && (fscanf(file, "%lld", &n) != EOF)) {
					c = fgetc(file);
					res = res + n;
				}
				fclose(file);
				rootPath[strlen(rootPath) - strlen(dir->d_name) - 1] = '\0';
			}
			dir = readdir(dirList);
		}
	}
	closedir(dirList);
	return res;
}

long long mul(char *rootPath) {
	FILE* file;
	DIR* dirList = opendir(rootPath);
	long long res = 1;
	long long n;
	long long flag = 0;
	char c;
	char c1;
	if (dirList) {
		struct dirent* dir = readdir(dirList);
		while (dir) {
			if (dir->d_name[0] == '.') {
				dir = readdir(dirList);
				continue;
			}
			if (strcmp(dir->d_name, "add") == 0) {
				strcat(rootPath, "/add");
				res = res * add(rootPath);
				rootPath[strlen(rootPath) - 4] = '\0';
			}
			else if (strcmp(dir->d_name, "mul") == 0) {
				strcat(rootPath, "/mul");
				res = res * mul(rootPath);
				rootPath[strlen(rootPath) - 4] = '\0';
			}
			else {
				strcat(rootPath, "/");
				strcat(rootPath, dir->d_name);
				file = fopen(rootPath, "r");
				fscanf(file, "%lld", &n);
				c = fgetc(file);
				res = res * n;
				while ((c != EOF) && (c != '\n') && (fscanf(file, "%lld", &n) != EOF)) {
					c = fgetc(file);
					res = res * n;
				}
				fclose(file);
				rootPath[strlen(rootPath) - strlen(dir->d_name) - 1] = '\0';
			}
			dir = readdir(dirList);
		}
	}
	closedir(dirList);
	return res;
}

int main() {
	char path[10000];
	FILE* result = fopen("./result.txt", "w");
	strcat(path, "./tmp");
	DIR* dirList = opendir(path);
	struct dirent* dir = readdir(dirList);
	if (dirList) {
		while (dir) {
			if (dir->d_name[0] == '.') {
				dir = readdir(dirList);
				continue;
			}
			if (strcmp(dir->d_name, "add")) {
				fprintf(result, "%lld", add(path));
				dir = readdir(dirList);
				continue;
			}
			if (strcmp(dir->d_name, "mul")) {
				fprintf(result, "%lld", mul(path));
				dir = readdir(dirList);
				continue;
			}
		}
	}
	return 0;
}