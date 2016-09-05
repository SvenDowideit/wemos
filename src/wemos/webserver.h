
#include <string>
typedef const char *handler();

void setupWebserver();
void updateWebserver();

void addHandler(const char *url, handler fn);
