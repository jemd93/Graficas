#define textureWidth 600.0
#define textureHeight 800.0	
#define texel_size_x 1.0 / textureWidth
#define texel_size_y 1.0 / textureHeight

uniform sampler2D stexflat;
uniform sampler2D stexcent;
uniform sampler2D stexder;
uniform sampler2D stexizq;
//uniform float _mixI;
//uniform float _mixLuces;

vec4 texture2D_bilinear( sampler2D tex, vec2 uv )
{
	vec2 f;

	f.x	= fract( uv.x * textureWidth );
	f.y	= fract( uv.y * textureHeight );

	vec4 t00 = texture2D( tex, uv + vec2( 0.0, 0.0 ));
	vec4 t10 = texture2D( tex, uv + vec2( texel_size_x, 0.0 ));
	vec4 tA = mix( t00, t10, f.x);

	vec4 t01 = texture2D( tex, uv + vec2( 0.0, texel_size_y ) );
	vec4 t11 = texture2D( tex, uv + vec2( texel_size_x, texel_size_y ) );
	vec4 tB = mix( t01, t11, f.x );

	return mix( tA, tB, f.y );
}

void main(void) {

	vec4 cFinal;
	vec4 cFinal01;
	vec4 cFinal02;
	vec4 cFinal03;
	vec4 cT01;
	vec4 cT02;
	vec4 cT03;
	vec4 cT04;

	vec4 t1;
	vec4 t2;
	vec4 t3;

	cT01 = texture2D(stexflat,gl_TexCoord[0].st);
	cT02 = texture2D(stexcent,gl_TexCoord[0].st);

	cT03 = texture2D(stexder,gl_TexCoord[0].st);
	cT04 = texture2D(stexizq,gl_TexCoord[0].st);

	// Blendea la luz der y luz izq.
	cFinal01 =  mix(cT04,cT03, max(0.5,0.0)); // Los valores de los mix en max(valor,0.0) ese valor va en una variable. Estoy probando nada mas.
	// Blendea el blend anterior con la luz del medio.
	cFinal02 =  mix(cFinal01, cT02,max(1.0,0.0));  // El valor es entre 0 y 1. Por lo que entiendo es cuanto de cada textura es usado.
												   // 0.5 es 50/50 
	// Blendea el blend anterior con el paisaje.
	cFinal = mix(cFinal02,cT01,cFinal02.xyzw);
	gl_FragColor = cFinal;
}