// SettingsDialog.cpp
#include "SettingsDialog.h"

wxBEGIN_EVENT_TABLE(SettingsDialog, wxDialog)
    EVT_BUTTON(wxID_OK, SettingsDialog::OnSave)
        EVT_BUTTON(wxID_CANCEL, SettingsDialog::OnCancel)
            wxEND_EVENT_TABLE()

                SettingsDialog::SettingsDialog(wxWindow *parent)
    : wxDialog(parent, wxID_ANY, "Settings", wxDefaultPosition, wxSize(300, 200)),
      m_timerDuration(25) // Default to 25 minutes
{
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText *timerLabel = new wxStaticText(this, wxID_ANY, "Timer Duration (minutes):");
    m_timerDurationInput = new wxTextCtrl(this, wxID_ANY, wxString::Format("%d", m_timerDuration));

    sizer->Add(timerLabel, 0, wxALL | wxALIGN_LEFT, 10);
    sizer->Add(m_timerDurationInput, 0, wxALL | wxEXPAND, 10);

    wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(new wxButton(this, wxID_OK, "Save"), 0, wxALL, 5);
    buttonSizer->Add(new wxButton(this, wxID_CANCEL, "Cancel"), 0, wxALL, 5);

    sizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 10);

    SetSizerAndFit(sizer);
}

void SettingsDialog::OnSave(wxCommandEvent &event)
{
    long duration;
    if (m_timerDurationInput->GetValue().ToLong(&duration) && duration > 0)
    {
        m_timerDuration = duration;
        EndModal(wxID_OK); // Close the dialog with OK result
    }
    else
    {
        wxMessageBox("Please enter a valid duration.", "Invalid Input", wxOK | wxICON_ERROR);
    }
}

void SettingsDialog::OnCancel(wxCommandEvent &event)
{
    EndModal(wxID_CANCEL); // Close the dialog with Cancel result
}

int SettingsDialog::GetTimerDuration() const
{
    return m_timerDuration;
}
