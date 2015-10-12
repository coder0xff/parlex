#include "token.hpp"
#include "terminal.hpp"
#include "job.hpp"

namespace parlex {
namespace details {

token::token(job & owner, terminal const & t, int documentPosition) : producer(owner, t, documentPosition) { 
	if (t.test(owner.document, documentPosition)) {
		add_result(t.get_length(), std::vector<match>());		
	}

}

}
}