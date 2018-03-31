//////////////////////////////////////////////////////////////////////////////////
/// @file         COpendssAdapter.hpp
///
/// @author       Thomas Roth <tprfh7@mst.edu>, Manish Jaisinghani <mjkhf@mst.edu>
///
/// @project      FREEDM DGI
///
/// @description  Adapter for the Opendss power simulation
///
/// These source code files were created at Missouri University of Science and
/// Technology, and are intended for use in teaching or research. They may be
/// freely copied, modified, and redistributed as long as modified versions are
/// clearly marked as such and this notice is not removed. Neither the authors
/// nor Missouri S&T make any warranty, express or implied, nor assume any legal
/// responsibility for the accuracy, completeness, or usefulness of these files
/// or any information distributed with these files.
///
/// Suggested modifications or questions about these files can be directed to
/// Dr. Bruce McMillin, Department of Computer Science, Missouri University of
/// Science and Technology, Rolla, MO 65409 <ff@mst.edu>.
//////////////////////////////////////////////////////////////////////////////////

#ifndef C_ADAPTER_OPENDSS_HPP
#define C_ADAPTER_OPENDSS_HPP

#include "IServer.hpp"
#include "CAdapter.hpp"

#include <boost/property_tree/ptree_fwd.hpp>

namespace freedm {
    namespace simulation {
        namespace adapter {

/// Opendss adapter used for interfacing device server with opendss application
///////////////////////////////////////////////////////////////////////////////
/// The adapter expects a string of csv data from the opendss application. 
/// The adapter returns DGI commands to the opendss application if any.
/// @limitations subject to improvement.
///////////////////////////////////////////////////////////////////////////////
            class COpendssAdapter
                    : public IServer
                            , public CAdapter
            {
            public:
                /// constructs a simulation adapter instance
                COpendssAdapter( unsigned short port,
                                    const boost::property_tree::ptree & tree );
            private:
                /// handles the accepted socket connection
                virtual void HandleConnection();

                /// writes the command table data to the socket
                void GetExternalCommand();
            public:
                /// buffer size in bytes of the simulation packet
                static const unsigned int BUFFER_SIZE = 1024;
                /// socket desciptor and int n for error handling
                static unsigned int sd,n;
                //carries data received or data to be sent
                static char buffer[BUFFER_SIZE];
                /// shared opendss data variable
                static std::string opendssData;
                //gets saved opendss data
                static std::string GetData();
                //deletes data
                static void clearData();
                /// updates the state table with data read from the socket
                static void SendCommands(std::string command, unsigned int sd);
            };

        } // namespace adapter
    } // namespace simulation
} // namespace freedm

#endif // C_ADAPTER_SIMULATION_HPP
