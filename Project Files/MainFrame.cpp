#include "MainFrame.h"
#include <wx/wx.h>
#include "Data_Definitions.h"
#include "Functions.h"

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_BUTTON(10001, MainFrame::OnSendMessage)
EVT_BUTTON(10002, MainFrame::OnStopSpamMode)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
    wxPanel* panel = new wxPanel(this);

    wxButton* button = new wxButton(panel, 10001, "Send Message", wxPoint(300, 110), wxSize(100, 35));
    wxButton* button2 = new wxButton(panel, 10002, "Stop Spam Mode", wxPoint(300, 160), wxSize(100, 35));

    wxStaticText* staticText = new wxStaticText(panel, wxID_ANY, "Goofy ahh User Interface but whatever, it works.", wxPoint(50, 50));

    textCtrl = new wxTextCtrl(panel, wxID_ANY, "Your webhook URL", wxPoint(50, 75), wxSize(200, -1));
    messageCtrl = new wxTextCtrl(panel, wxID_ANY, "Your message", wxPoint(50, 125), wxSize(200, -1));

    wxArrayString choices; // dropdown choice menu
    choices.Add("Normal Mode");
    choices.Add("Spam Mode");
    choice = new wxChoice(panel, wxID_ANY, wxPoint(150, 150), wxSize(100, -1), choices);
    choice->Select(0);
}

void MainFrame::OnSendMessage(wxCommandEvent& event) {
    WebhookURL = textCtrl->GetValue().ToStdString();
    Message = messageCtrl->GetValue().ToStdString();
    SendPOSTRequest();
}

void MainFrame::OnStopSpamMode(wxCommandEvent& event) {
    // Implement the stop spam mode functionality
}
