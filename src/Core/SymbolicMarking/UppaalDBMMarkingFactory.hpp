#ifndef UPPAALDBMMARKINGFACTORY_HPP_
#define UPPAALDBMMARKINGFACTORY_HPP_

#include "MarkingFactory.hpp"
#include "DBMMarking.hpp"
#include "dbm/print.h"
#include <stdexcept>

namespace VerifyTAPN {

	class UppaalDBMMarkingFactory : public MarkingFactory {
	protected:
		static id_type nextId;
	public:
		UppaalDBMMarkingFactory(const TAPN::TimedArcPetriNet* tapn)
		{
			DBMMarking::tapn = tapn;
		};
		virtual ~UppaalDBMMarkingFactory() {};

		virtual SymbolicMarking* InitialMarking(const std::vector<int>& tokenPlacement, const std::vector<int>& tokenAges) const
		{
			if (tokenAges.size() > tokenPlacement.size()) {
				throw std::invalid_argument("More token ages than token placements");
            }

			for (int age : tokenAges) {
				if (age < 0 || age >= dbm_INFINITY) {
					throw std::out_of_range("Initial token age exceeds the supported DBM bound");
                }
            }

			dbm::dbm_t dbm(tokenPlacement.size()+1);
			dbm.setZero();
			for (size_t i = 0; i < tokenAges.size(); ++i) {
				if (tokenAges[i] != 0) {
					dbm(i + 1) = tokenAges[i];
				}
			}
            
			DBMMarking* marking = new DBMMarking(DiscretePart(tokenPlacement), dbm);
			marking->id = 0;
			return marking;
		};

		virtual SymbolicMarking* Clone(const SymbolicMarking& marking) const
		{
			DBMMarking* clone = new DBMMarking(static_cast<const DBMMarking&>(marking));
			clone->id = nextId++;
			return clone;
		};

		virtual StoredMarking* Convert(SymbolicMarking* marking) const { return static_cast<DBMMarking*>(marking); };
		virtual SymbolicMarking* Convert(StoredMarking* marking) const { return static_cast<DBMMarking*>(marking); };

		virtual void Release(SymbolicMarking* marking)
		{

		};

		virtual void Release(StoredMarking* marking)
		{
			delete marking;
		};
	};

}

#endif /* UPPAALDBMMARKINGFACTORY_HPP_ */
