/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

/* Copyright (C) 2004 
 *
 * Authors: Erik Eliasson <eliasson@it.kth.se>
 *          Johan Bilien <jobi@via.ecp.fr>
*/


/*

 +-Sip------------------------------------------+
 |                                              |  invite(string)
 | +-SipDialogContainer---+                     |<----------------------------------
 | |                      | addCall(SipCall)    |
 | |                      |<----------------    | handleCommand(SipSMCommand)
 | |                      |                     |<----------------------------------
 | |                      | handleCommand(CS)   |
 | |                      |-------------------->| sipcb_handleCommand(CommandString)
 | |                      |                     |---------------------------------->
 | |                      | sipcb_handleCommand |
 | |                      |-------------------->|
 | |                      |                     |
 | |                      | enqueuePacket()     |
 | |                      |<----------------    |
 | |                      |                     |
 | |                      | enqueueCommand()    |
 | |                      |<----------------    |
 | |                      |                     |
 | | [call_list]          | handleSipMessage()  |
 | | [defaultHandler]     |<---+                |
 | +----------------------+    |                |
 |                             |                |
 | [SipMessageTransport]-------+                |
 | [SipSoftPhoneConfiguration]                  |
 |                                              |
 |                                              |
 +----------------------------------------------+

*/

#ifndef MINISIP_SIP_H
#define MINISIP_SIP_H

#include<config.h>

#include<libmutil/minilist.h>
#include<libmsip/SipCallback.h>
#include<libmsip/SipDialogContainer.h>
#include"../sdp/SdpPacket.h"

#include<libmsip/SipDialog.h>


class SipSoftPhoneConfiguration;
class LogEntry;
class MediaHandler;

using namespace std;

class Sip: public SipSMCommandReceiver, public Runnable{

	public:
		Sip(MRef<SipSoftPhoneConfiguration*> phoneconfig,
		    MRef<MediaHandler*> mediaHandler);

		virtual std::string getMemObjectType(){return "Sip";}
		
		void init();

		MRef<SipSoftPhoneConfiguration*> getPhoneConfig();
		
                virtual void run();

		//void registerMediaStream(MRef<SdpPacket*> sdppack);

		string invite(string &user);

		MRef<SipDialogContainer*> getDialogContainer(){return dialogContainer;}

		void setMediaHandler( MRef<MediaHandler *> mediaHandler );

		bool handleCommand(const SipSMCommand &command);
		
		void setCallback(SipCallback *callback);

		SipCallback *getCallback();
                
	private:
		MRef<SipSoftPhoneConfiguration*> phoneconfig;
		MRef<MediaHandler *> mediaHandler;
		
		SipCallback *callback;

		MRef<SipDialogContainer*> dialogContainer;
                
};


#endif
