
#include <WString.h>

typedef String *handler();

void setupWebserver(handler handleNotFound);
void updateWebserver();

void addHandler(const char *url, const char *content_type, handler fn);
String *NotFoundMessage();
