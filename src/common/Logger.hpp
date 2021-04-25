#pragma once

#include <stdexcept>
#include <string>
#include <atomic>
#include <string_view>

#include <cstdint>

#include "Singletone.hpp"
#include "LoggerMessage.hpp"
#include "Pool.hpp"
#include "StringFormer.hpp"


//#define ENABLE_DEBUG

#ifdef ENABLE_DEBUG
#include <cstdio>
#define DEBUG(FMT, ...) fprintf(stderr,\
	"LOG [" __FILE__ ":%d]: " FMT "\n", __LINE__ __VA_OPT__(,) __VA_ARGS__)
#else
#define DEBUG(FMT, ...)
#endif


constexpr char const* short_filename(char const* fname)
{
	std::string_view fname_sv {fname};
	size_t p = fname_sv.rfind('/');
	return (p != std::string_view::npos)
		? fname_sv.substr(p + 1).data()
		: fname_sv.data();
}


#define LOG_E(FMT, ...)  Logger::RefInstance().LogErr(short_filename(__FILE__), __LINE__, FMT __VA_OPT__(,) __VA_ARGS__)
#define LOG_W(FMT, ...)  Logger::RefInstance().LogWrn(short_filename(__FILE__), __LINE__, FMT __VA_OPT__(,) __VA_ARGS__)
#define LOG_I(FMT, ...)  Logger::RefInstance().LogInf(short_filename(__FILE__), __LINE__, FMT __VA_OPT__(,) __VA_ARGS__)
#define LOG_D(FMT, ...)  Logger::RefInstance().LogDbg(short_filename(__FILE__), __LINE__, FMT __VA_OPT__(,) __VA_ARGS__)
#define LOG_SV(sv) (int)sv.size(), sv.data()

#define THROW_ERROR(FMT, ...) \
	do { \
		LOG_E("{THROW_ERROR} " FMT, __VA_ARGS__); \
		constexpr std::size_t MAX_SIZE = 256; \
		char buffer[MAX_SIZE]; \
		throw std::runtime_error( \
			StringFormer(buffer, MAX_SIZE)(FMT, __VA_ARGS__) \
			.c_str()); \
	} while(false)



class Logger : public SingletoneThreadLocal<Logger>
{
public:
	enum class log_level_e : uint8_t
	{
		DEBUG,
		INFO,
		WARNING,
		ERROR,
	};

	Logger();
	~Logger();

	void LogErr(char const* filename, std::size_t line, char const* fmt, ...);
	void LogWrn(char const* filename, std::size_t line, char const* fmt, ...);
	void LogInf(char const* filename, std::size_t line, char const* fmt, ...);
	void LogDbg(char const* filename, std::size_t line, char const* fmt, ...);

private:
	void LogMessage(
		log_level_e    lvl,
		char const*    filename,
		std::size_t    line_n,
		char const*    fmt,
		va_list        vlist);

private:
	static constexpr std::size_t INIT_POOL_SIZE = 64;
	static constexpr std::size_t INC_POOL_SIZE  = 32;

	Pool<LoggerMessage>&   m_pool;
	std::string            m_thread_id;

private:
	static std::atomic_uint32_t m_counter;
};

char const* toString(Logger::log_level_e);

