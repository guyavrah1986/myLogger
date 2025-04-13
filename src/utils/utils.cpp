#include "utils.h"

using namespace std;

void UtilsReplaceStrings(IN string& str, IN const string& oldStr, IN const string& newStr)
{
    string::size_type pos = 0u;
    while((pos = str.find(oldStr, pos)) != string::npos)
    {
        str.replace(pos, oldStr.length(), newStr);
        pos += newStr.length();
    }
}