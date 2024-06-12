# Discord Webhook Manager

Discord Webhook Manager is a simple console application with a graphical user interface (GUI) for sending messages to Discord webhooks. This project demonstrates basic usage of wxWidgets for GUI and libcurl for making HTTP POST requests to Discord's webhook API.

## Features

- Send messages to Discord webhooks.
- Choose between normal and spam mode.
- Simple and user-friendly GUI.

## Requirements

- Visual Studio 2022
- vcpkg (for dependency management)
- wxWidgets (for GUI)
- libcurl (for HTTP requests)

## Installation
To compile make sure you have set the SubSystem to: Windows(/SUBSYSTEM:WINDOWS) in Configuration properties -> Linker -> System -> SubSystem

If you don't want to compile then download the ReleaseV2.zip and extract everything in the same directory. The DLLS are required for the EXE to run.

The spam mode sends 1 message in the span of 1 second. This is to avoid rate-limiting.