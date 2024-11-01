// MainFrame.h

#pragma once
#include <wx/wx.h>
#include <wx/timer.h>
#include <wx/sound.h>
#include <wx/image.h>
// #include "SettingsDialog.h"

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString &title);
    void OnStart(wxCommandEvent &event);
    void OnReset(wxCommandEvent &evet);
    void OnPause(wxCommandEvent &event);
    void OnTimer(wxTimerEvent &event);
    void OnSetTimer(wxCommandEvent &event);

private:
    wxStaticText *m_timeDisplay;
    wxButton *m_startButton;
    wxButton *m_pauseButton;
    wxButton *m_resetButton;
    wxButton *m_setTimerButton;
    wxTextCtrl *m_timerInput;

    wxTimer m_timer;
    int m_secondsRemaining;

    wxPanel *m_mainPanel;
    wxBitmap m_backgroundImage;

    void UpdateTimeDisplay();
    void OnPaint(wxPaintEvent &event);
    void OnOpenSettings(wxCommandEvent &event);
    wxDECLARE_EVENT_TABLE();
};