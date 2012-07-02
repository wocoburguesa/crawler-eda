#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <boost/serialization/set.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

using namespace std;

class Numero{
  friend class boost::serialization::access;
  template<class Archive>
    void serialize(Archive &ar, const unsigned int file_version){
    ar & n;
  }
public:
  int n;
  Numero(){};
  Numero(int ni){ n = ni; }
};

class Persona{
  friend class boost::serialization::access;
  template<class Archive>
    void serialize(Archive &ar, const unsigned int file_version){
    ar & personas & nombre;
  }
  set<Persona*> personas;
  string nombre;
 public:
  Persona(){}
  Persona(string n){
    nombre = n;
    personas.clear();
  }

  void insert(string n){
    Persona * a = new Persona(n);
    personas.insert(a);
  }
  void print(){
    set<Persona*>::iterator it;
    cout << nombre << endl;
    for(it = personas.begin(); it != personas.end(); ++it)
      cout << (*it)->nombre << endl;
  }
};

void save_p(const Persona &p, const char * filename){
  ofstream ofs(filename);
  boost::archive::text_oarchive oa(ofs);
  oa << p;
}

void restore_p(Persona &p, const char * filename){
  ifstream ifs(filename);
  boost::archive::text_iarchive ia(ifs);
  ia >> p;
  }

int main(int argc, char* argv[]){
  Persona a("pedro");
  a.insert("juean");
  a.insert("coco");
  string arch = "text.txt";
  //save_p(a, arch.c_str());
  restore_p(a, arch.c_str());
  a.print();
};
