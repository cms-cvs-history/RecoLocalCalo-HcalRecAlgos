#include "RecoLocalCalo/HcalRecAlgos/src/HcalTDCReco.h"
#include "DataFormats/HcalDigi/interface/HcalUpgradeDataFrame.h"
#include "DataFormats/HcalRecHit/interface/HcalUpgradeRecHit.h"

HcalTDCReco::HcalTDCReco() 
{}

void HcalTDCReco::reconstruct(const HcalUpgradeDataFrame & digi, 
                              HcalUpgradeRecHit & recHit) const
{
  int n = digi.size();
  double risingTime = -999.;
  double fallingTime = -999.;
  int signalBX = 5;
std::cout << digi << std::endl;
  for(int i=0; i < n; ++i)
  {
    unsigned tdc = digi.tdc(i);
    unsigned rising = tdc & 0x1F;
    unsigned falling = (tdc >> 5) & 0x1F;
    // only set the first time
    if(risingTime < -998. && rising != 0 && rising != 31) {
      risingTime = rising*25./32. + (i-signalBX)*25.;
std::cout << "RISING " << risingTime << " " << rising << " " << i << " " << rising*25./32. <<  
 " " << (i-signalBX)*25. << " IMUNSBS " << (i-signalBX) << " " << signalBX << std::endl;
std::cout << digi << std::endl;
    }
    if(fallingTime < -998. && falling != 0 && falling != 31) {
      fallingTime = falling*25./32. + (i-signalBX)*25.;
std::cout << "FALLING " << fallingTime << std::endl;
    }    
  }
  recHit = HcalUpgradeRecHit(recHit.id(), recHit.energy(), risingTime, fallingTime);
}
