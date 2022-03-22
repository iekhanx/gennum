/*
 * ========================================================================
 *
 *       Filename:  windowImpl.cpp
 *
 *    Description:  Implementation windowImpl.cpp 
 *
 *        Version:  1.0
 *        Created:  11/01/22 01:49:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
#include <alogrithm>
#include <cmath>

#include "windowImpl.hpp"
#include "Event.hpp"

namespace xwc
{
    namespace priv
    {
        WindowImpl* WindowImpl::create (VideoMode mode, const String& title,
                               uint32_t style, const ContextSetting& setting)
        {
            return new WindowImplType (mode, title, style, setting);
        }
        WindowImpl* WindowImpl::create (windowHandle handle)
        {
            return new WindowImplType (handle);
        }
        WindowImpl::WindowImpl ()
        {

        }
        WindowImpl::~WindowImpl()
        {
            // nothing to do
        }
        /* 
         * ===  FUNCTION  ====================================================
         *         Name:  bool WindowImpl::popEvent (Event& event, bool block)
         *  Description:  
         * ===================================================================
         */
         bool 
          WindowImpl::popEvent (Event& event, bool block)
          { // if the vent queue is empty let first check if new event are 
            // available for the OS
            if (m_event.empty ()) {
                // get the event from system
                processEvent ();
                if (block) {
                    // here we use a manual wait loop instead of optimized
                    // wait event provided by the OS, so that we don't skip
                    // event
                    while (m_event.empty()) {
                        slepp (millisecond (10));
                        processEvent ();
                    }
                }
            }
            // Pop the first event of the queue
            if (!m_event.empty()) {
                event = m_events.front();
                m_events.pop ();
                return true;
            }
            return false;
          }	/*  end of function bool WindowImpl::popEvent ()   */
         /* 
          * ===  FUNCTION  ====================================================
          *         Name:  WindowImpl::pushEvent (const Event& event)
          *  Description:  
          * ===================================================================
          */
         void
             WindowImpl::pushEvent (const Event& event)
             {
                 m_events.push (event);
             }/*  end of function WindowImpl::pushEvent ()  ----- */
       
    }   // end of namespace priv
}       // end of namespace xwc

