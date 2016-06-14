uniform float _R;
uniform float _hoff;
uniform float _freq;
uniform float _calctype;
uniform float _f;

vec4 HSVtoRGB( float h, float s, float v ){
   int i;
   float f, p, q, t;
   vec4 RGB;
   
   h = 360.0*h;
   /*if( s == 0 ) {
      // achromatic (grey)
      RGB = vec3(v,v,v);
      return RGB
   }*/
   
   h /= 60.0;         // sector 0 to 5
   i = int(floor( h ));
   f = h - i;         // factorial part of h
   p = v * ( 1.0 - s );
   q = v * ( 1.0 - s * f );
   t = v * ( 1.0 - s * ( 1.0 - f ) );
   
   switch( i ) {
      case 0:
         RGB.x = v;
         RGB.y = t;
         RGB.z = p;
         break;
      case 1:
         RGB.x = q;
         RGB.y = v;
         RGB.z = p;
         break;
      case 2:
         RGB.x = p;
         RGB.y = v;
         RGB.z = t;
         break;
      case 3:
         RGB.x = p;
         RGB.y = q;
         RGB.z = v;
         break;
      case 4:
         RGB.x = t;
         RGB.y = p;
         RGB.z = v;
         break;
      default:      // case 5:
         RGB.x = v;
         RGB.y = p;
         RGB.z = q;
         break;
   }
   
   RGB.w = 1.0;
   return RGB;
   
}

float LCM (float R, float rv){
	float i = 0;
	float cm = 1.0;

	if (mod(R,rv)==0){
		cm = 1.0;
	} else {
		i = 1;
		while(mod(R*i,rv)!=0){
			i = i + 1;
		}
		cm = i;
	}
	return cm;
}

float calcspiro(float R, float rv, float b, float a){
	float rho;
	rho = (sqrt((R-rv)*(R-rv) + b*b + 2*(R-rv)*b*cos((1+R/rv)*a)));
	return rho;
}

vec4 spirofield(float R, float rv, float b, float hoff, float freq, float calctype, float f){
	float i, theta, rho, nrev, a, rsp, ss, tt;
	float mindist, deltad, maxdist;
	float avdist = 0;
	vec4 Ch, Cg;
	vec4 Ci;

	ss = gl_TexCoord[0].s - 0.5;
	tt = gl_TexCoord[0].t - 0.5;
	theta = atan(tt,ss);
	theta += 3.1415;
	rho = 2*sqrt(ss*ss + tt*tt);
	if ((rho > ((R-rv+b)/R)) || (rho < ((R-rv-b)/R))){
		Ci = vec4(0.25,0.25,0.25,1.0);
	} else {
		nrev = LCM(R,rv);
		if (0 == calctype){
			maxdist = -2;

			for (int i = 0; i < nrev; i++){
				a = theta + i*2*3.1415;
				rsp = calcspiro(R,rv,b,a)/R;
				deltad = abs(rsp-rho);
				if (deltad > maxdist){
					maxdist = deltad;
				}
			}
			maxdist = maxdist*nrev*freq;
			maxdist = mod((maxdist+hoff),1.0);
			Ch = HSVtoRGB(maxdist,1,1);
			Cg = vec4(maxdist,maxdist,maxdist,1.0);
		} else if (1 == calctype){
			mindist = 2;
			for (int i = 0; i < nrev; i++){
				a = theta + i*2*3.1415;
				rsp = calcspiro(R,rv,b,a)/R;
				deltad = abs(rsp - rho);
				if (deltad < mindist){
					mindist = deltad;
				}
			}
			mindist = mindist * nrev * freq;
			mindist = mod((mindist + hoff), 1.0);
			Ch = HSVtoRGB(mindist,1,1);
			Cg = vec4(mindist,mindist,mindist,1.0);
		} else{
			for (int i = 0; i < nrev ; i++){
				a = theta + i*2*3.1415;
				rsp = calcspiro(R,rv,b,a)/R;
				avdist = avdist + abs(rsp - rho);
			}
			avdist = avdist * freq;
			avdist = mod((avdist + hoff), 1.0);
			Ch = HSVtoRGB(avdist,1,1);
			Cg = vec4(avdist, avdist, avdist, 1.0);
		}
		Ci = mix(Cg, Ch, f);
		return Ci;
	}
}

void main(void) {
	float rv = 5.0;
	float b = 5.0;
	gl_FragColor = spirofield(_R, rv, b, _hoff, _freq, _calctype, _f);
	//gl_FragColor = HSVtoRGB(0.0,1.0,1.0);
}