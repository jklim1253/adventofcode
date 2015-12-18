#include <iostream>
#include <fstream>
#include <istream>
using namespace std;

class Santa {
private :
	int _floor;
	int _position;
	bool _trigger;
	static const char up = '(';
	static const char down = ')';
public :
	Santa() : _floor(0), _position(0), _trigger(false) {}

	inline void go_down() {
		--_floor;
	}
	inline void go_up() {
		++_floor;
	}
	int where_am_i() const {
		return _floor;
	}
	void follow_instruction(istream& instruction) {
		char direction;
		while (instruction.get(direction).good()) {
			if (direction == up) go_up();
			else if (direction == down) go_down();
			else unknown_instruction(direction);

			// trigger check
			trigger();
		}
	}
	void unknown_instruction(const char& what) const {
		cout << "unknown instruction : " << what << endl;
	}
	bool trigger() {
		// if trigger was already invoked
		if (_trigger)
			return _trigger;

		// for check when trigger is invoked.
		++_position;

		// condition of which trigger occur
		if (_floor < 0)
			_trigger = true;

		return _trigger;
	}
	int when_trigger_invoked() const {
		return _position;
	}
};

int main(int argc, char* argv[]) {

	if (argc != 2) {
		cerr << "Usage : Day-01 [file]" << endl;
		return 1;
	}

	ifstream file(argv[1]);
	if (!file.good()) {
		cerr << "file not found." << endl;
		return 2;
	}

	Santa goodman;

	goodman.follow_instruction(file);

	cout << "Santa\'s floor is " << goodman.where_am_i() << endl;
	cout << "first time Santa entering basement : " << goodman.when_trigger_invoked() << endl;

	file.close();

	return 0;
}