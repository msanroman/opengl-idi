#ifndef _GROUND_H_
#define _GROUND_H_

class Ground
{
  double midaX, midaY, midaZ;

 public:
  Ground();

  void Init(double sx, double sz);
  void Render();
  double MidaX ();
  double MidaY ();
  double MidaZ ();
};
#endif
