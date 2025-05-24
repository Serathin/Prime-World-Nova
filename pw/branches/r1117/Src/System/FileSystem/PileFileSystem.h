#ifndef PACKFILESYSTEM_H_INCLUDED
#define PACKFILESYSTEM_H_INCLUDED

#include "FileSystem.h"
#include "../StarForce/StarForce.h"

#include <vector>


namespace fileSystem
{

class FilePileLoader;

class PileFileSystem : public IFileSystem, public CObjectBase
{
  OBJECT_BASIC_METHODS( PileFileSystem );

public:
  PileFileSystem();
  PileFileSystem( IFileReadCallback* callback, std::vector<int>* hashes );

  virtual bool            GetFileInfo( SFileInfo *info, const string &fileName );
  virtual void            GetDirectories( vector<string> *pDirectories, const string &root );
  virtual void            GetFiles( vector<string> *pFiles, const string &root, const string & mask , bool recursive, int param = 0 );
  virtual Stream *        OpenFile( const string &fileName, EFileAccess access, EFileOpen options  );
  virtual IFileWatcher *  CreateFileWatcher( const string & path ) { return 0; }
  virtual void SetFileReadCallback( IFileReadCallback* cb ) { readCallback = cb; }

private:
  typedef list<Strong<FilePileLoader> > TPiles;
  TPiles piles;

  CObj<IFileReadCallback> readCallback;

  bool ScanForPiles();

  std::vector<int>* hashes;
};

} //namespace fileSystem

#endif //PACKFILESYSTEM_H_INCLUDED
