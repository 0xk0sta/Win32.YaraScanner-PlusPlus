#include <iostream>
#include "SimpleYara.h"
#include "Agent.h"

int main()
{
	SimpleYara	*yara;
	Agent		*agent;
	try {
		yara = new SimpleYara();
		agent = new Agent(yara);
		while (true) agent->ProcScanner();
	} catch (std::runtime_error &e) {
		std::cout << e.what() << std::endl;
	}
}
