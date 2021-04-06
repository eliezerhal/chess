#include "Controller.h"

int main()
{
	Controller& c = Controller::getInstance();
	c.run();
	return 0;
}
