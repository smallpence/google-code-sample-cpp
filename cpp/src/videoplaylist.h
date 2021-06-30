#pragma once

#include "video.h"

#include <string>
#include <vector>

/** A class used to represent a Playlist */

class VideoPlaylist {
 private:
  const std::string mTitle;
  std::vector<std::string> *mVideos;

 public:
  VideoPlaylist(const std::string& title, std::vector<std::string> *v) :
    mTitle(title), mVideos(v) {}

  // Returns the original name of the playlist
  const std::string& getTitle() const;

  // Returns a vector of video ids
  std::vector<std::string>* getVideos() const;
};
