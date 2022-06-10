#include "Application.h"

int main()
{
	nadpher::Application app;
	if (!app.init(1024, 768))
	{
		return 1;
	}

	app.run();
}