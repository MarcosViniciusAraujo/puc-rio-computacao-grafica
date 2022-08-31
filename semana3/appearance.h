#ifndef APPEARANCE_H
#define APPEARANCE_H

class Appearance {
public:
  virtual void Load () = 0;
  virtual void Unload () {}
};

#endif