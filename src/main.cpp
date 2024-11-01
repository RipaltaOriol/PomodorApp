#include <wx/wx.h>
#include <wx/timer.h>
#include <wx/image.h>
#include <wx/sound.h>
#include "MainFrame.cpp"

// enhance buttons & border
// move change timer to a settings windw
// separate code by parts
// keep track of pauses and internvals
// deploy GitHub
// compile as an app?

class PomodoroApp : public wxApp
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(PomodoroApp);

bool PomodoroApp::OnInit()
{
    wxInitAllImageHandlers();

    MainFrame *frame = new MainFrame("Pomodoro Timer");
    frame->Show(true);
    return true;
}