string类的传统版写法 
#include <assert.h>
#include <string.h>
class String
{
public:
	String(const char* str = "")
	{
		//构造string类对象时，如果传递nullptr指针，认为程序非法，此处断言
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
现代版写法：
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
		String strTmp(s._str);//根据s创建一个临时对象，此对象具有资源
		swap(_str, strTmp);//将这个对象与_str交换，_str拿到这个资源，而这个临时对象得到nullptr
	}

	String& operator=(String s)
	{
		//在传统的赋值中，参数传入的是一个对象的引用，此处使用了直接传值的办法
		//在传引用的时候，我们也需要进行this!=&s的判断，此时传值，一定不需要这步判断
		//且传引用时，如果采用swap的方法，我们还需临时创建一个对象，来完成。
		//但如果直接传值，我们知道在实现的时候，它会自动利用传过来的值创建一个临时对象
		//我们就可以直接使用s._str了，非常巧妙
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