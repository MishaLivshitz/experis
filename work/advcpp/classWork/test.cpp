#include <cstdio>
#include <cstring>

#include <string>
#include <iostream>

class K9 {
	int n;
	const char* p;
public:
	K9(const char* s)
	: n(strlen(s))
	, p(s)
	{
	}

	operator const char*() const {
		
		return this;
	}
};


int main(){
	K9 fido("poly");
	//const char* ps = fido;
	//printf("%s\n", ps);
	//printf("%s\n", reinterpret_cast<const char*>(&fido));
	//printf("%s\n", static_cast<const char*>(fido));
	printf("%s\n", fido);
}