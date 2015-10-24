#include <queue>

#include "abstract_syntax_graph.hpp"
#include "recognizer.hpp"

std::string parlex::abstract_syntax_graph::to_dot() const {
	std::string result = "digraph {\n";
	std::set<details::match> completed;
	std::queue<details::match> pending;
	pending.push(root);
	while (pending.size()) {
		details::match i = pending.front();
		pending.pop();
		completed.insert(i);
		std::string from_name = i.match_class.r.get_id() + ":" + std::to_string(i.match_class.document_position) + ":" + std::to_string(i.consumed_character_count);
		auto l = table.find(i);
		if (l == table.end()) {
			result += "\t# " + from_name + " was not found";
			continue;
		}
		for (permutation const & j : l->second) {
			for (details::match const & k : j) {
				std::string to_name = k.match_class.r.get_id() + ":" + std::to_string(k.match_class.document_position) + ":" + std::to_string(k.consumed_character_count);
				result += "\t\"" + from_name + "\" -> \"" + to_name + "\"\n";				
				if (completed.count(k) == 0) {
					pending.push(k);
				}
			}
		}
	}
	result += "}";
	return result;
}