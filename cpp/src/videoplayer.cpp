#include "videoplayer.h"
#include "helper.h"

#include <iostream>
#include <algorithm>

using namespace std;

void VideoPlayer::numberOfVideos() {
  std::cout << mVideoLibrary.getVideos().size() << " videos in the library"
            << std::endl;
}

// function to compare title of video
bool videoComparer (Video i, Video j) {
  return i.getTitle().compare(j.getTitle()) < 0;
}

// function to print a video (with no newlines)
void printVideo(const Video &video) {
  cout << video.getTitle() << " (" << video.getVideoId() << ") [";

  auto tagIter = video.getTags().begin();
  for (; tagIter != video.getTags().end(); tagIter++)
  {
    // only prepend a space on the second++ tag
    if (tagIter != video.getTags().begin()) cout << " ";
    cout << *tagIter;
  }

  cout << "]";
}

void VideoPlayer::showAllVideos() {
  cout << "Here's a list of all available videos:" << endl;

  // get videos & sort by title
  auto sortedVideos = mVideoLibrary.getVideos();
  sort (sortedVideos.begin(), sortedVideos.end(), videoComparer);

  for (auto &video : sortedVideos) {
    cout << " ";

    printVideo(video);

    cout << endl;
  }
}

void VideoPlayer::playVideo(const string& videoId) {
  const Video *foundVideo = mVideoLibrary.getVideo(videoId);

  // if video was found
  if (foundVideo != nullptr) {
    if (currentVideo != nullptr) cout << "Stopping video: " << currentVideo->getTitle() << endl;
    cout << "Playing video: " << foundVideo->getTitle() << endl;
    currentVideo = foundVideo; // store in memory
    paused = false; // assert non paused
  }
  else cout << "Cannot play video: Video does not exist" << endl;
}

void VideoPlayer::stopVideo() {
  if (currentVideo != nullptr) {
    cout << "Stopping video: " << currentVideo->getTitle() << endl;
    currentVideo = nullptr;
  }
  else cout << "Cannot stop video: No video is currently playing" << endl;
}

void VideoPlayer::playRandomVideo() {
  unsigned long i = rand(); 
  Video randomVideo = mVideoLibrary.getVideos()[i % mVideoLibrary.getVideos().size()];
  playVideo(randomVideo.getVideoId());
}

void VideoPlayer::pauseVideo() {
  // if theres a video playing
  if (currentVideo != nullptr) {
    if (!paused) {
      cout << "Pausing video: " << currentVideo->getTitle() << endl;
      paused = true;
    }
    else cout << "Video already paused: " << currentVideo->getTitle() << endl;
  }
  else cout << "Cannot pause video: No video is currently playing" << endl;
}

void VideoPlayer::continueVideo() {
  // if theres a video playing
  if (currentVideo != nullptr) {
    if (paused) {
      cout << "Continuing video: " << currentVideo->getTitle() << endl;
      paused = false;
    }
    else cout << "Cannot continue video: Video is not paused" << endl;
  }
  else cout << "Cannot continue video: No video is currently playing" << endl;
}

void VideoPlayer::showPlaying() {
  if (currentVideo != nullptr) {
    cout << "Currently playing: ";

    printVideo(*currentVideo);

    if (paused) cout << " - PAUSED";

    cout << endl;
  }
  else cout << "No video is currently playing" << endl;
}

void VideoPlayer::createPlaylist(const std::string& playlistName) {
  // if none stored with this name
  if (playlists.count(strToLower(playlistName)) == 0) {
    // place in slot designated by lower case name (to make non caps sensitive)
    // but also store the original name with the playlist
    playlists.insert({strToLower(playlistName), VideoPlaylist(playlistName)});
    
    cout << "Successfully created new playlist: " << playlistName << endl;
  }
  else cout << "Cannot create playlist: A playlist with the same name already exists" << endl;
}

void VideoPlayer::addVideoToPlaylist(const std::string& playlistName,
                                     const std::string& videoId) {
  std::cout << "addVideoToPlaylist needs implementation" << std::endl;
}

void VideoPlayer::showAllPlaylists() {
  std::cout << "showAllPlaylists needs implementation" << std::endl;
}

void VideoPlayer::showPlaylist(const std::string& playlistName) {
  std::cout << "showPlaylist needs implementation" << std::endl;
}

void VideoPlayer::removeFromPlaylist(const std::string& playlistName,
                                     const std::string& videoId) {
  std::cout << "removeFromPlaylist needs implementation" << std::endl;
}

void VideoPlayer::clearPlaylist(const std::string& playlistName) {
  std::cout << "clearPlaylist needs implementation" << std::endl;
}

void VideoPlayer::deletePlaylist(const std::string& playlistName) {
  std::cout << "deletePlaylist needs implementation" << std::endl;
}

void VideoPlayer::searchVideos(const std::string& searchTerm) {
  std::cout << "searchVideos needs implementation" << std::endl;
}

void VideoPlayer::searchVideosWithTag(const std::string& videoTag) {
  std::cout << "searchVideosWithTag needs implementation" << std::endl;
}

void VideoPlayer::flagVideo(const std::string& videoId) {
  std::cout << "flagVideo needs implementation" << std::endl;
}

void VideoPlayer::flagVideo(const std::string& videoId, const std::string& reason) {
  std::cout << "flagVideo needs implementation" << std::endl;
}

void VideoPlayer::allowVideo(const std::string& videoId) {
  std::cout << "allowVideo needs implementation" << std::endl;
}
