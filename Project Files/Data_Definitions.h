#pragma once
#include <string>

std::string WebhookURL; // The user's webhook URL
std::string UserChoice; // Break the loop in case of a yes
std::string Message; // The user's message to the webhook
bool Override = false; // Keep Loop active in case of a no
