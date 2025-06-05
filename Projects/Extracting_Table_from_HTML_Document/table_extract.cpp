#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include <regex>

using namespace std;

size_t CallBack(void* contents, size_t size, size_t, size_t nmemb, string* output)
{
  size_t totalSize = size * nmemb;
  output->append((char*)contents, totalSize);
  return totalSize;
}

string FetchHTML(const string& url)
{
  CURL* curl = curl_easy_init();
  string buffer;

  if (curl)
  {
    cout << "curl read!" << endl;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    cout << "opt 1 done" << endl;
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    cout << "opt 2 done" << endl;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CallBack);
    cout << "opt 3 done" << endl;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
    cout << "opt 4 done" << endl;
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    cout << "curl init done" << endl;
  }
  else cout << "curl init failed!" << endl;
  cout << buffer<< endl;
  return buffer;
}

void ExtractTable(const string& html)
{
  regex tableRow(R"(<tr.*?>(.*?)</tr>)");
  regex tableCell(R"(<td.*?><p.*?><span.*?>(.*?)</span></p></td>)");

  auto rowBegin = sregex_iterator(html.begin(), html.end(), tableRow);
  auto rowEnd = sregex_iterator();

  for (auto rowIt = rowBegin; rowIt != rowEnd; ++rowIt)
  {
    cout << "first loop entered!" << endl;
    string rowHTML = (*rowIt)[1].str();
    vector<string> cells;
    
    auto cellBegin = sregex_iterator(rowHTML.begin(), rowHTML.end(), tableCell);
    auto cellEnd = sregex_iterator();

    for(auto cellIt = cellBegin; cellIt != cellEnd; ++cellIt)
    {
      cells.push_back((*cellIt)[1].str());
    }

    if(cells.size() == 3 && cells[0] != "x-coordinate")
    {
      cout << "x: " << cells[0] << ", char: " << cells[1] << ", y: " << cells[2] << endl;
    }
  }
}

int main(int argCount, char* argVector[])
{
  if (argCount < 2)
  {
  cout << "Invalid number of inputs. Usage: " << argVector[0] << "<URL>" << endl;
  return 1;
  }

  string url = argVector[1];
  cout << "Recieved URL: " << url << endl;

  string html = FetchHTML(url);

  ExtractTable(html);

  return 0;
}