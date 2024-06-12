#include <wx/wx.h>
#include "MainApp.h"
#include "MainFrame.h"

wxIMPLEMENT_APP(MainApp);

bool MainApp::OnInit() {
    MainFrame* mainFrame = new MainFrame("Discord Webhook Manager");
    mainFrame->SetClientSize(700, 350);
    mainFrame->Center();
    mainFrame->Show();
    return true;
}
