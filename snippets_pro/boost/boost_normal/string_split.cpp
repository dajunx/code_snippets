#include "boost_common.h"

using namespace boost::algorithm;
using namespace std;

bool string_split() {
  string str("miss,you.just.call_to,say,I~love~you");
  vector<string> strVec;
  split(strVec, str, is_any_of(",."));
  vector<string>::iterator it = strVec.begin();
  for (; it != strVec.end(); it++) {
    cout << *it << endl;
  }

  return true;
}