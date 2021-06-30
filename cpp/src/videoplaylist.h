#pragma once

#include "video.h"

#include <string>
#include <vector>

/** A class used to represent a Playlist */

class VideoPlaylist {
 private:
  std::string mTitle;
  std::vector<Video> mVidoes;

 public:
  VideoPlaylist(const std::string& title) {
    mTitle = title;
    mVidoes = {};
  }

  // Returns the title of the video.
  const std::string& getTitle() const;

  // Returns the video id of the video.
  const std::vector<Video>& getVideos() const;
};
