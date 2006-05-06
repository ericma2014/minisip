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

/*
 * Authors: Erik Eliasson <eliasson@it.kth.se>
 *          Johan Bilien <jobi@via.ecp.fr>
*/


#include<config.h>

#include<libmutil/mtime.h>

#include<time.h>

#include <sys/timeb.h>
#include <winsock2.h>

LIBMUTIL_API uint64_t mtime(){
	#ifdef _WIN32_WCE
		struct timeb tb;
	#else
		struct _timeb tb;
	#endif
		_ftime (&tb);

	return ((uint64_t)tb.time) * (int64_t)1000 + ((uint64_t)tb.millitm);
}


	void gettimeofday (struct timeval *tv, struct timezone *tz){
		#ifdef _WIN32_WCE
		struct timeb tb;
		#else
		struct _timeb tb;
		#endif
		_ftime (&tb);

		tv->tv_sec = tb.time;
		tv->tv_usec = tb.millitm * 1000L;
		if( tz ){
			tz->tz_minuteswest = tb.timezone;	/* minutes west of Greenwich  */
			tz->tz_dsttime = tb.dstflag;	/* type of dst correction  */
		}
	}


LIBMUTIL_API int msleep(int32_t ms){
	Sleep(ms); //function returns void
	return 0;
}