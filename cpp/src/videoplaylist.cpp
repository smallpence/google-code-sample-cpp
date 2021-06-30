#include "videoplaylist.h"

const std::string& VideoPlaylist::VideoPlaylist::getTitle() const {
    return mTitle;
}

std::unordered_set<std::string>* VideoPlaylist::VideoPlaylist::getVideos() const {
    return mVidoes;
}
