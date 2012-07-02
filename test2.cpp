#include <iostream>
#include <sstream>
#include <vector>
#include <boost/thread.hpp>
#include "crawler.h"

using namespace std;

int main(int argc, char* argv[]){
  Crawler c("save.txt");
  c.restore();
  string url;
  cin >> url;
  c.run(url);
  c.save();
  /*  string url;    
  vector<string> urls;
  cin >> url;
  urls.push_back(url);
  int counter = 0;
  while(counter < urls.size()){
    if(counter > 0)
      url = urls[counter];
    else;
    PageScanner p(url);
    p.set_domain();
    p.read_page();
    p.process_href_tags();
    vector<string> clean_hrefs = p.get_clean_hrefs();
    for(int i = 0; i < clean_hrefs.size(); ++i)
      urls.push_back(clean_hrefs[i]);
    ++counter;
    }*/
};
