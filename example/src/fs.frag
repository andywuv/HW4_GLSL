uniform sampler2D myTexture_wall;
uniform float moveright;
uniform float moveup;
varying float  sw;
varying vec2  MCposition;


void main (void)  
{  
   
	vec2  position;
//vec4 color_sky = texture2DProj(myTexture_sky, fTexCoord);
//vec4 color_wall = texture2DProj(myTexture_wall, fTexCoord);
	vec4 color_default = vec4(1, 1, 0, 0);
	vec4 color;
	
	

   if (color.rgb == vec3(1.0,0.0,0.0))
      discard; 


if(sw==2.0)
{
	color = vec4(1, 0.2,0.2, 1);
}
else if(sw==0.0)
{
		position = MCposition / vec2(2,2);
		if (fract(position.x*0.8) > 0.3)
		{
			position.x += 0.5;
			color.rgb = vec3(sin(moveup),cos(moveright), tan(moveright));
		}
		else	
		color.rgb = vec3(1, 1, 1);

}
else if(sw==4.0)
{
		position = MCposition / vec2(0.2,0.2);
		if (fract(position.y*0.5) > 0.5)
			color = vec4(1, 1, 1, 0);
		else
			color = vec4(1, 0, 0, 0);
			

}
else
{
		position = MCposition / vec2(0.2,0.2);
		if (fract(position.y*0.5) > 0.5)
			color = vec4(1, 1, 1, 0);
		else
			color = vec4(1, 0, 0, 0);
			

}






    
   gl_FragColor = color;

}