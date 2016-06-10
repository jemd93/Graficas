#define textureWidth 2048
#define textureHeight 2048
#define texel_size_x 1.0 / textureWidth
#define texel_size_y 1.0 / textureHeight

// Texturas
uniform sampler2D stexflat;
uniform sampler2D stexcent;
uniform sampler2D stexder;
uniform sampler2D stexizq;
uniform sampler2D stexpiso;

// Intensidad de las luces
uniform float _intensidadAmb;
uniform float _intensidadCent;
uniform float _intensidadDer;
uniform float _intensidadIzq;

// Color del piso
uniform vec4 _colorPiso;
uniform int _pisoCambiado;

// Color de las luces
uniform vec4 _colorAmb;
uniform vec4 _colorCent;
uniform vec4 _colorDer;
uniform vec4 _colorIzq;

// Filtro bilineal
uniform int _filtActivo;

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
	vec4 Amb, Cent, Der, Izq, Piso;
	vec4 cT01, cT02, cT03, cT04, cT05;

	if (_filtActivo == 0){
		cT01 = texture2D(stexflat,gl_TexCoord[0].st);
		cT02 = texture2D(stexcent,gl_TexCoord[0].st);
		cT03 = texture2D(stexder,gl_TexCoord[0].st);
		cT04 = texture2D(stexizq,gl_TexCoord[0].st);
		cT05 = texture2D(stexpiso,gl_TexCoord[0].st);

	} else {
		cT01 = texture2D_bilinear(stexflat,gl_TexCoord[0].st);
		cT02 = texture2D_bilinear(stexcent,gl_TexCoord[0].st);
		cT03 = texture2D_bilinear(stexder,gl_TexCoord[0].st);
		cT04 = texture2D_bilinear(stexizq,gl_TexCoord[0].st);
		cT05 = texture2D_bilinear(stexpiso,gl_TexCoord[0].st);
	}

	if (_pisoCambiado == 1){
		Piso = mix(cT01,_colorPiso,cT05);
	} else {
		Piso = cT01;
	}
	Amb =  Piso*_intensidadAmb*_colorAmb;
	Cent = cT02*_intensidadCent*_colorCent;
	Der = cT03*_intensidadDer*_colorDer;
	Izq = cT04*_intensidadIzq*_colorIzq;

	cFinal = Amb * (Cent + Der + Izq);
	gl_FragColor = cFinal;
}