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
    playlists.insert({strToLower(playlistName), VideoPlaylist(playlistName, new vector<string>())});
    
    cout << "Successfully created new playlist: " << playlistName << endl;
  }
  else cout << "Cannot create playlist: A playlist with the same name already exists" << endl;
}

void VideoPlayer::addVideoToPlaylist(const std::string& playlistName,
                                     const std::string& videoId) {
  string playlistNameLower = strToLower(playlistName);
  // if playlist exists
  if (playlists.count(playlistNameLower) > 0) {
    const Video *foundVideo = mVideoLibrary.getVideo(videoId);

    // if could find a video
    if (foundVideo != nullptr) {
      vector<string>* videoIds = playlists.at(playlistNameLower).getVideos();

      // if playlist doesnt contain video
      if (find(videoIds->begin(), videoIds->end(), videoId) == videoIds->end()) {
        videoIds->insert(videoIds->end(), videoId);
        cout << "Added video to " << playlistName << ": " << foundVideo->getTitle() << endl;
      }
      else cout << "Cannot add video to " << playlistName << ": " << "Video already added" << endl;
    }
    else cout << "Cannot add video to " << playlistName << ": " << "Video does not exist" << endl;
  }
  else cout << "Cannot add video to " << playlistName << ": " << "Playlist does not exist" << endl;
}

void VideoPlayer::showAllPlaylists() {
  // if there are playlists
  if (playlists.size() > 0) {
    cout << "Showing all playlists:" << endl;
    for (auto pair : playlists) {
      cout << pair.second.getTitle() << endl;
    }
  }
  else cout << "No playlists exist yet" << endl;
}

void VideoPlayer::showPlaylist(const std::string& playlistName) {
  string playlistNameLower = strToLower(playlistName);

  // if playlist exists
  if (playlists.count(playlistNameLower) > 0) {
    cout << "Showing playlist: " << playlistName << endl;

    // display message if empty
    if (playlists.at(playlistNameLower).getVideos()->size() == 0)
      cout << "  No videos here yet" << endl;

    for (auto videoID : *playlists.at(playlistNameLower).getVideos()) {
      cout << "  ";
      
      printVideo(*mVideoLibrary.getVideo(videoID));

      cout << endl;
    }
  }
  else cout << "Cannot show playlist " << playlistName << ": Playlist does not exist" << endl;
}

void VideoPlayer::removeFromPlaylist(const std::string& playlistName,
                                     const std::string& videoId) {
  string playlistNameLower = strToLower(playlistName);
  // if playlist exists
  if (playlists.count(playlistNameLower) > 0) {
    const Video *foundVideo = mVideoLibrary.getVideo(videoId);

    // if could find a video
    if (foundVideo != nullptr) {
      vector<string>* videoIds = playlists.at(playlistNameLower).getVideos();
      
      // if playlist contains video
      if (find(videoIds->begin(), videoIds->end(), videoId) != videoIds->end()) {
        videoIds->erase(remove(videoIds->begin(), videoIds->end(), videoId), videoIds->end());
        cout << "Removed video from " << playlistName << ": " << foundVideo->getTitle() << endl;
      }
      else cout << "Cannot remove video from " << playlistName << ": " << "Video is not in playlist" << endl;
    }
    else cout << "Cannot remove video from " << playlistName << ": " << "Video does not exist" << endl;
  }
  else cout << "Cannot remove video from " << playlistName << ": " << "Playlist does not exist" << endl;
}

void VideoPlayer::clearPlaylist(const std::string& playlistName) {
  string playlistNameLower = strToLower(playlistName);

  // if playlist exists
  if (playlists.count(playlistNameLower) > 0) {
    VideoPlaylist foundPlaylist = playlists.at(playlistNameLower);

    foundPlaylist.getVideos()->clear();
    cout << "Successfully removed all videos from " << foundPlaylist.getTitle() << endl;
  }
  else cout << "Cannot clear playlist " << playlistName << ": Playlist does not exist" << endl;
}

void VideoPlayer::deletePlaylist(const std::string& playlistName) {
  string playlistNameLower = strToLower(playlistName);

  // if playlist exists
  if (playlists.count(playlistNameLower) > 0) {
    playlists.erase(playlistNameLower);
    cout << "Deleted playlist: " << playlistName << endl;
  }
  else cout << "Cannot delete playlist " << playlistName << ": Playlist does not exist" << endl;
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
