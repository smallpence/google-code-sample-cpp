#include "videoplaylist.h"

const std::string& VideoPlaylist::VideoPlaylist::getTitle() const {
    return mTitle;
}

const std::vector<Video>& VideoPlaylist::VideoPlaylist::getVideos() const {
    return mVidoes;
}
