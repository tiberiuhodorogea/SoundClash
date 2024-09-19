#pragma once
enum MessageType {
	Empty,Load, Pause, Stop, Sync, Exit,Play,Resume
};
//void listAudioDevices() {
//    int count = SDL_GetNumAudioDevices(0);  // Get number of output devices
//    printf("Number of available audio devices: %d\n", count);
//
//    for (int i = 0; i < count; ++i) {
//        printf("%d: %s\n", i, SDL_GetAudioDeviceName(i, 0));
//    }
//}