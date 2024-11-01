// SettingsDialog.h
#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <wx/wx.h>

class SettingsDialog : public wxDialog
{
public:
    SettingsDialog(wxWindow *parent);

    int GetTimerDuration() const;

private:
    wxTextCtrl *m_timerDurationInput;
    void OnSave(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);

    int m_timerDuration;

    wxDECLARE_EVENT_TABLE();
};

#endif
