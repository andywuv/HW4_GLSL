varying vec2  MCposition;

uniform float moveright;
uniform float moveup;
uniform float angle;
uniform float shake_tail;
varying float sw;



//uniform float ang;
void main(void)
{

	mat4 tail;
	mat4 rotate;
	mat4 move;
	//mat4 z_rotate;


						 
	rotate =		mat4( cos(angle), sin(angle) , 0.0, 0.0,		
						  sin(angle), cos(angle),0.0, 0.0,		
						  0.0, 0.0, 1.0, 0.0,		
						  0.0, 0.0,0.0, 1.0
						 );
	tail = mat4(		1.0	, 0.0	, 0.0	, 0.0,
						  0.0	, 1.0	, 0.0, 0.0,		
						  0.0	, 0.0	, cos(shake_tail)	, sin(shake_tail),	
						  0.0	,0.0	, sin(shake_tail)	, cos(shake_tail)
						 );

	move = mat4(1.0, 0.0, 0.0, 0.0,		
				0.0, 1.0, 0.0, 0.0,		
				0.0, 0.0, 1.0, 0.0,		
				moveright, moveup, 0.0, 1.0
				);
/*
	z_rotate = mat4( 1.0	, 0.0	, 0.0	, 0.0,		
						  0.0	, 1.0	, 0.0	, 0.0,		
						  0.0				, 0.0				, cos(ang)	, sin(ang),		
						  0.0				,0.0				, sin(ang)	, cos(ang)
						 );
*/
					 
/*
move =			mat4(1.0, 0.0, 0.0, 0.0,		
					 0.0, 1.0, 0.0, 0.0,		
					 0.0, 0.0, 1.0, 0.0,		
					 0.0, 0.0, 0.0, 1.0
					 );

rotate_bytime = mat4(1.0, 0.0, 0.0, 0.0,	
					 0.0, 1.0, 0.0, 0.0,		
					 0.0, 0.0, 1.0, 0.0,		
					 0.0, 0.0, 0.0, 1.0
					 );
rotate     =	mat4(1.0, 0.0, 0.0, 0.0,	
					 0.0, 1.0, 0.0, 0.0,		
					 0.0, 0.0, 1.0, 0.0,		
					 0.0, 0.0, 0.0, 1.0
					 );
*/
    


		MCposition = gl_Vertex.xy;
		gl_TexCoord[0] =  gl_MultiTexCoord0;



		if( gl_Vertex.z == 5.0)
		{
			sw=2.0;
			gl_Position =ftransform();
		}
		else if( gl_Vertex.x == 6.0)
		{
			sw=1.0;
			gl_Position =move  *   rotate   * tail  *  gl_ModelViewProjectionMatrix  *gl_Vertex;
		}
		else if( gl_Vertex.x == 3.5||gl_Vertex.x == 2.0)
		{
			sw=4.0;
			gl_Position =move*   rotate   *   gl_ModelViewProjectionMatrix  *gl_Vertex;
		}
		else  
		{
			sw=0.0;
			gl_Position =move*   rotate    *   gl_ModelViewProjectionMatrix  *gl_Vertex;
		}

		//gl_Position = rotate_bytime		*gl_ModelViewProjectionMatrix  *gl_Vertex;

		//gl_Position =ftransform();
	
  
}