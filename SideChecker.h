#ifndef _SIDECHECKER_H_
#define _SIDECHECKER_H_


class SideChecker {
  public:
    SideChecker(const int numberOfSides);
    void init();
    int getSide();
    int getChangedSide();
    
    int whichBucket(int n);
    
  private:
    int numberOfSides;
};

#endif //_SIDECHECKER_H_
