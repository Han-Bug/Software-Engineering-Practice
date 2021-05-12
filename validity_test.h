#ifndef VALIDITY_TEST_H
#define VALIDITY_TEST_H
#include <QString>

class validity_test
{
public:
    validity_test();
    bool IsDigit(QString& str);
    bool IsDigitAndWord(QString& str);
    bool IsTrue(QString& str);
};

#endif // VALIDITY_TEST_H
