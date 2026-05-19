#include <iostream>
#include "controller/Controller.h"

int main(void) {
   try {
      Controller controller_;
      controller_.run();
   } catch (std::exception & e) {
      std::cerr << e.what() << std::endl;
   }
   

   return 0;
}