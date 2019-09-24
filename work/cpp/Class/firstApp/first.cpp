#include <iostream>
#include <string> 

int main()
{
	char* text = new char[60];
	std::cout << "hello world\n";
	std::cin >> text;
	std::cout << '{' << text << "}\n";
	delete [] text;
	return 0;

}
