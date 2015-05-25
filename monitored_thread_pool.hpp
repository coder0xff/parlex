#ifndef MONITORED_THREAD_POOL_HPP
#define MONITORED_THREAD_POOL_HPP

#include <functional>
#include <atomic>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

namespace parlex {

class monitored_thread_pool {
public:
	monitored_thread_pool(std::function<void()> const & onIdle);
	~monitored_thread_pool();
	void schedule(std::function<void ()> const & callback);
private:
	std::function<void ()> on_idle;
	std::atomic<int> activeCount;
	std::vector<std::thread> workers;
	std::queue<std::function<void ()>> work;
	std::mutex mutex;
	std::condition_variable cv;
	std::atomic<bool> terminating;
};

}

#endif