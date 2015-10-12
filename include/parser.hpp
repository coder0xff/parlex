#ifndef PARSER_HPP
#define PARSER_HPP

#include <thread>
#include <condition_variable>
#include <atomic>
#include <queue>

#include "abstract_syntax_graph.hpp"
#include "grammar.hpp"

namespace parlex {
namespace details {

class job;
class subjob;
class producer;
struct context;

}

class parser {
public:
	parser(int thread_count = std::thread::hardware_concurrency());
	~parser();
	abstract_syntax_graph parse(recognizer const & g, std::u32string const & document);
private:
	friend class details::job;
	friend class details::subjob;
	friend class details::producer;
	std::mutex mutex;
	std::condition_variable halt_cv;
	std::atomic<int> activeCount;
	bool terminating;

	std::vector<std::thread> workers;
	std::queue<std::tuple<details::context, int>> work;
	std::condition_variable work_cv;

	void schedule(details::context context, int nextDfaState);
	//returns true if the job is complete
	bool handle_deadlocks(details::job const & j);
	abstract_syntax_graph construct_result(details::job const & j, details::match const & match);
};

}

#endif
