#ifndef _STRING_HPP
#define _STRING_HPP
namespace fenrir {
	class string {
	private:
		char* mString;
	public:
		string(const char* str);
		string& operator+=(const string& rh);
		const char* c_str() { return mString; }
		~string();
	};
}
#endif // _STRING_HPP
