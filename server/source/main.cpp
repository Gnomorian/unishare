#include "unishare.hpp"
#include "app.hpp"
#include "settings.hpp"

int main()
{
	Settings settings(UNISHARE_INI_FILE);
	USError result = settings.readIniFile();
	CHECK_RESULT;

	UnishareServerApp app(&settings);
	return app.run();
}