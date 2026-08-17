#ifndef RANDOMSEARCH_HPP_
#define RANDOMSEARCH_HPP_

#include "SearchStrategy.hpp"
#include "../PassedWaitingList/PriorityQueueWaitingList.hpp"
#include "../PassedWaitingList/Node.hpp"

namespace VerifyTAPN
{
	struct Random : public std::unary_function<Node*, int>
	{
		int operator()(const Node* node) const
		{
			return rand() % 1000;
		}
	};

	class RandomSearch : public DefaultSearchStrategy
	{
	public:
		RandomSearch(
			const VerifyTAPN::TAPN::TimedArcPetriNet& tapn,
			SymbolicMarking* initialMarking,
			const AST::Query* query,
			const VerificationOptions& options,
			MarkingFactory* factory,
			const std::vector<int>& initialAges
		) : DefaultSearchStrategy(tapn, initialMarking, query, options, factory, initialAges) { };

	protected:
		virtual WaitingList* CreateWaitingList() const { return new PriorityQueueWaitingList<Random>; };
	};

}

#endif /* RANDOMSEARCH_HPP_ */
