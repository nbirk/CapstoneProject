/*-----------------------------------------------------------------------------
**
** Copyright:   Copyright 2016 Rockwell Collins.  All rights reserved.
**
** Source File:  main.cpp
**
** Description:
**
**    This file is an example of how to parse network log raw files.
**
**-----------------------------------------------------------------------------
*/

// system includes
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iomanip>

// protobuf lib includes
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>

// app includes
#include "PBNetStat.pb.h"

using namespace google::protobuf::io;
using namespace std;

bool printNLIptableStat(const NL_Message& message)
{
   // always good to validate inputs to a function, right?
   if(message.IsInitialized())
   {
      // loop through all the ipstat items in this message
	  cout << "\t\t\t\"DataItems\":[" << endl;
      for(int i = 0; i < message.ipstat_size(); i++)
      {
		  cout << "\t\t\t\t{" << endl;
         // see if this is a registration message or an update message
         if(message.ipstat(i).has_desc())
         {
			
			// this has a description so it's a registration message
			cout << "\t\t\t\t\t\"id\":" << "\"" << message.ipstat(i).ident() << "\"," << endl;
			cout << "\t\t\t\t\t\"chain\":" << "\"" << message.ipstat(i).chain() << "\"," << endl;
			cout << "\t\t\t\t\t\"description\":" << "\"" << message.ipstat(i).desc() << "\"" << endl;
		    
         }
         else if(message.ipstat(i).has_bytecount() && message.ipstat(i).has_packetcount())
         {
            // this has both byte and packet counts, so it's an update
			cout << "\t\t\t\t\t\"ID\":" << "\"" << message.ipstat(i).ident() << "\"," << endl;
			cout << "\t\t\t\t\t\"Chain\":" << "\"" << message.ipstat(i).chain() << "\"," << endl;
			cout << "\t\t\t\t\t\"Bytes\":" << "\"" << message.ipstat(i).bytecount() << "\"," << endl;
			cout << "\t\t\t\t\t\"Packets\":" << "\"" << message.ipstat(i).packetcount() << "\"" << endl;
		
         }
		 
		 
		 //if its the last object dont print another ,
		 if(i == (message.ipstat_size() - 1))
		 {
			 cout << "\t\t\t\t}" << endl;
		 }
		 else{
			 cout << "\t\t\t\t}," << endl;
		 }
		 
      }
	  cout << "\t\t\t]" << endl;
   }
}

bool printNLEthernetStat(const NL_Message& message)
{
   // always good to validate inputs to a function, right?
   if(message.IsInitialized())
   {
	   cout << "\t\t\t\"DataItems\":[" << endl;
      // loop through all the ipstat items in this message
      for(int i = 0; i < message.ethernetstat_size(); i++)
      {
		    cout << "\t\t\t\t{" << endl;
         //check if a registration or update message
			if(message.ethernetstat(i).has_interface() && message.ethernetstat(i).has_interfacename())
			{
				//message has an interface so it is a registration message
					 
				cout << "\t\t\t\t\t\"ID\":" << "\"" << message.ethernetstat(i).ident() << "\"," << endl;
				cout << "\t\t\t\t\t\"Interface\":" << "\"" << message.ethernetstat(i).interface() << "\"," << endl;
				cout << "\t\t\t\t\t\"InterfaceName\":" << "\"" << message.ethernetstat(i).interfacename() << "\"" << endl;
			}
			else if(message.ethernetstat(i).has_rxgood() &&
					message.ethernetstat(i).has_rxerrors() &&
					message.ethernetstat(i).has_rxdropped() &&
					message.ethernetstat(i).has_rxoverruns() &&
					message.ethernetstat(i).has_rxframe() &&
					message.ethernetstat(i).has_txgood() &&
					message.ethernetstat(i).has_txerrors() &&
					message.ethernetstat(i).has_txdropped() &&
					message.ethernetstat(i).has_txoverruns() &&
					message.ethernetstat(i).has_txcarrier() &&
					message.ethernetstat(i).has_txcollisions() &&
					message.ethernetstat(i).has_status())
			{
				
				//update message stuff goes here
				cout << "\t\t\t\t\t\"ID\":" << "\"" << message.ethernetstat(i).ident() << "\"," << endl;
				cout << "\t\t\t\t\t\"RxGood\":" << "\"" << message.ethernetstat(i).rxgood() << "\"," << endl;
				cout << "\t\t\t\t\t\"RxErrors\":" << "\"" << message.ethernetstat(i).rxerrors() << "\"," << endl;
				cout << "\t\t\t\t\t\"RxDropped\":" << "\"" << message.ethernetstat(i).rxdropped() << "\"," << endl;
				cout << "\t\t\t\t\t\"RxOverruns\":" << "\"" << message.ethernetstat(i).rxoverruns() << "\"," << endl;
				cout << "\t\t\t\t\t\"RxFrame\":" << "\"" << message.ethernetstat(i).rxframe() << "\"," << endl;
				cout << "\t\t\t\t\t\"TxGood\":" << "\"" << message.ethernetstat(i).txgood() << "\"," << endl;
				cout << "\t\t\t\t\t\"TxErrors\":" << "\"" << message.ethernetstat(i).txerrors() << "\"," << endl;
				cout << "\t\t\t\t\t\"TxDropped\":" << "\"" << message.ethernetstat(i).txdropped() << "\"," << endl;
				cout << "\t\t\t\t\t\"TxOverruns\":" << "\"" << message.ethernetstat(i).txoverruns() << "\"," << endl;
				cout << "\t\t\t\t\t\"TxCarrier\":" << "\"" << message.ethernetstat(i).txcarrier() << "\"," << endl;
				cout << "\t\t\t\t\t\"TxCollisions\":" << "\"" << message.ethernetstat(i).txcollisions() << "\"," << endl;
				cout << "\t\t\t\t\t\"Status\":" << "\"" << message.ethernetstat(i).status() << "\"" << endl;
				
			}
			
			//if its the last object dont print another ,
			if(i == (message.ethernetstat_size() - 1))
			{
				cout << "\t\t\t\t}" << endl;
			}
			else
			{
				cout << "\t\t\t\t}," << endl;
			}
		}
		cout << "\t\t\t]" << endl;
   }
}

bool printNLSwitchStat(const NL_Message& message)
{
   // always good to validate inputs to a function, right?
   if(message.IsInitialized())
   {
	   cout << "\t\t\t\"DataItems\":[" << endl;
      // loop through all the ipstat items in this message
      for(int i = 0; i < message.switchstat_size(); i++)
      {
		cout << "\t\t\t\t{" << endl;
        if(!message.switchstat(i).has_stat())
		{
				//message doesn't have stat so it is a registration message
					 
				cout << "\t\t\t\t\t\"ID\":" << "\"" << message.switchstat(i).ident() << "\"" << endl; //do we even need to print registration at this point?
				
		}
		else if(message.switchstat(i).has_stat() &&
				message.switchstat(i).has_dplx() &&
				message.switchstat(i).has_spd() &&
				message.switchstat(i).has_ingressbytes() &&
				message.switchstat(i).has_ingressunicast() &&
				message.switchstat(i).has_ingressbroadcast() &&
				message.switchstat(i).has_ingressmulticast() &&
				message.switchstat(i).has_ingresspause() &&
				message.switchstat(i).has_ingressundersize() &&
				message.switchstat(i).has_ingressfragments() &&
				message.switchstat(i).has_ingressoversize() &&
				message.switchstat(i).has_ingressjabber() &&
				message.switchstat(i).has_ingressrxerr() &&
				message.switchstat(i).has_ingressfcserr() &&
				message.switchstat(i).has_egressbytes() &&
				message.switchstat(i).has_egressunicast() &&
				message.switchstat(i).has_egressbroadcast() &&
				message.switchstat(i).has_egressmulticast() &&
				message.switchstat(i).has_egresspause() &&
				message.switchstat(i).has_egressexcessive() &&
				message.switchstat(i).has_egresscollisions() &&
				message.switchstat(i).has_egressother())
		{
			cout << "\t\t\t\t\t\"ID\":" << "\"" << message.switchstat(i).ident() << "\"," << endl;
			cout << "\t\t\t\t\t\"Status\":" << "\"" << message.switchstat(i).stat() << "\"," << endl;
			cout << "\t\t\t\t\t\"Duplex\":" << "\"" << message.switchstat(i).dplx() << "\"," << endl;
			cout << "\t\t\t\t\t\"Speed\":" << "\"" << message.switchstat(i).spd() << "\"," << endl;
			cout << "\t\t\t\t\t\"IngressBytes\":" << "\"" << message.switchstat(i).ingressbytes() << "\"," << endl;
			cout << "\t\t\t\t\t\"IngressUnicast\":" << "\"" << message.switchstat(i).ingressunicast() << "\"," << endl;
			cout << "\t\t\t\t\t\"IngressBroadcast\":" << "\"" << message.switchstat(i).ingressbroadcast() << "\"," << endl;
			cout << "\t\t\t\t\t\"IngressMulticast\":" << "\"" << message.switchstat(i).ingressmulticast() << "\"," << endl;
			cout << "\t\t\t\t\t\"IngressPause\":" << "\"" << message.switchstat(i).ingresspause() << "\"," << endl;
			cout << "\t\t\t\t\t\"IngressUndersize\":" << "\"" << message.switchstat(i).ingressundersize() << "\"," << endl;
			cout << "\t\t\t\t\t\"IngressFragments\":" << "\"" << message.switchstat(i).ingressfragments() << "\"," << endl;
			cout << "\t\t\t\t\t\"IngressOversize\":" << "\"" << message.switchstat(i).ingressoversize() << "\"," << endl;
			cout << "\t\t\t\t\t\"IngressJabber\":" << "\"" << message.switchstat(i).ingressjabber() << "\"," << endl;
			cout << "\t\t\t\t\t\"IngressRxErr\":" << "\"" << message.switchstat(i).ingressrxerr() << "\"," << endl;
			cout << "\t\t\t\t\t\"IngressFcsErr\":" << "\"" << message.switchstat(i).ingressfcserr() << "\"," << endl;
			cout << "\t\t\t\t\t\"EgressBytes\":" << "\"" << message.switchstat(i).egressbytes() << "\"," << endl;
			cout << "\t\t\t\t\t\"EgressUnicast\":" << "\"" << message.switchstat(i).egressunicast() << "\"," << endl;
			cout << "\t\t\t\t\t\"EgressBroadcast\":" << "\"" << message.switchstat(i).egressbroadcast() << "\"," << endl;
			cout << "\t\t\t\t\t\"EgressMulticast\":" << "\"" << message.switchstat(i).egressmulticast() << "\"," << endl;
			cout << "\t\t\t\t\t\"EgressPause\":" << "\"" << message.switchstat(i).egresspause() << "\"," << endl;
			cout << "\t\t\t\t\t\"EgressExcessive\":" << "\"" << message.switchstat(i).egressexcessive() << "\"," << endl;
			cout << "\t\t\t\t\t\"EgressCollisions\":" << "\"" << message.switchstat(i).egresscollisions() << "\"," << endl;
			cout << "\t\t\t\t\t\"EgressOther\":" << "\"" << message.switchstat(i).egressother() << "\"" << endl;
		}
		
		//if its the last object dont print another ,
		if(i == (message.switchstat_size() - 1))
		{
			cout << "\t\t\t\t}" << endl;
		}
		else
		{
			cout << "\t\t\t\t}," << endl;
		}
      }
	  cout << "\t\t\t]" << endl;
   }
}


bool printNlMessage(const NL_Message& message)
{
   // always good to validate inputs to a function, right?
   if(message.IsInitialized())
   {
      // source and command are required, so just print them out here
      //    Notice that message.source() returns an integer that maps to the
      //    enum listed in the .proto file, but it's not very "pretty" to
      //    print out. So by calling <element>_Name(...) you can resolve the
      //    enum to a string representation.
      //cout << "Source: " << message.Source_Name(message.source()) << endl;
      //cout << "Command: " << message.Command_Name(message.command()) << endl;
	  
	  cout << "\t\t\t\"Source\":" << "\"" << message.Source_Name(message.source()) << "\"," << endl;
	  cout << "\t\t\t\"Command\":" << "\"" << message.Command_Name(message.command()) << "\"," << endl;
	  
	  
      // the switch network is optional, so check to see if it exists before printing
      if(message.has_switchstatnetwork())
      {
         // again here we call <element>_Name(...) to resolve to a "pretty" string
		 cout << "\t\t\t\"Network\":" << "\"" << message.Network_Name(message.switchstatnetwork()) << "\"," << endl;
         
      }

      // IPTables stats are optional and could have more than one instance, so
      // check to see if there is at least one of them. if so, have it printed
      if(message.ipstat_size() > 0)
      {
         printNLIptableStat(message);
      }

      // same thing for switch stats as IPTables stats
      if(message.switchstat_size() > 0)
      {
         printNLSwitchStat(message);
      }

      // and again for Ethernet stats
      if(message.ethernetstat_size() > 0)
      {
         printNLEthernetStat(message);
      }
   }
   else
   {
      cerr << "NL Message not initialized" << endl;
      return false;
   }

   // if we got here then all went well
   return true;
}

bool readProtobufMessagesFromFile(const char* const iPath)
{
   cout << "{" << endl;
   cout << "\t\"RawFileName\":" << "\"" << iPath << "\"," << endl;
   int fd = open(iPath, O_RDONLY);
   long int totalSize = 0;

   if(fd >= 0)
   {
      struct stat stbuf;

      // figure out the total file size
      if ((fstat(fd, &stbuf) != 0) || (!S_ISREG(stbuf.st_mode)))
      {
         cerr << "Unable to determine file size" << endl;
         return false;
      }

      totalSize = stbuf.st_size;

      cout << "\t\"TotalSize\":" << "\"" << totalSize << "\"," << endl;

      uint32_t msgSize = 0;
      // the zero copy input stream knows how to read files
      ZeroCopyInputStream* raw_input = new FileInputStream(fd);
      // and coded input stream knows how the file is formatted
      CodedInputStream* coded_input  = new CodedInputStream(raw_input);

      // used later to read messages into ... probably could just be one variable,
      // but might be useful to keep the register message around depending on
      // what the goal is
      NL_Message registerMsg;
      NL_Message updateMsg;

	  
      // get the size of the register message (always the first message)
      coded_input->ReadVarint32(&msgSize);
	  
      
      // limit the coded stream parser to the size of the registration message
      // this will keep the stream parser from reading into subsequent
      // messages in this file
      CodedInputStream::Limit mLimit = coded_input->PushLimit(msgSize);
      // turn coded stream into registration message
      registerMsg.ParseFromCodedStream(coded_input);
      // pop the coded stream parser limit so we can read another message
      coded_input->PopLimit(mLimit);

	  
      // check to see what type of log file has been loaded
      if(registerMsg.ipstat_size() > 0)
      {
         cout << "\t\"LogType\":" << "\"" << "IPTable" << "\"," << endl;
      }

      else if(registerMsg.switchstat_size() > 0)
      {
         cout << "\t\"LogType\":" << "\"" << "Switch" << "\"," << endl;
      }

      else if(registerMsg.ethernetstat_size() > 0)
      {
         cout << "\t\"LogType\":" << "\"" << "Ethernet" << "\"," << endl;
      }
	  else
	  {
		  cout << "\t\"LogType\":" << "\"" << "Invalid" << "\"," << endl;
	  }
	  
	  cout << "\t\"Messages\":[" << endl;
	  cout << "\t\t{" << endl;
	  
	  //cout << "Registration message is " << msgSize << " bytes long" << endl;
	  cout << "\t\t\t\"ByteLength\":" << "\"" << msgSize << "\"," << endl;
	  
      // print the registration message
      printNlMessage(registerMsg);
	  cout << "\t\t}," << endl;
	 
	  // now we need to read all the different stats update messages which
      // will follow the registration message. there is no way at this time
      // to know how many there might before
	 
      while(coded_input->ReadVarint32(&msgSize))
      {
         const void* data;
         int remainingBufferSize;
		 
		 cout << "\t\t{" << endl;
		 
         // this is used to get the number of bytes left in the current buffer
         if(!coded_input->GetDirectBufferPointer(&data, &remainingBufferSize))
         {
            cerr << "GetDirectBufferPointer failed for some reason" << endl;
            return false;
         }

         // this is used to check to see when we are at the end of the file. due to
         // the way that the coded stream parsing works, it will only read a max of
         // 8k blocks at any given time, so the size variable only represents how
         // much data is left in the current 8k buffer and not how much is left in
         // the total file.
         //
         // to know if we are reading from the last 8k block of the file, we can
         // use the original raw_input stream to see how much of the total file
         // the coded buffer parser has read. once the coded buffer parser has
         // read all the bytes in the total files size, then we know that the 
         // remaining buffer size is also the same as the bytes remaining in the
         // total file.
         //
         // so as long as msgSize is less than the remaining bytes of the file
         // we know that there is another full message to read. but if the next
         // message size is greater than the remaining size in the buffer, then
         // there must be a partial message at the end of the file due to a sync
         // issue during a power loss or something.
         if(totalSize == raw_input->ByteCount() && msgSize > remainingBufferSize)
         {
            cout << "Found a partial message at the end of the raw file. Ignoring it" << endl;
            cout << "File Size: " << totalSize << " Bytes Read: " << raw_input->ByteCount() << endl;
            cout << "Message Size: " << msgSize << " Remaining Size: " << remainingBufferSize << endl;
            break;
         }
		
         cout << "\t\t\t\"ByteLength\":" << "\"" << msgSize << "\"," << endl;

         // limit the stream parser so the next read is just this message
         mLimit = coded_input->PushLimit(msgSize);
         updateMsg.ParseFromCodedStream(coded_input);
         //pop the coded stream parser limit so we can read another message
         coded_input->PopLimit(mLimit);

         // now print the update message contents
         printNlMessage(updateMsg);
		 
		 cout << "\t\t}," << endl; //move this into print nlmessage?
		 
      }
	  cout << "\t\t{}" << endl; //empty object to make json valid, figure out how to fix this later
	  
	  cout << "\t]" << endl;
      cout << "}" << endl;
   

      // always be good and clean up after yourself so that we don't leak
      // memory and make people think they need more RAM
      close(fd);
      delete coded_input;
      delete raw_input;
   }
   else
   {
      // well that's unexpected ... 
      cerr << "Failed to open file" << endl;
   }
}


int main(int argc, char* argv[])
{
	_fmode = _O_BINARY; //used for opening files in binary mode on windows
	
   if(argc == 2)
   {
      readProtobufMessagesFromFile(argv[1]);
      return 0;
   }
   else
   {
      cerr << "Usage: " << argv[0] << " <path to raw file>" << endl;
      return 1;
   }
}


