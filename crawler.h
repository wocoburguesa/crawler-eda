#include <iostream>
#include "webweb.h"

using namespace std;

class Crawler
{
 private:
  Webweb * web;
  string save_file;

 public:
  Crawler(string s){
    save_file = s;
    web = new Webweb();
  }

  void save(){
    ofstream ofs(save_file.c_str());
    boost::archive::text_oarchive oa(ofs);
    oa << *web;
  }

  void restore(){
    ifstream ifs(save_file.c_str());
    boost::archive::text_iarchive ia(ifs);
    ia >> *web;
  }

  void run(string start_url){
    //el primero siempre tiene un dominio sin sublinks

    /********/
    Node * node;
    if(web->is_new()){
      cout << "New webweb" << endl;
      node = new Node(start_url);
    }
    else{
      node = web->get_last();
      cout << "Resumed" << endl;
    }
    /*******/

    string url;
    web->add_node(node);
    int counter = 0;
    //esto debe ser < web->get_size()
    //    while(counter < web->get_size()){
    while(counter < 2){
      if(counter == 0)
	url = start_url;
      else{
	url = web->get_nth_domain(counter)->get_domain();
	node = web->get_nth_domain(counter);
      }

      cout << "URL N#" << counter << ": " << url << endl;

      PageScanner p(url);
      p.set_domain();
      p.read_page();
      p.process_href_tags();
      vector<string> clean_hrefs = p.get_clean_hrefs();
      for(int i = 0; i < clean_hrefs.size(); ++i){
	if(clean_hrefs[i].length() > 0)
	  web->add_url(p.get_domain(clean_hrefs[i]), clean_hrefs[i], node);
      }

      //delete(p);
      clean_hrefs.clear();
      for(int i = node->get_last(); i < 2 && i < node->get_sublink_size(); ++i){
	cout << "URL N#" << counter << "_" << i << ": " << node->get_nth_sublink(i) << endl;
	PageScanner p(node->get_nth_sublink(i));
	p.set_domain();
	p.read_page();
	p.process_href_tags();
	clean_hrefs = p.get_clean_hrefs();
	for(int i = 0; i < clean_hrefs.size(); ++i){
	  web->add_url(p.get_domain(clean_hrefs[i]), clean_hrefs[i], node);
	}
	node->increase_last();
      }
      ++counter;
      web->increase_last();
    }
  }
  
};
