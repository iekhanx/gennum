/*
 * ==========================================================================
 *
 *       Filename:  ClipboardImpl.hpp
 *
 *    Dexwcription:  ClipboardImpl class declaration
 *
 *        Version:  1.0
 *        Created:  29/01/22 15:45:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _CLIPBOARDIMPLX11_HPP
#define _CLIPBOARDIMPLX11_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "../system/String.hpp"
#include <X11/Xlib.h>
#include <deque>


namespace xwc
{
namespace priv
{

////////////////////////////////////////////////////////////
/// \brief Give access to the system clipboard
///
////////////////////////////////////////////////////////////
class ClipboardImpl
{
public:

    ////////////////////////////////////////////////////////////
    /// \brief Get the content of the clipboard as string data
    ///
    /// This function returns the content of the clipboard
    /// as a string. If the clipboard does not contain string
    /// it returns an empty xwc::String object.
    ///
    /// \return Current content of the clipboard
    ///
    ////////////////////////////////////////////////////////////
    static String getString();

    ////////////////////////////////////////////////////////////
    /// \brief Set the content of the clipboard as string data
    ///
    /// This function sets the content of the clipboard as a
    /// string.
    ///
    /// \param text xwc::String object containing the data to be sent
    /// to the clipboard
    ///
    ////////////////////////////////////////////////////////////
    static void setString(const String& text);

    ////////////////////////////////////////////////////////////
    /// \brief Process pending events for the hidden clipboard window
    ///
    /// This function has to be called as part of normal window
    /// event processing in order for our application to respond
    /// to selection requests from other applications.
    ///
    ////////////////////////////////////////////////////////////
    static void processEvents();

private:

    ////////////////////////////////////////////////////////////
    /// \brief Constructor
    ///
    ////////////////////////////////////////////////////////////
    ClipboardImpl();

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ////////////////////////////////////////////////////////////
    ~ClipboardImpl();

    ////////////////////////////////////////////////////////////
    /// \brief Get singleton instance
    ///
    /// \return Singleton instance
    ///
    ////////////////////////////////////////////////////////////
    static ClipboardImpl& getInstance();

    ////////////////////////////////////////////////////////////
    /// \brief getString implementation
    ///
    /// \return Current content of the clipboard
    ///
    ////////////////////////////////////////////////////////////
    String getStringImpl();

    ////////////////////////////////////////////////////////////
    /// \brief setString implementation
    ///
    /// \param text xwc::String object containing the data to be 
    ///             sent to the clipboard
    ///
    ////////////////////////////////////////////////////////////
    void setStringImpl(const String& text);

    ////////////////////////////////////////////////////////////
    /// \brief processEvents implementation
    ///
    ////////////////////////////////////////////////////////////
    void processEventsImpl();

    ////////////////////////////////////////////////////////////
    /// \brief Process an incoming event from the window
    ///
    /// \param windowEvent Event which has been received
    ///
    ////////////////////////////////////////////////////////////
    void processEvent(XEvent& windowEvent);

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    ::Window       m_window;            ///< X identifier defining our window
    ::Display*     m_display;           ///< Pointer to the display
    Atom   m_clipboard;            ///< X Atom identifying the CLIPBOARD select
    Atom               m_targets;           ///< X Atom identifying TARGETS
    Atom               m_text;              ///< X Atom identifying TEXT
    Atom               m_utf8String;        ///< X Atom identifying UTF8_STRING
    Atom       m_targetProperty;    ///< X Atom identifying our window property
    String             m_clipboardContents; ///< Our clipboard contents
    std::deque<XEvent> m_events; ///< Queue we use to store pending eventswindow
    bool               m_requestResponded;  ///< Holds whether our selection 
};

} // namespace priv

} // namespace xwc


#endif // _CLIPBOARDIMPLX11_HPP
