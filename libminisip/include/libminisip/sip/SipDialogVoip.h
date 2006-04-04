/*
 Copyright (C) 2004-2006 the Minisip Team
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */

/* Copyright (C) 2004 
 *
 * Authors: Erik Eliasson <eliasson@it.kth.se>
 *          Johan Bilien <jobi@via.ecp.fr>
 *	    Joachim Orrblad <joachim@orrblad.com>
*/

/* Name
 * 	SipDialogVoip.h
 * Author
 * 	Erik Eliasson, eliasson@it.kth.se
 * Purpose
 * 
*/


#ifndef SipDialogVoip_H
#define SipDialogVoip_H

#include<libminisip/libminisip_config.h>

#include<libmsip/SipDialog.h>
#include<libmsip/SipTransaction.h>
#include<libmsip/SipResponse.h>
#include<libmutil/StateMachine.h>

#include<libminisip/sip/SipSoftPhoneConfiguration.h>

#ifdef IPSEC_SUPPORT
#	include<libminisip/ipsec/MsipIpsecAPI.h>
#endif

class Session;
class SipDialogContainer;
class SipDialogConfig;
class LogEntry;

class SipDialogVoip: public SipDialog{
	public:
/*#ifdef IPSEC_SUPPORT
		SipDialogVoip(MRef<SipStack*> stack, MRef<SipDialogConfig*> callconfig, MRef<SipSoftPhoneConfiguration*> phoneconf, MRef<Session *> mediaSession, string callId="", MRef<MsipIpsecAPI *> ipsecSession=NULL);
#else
		SipDialogVoip(MRef<SipStack*> stack, MRef<SipDialogConfig*> callconfig, MRef<SipSoftPhoneConfiguration*> phoneconf, MRef<Session *> mediaSession, string callId="");

#endif		*/
		SipDialogVoip::SipDialogVoip(	MRef<SipStack*> stack,
						MRef<SipDialogConfig*> callconfig,
						MRef<SipSoftPhoneConfiguration*> pconf,
						MRef<Session *> mediaSession,
						string cid=""
					#ifdef IPSEC_SUPPORT
						, MRef<MsipIpsecAPI *> ipsecSession = NULL
					#endif
					);
		virtual ~SipDialogVoip();

		virtual void dummy()=0;

		virtual std::string getMemObjectType(){return "SipDialogVoip";}
		
		virtual string getName(){return "SipDialogVoip[callid="+dialogState.callId +"]";}


		virtual bool handleCommand(const SipSMCommand &command);

	
		MRef<Session *> getMediaSession();
#ifdef IPSEC_SUPPORT
		MRef<MsipIpsecAPI *> getIpsecSession();
#endif

	protected:
		void sendBye(const string &branch, int);
		void sendByeOk(MRef<SipRequest*> bye, const string &branch);
		void sendCancel(const string &branch);
		MRef<SipRequest*> getLastInvite();
		void setLastInvite(MRef<SipRequest*> i);
		bool sortMIME(MRef<SipMessageContent *> Offer, string peerUri, int type);		
		MRef<LogEntry *> getLogEntry();
		void setLogEntry( MRef<LogEntry *> );

		void registerSDP(uint32_t sourceId, MRef<SdpPacket*> sdppack);

		
		MRef<SipSoftPhoneConfiguration*> phoneconf;
		MRef<Session *> mediaSession;
		
		/**
		Used to notify once of the call_terminated_early command.
		Useful for shutdown and management purposes.
		*/
		bool notifyEarlyTermination;
		
	private:
		
		void setUpStateMachine();
		
		
		void sendReferOk(const string &branch);
		void sendNotifyOk(MRef<SipRequest*> notif, const string &branch);
		void sendReferReject(const string &branch);
		void sendRefer(const string &branch, int, const string referredUri);
		
		/* Ending a call */
		bool a1001_incall_termwait_BYE( const SipSMCommand &command);
		bool a1002_incall_termwait_hangup( const SipSMCommand &command);
		
		/* Dialog/transaction management */
		bool a1101_termwait_terminated_notransactions( const SipSMCommand &command);
		bool a1102_termwait_termwait_early( const SipSMCommand &command);
		
		/* Call transfer */
		bool a1201_incall_transferrequested_transfer( const SipSMCommand &command);
		bool a1202_transferrequested_transferpending_202( const SipSMCommand &command);
		bool a1203_transferrequested_incall_36( const SipSMCommand &command);
		bool a1204_transferpending_transferpending_notify( const SipSMCommand &command);
		
		bool a1301_incall_transferaskuser_REFER( const SipSMCommand &command);
		bool a1302_transferaskuser_transferstarted_accept( const SipSMCommand &command);
		bool a1303_transferaskuser_incall_refuse( const SipSMCommand &command);
                
		
		MRef<LogEntry *> logEntry;

		MRef<SipRequest*> lastInvite;
		MRef<SipRequest*> lastRefer;

#ifdef IPSEC_SUPPORT
		MRef<MsipIpsecAPI *> ipsecSession;
#endif
};

#endif