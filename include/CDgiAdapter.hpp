///////////////////////////////////////////////////////////////////////////////
/// @file         CDgiAdapter.hpp
///
/// @author       Thomas Roth <tprfh7@mst.edu>, Manish Jaisinghani <mjkhf@mst.edu>
///
/// @project      FREEDM DGI
///
/// @description  Adapter for the DGI interfacing.
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

#ifndef C_ADAPTER_DGI_HPP
#define C_ADAPTER_DGI_HPP

#include "IServer.hpp"
#include "CAdapter.hpp"

#include <boost/property_tree/ptree_fwd.hpp>

namespace freedm {
    namespace simulation {
        namespace adapter {

/// DGI interface adapter that handles messages from the DGI to the device server
/////////////////////////////////////////////////////////////////////////////////
/// The DGI adapter sends opendss updates to the DGI and receives commands from
/// from the DGI.
/// @limitations: subject to improvement.
/////////////////////////////////////////////////////////////////////////////////
            class CDgiAdapter
                    : public IServer
                            , public CAdapter
            {
            public:
                /// constructs a dgi adapter instance
                CDgiAdapter( unsigned short port,
                                    const boost::property_tree::ptree & tree );
            private:
                /// handles the accepted socket connection
                virtual void HandleConnection();
                /// sends commands to opendss application
                void SendCommands(std::string command);
                /// gets commands from dgi
                void GetExternalCommand();
            public:
                /// buffer size in bytes of the simulation packet
                static const unsigned int BUFFER_SIZE = 1024;
                /// socket desciptor and int n for error handling
                unsigned int sd,n;
                //carries data received or data to be sent
                char buffer[BUFFER_SIZE];
                /// shared opendss data variable
                static std::string commands;
                //gets saved commands
                static std::string GetData();
            };

        } // namespace adapter
    } // namespace simulation
} // namespace freedm

#endif // C_ADAPTER_SIMULATION_HPP
