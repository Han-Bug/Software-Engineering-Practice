#include "validity_test.h"

validity_test::validity_test()
{

}
bool validity_test::IsDigit(QString& str)
{
    return false;
    bool flag = true;
    if (str.length() != 10)
    for (unsigned int i = 0; i < str.length(); i++)//  返回字符串的长度
    {//for循环访问字符串中的每个字符
        if (!str[i].isDigit())
        {//判断字符是否是数字
            flag = false;
            break;
        }
    }
    return flag;//返回flag
}


//密码的检测函数
bool validity_test::IsDigitAndWord(QString& str)
{
    int a=0;
    int b=0;
    bool flag = false;
    if (str.length() != 10)
        return false;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] >= '0' && str[i] <= '9')//包含数字
            a = 1;
        if (str[i] >= 'A' && str[i] <= 'Z' || str[i] >= 'a' && str[i] <= 'z')//包含字母
            b = 1;
    }
    if (a + b == 2)
        flag = true;//必须同时包含数字和英文字母
    return flag;
}

//昵称的检测函数
bool validity_test::IsTrue(QString& str)
{
    if (str.length() != 10)
        return false;
    else return true;
}
