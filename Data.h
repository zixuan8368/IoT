#ifndef DATA_H
#define DATA_H

#include <vector>
using std::vector;

vector<String> strID;
vector<String strTIme;

void addCheckIn(String ID, String Time)
{
    strID.push_back(ID);
    
}

void removeCheckIn(String ID, String Time)
{

}

int findEntryIndex(String ID)
{
  int size = strID.size();
  for(int i = 0; i < size; ++i)
  {
    if(strID[i] == ID)
    {
      return i;
      i = size;
    }
    else
      return -1;
  }
}


#endif