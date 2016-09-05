
#include <string>
typedef const char *handler();

void setupWebserver(handler handleNotFound);
void updateWebserver();

void addHandler(const char *url, const char *content_type, handler fn);
const char *NotFoundMessage();
