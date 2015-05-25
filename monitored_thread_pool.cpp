#include "monitored_thread_pool.hpp"

namespace parlex {

monitored_thread_pool::monitored_thread_pool(std::function<void ()> const & onIdle) : on_idle(onIdle) {
	for (int i = std::thread::hardware_concurrency(); i > 0; --i) {
		workers.emplace_back([=]() {
			std::unique_lock<std::mutex> lock(mutex);
			goto wait;			
			while (!terminating) {
				{
					auto item = work.front();
					work.pop();
					lock.unlock();
					item();
					if (--activeCount == 0) {
						on_idle();
					}
					lock.lock();
				}
wait:
				cv.wait(lock, [this]() { return work.size() > 0 && !terminating; });
			}
		});
	}
}

monitored_thread_pool::~monitored_thread_pool() {
	terminating = true;
	cv.notify_all();
	for (auto & thread : workers) {
		thread.join();
	}
}

void monitored_thread_pool::schedule(std::function<void ()> const & item) {	
	std::unique_lock<std::mutex> lock(mutex);
	activeCount++;
	work.push(item);
	cv.notify_one();
}

}