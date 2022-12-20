#include <memory>
class Appearance;
typedef std::shared_ptr<Appearance> AppearancePtr;

#ifndef APPEARANCE_H
#define APPEARANCE_H

class Appearance {
public:
  virtual ~Appearance () {}
  virtual void Load () = 0;
  virtual void Unload () {};
};

#endif