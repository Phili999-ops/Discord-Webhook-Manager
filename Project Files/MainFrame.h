#pragma once
#include <wx/wx.h>

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title);

private:
    void OnSendMessage(wxCommandEvent& event);
    void OnStopSpamMode(wxCommandEvent& event);
    void OnSpamMode(wxCommandEvent& event);

    wxTextCtrl* textCtrl;
    wxTextCtrl* messageCtrl;
    wxChoice* choice;

    wxDECLARE_EVENT_TABLE();
};
