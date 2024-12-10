#include <iostream>
#include <fstream>
using namespace std;

#define HEADER_BLOCK_SIZE 512
#define FILESIZE_BLOCK_OFFSET 124
#define FILENAME_BUFFER_SIZE 100
#define FILESIZE_BUFFER_SIZE 12

long long oct_to_dec(char buf[FILESIZE_BUFFER_SIZE]) {
	long long res = 0;
	for (int i = 0; i < FILESIZE_BUFFER_SIZE - 1; i++)
		res = res * 8 + (buf[i] - '0');
	return res;
}

void read_tar(const char *inf) {
	std::ifstream ifs(inf, std::ios::binary);
	if (ifs.is_open()) {
		char filename[FILENAME_BUFFER_SIZE] = {0};
		char filesize[FILESIZE_BUFFER_SIZE] = {0};
		int nFile = 1;
		ifs.seekg(0, std::ios::beg);
		while (!ifs.eof()) {
			ifs.read(filename, FILENAME_BUFFER_SIZE);
			if (filename[0] == '\0') {
				break;
			}
			ifs.seekg(FILESIZE_BLOCK_OFFSET - FILENAME_BUFFER_SIZE, std::ios::cur);
			ifs.read(filesize, FILESIZE_BUFFER_SIZE);
			ifs.seekg(HEADER_BLOCK_SIZE - (FILESIZE_BLOCK_OFFSET + FILESIZE_BUFFER_SIZE), std::ios::cur);

			long long filesize_decimal = oct_to_dec(filesize);
			if (filesize_decimal < 0) {
				std::cout << "ERROR: invalid tar file\n";
				ifs.close();
				exit(1);
			}
			std::cout << "[" << nFile++ << "] " << filename << " " << filesize_decimal << "\n";
			if (filesize_decimal % 512 != 0) {
				filesize_decimal += 512 - filesize_decimal % 512;
			}
			ifs.seekg(filesize_decimal, std::ios::cur);
		}
		ifs.close();
	}
}

int main()
{
	read_tar("2208.11970.tar.gz");
	return 0;
}