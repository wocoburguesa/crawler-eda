#include <iostream>
#include <fstream>
#include <set>
#include "page_scanner.h"
#include <boost/serialization/set.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

using namespace std;

class Node
{
 private:
  // serializer
  friend class boost::serialization::access;
  template<class Archive>
    void serialize(Archive &ar, const unsigned int file_version){
    ar.register_type(static_cast<Node*>(NULL));
    ar & domain & sublinks & links & last;
  }
  // miembros
 public:
  set<string> sublinks;
  set< Node*> links;
  string domain;
  int last;


  /*  static bool comp(Node * a, Node * b){
    return a->domain < b->domain;
    }*/

  Node(){};
  Node(string domain_){
    domain = domain_;
    sublinks.clear();
    //    links = set< Node*, bool(*)(Node * a, Node * b) >(comp);
    links.clear();
    last = 0;
  }

  void increase_last(){
    last++;
  }

  int get_last(){
    return last;
  }

  string get_domain(){
    return domain;
  }

  string get_nth_sublink(int i){
    set<string>::iterator it;
    int counter = 0;
    for(it = sublinks.begin(); counter < i; ++it, ++counter);
    return (*it);
  }

  int get_sublink_size(){
    return sublinks.size();
  }

  void add_sublink(string sublink){
    sublinks.insert(sublink);
  }

  void add_link(Node * link){
    links.insert(link);
  }
  
};

class Webweb
{
 private:
  friend class boost::serialization::access;
  template<class Archive>
    void serialize(Archive &ar, const unsigned int file_version){
     ar & domains & last;
  }
  //miembros

 public:
  vector< Node* > domains;
  int last;

  Webweb(){
    domains.clear();
    last = 0;
  }

  bool is_new(){
    return !last;
  }

  void increase_last(){
    last++;
  }

  Node* get_last(){
    cout << last << endl;
    return domains[last];
  }

  void add_url(string domain, string url, Node * node){
    Node * found = find(domain);
    if(found){
      found->add_sublink(url);
      node->add_link(found);
    }
    else{
      found = new Node(domain);
      found->add_sublink(url);
      node->add_link(found);
      domains.push_back(found);
    }
  }

  void add_node(Node * node){
    domains.push_back(node);
  }

  int get_size(){
    return domains.size();
  }

  Node * get_nth_domain(int i){
    return domains[i];
  }

  Node * find(string domain){
    for(int i = 0; i < domains.size(); ++i){
      if(domains[i]->get_domain() == domain)
	return domains[i];
    }
    return 0;
  }

  
};
