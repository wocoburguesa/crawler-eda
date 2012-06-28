#include <iostream>
#include <vector>
#include "reader.h"
#include "cleaner.h"

using namespace std;

class PageScanner{
private:
  string domain;
  char * url;
  string url_s;
  string html;
  HTMLGetter * getter;
  Cleaner * cleaner;
  vector<string> raw_hrefs;
  vector<string> clean_hrefs;

public:
  PageScanner(string url_){
    cleaner = new Cleaner();
    url_ = cleaner->clean_special(url_);
    url_s = url_;
    url = new char[url_.size()];
    for(int i = 0; i < url_.length(); ++i)
      url[i] = (char)url_[i];

    getter = new HTMLGetter();

  }

  string get_domain(string url_){
    string domain_;
    //    string url_(url);
    url_ = cleaner->clean_special(url_);
    if(url_.substr(0, 4) == "http"){
      int counter = 0, i = 0;
      
      for(; counter < 2; ++i)
	//NEVER FORGET
        if(url_[i] == '/')
          ++counter;

      int j = i;
      for(; url_[j] != '/' && j < url_.length(); ++j);
      domain_ = url_.substr(i, j-i);
    }
    else{
      int i = 0;
      //NEVER FORGIVE
      for(; url_[i] != '/' && i < url_.length(); ++i);
      domain_ = url_.substr(0, i);
    }
    return domain_;
  }
  
  void set_domain(){
    domain = get_domain(url_s);
  }

  void read_page(){
    getter->read(url, html);
  }

  void process_href_tags(){
    raw_hrefs = cleaner->get_href_tags(html);
    for(int i = 0; i < raw_hrefs.size(); ++i){
      if(raw_hrefs[i].length() > 0){
	string clean_href = "";
	if(raw_hrefs[i].substr(0,4) != "http"){
	  if(raw_hrefs[i][0] == '/')
	    clean_href += domain + raw_hrefs[i];
	}
	else
	  clean_href = raw_hrefs[i];
	clean_hrefs.push_back(clean_href);
      }
    }
  }

  vector<string> get_clean_hrefs(){
    /*for(int i = 0; i < clean_hrefs.size(); ++i)
      cout << clean_hrefs[i] << endl;*/
    return clean_hrefs;
  }

  ~PageScanner(){
    getter->cleanup();
  }
  
};
