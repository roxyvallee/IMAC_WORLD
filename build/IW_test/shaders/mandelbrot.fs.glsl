#version 330 core

in vec2 vFragPosition;

out vec3 fFragColor;

vec2 complexSqr(vec2 z)
{
	return vec2((z.x*z.x)-(z.y*z.y), 2*z.x*z.y);
}

void main() {

  int Nmax = 40;

// u0
  vec2 z = vFragPosition;

  for(int i =0; i< Nmax; i++)
  {

  	if(length(z) >= 2)
  	{
  		fFragColor = vec3(1,1,1);
  		return;
  	}
  	if( i == 10)
  	{
  		fFragColor = vec3(float(i)/Nmax);
  		return;
  	}
// calcule terme un+1
	 z = complexSqr(z) + vFragPosition;

  }

  fFragColor = vec3(0, 0, 0);
};