#ifndef VALIDITY_TEST_H
#define VALIDITY_TEST_H
#include <QString>

class validity_test
{
public:
    validity_test();
    //仅数字
    bool IsDigit(QString& str,int num);
    //仅数字和字母
    bool IsDigitAndWord(QString& str,int num);
    //字符数量是否在范围内
    bool wordLimit(QString& str,int num);
};

#endif // VALIDITY_TEST_H
