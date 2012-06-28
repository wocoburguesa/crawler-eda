#include <iostream>
#include "curl/curl.h"

using namespace std;

class HTMLGetter
{
 private:
  CURL * curl;
  CURLcode result;
  char error_buffer[CURL_ERROR_SIZE];  

 public:
  HTMLGetter(){
    curl = curl_easy_init();
  }

  static int writer(char *data, size_t size, size_t nmemb,  
                    string *buffer){  
    int res = 0;  
    
    if (buffer != NULL)  
      {  
        buffer->append(data, size * nmemb);  
        res = size * nmemb;  
      }  
  
    return res;  
  }  
     
  bool read(char * url, string &buffer){
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, error_buffer);  
    curl_easy_setopt(curl, CURLOPT_URL, url);  
    curl_easy_setopt(curl, CURLOPT_HEADER, 0);  
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);  
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);  
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);  

    result = curl_easy_perform(curl);

    /*    for(int i = 0; i < CURL_ERROR_SIZE; ++i)
	  cout << error_buffer[i] << endl;*/

    if(result == CURLE_OK){
      return 1;
    }
    /*    else{
      cout << "prob" << endl;
      }*/
    return 0;
  }

  void cleanup(){
    curl_easy_cleanup(curl);
  }

  ~HTMLGetter(){
    cleanup();
    delete this;
  }

};
