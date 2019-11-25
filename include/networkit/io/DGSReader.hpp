/*
 * DGSReader.h
 *
 *  Created on: 01.06.2013
 *      Author: cls
 */

#ifndef NETWORKIT_IO_DGS_READER_HPP_
#define NETWORKIT_IO_DGS_READER_HPP_

#include <fstream>

#include <networkit/io/DynamicGraphReader.hpp>

#include <string>
#include <unordered_map>

#include <networkit/dynamics/GraphEventProxy.hpp>
#include <networkit/auxiliary/StringTools.hpp>

namespace NetworKit {

/**
 * @ingroup io
 * DGS is a file format allowing to store graphs and dynamic graphs in a textual human readable way,
 * yet with a small size allowing to store large graphs. Graph dynamics is defined using events like
 * adding, deleting or changing a node or edge. With DGS, graphs will therefore be seen as stream of
 *  such events.
 *
 * Format documentation: http://graphstream-project.org/doc/Advanced-Concepts/The-DGS-File-Format/
 *
 */
class DGSReader: public DynamicGraphReader {

public:
    
    /**
     * @param[in]	path	Path to file in DGS format.
     * @param[in]	Gproxy	Graph event proxy receives the events from the file.
     */
    virtual void read(std::string path, GraphEventProxy& Gproxy);
};

} /* namespace NetworKit */
#endif // NETWORKIT_IO_DGS_READER_HPP_
