#ifndef VALIDITY_TEST_H
#define VALIDITY_TEST_H
#include <QString>

class validity_test
{
public:
    validity_test();
    //仅数字
    bool IsDigit(QString& str,int maxNum,int minNum=1);
    //仅数字和字母
    bool IsDigitAndWord(QString& str, int num, int minNum=1);
    //字符数量是否在范围内
    bool wordLimit(QString& str, int maxNum, int minNum=1);
};

#endif // VALIDITY_TEST_H
