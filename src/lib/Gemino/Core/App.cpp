#include "App.h"

using std::cout;
using std::strtol;

namespace Gemino {
namespace Core {

void App::Init() {
    // TO DO
}

void App::Process(FCGX_Request &request) {
    char * request_uri = FCGX_GetParam("REQUEST_URI", request.envp);
    char * content_length = FCGX_GetParam("CONTENT_LENGTH", request.envp);

    cout << "Content-Type: text/html\r\n"
         << "\r\n"
         << "uri: " << request_uri << "<br/>"
         << "content length: " << strtol(content_length, &content_length, 10)
         ;
}

} // end namespace Core
} // end namespace Gemino
