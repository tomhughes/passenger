/*
 *  Phusion Passenger - http://www.modrails.com/
 *  Copyright (c) 2009 Phusion
 *
 *  "Phusion Passenger" is a trademark of Hongli Lai & Ninh Bui.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 */
#ifndef _PASSENGER_BACKTRACES_SERVER_H_
#define _PASSENGER_BACKTRACES_SERVER_H_

#include <oxt/thread.hpp>
#include <oxt/backtrace.hpp>
#include "MessageServer.h"

namespace Passenger {

using namespace std;

/**
 * A MessageServer handler for reporting the backtraces of all running oxt::threads.
 */
class BacktracesServer: public MessageServer::Handler {
public:
	virtual bool processMessage(MessageServer::CommonClientContext &commonContext,
	                            MessageServer::ClientContextPtr &handlerSpecificContext,
	                            const vector<string> &args)
	{
		TRACE_POINT();
		if (args[0] == "backtraces") {
			UPDATE_TRACE_POINT();
			commonContext.requireRights(Account::INSPECT_BACKTRACES);
			commonContext.channel.writeScalar(oxt::thread::all_backtraces());
			return true;
		} else {
			return false;
		}
	}
};

} // namespace Passenger

#endif /* _PASSENGER_BACKTRACES_SERVER_H_ */