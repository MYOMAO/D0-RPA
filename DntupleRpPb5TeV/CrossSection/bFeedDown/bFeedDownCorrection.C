#include <TF1.h>

// Yen-Jie: B feeddown fraction

float bFeedDownCorrection(double pt, bool isPbPb, int method=0)
{

  //method decaylength=0
  //method DCA=1
  //method FONLL=2

  double val=-1.0; // place holder
  double errval=-1.0;

  if (method==1) {   
    if (!isPbPb) { // pp
      if (pt>1&&pt<3) {
	val = 0.907438;
      } else if (pt>3&&pt<4) {
	val = 0.891066;
      } else if (pt>4&&pt<5) {
	val = 0.851007;
      } else if (pt>5&&pt<6) {
	val = 0.875401;
      } else if (pt>6&&pt<8) {
	val = 0.836946;
      } else if (pt>8&&pt<10) {
	val = 0.799743;
      } else if (pt>10&&pt<12.5) {
	val = 0.76734;
      } else if (pt>12.5&&pt<15) {
	val = 0.81736;
      } else if (pt>15&&pt<20) {
	val = 0.700143;
      } else if (pt>20&&pt<25) {
	val = 0.763407;
      } else if (pt>25&&pt<30) {
	val = 0.70424;
      } else if (pt>30&&pt<40) {
	val = 0.787326;
      } else if (pt>40&&pt<60) {
	val = 0.767477;
      } else if (pt>60&&pt<100) {
	val = 0.763097;
      }
    } 
    else{
      // PbPb
      if (pt>1&&pt<3) {
	val = 0.772;
      } else if (pt>3&&pt<4) {
	val = 0.772;
      } else if (pt>4&&pt<5) {
	val = 0.764919;
      } else if (pt>5&&pt<6) {
	val = 0.788761;
      } else if (pt>6&&pt<8) {
	val = 0.774951;
      } else if (pt>8&&pt<10) {
	val = 0.742544;
      } else if (pt>10&&pt<12.5) {
	val = 0.815646;
      } else if (pt>12.5&&pt<15) {
	val = 0.778901;
      } else if (pt>15&&pt<20) {
	val = 0.786314;
      } else if (pt>20&&pt<25) {
	val = 0.795452;
      } else if (pt>25&&pt<30) {
	val = 0.717988;
      } else if (pt>30&&pt<40) {
	val = 0.767657;
      } else if (pt>40&&pt<60) {
	val = 0.822358;
      } else if (pt>60&&pt<100) {
	val = 0.807229;
      } 
    }
  } 
  else  if (method==0) {
    if (!isPbPb) { // pp
      if (pt>1&&pt<2) {
        val = 0.626; // 10.2%
      } else if (pt>2&&pt<6) {
        val = 0.827; // 0.9%
      } else if (pt>6&&pt<10) {
        val = 0.890; // 1.7%
      }else if (pt>10&&pt<20) {
        val = 0.871; // 2.8%
      } else if (pt>20&&pt<30) {
        val = 0.848; // 2.0%
      } else if (pt>30&&pt<40) {
        val = 0.87; // 1.6%
      } else if (pt>40&&pt<=50) {
        val = 0.856; // 3.6%
      } else if (pt>50&&pt<60) {
        val = 0.781; // 3.1%
      } else if (pt>60&&pt<100) { 
        val = 0.784; // 4.3%
      }
    } 
    else{
      // PbPb
      if (pt>1&&pt<2) {
        val = 1.000;
      } else if (pt>2&&pt<6) {
        val = 0.828;
      } else if (pt>6&&pt<10) {
        val = 0.771;
      }else if (pt>10&&pt<20) {
        val = 0.803; // 1.3%
      } else if (pt>20&&pt<=50) {
        val = 0.955; // 0.8%
      } else if (pt>50&&pt<100) {
        val = 0.92; // 3.4%
      }
    }
  } 
  else  if (method==2) {
    if (!isPbPb) { // pp
      if (pt>1&&pt<2) {
        val = 0; // 10.2%
      } else if (pt>2&&pt<3) {
        val =0.911835;
      } else if (pt>3&&pt<4) {
        val =0.922662 ;
      }else if (pt>4&&pt<5) {
        val = 0.916763;
      } else if (pt>5&&pt<6) {
        val = 0.912038;
      } else if (pt>6&&pt<8) {
        val = 0.897021;
      } else if (pt>8&&pt<=10) {
        val = 0.874547;
      } else if (pt>10&&pt<12.5) {
        val = 0.851351;
      } else if (pt>12.5&&pt<15) { 
        val =0.833103;
      } else if (pt>15&&pt<20) { 
        val = 0.821424;
      } else if (pt>20&&pt<25) { 
        val =0.813101 ;
      } else if (pt>25&&pt<30) { 
        val =0.806648;
      } else if (pt>30&&pt<40) { 
        val =0.801502;
      } else if (pt>40&&pt<60) { 
        val =0.799747;
      } else if (pt>60&&pt<100) { 
        val =0.803259;
      }
    } 
    else{
      // PbPb
      if (pt>1&&pt<2) {
        val = 0; // 10.2%
      } else if (pt>2&&pt<3) {
        val =0.911835;
      } else if (pt>3&&pt<4) {
        val =0.916723 ;
      }else if (pt>4&&pt<5) {
        val = 0.908409;
      } else if (pt>5&&pt<6) {
        val = 0.907056;
      } else if (pt>6&&pt<8) {
        val = 0.89381;
      } else if (pt>8&&pt<=10) {
        val = 0.870865;
      } else if (pt>10&&pt<12.5) {
        val = 0.85806;
      } else if (pt>12.5&&pt<15) { 
        val =0.84131;
      } else if (pt>15&&pt<20) { 
        val = 0.836659;
      } else if (pt>20&&pt<25) { 
        val =0.83505 ;
      } else if (pt>25&&pt<30) { 
        val =0.83288;
      } else if (pt>30&&pt<40) { 
        val =0.829883;
      } else if (pt>40&&pt<60) { 
        val =0.826719;
      } else if (pt>60&&pt<100) { 
        val =0.829382;
      }
    }
  }



  else  if (method==30) {   
    if (!isPbPb) { // pp
      if (pt>1&&pt<3) {
	val = 0.893;
      } else if (pt>3&&pt<4) {
	val = 0.847;
      } else if (pt>4&&pt<5) {
	val = 0.842;
      } else if (pt>5&&pt<6) {
	val = 0.844;
      } else if (pt>6&&pt<8) {
	val = 0.798;
      } else if (pt>8&&pt<10) {
	val = 0.806;
      } else if (pt>10&&pt<12.5) {
	val = 0.801;
      } else if (pt>12.5&&pt<15) {
	val = 0.838;
      } else if (pt>15&&pt<20) {
	val = 0.736;
      } else if (pt>20&&pt<25) {
	val = 0.812;
      } else if (pt>25&&pt<30) {
	val = 0.782;
      } else if (pt>30&&pt<40) {
	val = 0.863;
      } else if (pt>40&&pt<60) {
	val = 0.802;
      } else if (pt>60&&pt<100) {
	val = 0.778;
      }
    } 
    else{
      if (pt>1&&pt<3) {
	val = 0.893;
      } else if (pt>3&&pt<4) {
	val = 0.847;
      } else if (pt>4&&pt<5) {
	val = 0.842;
      } else if (pt>5&&pt<6) {
	val = 0.844;
      } else if (pt>6&&pt<8) {
	val = 0.798;
      } else if (pt>8&&pt<10) {
	val = 0.806;
      } else if (pt>10&&pt<12.5) {
	val = 0.801;
      } else if (pt>12.5&&pt<15) {
	val = 0.838;
      } else if (pt>15&&pt<20) {
	val = 0.736;
      } else if (pt>20&&pt<25) {
	val = 0.812;
      } else if (pt>25&&pt<30) {
	val = 0.782;
      } else if (pt>30&&pt<40) {
	val = 0.863;
      } else if (pt>40&&pt<60) {
	val = 0.802;
      } else if (pt>60&&pt<100) {
	val = 0.778;
      }
    } 
  }


  else  if (method==31) {   
    if (!isPbPb) { // pp
      if (pt>1&&pt<3) {
	val = 0.893;
      } else if (pt>3&&pt<4) {
	val = 0.847;
      } else if (pt>4&&pt<5) {
	val = 0.842;
      } else if (pt>5&&pt<6) {
	val = 0.844;
      } else if (pt>6&&pt<8) {
	val = 0.798;
      } else if (pt>8&&pt<10) {
	val = 0.806;
      } else if (pt>10&&pt<12.5) {
	val = 0.801;
      } else if (pt>12.5&&pt<15) {
	val = 0.838;
      } else if (pt>15&&pt<20) {
	val = 0.736;
      } else if (pt>20&&pt<25) {
	val = 0.812;
      } else if (pt>25&&pt<30) {
	val = 0.782;
      } else if (pt>30&&pt<40) {
	val = 0.863;
      } else if (pt>40&&pt<60) {
	val = 0.802;
      } else if (pt>60&&pt<100) {
	val = 0.778;
      }
    } 
    else{
      // PbPb
      if (pt>1&&pt<3) {
	val = 0.915;
      } else if (pt>3&&pt<4) {
	val = 0.915;
      } else if (pt>4&&pt<5) {
	val = 0.803;
      } else if (pt>5&&pt<6) {
	val = 0.633;
      } else if (pt>6&&pt<8) {
	val = 0.545;
      } else if (pt>8&&pt<10) {
	val = 0.618;
      } else if (pt>10&&pt<12.5) {
	val = 0.773;
      } else if (pt>12.5&&pt<15) {
	val = 0.744;
      } else if (pt>15&&pt<20) {
	val = 0.741;
      } else if (pt>20&&pt<25) {
	val = 0.766;
      } else if (pt>25&&pt<30) {
	val = 0.898;
      } else if (pt>30&&pt<40) {
	val = 0.812;
      } else if (pt>40&&pt<60) {
	val = 0.894;
      } else if (pt>60&&pt<100) {
	val = 0.818;
      } 
    }
  } 



  else  if (method==40) {   
    if (!isPbPb) { // pp
      if (pt>1&&pt<3) {
	val = 0.893;
      } else if (pt>3&&pt<4) {
	val = 0.847;
      } else if (pt>4&&pt<5) {
	val = 0.842;
      } else if (pt>5&&pt<6) {
	val = 0.844;
      } else if (pt>6&&pt<8) {
	val = 0.798;
      } else if (pt>8&&pt<10) {
	val = 0.806;
      } else if (pt>10&&pt<12.5) {
	val = 0.801;
      } else if (pt>12.5&&pt<15) {
	val = 0.838;
      } else if (pt>15&&pt<20) {
	val = 0.736;
      } else if (pt>20&&pt<25) {
	val = 0.812;
      } else if (pt>25&&pt<30) {
	val = 0.782;
      } else if (pt>30&&pt<40) {
	val = 0.863;
      } else if (pt>40&&pt<60) {
	val = 0.802;
      } else if (pt>60&&pt<100) {
	val = 0.778;
      }
    } 
    else{
      // PbPb
      if (pt>1&&pt<3) {
	val = 0.898;
      } else if (pt>3&&pt<4) {
	val = 0.898;
      } else if (pt>4&&pt<5) {
	val = 0.790;
      } else if (pt>5&&pt<6) {
	val = 0.751;
      } else if (pt>6&&pt<8) {
	val = 0.771;
      } else if (pt>8&&pt<10) {
	val = 0.679;
      } else if (pt>10&&pt<12.5) {
	val = 0.762;
      } else if (pt>12.5&&pt<15) {
	val = 0.821;
      } else if (pt>15&&pt<20) {
	val = 0.778;
      } else if (pt>20&&pt<25) {
	val = 0.822;
      } else if (pt>25&&pt<30) {
	val = 0.864;
      } else if (pt>30&&pt<40) {
	val = 0.892;
      } else if (pt>40&&pt<60) {
	val = 0.862;
      } else if (pt>60&&pt<100) {
	val = 0.851;
      } 
    }
  } 



  else  if (method==41) {   
    if (!isPbPb) { // pp
      if (pt>1&&pt<3) {
	val = 0.893;
      } else if (pt>3&&pt<4) {
	val = 0.847;
      } else if (pt>4&&pt<5) {
	val = 0.842;
      } else if (pt>5&&pt<6) {
	val = 0.844;
      } else if (pt>6&&pt<8) {
	val = 0.798;
      } else if (pt>8&&pt<10) {
	val = 0.806;
      } else if (pt>10&&pt<12.5) {
	val = 0.801;
      } else if (pt>12.5&&pt<15) {
	val = 0.838;
      } else if (pt>15&&pt<20) {
	val = 0.736;
      } else if (pt>20&&pt<25) {
	val = 0.812;
      } else if (pt>25&&pt<30) {
	val = 0.782;
      } else if (pt>30&&pt<40) {
	val = 0.863;
      } else if (pt>40&&pt<60) {
	val = 0.802;
      } else if (pt>60&&pt<100) {
	val = 0.778;
      }
    } 
    else{
      // PbPb
      if (pt>1&&pt<3) {
	val = 0.915;
      } else if (pt>3&&pt<4) {
	val = 0.915;
      } else if (pt>4&&pt<5) {
	val = 0.803;
      } else if (pt>5&&pt<6) {
	val = 0.633;
      } else if (pt>6&&pt<8) {
	val = 0.545;
      } else if (pt>8&&pt<10) {
	val = 0.618;
      } else if (pt>10&&pt<12.5) {
	val = 0.773;
      } else if (pt>12.5&&pt<15) {
	val = 0.744;
      } else if (pt>15&&pt<20) {
	val = 0.741;
      } else if (pt>20&&pt<25) {
	val = 0.766;
      } else if (pt>25&&pt<30) {
	val = 0.898;
      } else if (pt>30&&pt<40) {
	val = 0.812;
      } else if (pt>40&&pt<60) {
	val = 0.894;
      } else if (pt>60&&pt<100) {
	val = 0.818;
      } 
    }
  } 



  return val;
}
