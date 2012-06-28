#include <string>  
#include <iostream>  
#include "curl/curl.h"  

using namespace std;  

static char errorBuffer[CURL_ERROR_SIZE];

int writer(char *data, size_t size, size_t nmemb, string *buffer)  
{  
  int result = 0;  
  
  if (buffer != NULL)  
    {  
      buffer->append(data, size * nmemb);  
      result = size * nmemb;  
    }  
  
  return result;  
}  
      
void usage()  
{  
  cout << "curltest: \n" << endl;  
  cout << "  Usage:  curltest url\n" << endl;  
}   
      
int main(int argc, char* argv[])  
{  
  while(1)  
    {  
      string addr;
      cin >> addr;
      string url(addr);  
      string buffer;
      
      cout << "Retrieving " << url << endl;  
      
      CURL *curl;  
      CURLcode result;  
      
      curl = curl_easy_init();  
      
      if (curl)  
        {  
          curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);  
          curl_easy_setopt(curl, CURLOPT_URL, argv[1]);  
          curl_easy_setopt(curl, CURLOPT_HEADER, 0);  
          curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);  
          curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);  
          curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);  
      
          result = curl_easy_perform(curl);  
      
          curl_easy_cleanup(curl);
      
          if (result == CURLE_OK)  
            {  
              cout << buffer << "\n";  
            }  
          else  
            {  
              cout << "Error: [" << result << "] - " << errorBuffer;  
            }  
        }  
      else
        cout << "fail" << endl;
    }  
  return 0;
}  
