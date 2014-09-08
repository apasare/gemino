#ifndef GEMINO_GEMINO_CORE_APP_H_
#define GEMINO_GEMINO_CORE_APP_H_

#include <iostream>
#include <cstdlib>
#include "fcgio.h"

// class FCGX_Request;

namespace Gemino {
namespace Core {

class App {
public:
    static void Init();
    static void Process(FCGX_Request & request);
}; // end class App

} // end namespace Core
} // end namespace Gemino

#endif // GEMINO_GEMINO_CORE_APP_H_
