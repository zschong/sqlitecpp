#ifndef __XSTRING_H__
#define __XSTRING_H__
#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string>
using namespace std;

class xstring : public string
{
public:
	string& operator()() 
	{
		return (*(string*)this);
	}
    xstring& operator=(const xstring& xs)
    {
		(*(string*)this) = xs.data();
        return *this;
    }
public:
    xstring(){}
    xstring(const string& s)
    {
        (*(string*)this) = s;
    }
    xstring(const xstring& xs)
    {
        (*(string*)this) = xs;
    }
	xstring(const char* fmt,...)
	{
		int len = -1;

		if( fmt )
		{
			va_list ap;
			char buf[32*1024];
			va_start(ap, fmt);
			len = vsprintf(buf, fmt, ap);
			if( len > 0 )
			{
				if( len >= sizeof(buf) )
				{
					len = sizeof(buf) - 1;
				}
				buf[len] = 0;
				(*(string*)this) = buf;
			}
			va_end(ap);
		}
	}
public:
	const string& tostring() const
	{
		return *(string*)this;
	}
	int format(const char* fmt,...)	
	{
		int len = -1;

		if( fmt )
		{
			va_list ap;
			char buf[32*1024];
			va_start(ap, fmt);
			len = vsprintf(buf, fmt, ap);
			if( len > 0 )
			{
				if( len >= sizeof(buf) )
				{
					len = sizeof(buf) - 1;
				}
				buf[len] = 0;
				(*(string*)this) = buf;
			}
			va_end(ap);
		}
		return len;
	}
public:
	float tofloat() const
	{
		if( this->empty() )
			return 0.0000;
		return strtof(data(),NULL);
	}
	double todouble () const
	{
		if( this->empty() )
			return 0.0000;
		return strtod(data(),NULL);
	}
	int toint() const
	{
		if( this->empty() )
			return int(0);
		return atoi(data());
	}
	int tohex() const
	{
		if( this->empty() )
			return int(0);
		return strtol(data(), 0, 16);
	}
    bool toboolean() const
    {
        if( "TRUE" == (*(string*)this) )
            return true;
        if( "true" == (*(string*)this) )
            return true;
        return false;
    }
    time_t todaytime() const
    {
		if( false == empty() )
		{
			struct tm t = {0};
			if( !strptime(data(), "%H:%M:%S", &t) )
			{
				return time_t(-1);
			}
			return (t.tm_hour*3600+t.tm_min*60+t.tm_sec);
		}
		return time_t(-1);
    }
    time_t todatetime() const
    {
		if( false == empty() )
		{
			struct tm t = {0};
			if( !strptime(data(), "%Y-%m-%d", &t) )
			{
				return time_t(0);
			}
			return mktime(&t);
		}
		return time_t(0);
    }
	xstring& timeformat(const char *fmt, const time_t t)
	{
		if( fmt )
		{
			struct tm dtime = {0};
			if( localtime_r(&t, &dtime) )
			{
				char buf[64] = {0};
				strftime(buf, sizeof(buf), fmt, &dtime);
				(*this) = buf;
			}
		}
		return (*this);
	}
};

#endif//__XSTRING_H__
