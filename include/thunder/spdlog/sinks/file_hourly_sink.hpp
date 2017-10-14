#include <mutex>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/sink.h>
#include <spdlog/sinks/base_sink.h>
#include <spdlog/sinks/file_sinks.h>
#include <spdlog/details/null_mutex.h>

namespace thunder {
namespace sinks {
	/*
	* Rotating file sink based on hour. rotates every hour
	*/
	template<class Mutex, class FileNameCalc = spdlog::sinks::default_daily_file_name_calculator>
	class hourly_file_sink : public spdlog::sinks::base_sink<Mutex>
	{
	public:
		//create hourly file sink which rotates on given time
		hourly_file_sink(const spdlog::filename_t& base_filename)
			: _base_filename(base_filename), _file_helper()
		{
			_rotation_tp = _next_rotation_tp();
			_file_helper.open(FileNameCalc::calc_filename(_base_filename));
		}

	protected:
		void _sink_it(const spdlog::details::log_msg& msg) override final
		{
			if (std::chrono::system_clock::now() >= _rotation_tp)
			{
				_file_helper.open(FileNameCalc::calc_filename(_base_filename));
				_rotation_tp = _next_rotation_tp();
			}
			_file_helper.write(msg);
		}

		void _flush() override final
		{
			_file_helper.flush();
		}

	private:
		std::chrono::system_clock::time_point _next_rotation_tp()
		{
			using namespace std::chrono;
			auto now = system_clock::now();
			now += hours(1);
			time_t tnow = std::chrono::system_clock::to_time_t(now);
			tm date = spdlog::details::os::localtime(tnow);
			date.tm_min = 0;
			date.tm_sec = 0;
			auto rotation_time = std::chrono::system_clock::from_time_t(std::mktime(&date));
			return rotation_time;
		}

		spdlog::filename_t _base_filename;
		std::chrono::system_clock::time_point _rotation_tp;
		spdlog::details::file_helper _file_helper;
	};

	typedef hourly_file_sink<std::mutex> hourly_file_sink_mt;
	typedef hourly_file_sink<spdlog::details::null_mutex> hourly_file_sink_st;
};
};
