/*
  Copyright (C) 2005, 2004 Erik Eliasson, Johan Bilien
  
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
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/


/* Copyright (C) 2004 
 *
 * Authors: Erik Eliasson <eliasson@it.kth.se>
 *          Johan Bilien <jobi@via.ecp.fr>
*/

#ifndef RTPHEADER_H
#define RTPHEADER_H

#ifdef _MSC_VER
#ifdef LIBMINISIP_EXPORTS
#define LIBMINISIP_API __declspec(dllexport)
#else
#define LIBMINISIP_API __declspec(dllimport)
#endif
#else
#define LIBMINISIP_API
#endif

#ifdef _MSC_VER
typedef uint16_t unsigned short;
typedef uint32_t unsigned;
#else
#include<stdint.h>
#endif

#include<vector>

using namespace std;

class LIBMINISIP_API RtpHeader{

	public:
		RtpHeader();
		void setVersion(int v);
		void setExtension(int x);
		void setCSRCCount(int cc);
		void setMarker(int m);
		bool getMarker();
		void setPayloadType(int pt);
		int getPayloadType();
		void setSeqNo(uint16_t seq_no);
		uint16_t getSeqNo();
		void setTimestamp(uint32_t timestamp);
		uint32_t getTimestamp();
		void setSSRC(uint32_t ssrc);
		uint32_t getSSRC();
		void addCSRC(int csrc);

		void printDebug();

		int size();
		char *getBytes();

		int CSRC_count;
		int version;
		int extension;
		int marker;
		int payload_type;
		uint16_t sequence_number;
		uint32_t timestamp;
		uint32_t SSRC;
		std::vector<int> CSRC; 
	private:
};

#endif
