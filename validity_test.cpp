#include "validity_test.h"

validity_test::validity_test()
{

}
bool validity_test::IsDigit(QString& str,int maxNum,int minNum)
{
    bool flag = true;
    if (str.length() > maxNum && maxNum>0)return false;
    else if(str.length()<minNum)return false;
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
bool validity_test::IsDigitAndWord(QString& str,int maxNum,int minNum)
{

    if (str.length() > maxNum && maxNum>0)return false;
    else if(str.length()<minNum)return false;
    for (int i = 0; i < str.length(); i++)
    {
        if(!str[i].isLetterOrNumber())return false;
        QChar cha = str[i];
            ushort uni = cha.unicode();
            //若含有中文，返回false
            if(uni >= 0x4E00 && uni <= 0x9FA5)
            {
                return false;
            }


    }
    return true;

}

//昵称的检测函数
bool validity_test::wordLimit(QString& str,int maxNum,int minNum)
{
    if (str.length() > maxNum && maxNum>0)return false;
    else if(str.length()<minNum)return false;
    else return true;
}
