#ifndef TRACESTORE_HPP_
#define TRACESTORE_HPP_


#include "boost/functional/hash.hpp"
#include "google/sparse_hash_map"
#include <deque>
#include "../../Core/VerificationOptions.hpp"
#include "../../typedefs.hpp"
#include "TraceInfo.hpp"
#include "../../Core/TAPN/TAPN.hpp"
#include "ConcreteMarking.hpp"

namespace VerifyTAPN
{
	class SymbolicMarking;

	inline ConcreteMarking CreateConcreteInitialMarking(SymbolicMarking* initialMarking, unsigned int kbound, const TAPN::TimedArcPetriNet& tapn, const std::vector<int>& initialAges)
	{
		std::deque<Token> tokens;
		for(unsigned int i = 0; i < initialMarking->NumberOfTokens(); i++)
		{
			decimal age = (i < initialAges.size()) ? decimal(initialAges[i]) : decimal(0);
			Token token(tapn.GetPlace(initialMarking->GetTokenPlacement(i)).GetName(), age);
			tokens.push_back(token);
		}

		for(unsigned int i = tokens.size(); i < kbound; i++)
		{
			tokens.push_back(Token(TAPN::TimedPlace::BOTTOM_NAME));

		}

		return ConcreteMarking(tokens);
	};

	class TraceStore
	{
	private:
		typedef google::sparse_hash_map<id_type, TraceInfo*, boost::hash<id_type> > HashMap;
	public:
	    TraceStore(const VerificationOptions & options, SymbolicMarking *initialMarking, const TAPN::TimedArcPetriNet & tapn, const std::vector<int>& initialAges)
	    : store(), initialMarking(CreateConcreteInitialMarking(initialMarking, options.GetKBound(), tapn, initialAges)), finalMarkingId(-1), lastInvariants(), options(options), identity_map(options.GetKBound(), -1), initialAges(initialAges)
	    {
	        for(unsigned int i = 0;i < static_cast<unsigned int>(options.GetKBound());++i){
	            identity_map[i] = i;
	        }
	    }

	    ;
	    ~TraceStore()
	    {
	    	for(HashMap::iterator it = store.begin(); it != store.end(); it++)
	    	{
	    		delete it->second;
	    	}
	    }

	    ;
	public:
	    inline void Save(const id_type & id, TraceInfo* traceInfo)
	    {
	        store.insert(std::pair<id_type,TraceInfo*>(id, traceInfo));
	    }

	    ;
	    inline void SetFinalMarkingIdAndInvariant(id_type id, std::vector<TraceInfo::Invariant> & inv)
	    {
	        finalMarkingId = id;
	        lastInvariants.swap(inv);
	    }

	    ;
	    void OutputTraceTo(const TAPN::TimedArcPetriNet & tapn) const;
	private:
	    void CalculateDelays(const std::deque<TraceInfo> & traceInfos, std::vector<decimal> & delays) const;
	    void ComputeIndexMappings(std::deque<TraceInfo> & traceInfos) const;
	    void AugmentSymmetricMappings(std::deque<TraceInfo> & traceInfos) const;
	    void OutputTraceInXmlFormat(ConcreteMarking& marking, const TAPN::TimedArcPetriNet& tapn, const std::deque<TraceInfo>& traceInfos, const std::vector<decimal>& delays) const;
	private:
	    HashMap store;
		ConcreteMarking initialMarking;
		id_type finalMarkingId;
		std::vector<TraceInfo::Invariant> lastInvariants;
		const VerificationOptions& options;

		std::vector<unsigned int> identity_map;
		const std::vector<int> initialAges;
	};
}

#endif /* TRACESTORE_HPP_ */
