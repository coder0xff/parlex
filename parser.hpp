#ifndef PARSER_HPP
#define PARSER_HPP

#include <thread>
#include <condition_variable>
#include <queue>

#include "abstract_syntax_graph.hpp"
#include "grammar.hpp"

namespace parlex {
namespace details {

class job;
class subjob;
struct parse_context;

}

class parser {
public:
	parser(int thread_count = std::thread::hardware_concurrency());
	~parser();
	abstract_syntax_graph parse(grammar const & g, std::u32string const & document);
private:
	std::mutex mutex;
	std::condition_variable halt_cv;	
	int activeCount;
	bool terminating;

	std::vector<std::thread> workers;
	std::queue<std::pair<details::parse_context, details::match_class>> work;
	std::condition_variable work_cv;

	void schedule(details::parse_context const & context, details::match_class const & matchClass);
	bool handle_deadlocks_check_completion();
	abstract_syntax_graph construct_result(details::job const & j, details::match_class const & matchClass);
};

}

#endif