#include <iostream>
#include <fstream>
#include <istream>
#include <map>
#include <set>
using namespace std;

class Santa {
private :
	int x;
	int y;
public :
	Santa() : x(0), y(0) {}
	inline void go_north() { ++y; }
	inline void go_south() { --y; }
	inline void go_east() { ++x; }
	inline void go_west() { --x; }
	inline int getx() const { return x; }
	inline int gety() const { return y; }
};

class World {
	static const char north = '^';
	static const char south = 'v';
	static const char east = '>';
	static const char west = '<';
private :
	Santa goodman;
	map<int, set<int>> locations;
	int houses;
public :
	World() : houses(0) {}
	void follow_instruction(istream& is) {
		// present to the house at his starting location.
		update_location(goodman);

		char direction;
		while (is.get(direction).good()) {
			if (direction == north) goodman.go_north();
			else if (direction == south) goodman.go_south();
			else if (direction == east) goodman.go_east();
			else if (direction == west) goodman.go_west();

			update_location(goodman);
		}
	}
	void update_location(const Santa& santa) {
		if (locations[santa.getx()].insert(santa.gety()).second)
			++houses;
	}
	int get_houses_count() const { return houses; }
};

int main(int argc, char* argv[]) {

	if (argc != 2) {
		cerr << "Usage : Day-03 [file]" << endl;
		return 1;
	}

	ifstream file(argv[1]);
	if (!file.good()) {
		cerr << "file not found." << endl;
		return 2;
	}

	World earth;
	earth.follow_instruction(file);

	cout << "Santa deliver at least one present to "
		<< earth.get_houses_count()
		<< " houses." << endl;


	file.close();

	return 0;
}