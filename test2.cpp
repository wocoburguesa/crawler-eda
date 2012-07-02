#include <iostream>
#include <sstream>
#include <vector>
#include "crawler.h"

using namespace std;

/*boost::thread t(){
  Crawler c("save.txt", "www.elcomercio.pe");
  return boost::thread(c);
  }*/

int main(int argc, char* argv[]){
  /*  boost::thread a = t();
      a.join();*/
  Crawler c("save.txt", "www.elcomercio.pe");
  c.run();
  //  c.save();
};
