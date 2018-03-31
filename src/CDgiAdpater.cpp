///////////////////////////////////////////////////////////////////////////////////
/// @file         CDgiAdapter.cpp
///
/// @author       Thomas Roth <tprfh7@mst.edu>, Manish Jaisinghani <mjkhf@mst.edu>
///
/// @project      FREEDM DGI
///
/// @description  Adapter for DGI interfacing with device server.
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
///////////////////////////////////////////////////////////////////////////////

#include "CDgiAdapter.hpp"
#include "CTableManager.hpp"
#include "COpendssAdapter.hpp"
#include "DeviceTable.hpp"
#include <vector>
#include <cstring>
#include <cstddef>
#include <boost/asio.hpp>

namespace freedm {
    namespace simulation {
        namespace adapter {

            namespace // unnamed
            {
                /// local logger for this file
                CLocalLogger Logger(__FILE__);
            }

///////////////////////////////////////////////////////////////////////////////
/// Calls its base class constructors on the given arguments.
/// @pre See IServer::IServer() and CAdapter::CAdapter().
/// @post Initializes the IServer and CAdapter base classes.
/// @param port The port number to use for the server.
/// @param tree The property tree specification of the adapter.
/// @limitations subject to improvement
///////////////////////////////////////////////////////////////////////////////
            CDgiAdapter::CDgiAdapter( unsigned short port,
                                                    const boost::property_tree::ptree & tree )
                    : IServer(port)
                    , CAdapter(tree)
            {
                Logger.Trace << __PRETTY_FUNCTION__ << std::endl;
            }

            std::string CDgiAdapter::commands ="";
            unsigned int CDgiAdapter::sd = -1,CDgiAdapter::n = -1;
            char CDgiAdapter::buffer[CDgiAdapter::BUFFER_SIZE] = "";
///////////////////////////////////////////////////////////////////////////////
/// Handles connection to openDSS application python socket.
/// @Peers Communicates through socket connection to the IServer client.
/// @ErrorHandling If socket connection is refused or lost before any data is
/// received, error is thrown.
/// @limitations None.
///////////////////////////////////////////////////////////////////////////////
            void CDgiAdapter::HandleConnection()
            {
                Logger.Trace << __PRETTY_FUNCTION__ << std::endl;

                sd = m_socket.native();
                bzero(buffer,BUFFER_SIZE-1);
                Logger.Status<<"DGI is connected"<<std::endl;

               if(COpendssAdapter::GetData().size()>0) {
                   strcpy(buffer, COpendssAdapter::GetData().c_str());
                    if(!(write(sd,buffer,BUFFER_SIZE-1))){
                        Logger.Error<<"Socket write failed!!!";
                    }
                    Logger.Status<<"Data sent to DGI: "<< buffer<<std::endl;
               }

                bzero(buffer,BUFFER_SIZE-1);
                if(!(read(sd,buffer,BUFFER_SIZE-1))){
                    Logger.Error<<"Socket read failed!!!";
                }

                Logger.Status<<"dgi commands: "<< buffer<<std::endl;
                commands =   buffer;
                Logger.Status<<"Opendss commands stored: "<<commands<<std::endl;
                
            }

///////////////////////////////////////////////////////////////////////////////
/// gets DGI commands
/// @limitations None.
///////////////////////////////////////////////////////////////////////////////
            std::string CDgiAdapter::GetData(){
                return commands;
            }
///////////////////////////////////////////////////////////////////////////////
/// writes commands from DGI to opendss socket
/// @pre The client must send the amount of data held in commands.
/// @limitations None.
///////////////////////////////////////////////////////////////////////////////

            void CDgiAdapter::SendCommands(std::string command, unsigned int sd)
            {
                if(!command.empty()){
                    bzero(buffer,BUFFER_SIZE);
                    strcpy(buffer,command.c_str());
                    if(!(write(sd,buffer,BUFFER_SIZE-1))){
                        Logger.Error<<"Socket write failed!!!";
                    }
                }
            }
///////////////////////////////////////////////////////////////////////////////
/// Reads the command table and writes the content back to the client.
/// @Peers Communicates through socket connection to the IServer client.
/// @Peers Acquires a shared read lock on the command table.
/// @pre None.
/// @post A read lock is acquired on the command table.
/// @post Writes to the socket the information specified in the XML file.
/// @limitations None.
///////////////////////////////////////////////////////////////////////////////
            void CDgiAdapter::GetExternalCommand()
            {

            }

        } // namespace adapter
    } // namespace simulation
} // namespace freedm
