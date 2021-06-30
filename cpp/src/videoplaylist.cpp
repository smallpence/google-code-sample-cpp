#include "videoplaylist.h"

const std::string& VideoPlaylist::VideoPlaylist::getTitle() const {
    return mTitle;
}

std::vector<std::string>* VideoPlaylist::VideoPlaylist::getVideos() const {
    return mVideos;    
}
