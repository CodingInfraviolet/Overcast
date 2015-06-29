#include "stdafx.h"
#include "System.h"

std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

void Error(std::string err)
{
	MessageBox(systemptr->hwnd(), (std::wstring(L"Error: ") + converter.from_bytes(err)).c_str(), L"Error", MB_OK | MB_ICONERROR);
}

void Warning(std::string err)
{
	MessageBox(systemptr->hwnd(), (std::wstring(L"Warning: ") + converter.from_bytes(err)).c_str(), L"Warning", MB_OK | MB_ICONWARNING);
}

void Inform(std::string inf)
{
	std::cout << ":- " << inf << "\n";
}

void ErrorSafe(std::string err)
{
	std::cout << "ERROR: " << err << "\n";
}


std::string FormatDebugOutputARB(size_t, GLenum source, GLenum type, GLuint id, GLenum severity, const char *msg)
{
	char sourceStr[32];
	const char *sourceFmt = "UNDEFINED(0x%04X)";
	switch (source)
	{
	case GL_DEBUG_SOURCE_API_ARB: sourceFmt = "API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB: sourceFmt = "WINDOW_SYSTEM"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER_ARB: sourceFmt = "SHADER_COMPILER"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY_ARB: sourceFmt = "THIRD_PARTY"; break;
	case GL_DEBUG_SOURCE_APPLICATION_ARB: sourceFmt = "APPLICATION"; break;
	case GL_DEBUG_SOURCE_OTHER_ARB: sourceFmt = "OTHER"; break;
	}
	_snprintf(sourceStr, 32, sourceFmt, source);
	char typeStr[32];
	const char *typeFmt = "UNDEFINED(0x%04X)";
	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR_ARB: typeFmt = "ERROR"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB: typeFmt = "DEPRECATED_BEHAVIOR"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB: typeFmt = "UNDEFINED_BEHAVIOR"; break;
	case GL_DEBUG_TYPE_PORTABILITY_ARB: typeFmt = "PORTABILITY"; break;
	case GL_DEBUG_TYPE_PERFORMANCE_ARB: typeFmt = "PERFORMANCE"; break;
	case GL_DEBUG_TYPE_OTHER_ARB: typeFmt = "OTHER"; break;
	}
	_snprintf(typeStr, 32, typeFmt, type);

	const char *severityFmt = "UNDEFINED";
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH_ARB: severityFmt = "HIGH"; break;
	case GL_DEBUG_SEVERITY_MEDIUM_ARB: severityFmt = "MEDIUM"; break;
	case GL_DEBUG_SEVERITY_LOW_ARB: severityFmt = "LOW"; break;
	}
	std::string out;
	if (id!=131185) //Filter out useless information
		out = std::string("OpenGL: ") + msg + " [source=" + sourceFmt + " type=" + typeFmt + " severity=" + severityFmt +
		" id=" + toString(id) + "]";

	return out;
}

void _stdcall debugCallbackARB(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei, const GLchar *message, GLvoid*)
{
	std::string messageF = FormatDebugOutputARB(256, source, type, id, severity, message);
	if (messageF.size()!=0)
		Inform(messageF);
}