/*
#if !defined(AFX_ITUNESEVENTHANDLER_H__42970B2C_41F2_4339_8DCC_9AC7D5550402__INCLUDED_)
#define AFX_ITUNESEVENTHANDLER_H__42970B2C_41F2_4339_8DCC_9AC7D5550402__INCLUDED_

#pragma once

#include "iTunesCOMInterface.h" // from Apple's iTunes SDK

namespace DJayy
{
	class CiTunesEventHandler : public CCmdTarget
	{
	public:
		CiTunesEventHandler();
		virtual ~CiTunesEventHandler();
		// Attributes
		
// Operations
public:

// Overrides
// ClassWizard generated virtual function overrides
//{{AFX_VIRTUAL(CiTunesEventHandler)
public:
virtual void OnFinalRelease();
//}}AFX_VIRTUAL

// Implementation
protected:

// Generated message map functions
//{{AFX_MSG(CiTunesEventHandler)
// NOTE - the ClassWizard will add and remove member functions here.
//}}AFX_MSG

DECLARE_MESSAGE_MAP()
// Generated OLE dispatch map functions
//{{AFX_DISPATCH(CiTunesEventHandler)
afx_msg void OnDatabaseChangedEvent(const VARIANT FAR&
deletedObjectIDs, const VARIANT FAR& changedObjectIDs);
afx_msg void OnPlayerPlayEvent(const VARIANT FAR& iTrack);
afx_msg void OnPlayerStopEvent(const VARIANT FAR& iTrack);
afx_msg void OnPlayerPlayingTrackChangedEv(const VARIANT FAR& iTrack);
afx_msg void OnUserInterfaceEnabledEvent();
afx_msg void OnCOMCallsDisabledEvent(short reason);
afx_msg void OnCOMCallsEnabled();
afx_msg void OnQuittingEvent();
afx_msg void OnAboutToPromptUserToQuitEvent();
afx_msg void OnSoundVolumeChangedEvent(long newVolume);
//}}AFX_DISPATCH
DECLARE_DISPATCH_MAP()
DECLARE_INTERFACE_MAP()

LPUNKNOWN GetInterfaceHook(const void *piid);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately
before the previous line.

#endif //
!defined(AFX_ITUNESEVENTHANDLER_H__42970B2C_41F2_4339_8DCC_9AC7D5550402__INCLUDED_)
---------
*/