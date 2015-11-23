#ifndef FILTER_HPP
#define FILTER_HPP

namespace parlex {
	class filter {
	protected:
		virtual void on_submit(subjob & sj, permutation const & p) = 0;
		virtual void on_flush(subjob & sj) = 0;
		void accept(subjob & sj, permutation const & p);
	};
}

#endif