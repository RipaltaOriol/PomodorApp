// MainFrame.cpp

#include "MainFrame.h"
#include "SettingsDialog.cpp"

MainFrame::MainFrame(const wxString &title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(400, 400),
              wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)),
      m_timer(this),
      m_secondsRemaining(1500)
{

    wxColour pomodoroColor(186, 73, 73);

    // Settings
    wxMenuBar *menuBar = new wxMenuBar;
    wxMenu *menuSettings = new wxMenu;
    menuSettings->Append(wxID_PREFERENCES, "Settings");
    menuBar->Append(menuSettings, "Options");
    SetMenuBar(menuBar);

    // Load the background image
    m_backgroundImage.LoadFile("images/background.png", wxBITMAP_TYPE_PNG);

    // Create the main panel and bind the paint event
    m_mainPanel = new wxPanel(this, wxID_ANY); //, wxDefaultPosition, GetClientSize());
    m_mainPanel->SetBackgroundColour(wxColor(216, 106, 106));
    // SetSizerAndFit(new wxBoxSizer(wxHORIZONTAL)); // CONTINUE FROM HERE
    m_mainPanel->Bind(wxEVT_PAINT, &MainFrame::OnPaint, this); // HAD THIS BEFORE

    // Initialize your main frame here
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->AddStretchSpacer(1);

    // TODO: logic for the timer;
    // Timer input field and set button
    m_timerInput = new wxTextCtrl(m_mainPanel, wxID_ANY, "25", wxDefaultPosition, wxSize(50, 25));
    m_setTimerButton = new wxButton(m_mainPanel, wxID_ANY, "Set Timer");
    wxBoxSizer *inputSizer = new wxBoxSizer(wxHORIZONTAL);
    inputSizer->Add(new wxStaticText(m_mainPanel, wxID_ANY, "Minutes:"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    inputSizer->Add(m_timerInput, 0, wxRIGHT, 5);
    inputSizer->Add(m_setTimerButton, 0);
    sizer->Add(inputSizer, 0, wxALIGN_CENTER | wxBOTTOM, 10);

    m_timeDisplay = new wxStaticText(m_mainPanel, wxID_ANY, "25:00", wxDefaultPosition, wxSize(280, 50), wxALIGN_CENTER);
    m_timeDisplay->SetFont(wxFont(50, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    m_timeDisplay->SetForegroundColour(*wxWHITE);
    sizer->Add(m_timeDisplay, 0, wxALIGN_CENTER | wxALL, 10);

    sizer->AddStretchSpacer(1);

    wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    m_startButton = new wxButton(m_mainPanel, wxID_ANY, "Start", wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
    m_startButton->SetBackgroundColour(*wxWHITE); // Change background color to blue
    m_startButton->SetForegroundColour(pomodoroColor);
    m_pauseButton = new wxButton(m_mainPanel, wxID_ANY, "Pause");
    m_resetButton = new wxButton(m_mainPanel, wxID_ANY, "Reset");
    m_startButton->SetFont(wxFont(20, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    wxBoxSizer *startButtonSizer = new wxBoxSizer(wxHORIZONTAL);
    startButtonSizer->Add(m_startButton, 0, wxALL, 10);
    buttonSizer->Add(startButtonSizer, 0, wxRIGHT, 20);
    buttonSizer->Add(m_pauseButton, 0, wxRIGHT, 20);
    buttonSizer->Add(m_resetButton, 0, wxALIGN_CENTER | wxBOTTOM, 5);
    sizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxBOTTOM | wxBOTTOM, 20);

    // Set the panel's sizer to manage layout
    m_mainPanel->SetSizer(sizer);
    m_mainPanel->Layout();

    // Set the main frame's sizer to fit the panel
    // SetSizerAndFit(new wxBoxSizer(wxHORIZONTAL));
    // GetSizer()->Add(m_mainPanel, 1, wxEXPAND);

    m_startButton->Bind(wxEVT_BUTTON, &MainFrame::OnStart, this);
    m_pauseButton->Bind(wxEVT_BUTTON, &MainFrame::OnPause, this);
    m_resetButton->Bind(wxEVT_BUTTON, &MainFrame::OnReset, this);
    m_setTimerButton->Bind(wxEVT_BUTTON, &MainFrame::OnSetTimer, this);
    m_timer.Bind(wxEVT_TIMER, &MainFrame::OnTimer, this);

    // Set fixed size for the window
    SetMinSize(wxSize(400, 400));
    SetMaxSize(wxSize(400, 400));

    UpdateTimeDisplay();
}

void MainFrame::OnStart(wxCommandEvent &event)
{
    m_timer.Start(1000); // 1-second interval
}

void MainFrame::OnReset(wxCommandEvent &event)
{
    m_timer.Stop();
    m_secondsRemaining = 10;
    UpdateTimeDisplay();
}

void MainFrame::OnPause(wxCommandEvent &event)
{
    m_timer.Stop();
}

void MainFrame::OnTimer(wxTimerEvent &event)
{
    if (m_secondsRemaining > 0)
    {
        m_secondsRemaining--;
        UpdateTimeDisplay();
    }
    else
    {
        m_timer.Stop();

        wxSound alarmSound("sounds/applause.wav");
        if (alarmSound.IsOk())
        {
            alarmSound.Play(wxSOUND_ASYNC);
        }
        else
        {
            wxLogError("Failed to load the alarm sound.");
        }
        // TODO: CHANGE THIS!!!
        wxMessageBox("Time's up!", "Pomodoro Timer");
    }
}

void MainFrame::UpdateTimeDisplay()
{
    int minutes = m_secondsRemaining / 60;
    int seconds = m_secondsRemaining % 60;
    m_timeDisplay->SetLabel(wxString::Format("%02d:%02d", minutes, seconds));
}

void MainFrame::OnSetTimer(wxCommandEvent &event)
{
    long minutes;
    if (m_timerInput->GetValue().ToLong(&minutes) && minutes > 0)
    {
        m_secondsRemaining = minutes * 60; // convert to seconds
        UpdateTimeDisplay();
    }
    else
    {
        wxMessageBox("Some Error Message"); // TDOO: refine this
    }
}

void MainFrame::OnPaint(wxPaintEvent &event)
{
    wxPaintDC dc(m_mainPanel);

    if (m_backgroundImage.IsOk())
    {
        // Define the desired image size
        int imageWidth = 300;  // Set the width for the smaller image
        int imageHeight = 300; // Set the height for the smaller image
        double transparency = 0.5;

        // Scale the image to this new size
        wxImage scaledImage = m_backgroundImage.ConvertToImage();
        scaledImage = scaledImage.Scale(imageWidth, imageHeight, wxIMAGE_QUALITY_HIGH);
        // scaledImage.InitAlpha(); // CONTINUE FROM HERE

        // Calculate the position to center the image on the panel
        wxSize panelSize = m_mainPanel->GetClientSize();
        int x = (panelSize.GetWidth() - imageWidth) / 2;
        int y = (panelSize.GetHeight() - imageHeight) / 2;

        // Draw the scaled image at the centered position
        dc.DrawBitmap(wxBitmap(scaledImage), x, y, true);

        // Optional: Invisible border by matching the color to the background (or you can skip this)
        dc.SetPen(wxPen(m_mainPanel->GetBackgroundColour(), 1)); // Matches panel color
        dc.SetBrush(*wxTRANSPARENT_BRUSH);                       // Transparent inside
        dc.DrawRectangle(x, y, imageWidth, imageHeight);         // Draws an "invisible" border
    }
}

void MainFrame::OnOpenSettings(wxCommandEvent &event)
{
    SettingsDialog settingsDialog(this);
    if (settingsDialog.ShowModal() == wxID_OK)
    {
        m_secondsRemaining = settingsDialog.GetTimerDuration() * 60; // Convert minutes to seconds
        // Reset the timer to the new duration if needed
    }
}

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_TIMER(wxID_ANY, MainFrame::OnTimer)
        EVT_BUTTON(wxID_ANY, MainFrame::OnStart)
            EVT_BUTTON(wxID_ANY, MainFrame::OnPause)
                EVT_BUTTON(wxID_ANY, MainFrame::OnReset)
                    EVT_BUTTON(wxID_ANY, MainFrame::OnSetTimer)
                        EVT_TIMER(wxID_ANY, MainFrame::OnTimer)
                            EVT_PAINT(MainFrame::OnPaint)
                                EVT_MENU(wxID_PREFERENCES, MainFrame::OnOpenSettings)
                                    wxEND_EVENT_TABLE()