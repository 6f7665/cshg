#include <string>

using namespace std;

class Webpage
{
	public:

	int num;
	string Category = "";
	string Destination = "";
	string Filename = "";
	string SubCategory = "";
	string Tags = "";
	string Title = "notitle";

	
	int BuildData(string &Filename, string &Title, string &Category, string &SubCategory, string &Tags, string &Destination);
	int ScanPage(string &Filename, string &Title, string &Category, string &SubCategory, string &Tags);
	void CallGenerate(string &Filename, string &Destination);
};
