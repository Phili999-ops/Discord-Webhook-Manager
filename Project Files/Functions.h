#pragma once
#include <iostream>
#include <curl/curl.h>
#include <string>
#include <thread>
#include <mutex>
#include "Data_Definitions.h"
#include "MainFrame.h"

std::mutex curl_mutex; // Mutex for thread safety

void SendPOSTRequest() {
    CURL* curl;
    CURLcode res;

    // Lock mutex for thread safety
    std::lock_guard<std::mutex> lock(curl_mutex);

    // Initialize curl lib
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Set the URL for the POST request
        curl_easy_setopt(curl, CURLOPT_URL, WebhookURL.c_str());

        // Set the payload with the Message variable
        std::string jsonPayload = "{\"content\": \"" + Message + "\"}";
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonPayload.c_str());

        // Override DNS
        curl_easy_setopt(curl, CURLOPT_DNS_SERVERS, "1.1.1.1,1.0.0.1"); // Cloudflare DNS

        // Set headers
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Perform request, res will return the code
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        // Clean up
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }

    curl_global_cleanup();
}

void MainFrame::OnSendMessage(wxCommandEvent& event) {
    WebhookURL = textCtrl->GetValue().ToStdString();
    Message = messageCtrl->GetValue().ToStdString();
    std::thread sendThread(SendPOSTRequest);
    sendThread.detach();
}

void MainFrame::OnSpamMode(wxCommandEvent& event) {
    WebhookURL = textCtrl->GetValue().ToStdString();
    Message = messageCtrl->GetValue().ToStdString();
    SpamMode = true;
    std::thread spamThread([this]() {
        while (SpamMode) {
            SendPOSTRequest();
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Adjust the delay as needed
        }
        });
    spamThread.detach();
}

void MainFrame::OnStopSpamMode(wxCommandEvent& event) {
    SpamMode = false;
}
