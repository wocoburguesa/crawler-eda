#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Cleaner
{
private:
  
public:
  Cleaner(){}

  bool is_valid(string s){
    for(int i = 0; i < s.size(); ++i)
      if(s[i] != ' ')
	return 1;
    return 0;
  }

  bool is_dot_pe(string addr){
    if(addr.substr(0,4) == "http"){
      int i = 0;
      int slash_count = 0;
      for(; i < addr.length() && slash_count < 3; ++i){
	if(addr[i] == '/')
	  ++slash_count;
      }
      if(addr.substr(i-3, 2) == "pe")
	return 1;
    }
    else{
      int i = 0;
      while(addr[i] != '/' && i < addr.length())
	++i;
      if(addr.substr(i-2-(i==addr.length()), 2) == "pe")
	return 1;
    }
    return 0;
  }

  string parse_line(string line){
    if(!is_valid(line))
      return "#";
    else;
    size_t pos = line.find("href=\"");
    if(pos != string::npos){
      int i = pos + 6;
      for(; line[i] != '\"' && line[i] != '\''; ++i );
      //      if(is_dot_pe(line.substr(pos+6, i-(pos+6))))
	  return line.substr(pos+6, i-(pos+6));
	  /*       else
		   return "#";*/
    }
    return "#";
  }

  string clean_special(string url){
    string clean = "";
    int i = 0;
    for( ; i < url.size(); ){
      if(url[i] == '%'){
	stringstream ss;
	int ascii;
	ss << hex << url.substr(i+1, 2);
	ss >> ascii;
	clean += (char)ascii;
	i += 3;
      }
      else{
	clean += url[i];
	++i;
      }
    }
    return clean;
  }

  vector<string> get_href_tags(string html){
    vector<string> hrefs;
    stringstream ss(html, stringstream::in);
    string line;
    while(getline(ss, line)){
      string href = parse_line(line);
      if(href != "#")
        hrefs.push_back(href);
    }
    return hrefs;
  }

};
