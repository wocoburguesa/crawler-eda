#include <iostream>
#include <set>
#include "page_scanner.h"

using namespace std;

class Node
{
 private:
  set<string> sublinks;
  set< Node*, bool(*)(Node * a, Node * b) > links;
  string domain;

 public:
  static bool comp(Node * a, Node * b){
    return a->domain < b->domain;
  }

  Node(string domain_){
    domain = domain_;
    sublinks.clear();
    links = set< Node*, bool(*)(Node * a, Node * b) >(comp);
    links.clear();
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
  vector< Node* > domains;

 public:
  Webweb(){
    domains.clear();
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
