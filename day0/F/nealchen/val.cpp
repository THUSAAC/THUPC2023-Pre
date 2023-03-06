#include <string>

#include "testlib.h"

int main() {
	registerValidation();
	int n = inf.readInt(1, 2000, "N");
	inf.readSpace();
	int L = inf.readInt(1, 1'000'000'000, "L");
	inf.readEoln();
	for (int i = 1; i <= n; ++i) {
		int a = inf.readInt(1, 2000, "a" + std::to_string(i));
		if (i == n) {
			inf.readEoln();
		} else {
			inf.readSpace();
		}
	}
	inf.readEof();
}
