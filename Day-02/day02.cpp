#include <iostream>
#include <fstream>
#include <istream>
#include <algorithm>
using namespace std;

class Box {
private :
	int length;
	int width;
	int height;
public :
	Box(const int& l = 0, const int& w = 0, const int& h = 0)
		: length(l), width(w), height(h)
	{}
	inline int surface() const {
		return 2 * (length*width + width*height + height*length) + length*width*height / max();
	}
	inline int max() const {
		return std::max(length, std::max(width, height));
	}
};

class Elf {
private :
	int papers;
public :
	Elf() : papers(0) {}
	void follow_instruction(istream& is) {
		int length, width, height;
		char x;

		while (is >> length >> x >> width >> x >> height) {
			Box present(length, width, height);
			papers += present.surface();
		}
	}
	inline int total_papaer() const {
		return papers;
	}
};
int main(int argc, char* argv[]) {

	if (argc != 2) {
		cerr << "Usage : Day-02 [file]" << endl;
		return 1;
	}

	ifstream file(argv[1]);
	if (!file.good()) {
		cerr << "file not found." << endl;
		return 2;
	}

	Elf elf;
	elf.follow_instruction(file);

	cout << "Elf needs paper of which size is " << elf.total_papaer() << endl;

	file.close();

	return 0;
}