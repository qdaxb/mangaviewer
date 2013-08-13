#include "common.h"


bool fileNameLessThan(const QString &s1, const QString &s2)
{
   QRegExp reg(".*([0-9]+).*");
   if(reg.exactMatch(s1))
   {
       QString str1=reg.capturedTexts().at(1);
       int file1=str1.toInt();
       if(reg.exactMatch(s2))
       {
           QString str2=reg.capturedTexts().at(1);
           int file2=str2.toInt();
           return file1<file2;
       }
   }
    return s1.toLower() < s2.toLower();
}
