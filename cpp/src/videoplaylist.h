#pragma once

#include "video.h"

#include <string>
#include <vector>
#include <unordered_set>

/** A class used to represent a Playlist */

class VideoPlaylist {
 private:
  std::string mTitle;
  std::unordered_set<std::string> *mVidoes;

 public:
  VideoPlaylist(const std::string& title) {
    mTitle = title;
    mVidoes = new std::unordered_set<std::string>;
  }

  // Returns the title of the video.
  const std::string& getTitle() const;

  // Returns the video id of the video.
  std::unordered_set<std::string>* getVideos() const;
};
