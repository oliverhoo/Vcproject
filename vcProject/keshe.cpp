#include<iostream>
#include<string>
//#include <unistd.h>  //header file with sleep function
#include<windows.h> 
using namespace std;
enum AccessControl { Public, Protected, Private, Global, Namespace, Argument, Local };//简要访问控制枚举,Argument, Local/参数，局部
/*enum {
        fIsMutable  = (1 << 0), /** @brief mutable variable  短暂的可变变量
        fIsStatic   = (1 << 1), /** @brief static variable  短暂的静态变量/2
        fIsConst    = (1 << 2), /** @brief const variable 短暂的常量变量/4
        fIsClass    = (1 << 3), /** @brief user defined type  短暂的用户定义类型/8
        fIsArray    = (1 << 4), /** @brief array variable 短暂的数组变量/16
        fIsPointer  = (1 << 5), /** @brief pointer variable 短暂的指针变量/32
        fHasDefault = (1 << 6)  /** @brief function argument with default value带有默认值的简短函数参数 /64
    };
*/
/** @brief what section is this variable declared in? */
   // AccessControl _access;  // public/protected/private

/**
     * Is variable static.是可变静态的
     * @return true if static, false if not如果是静态的的返回真，否则返回假
     */
class Variable {
	public:
    /** @brief what section is this variable declared in? 简要说明这个变量的哪个部分？*/
    char*  _access;  // public/protected/private
    /** @brief flags 简要标记*/
    int _flags;//标记
	int fIsStatic;//静态变量
	int fIsArray;//数组
	public: Variable(char* a,int x,int y,int z)
	{
		_access=a;//
		_flags=x;//_flag为简要标记，要与其他整数进行"与"操作
		fIsStatic=y;//2
		fIsArray=z;//16
	//cout<<a<<endl;
    //	cout<<_access<<endl;
	}
	public: Variable()
	{
	
	}

/**
     * Is variable local. //是局部变量
     * @return true if local, false if not//如果是局部的返回真，否则返回假
     */
  bool isLocal()  {
       // return _access == Local;
		if(cmp("Local",_access)==0)
			return true;//真1
		return false;//假0
		
    }
    
 /**
     * Get specified flag state.
     * @param flag_ flag to get state of
     * @return true if flag set or false in flag not set
     */
    bool getFlag(int flag_) const {
        return bool((_flags & flag_) != 0);
		/*
		&是按位与，&&是逻辑与。
		前者，两数的对应位上都为1时结果为1，否则结果为0；
		后者，两个数都不为0时结果为1(true)，否则结果为0(false)。
      前者如：10101100 & 01110110=00100100；
      后者如：3 && 1=1，3 && 0=0，0 && 3=0，0 && 0=0。
		*/
    }
    bool isStatic() const {
        return getFlag(fIsStatic);//fIsStatic = (1 << 1), /** @brief static variable  短暂的静态变量*/
    }
	 /**
     * Is variable an array.
     * @return true if array, false if not
     */
    bool isArray() const {
        return getFlag(fIsArray);//fIsArray= = (1 << 4), /** @brief array variable 短暂的数组变量*/
    }

	int cmp(char *s, char *p)
{
 while (*s&&*p)
 {
  if (*s>*p)
   return 1;
  else if (*s < *p)
   return -1;
  else
  {
   if (*(s+1) == '\0' && *(p+1) != '\0')
    return -1;
   else if (*(s+1) != '\0' && *(p+1) == '\0')
    return 1;
   else if (*(s+1) == '\0'&&*(p+1)=='\0')
    return 0;
   else
   {
    s++,p++;
    continue;
   }
  }
 }
}

void display(){

	//cout<<_access<<endl;
  cout<<"isLocal():"<<isLocal()<<endl;//真1假0
  cout<<"isStatic():"<<isStatic()<<endl;//真1假0
  cout<<"isArray():"<<isArray()<<endl;//真1假0
 

	if(cmp("Public",_access)==0){
			cout<<"访问控制:"<<_access<<endl;
	}else if(cmp("Protected",_access)==0)
	{
			cout<<"访问控制:"<<_access<<endl;
	}else if(cmp("Private",_access)==0)
	{
			cout<<"访问控制:"<<_access<<endl;
	}else if(cmp("Global",_access)==0)
	{
		cout<<"访问控制:"<<_access<<endl;
	}else if(cmp("Namespace",_access)==0)
	{
			cout<<"访问控制:"<<_access<<endl;
	}else if(cmp("Argument",_access)==0)
	{
			cout<<"访问控制:"<<_access<<endl;
	}else if(cmp("Local",_access)==0)
	{
			cout<<"访问控制:"<<_access<<endl;
	}else
	{
			cout<<"不在已有的访问权内！"<<endl;
	}
}

};

int main()
{
	int fIsStatic=2,fIsArray=16;
	bool  isAutoVarArray(Variable var);

//	Student S1("康熙",2,7);
//	S1.display();

//Variable v1("Local",16,0,16);//是自由变量F    F1F2F3F4  
//	Variable v1("Local",2,2,16);//不是自由变量T 
//Variable v1("Global",2,2,0);//不是自由变量  F1T2T3T4
Variable v1("Public",2,2,0);//不是自由变量  F1T2T3T4
//Variable v1;
	v1.display();

 if(isAutoVarArray(v1))
 {
	    cout<<"isAutoVarArray():"<<isAutoVarArray(v1)<<endl;//真1假0
 
	 	cout<<"经输入的数据判断是自动变量数组"<<endl;
 
 }else{
	 cout<<"isAutoVarArray():"<<isAutoVarArray(v1)<<endl;//真1假0
	 	cout<<"经输入的数据判断不是自动变量数组"<<endl;

 }
  Sleep(2000);
  exit(0);
return 0;
}
	
bool  isAutoVarArray( Variable p)
{
      Variable *var=&p; 
	   cout<<"!var:"<<!var<<endl;
	 if (!var || !var->isLocal()|| var->isStatic() || !var->isArray())
	 return false;
 return true;

}