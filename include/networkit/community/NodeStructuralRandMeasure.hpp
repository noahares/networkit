/*
 * RandMeasure.h
 *
 *  Created on: 19.01.2013
 *      Author: Christian Staudt (christian.staudt@kit.edu)
 */

#ifndef NETWORKIT_COMMUNITY_NODE_STRUCTURAL_RAND_MEASURE_HPP_
#define NETWORKIT_COMMUNITY_NODE_STRUCTURAL_RAND_MEASURE_HPP_

#include <networkit/community/DissimilarityMeasure.hpp>

namespace NetworKit {

/**
 * @ingroup community
 * The node-structural Rand measure assigns a similarity value in [0,1]
 * to two partitions of a graph, by considering all pairs of nodes.
 */
class NodeStructuralRandMeasure: public DissimilarityMeasure {

public:


    virtual double getDissimilarity(const Graph &G, const Partition &zeta, const Partition &eta);

};

} /* namespace NetworKit */
#endif // NETWORKIT_COMMUNITY_NODE_STRUCTURAL_RAND_MEASURE_HPP_
