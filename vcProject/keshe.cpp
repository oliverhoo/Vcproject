#include<iostream>
#include<string>
//#include <unistd.h>  //header file with sleep function
#include<windows.h> 
using namespace std;
enum AccessControl { Public, Protected, Private, Global, Namespace, Argument, Local };//��Ҫ���ʿ���ö��,Argument, Local/�������ֲ�
/*enum {
        fIsMutable  = (1 << 0), /** @brief mutable variable  ���ݵĿɱ����
        fIsStatic   = (1 << 1), /** @brief static variable  ���ݵľ�̬����/2
        fIsConst    = (1 << 2), /** @brief const variable ���ݵĳ�������/4
        fIsClass    = (1 << 3), /** @brief user defined type  ���ݵ��û���������/8
        fIsArray    = (1 << 4), /** @brief array variable ���ݵ��������/16
        fIsPointer  = (1 << 5), /** @brief pointer variable ���ݵ�ָ�����/32
        fHasDefault = (1 << 6)  /** @brief function argument with default value����Ĭ��ֵ�ļ�̺������� /64
    };
*/
/** @brief what section is this variable declared in? */
   // AccessControl _access;  // public/protected/private

/**
     * Is variable static.�ǿɱ侲̬��
     * @return true if static, false if not����Ǿ�̬�ĵķ����棬���򷵻ؼ�
     */
class Variable {
	public:
    /** @brief what section is this variable declared in? ��Ҫ˵������������ĸ����֣�*/
    char*  _access;  // public/protected/private
    /** @brief flags ��Ҫ���*/
    int _flags;//���
	int fIsStatic;//��̬����
	int fIsArray;//����
	public: Variable(char* a,int x,int y,int z)
	{
		_access=a;//
		_flags=x;//_flagΪ��Ҫ��ǣ�Ҫ��������������"��"����
		fIsStatic=y;//2
		fIsArray=z;//16
	//cout<<a<<endl;
    //	cout<<_access<<endl;
	}
	public: Variable()
	{
	
	}

/**
     * Is variable local. //�Ǿֲ�����
     * @return true if local, false if not//����Ǿֲ��ķ����棬���򷵻ؼ�
     */
  bool isLocal()  {
       // return _access == Local;
		if(cmp("Local",_access)==0)
			return true;//��1
		return false;//��0
		
    }
    
 /**
     * Get specified flag state.
     * @param flag_ flag to get state of
     * @return true if flag set or false in flag not set
     */
    bool getFlag(int flag_) const {
        return bool((_flags & flag_) != 0);
		/*
		&�ǰ�λ�룬&&���߼��롣
		ǰ�ߣ������Ķ�Ӧλ�϶�Ϊ1ʱ���Ϊ1��������Ϊ0��
		���ߣ�����������Ϊ0ʱ���Ϊ1(true)��������Ϊ0(false)��
      ǰ���磺10101100 & 01110110=00100100��
      �����磺3 && 1=1��3 && 0=0��0 && 3=0��0 && 0=0��
		*/
    }
    bool isStatic() const {
        return getFlag(fIsStatic);//fIsStatic = (1 << 1), /** @brief static variable  ���ݵľ�̬����*/
    }
	 /**
     * Is variable an array.
     * @return true if array, false if not
     */
    bool isArray() const {
        return getFlag(fIsArray);//fIsArray= = (1 << 4), /** @brief array variable ���ݵ��������*/
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
  cout<<"isLocal():"<<isLocal()<<endl;//��1��0
  cout<<"isStatic():"<<isStatic()<<endl;//��1��0
  cout<<"isArray():"<<isArray()<<endl;//��1��0
 

	if(cmp("Public",_access)==0){
			cout<<"���ʿ���:"<<_access<<endl;
	}else if(cmp("Protected",_access)==0)
	{
			cout<<"���ʿ���:"<<_access<<endl;
	}else if(cmp("Private",_access)==0)
	{
			cout<<"���ʿ���:"<<_access<<endl;
	}else if(cmp("Global",_access)==0)
	{
		cout<<"���ʿ���:"<<_access<<endl;
	}else if(cmp("Namespace",_access)==0)
	{
			cout<<"���ʿ���:"<<_access<<endl;
	}else if(cmp("Argument",_access)==0)
	{
			cout<<"���ʿ���:"<<_access<<endl;
	}else if(cmp("Local",_access)==0)
	{
			cout<<"���ʿ���:"<<_access<<endl;
	}else
	{
			cout<<"�������еķ���Ȩ�ڣ�"<<endl;
	}
}

};

int main()
{
	int fIsStatic=2,fIsArray=16;
	bool  isAutoVarArray(Variable var);

//	Student S1("����",2,7);
//	S1.display();

//Variable v1("Local",16,0,16);//�����ɱ���F    F1F2F3F4  
//	Variable v1("Local",2,2,16);//�������ɱ���T 
//Variable v1("Global",2,2,0);//�������ɱ���  F1T2T3T4
Variable v1("Public",2,2,0);//�������ɱ���  F1T2T3T4
//Variable v1;
	v1.display();

 if(isAutoVarArray(v1))
 {
	    cout<<"isAutoVarArray():"<<isAutoVarArray(v1)<<endl;//��1��0
 
	 	cout<<"������������ж����Զ���������"<<endl;
 
 }else{
	 cout<<"isAutoVarArray():"<<isAutoVarArray(v1)<<endl;//��1��0
	 	cout<<"������������жϲ����Զ���������"<<endl;

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