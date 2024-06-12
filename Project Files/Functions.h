#pragma once
#include <iostream>
#include <curl/curl.h>
#include <string>

extern std::string WebhookURL; // The user's webhook URL
extern std::string Message; // The user's message to the webhook

void SendPOSTRequest() { // Function for sending POST request to discord's API
    CURL* curl;
    CURLcode res;

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