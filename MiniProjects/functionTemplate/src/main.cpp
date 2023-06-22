#include <iostream>
#include <numeric>
#include <string>

#include "ftemplate.h"
#include "list.h"
#include "message.h"
#include "stack.h"
#include "version.h"
// #include "generated/version.h"
using std::string;
// for testing template only
void test(int a) {
	cout << a;
}
int main(int argc, char *argv[]) {
	stack<string> sqlStatement{};
	sqlStatement.push("Unity DE");
	sqlStatement.push("KDE");
	sqlStatement.push("Cinnamon");
	for (int i{}; i < sqlStatement.size(); i++)
		cout << sqlStatement.at(i) << " -> ";
	cout << sqlStatement.first() << " | " << sqlStatement.last() << endl;

	Message txtMessage{5};
	cout << "Message id: " << txtMessage.getId() << endl;
	cout << "Project version " << PROJECT_VERSION << endl;
	return 0;
}
