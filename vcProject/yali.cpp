#include<iostream>
#include<string>
//#include <unistd.h>  //header file with sleep function
#include<windows.h> 
using namespace std;
 bool b;
class Token {

public:  unsigned int _varId;//每个Token的标识号
		 string _str;//每个Token的内容
		 bool _isName;//是否为变量名
		 bool _isNumber;
		 bool _isBoolean;
		 int  _next_varId; //以此记录本Token节点的下一个节点的ID号: _next_varId,进而找到本节点的下一个节点     // Token *_next;
         int  _previous_varId;//以此记录本Token节点的前一个节点的ID号: _previous_varId,进而找到本节点的前一个节点 // Token *_previous;
    
     Token(string a,int x,bool y1,bool y2,bool y3,int z,int w)
	 {
		_str=a;
        _varId=x;
        _isName=y1;
		_isNumber=y2;
		_isBoolean=y3;
		_next_varId=z;
		_previous_varId=w;;

        
	 }
	 bool isName() const {
        return _isName;
    }
	 /*void isNumber(bool number) {
        _isNumber = number;
    }
	*/
	 bool isNumber() const {
        return _isNumber;
    }
	  bool isBoolean() const {
        return _isBoolean;
    }
      int previous() const {
        return _previous_varId;
    }

    int next() const {
        return _next_varId;
    }

    unsigned int varId() const {
        return _varId;
    }
    void varId(unsigned int id) {
        _varId = id;
    }
    string str() const {
        return _str;
   }
/////////////////////////////////////
	bool Match( Token tok1,  char pattern[],  int varid)
	//bool Token::Match( Token tok1)
	{// char pattern[5]={1};int varid=0;

     Token * tok=&tok1;
     char *p = pattern;
	 //int v=varid;
	  //cout<<"_varIdv"<<_varId<<endl;
	  // cout<<"_varIdv"<<v<<endl;
    bool firstpattern = true;
    while (*p) {
        // Skip spaces in pattern..//len=strlen(str); 
        while (*p == ' ')
            ++p;

        // No token => Success!
        if (*p == 0)
            return true;

        if (!tok) {
            // If we have no tokens, pattern "!!else" should return true
            if (p[1] == '!' && p[0] == '!' && p[2] != '\0') {
                while (*p && *p != ' ')
                    ++p;
                continue;
            } else
                return false;
        }

        // If we are in the first token, we skip all initial !! patterns
        if (firstpattern && !tok->previous() && tok->next() && p[1] == '!' && p[0] == '!' && p[2] != '\0') {
            while (*p && *p != ' ')
                ++p;
            continue;
        }

        firstpattern = false;

        // Compare the first character of the string for optimization reasons
        // before doing more detailed checks.
        if (p[0] == '%') {
            bool patternUnderstood = false;
            switch (p[1]) {
            case 'v':
                // TODO: %var% should match only for
                // variables that have varId != 0, but that needs a lot of
                // work, before that change can be made.
                // Any symbolname..
                if (p[4] == '%') { // %var%
                    if (!tok->isName())
                        return false;
                    p += 5;
                    patternUnderstood = true;
                } else { // %varid%
                    if (varid == 0) {
                        throw *tok;
                    }

                    if (tok->varId() != varid)
                        return false;

                    p += 7;
                    patternUnderstood = true;
                }
                break;
            case 't':
                // Type (%type%)
            {
                if (!tok->isName())
                    return false;

                if (tok->varId() != 0)
                    return false;

                if (tok->str() == "delete")
                    return false;

                p += 6;
                patternUnderstood = true;
            }
            break;
            case 'a':
                // Accept any token (%any%)
            {
                p += 5;
                patternUnderstood = true;
            }
            break;
            case 'n':
                // Number (%num)
            {
                if (!tok->isNumber())
                    return false;
                p += 5;
                patternUnderstood = true;
            }
            break;
            case 's':
                // String (%str%)
            {
                if (tok->_str[0] != '\"')
                    return false;
                p += 5;
                patternUnderstood = true;
            }
            break;
            case 'b':
                // Bool (%bool%)
            {
                if (!tok->isBoolean())
                    return false;
                p += 6;
                patternUnderstood = true;
            }
            break;
            case 'o':
                // Or (%or%) and Op (%op%)
                if (p[3] == '%') {
                    patternUnderstood = true;

                    // multicompare..
                    if (p[4] == '|') {
                        int result =  -1;                                // multiCompare(p, tok->str().c_str());
                        if (result == -1)
                            return false;   // No match

                        while (*p && *p != ' ')
                            p++;
                    }

                    // single compare..
                    else if (p[2] == 'r') {
                        if (tok->str() != "|")
                            return false;
                        p += 4;
                    } else if (p[2] == 'p') {

                            return false;
                        p += 4;
                    } else
                        patternUnderstood = false;
                }

                // Oror (%oror%)
                else if (p[5] == '%') {
                    // multicompare..
                    if (p[6] == '|') {

                            return false;   // No match

                        while (*p && *p != ' ')
                            p++;
                    }

                    // single compare..
                    else if (tok->str() != "||")
                        return false;

                    else
                        p += 6;

                    patternUnderstood = true;
                }
                break;
            default:

                break;
            }

            if (!patternUnderstood) {
                return false;
            }

            // debugging: assert that this is not part of a multicompare pattern..

           // tok = tok->next();
            //continue;
        }

    }
}
void show()
{
 cout<<"_str   "<<_str<<endl;
 cout<<"_varIdv   "<<_varId<<endl;
 cout<<"_isName   "<<_isName<<endl;
 cout<<"_isNumber   "<<_isNumber<<endl;
 cout<<"_isBoolean   "<<_isBoolean<<endl;
 cout<<"_next_varId  "<<_next_varId<<endl;
 cout<<"_previous_varId  "<<_previous_varId<<endl;


 
}
};


void main()
{
	//	bool Match(const Token tok1,char pattern[],  int varid);
	    bool Match( Token tok1,char pattern[],  int varid);
		void fun(Token t);
      // bool Match( Token tok1);

         //Token M1("delete",2,true,true,true,1,3);
		Token M1("delete",3,true,true,true,1,3);
         M1.show();
   fun(M1);
		//const Token *p=&M1;//(Match(M1,"delete",2)
	 char a[7]="delete";
		// bool b=Match(M1,a,2);
	 
        //bool b=Match(M1);
		  if(b)
		  {
			  cout<<"经测试匹配成功"<<endl;
			// cout<<b<<endl;
		  }else
		  {
			    cout<<"经测试匹配不成功"<<endl;
		  }

}
void fun(Token t)
{
	if(t._varId==2)
	{
       b=true;
	}
	else if(t._varId==3)
	{ b=false;
	}else
	{
	}
}