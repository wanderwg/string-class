string��Ĵ�ͳ��д�� 
#include <assert.h>
#include <string.h>
class String
{
public:
	String(const char* str = "")
	{
		//����string�����ʱ���������nullptrָ�룬��Ϊ����Ƿ����˴�����
		if (str == nullptr) {
			assert(false);
			return;
		}
		_str = new char[strlen((str)+1)];
		strcpy(_str, str);
	}

	String(const String& s)
		:_str(new char[strlen(s._str) + 1])
	{
		strcpy(_str, s._str);
	}

	String& operator=(const String& s)
	{
		if (&s != this) {
			char* pStr = new char[strlen(s._str) + 1];
			strcpy(pStr, s._str);
			delete[] _str;
			_str = pStr;
		}
		return *this;
	}

	~String()
	{
		if (_str) {
			delete[] _str;
			_str = nullptr;
		}
	}
private:
	char* _str;
};
�ִ���д����
class String
{
public:
	String(const char* str = "")
	{
		if (str == nullptr) {
			str = "";
		}
		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
	}
	String(const String& s)
		:_str(nullptr)
	{
		String strTmp(s._str);//����s����һ����ʱ���󣬴˶��������Դ
		swap(_str, strTmp);//�����������_str������_str�õ������Դ���������ʱ����õ�nullptr
	}

	String& operator=(String s)
	{
		//�ڴ�ͳ�ĸ�ֵ�У������������һ����������ã��˴�ʹ����ֱ�Ӵ�ֵ�İ취
		//�ڴ����õ�ʱ������Ҳ��Ҫ����this!=&s���жϣ���ʱ��ֵ��һ������Ҫ�ⲽ�ж�
		//�Ҵ�����ʱ���������swap�ķ��������ǻ�����ʱ����һ����������ɡ�
		//�����ֱ�Ӵ�ֵ������֪����ʵ�ֵ�ʱ�������Զ����ô�������ֵ����һ����ʱ����
		//���ǾͿ���ֱ��ʹ��s._str�ˣ��ǳ�����
		swap(_str, s._str);
		return *this;
	}

	~String()
	{
		if (_str) {
			delete[] _str;
			_str = nullptr;
		}
	}
private:
	char* _str;
};